#include "semantic.h" 

FieldList hashTable[HASH_SIZE];
int scope_id = 0;
int current_id = 0;
scope sc_table[50];



//散列函数
//代码第7行的常数（0x3fff）确定了符号表的大小（即16384）
unsigned int hash_func(char *type){
	unsigned int val = 0, i;
	for(;*type;++type){
		val = (val << 2) + *type;
		if(i=val & ~0x3fff){
			val = (val ^ (i>>12)) & 0x3fff;
		}
		return val % HASH_SIZE;
	}
}

void initHashtable(){
	for(int i=0; i<HASH_SIZE; i++){
		hashTable[i] = NULL;
	}
    scope sc;
    sc.id = 0;
    sc.parent_id = -1;//表示自己是最外层的
    sc.w[0] = 0;
    sc.wno =1;
    current_id = 0;
    sc_table[current_id] = sc;//注意！给表加上别漏了
}

void check_declar()
{
    for(int i=0;i<HASH_SIZE;i++)
    {
		if(hashTable[i]!=NULL)
        {
            FieldList temp =hashTable[i];
            if(temp->type->kind == FUNCTION)
            {
                if(temp->type->u.function.state == DECLA)
                {
                    printf("Error type 18 at Line %d: Undefined function %s.\n",temp->type->u.function.lineno,temp->type);
                }
            }
        }
    }
}

void enter_scope()
{
    scope_id++;  //2
    scope sc;
    sc.id = scope_id; //sc.id = 2
    sc.parent_id = current_id;//sc.parent_id = 0
    current_id = scope_id;     // current_id = 2 
    sc.wno = sc_table[sc.parent_id].wno + 1; //sc.wno = sc_table[0].wno +1
    for(int i=0;i<sc.wno-1;i++)
    {
        sc.w[i] = sc_table[sc.parent_id].w[i];
    }
    sc.w[sc.wno-1] = sc.id; 

    sc_table[current_id] = sc;//注意！给表加上别漏了

}

void exit_scope()
{
    scope sc = sc_table[current_id];
    if(current_id == 0 ) {printf("scope error");}//debug
    current_id = sc.parent_id;
}

int insert(FieldList f)
{
	if(f==NULL || f->name == NULL)
		return 0;
    //if(f->scope_id != current_id) printf("debugdebug\n");//当前语句块
	unsigned int key;
    //printf("d:%s\n",f->name);
	key = hash_func(f->name);
    //如果是函数 要注意原先存的如果是声明的要覆盖掉 当然,函数都在最外层定义故不用考虑语句块
    if(f->type->kind != FUNCTION)
    {
        //printf("debug");
        while(1)
        {
            if(hashTable[key] == NULL)
            {
                hashTable[key] = f;
                return 1;
            }
            key = (++key)%HASH_SIZE;
        }
    }
    else
    {
        while(1)
        {
            if(hashTable[key] == NULL)
            {
                hashTable[key] = f;
                return 1;
            }
            if(strcmp(hashTable[key]->name,f->name)==0)
            {
                    //printf("debug");
                    //这里判断除了DEFIN 其他其实是多余的
                if(TypeEqual(hashTable[key]->type,f->type)==1  
                    && hashTable[key]->type->u.function.state == DECLA
                    && f->type->u.function.state == DEFIN)
                {
                    hashTable[key] = f;
                    return 1;
                }   
            }
            key = (++key)%HASH_SIZE;
        }

    }
	return 0;
}

FieldList search(char *name
,int flag// flag=1:function flag =2: str_spe flag=0:变量 原因在于函数名和变量名可以一样
)
{
	if(name == NULL){
		return NULL;
	}
	unsigned int key;
    key = hash_func(name);
	FieldList p=hashTable[key];
	while(p!=NULL)
    {
		if(strcmp(name,p->name)==0)
        {
            scope sc = sc_table[current_id];
            //printf("debug p:%d current:%d wno:%d\n",p->scope_id,current_id,sc.wno);
            //从内层往外层找
            for(int i=sc.wno-1;i>=0;i--)
            {
                //printf("%d\n",sc.w[i]);
                if(p->scope_id == sc.w[i])
                {
                    //printf("name: %s flag: %d kind:%d\n",p->name,flag,p->name->kind);
                    //printSymbol();
                    //todo:array
                    if(flag != 2 && p->type->kind == STR_SPE)
                    {
                       // printf("debug\n");
                        return NULL;//与结构类型重名是不行的
                    }
                    // if(flag == 1 && p->name->kind == FUNCTION)
                    // return p;
                    // if(flag == 0 && p->name->kind == BASIC)
                    return p;

                }
            }
		}
		key=(++key)%HASH_SIZE;
		p=hashTable[key];
	}
	return NULL;
}

FieldList ifexist(char *name,int id)
{
	if(name == NULL){
		return NULL;
	}
	unsigned int key;
    key = hash_func(name);
	FieldList p=hashTable[key];
	while(p!=NULL)
    {
		if(strcmp(name,p->name)==0)
        {
           // printf("debug name:%s p:%d id:%d\n",name,p->scope_id,id);
            if(p->scope_id == id || p->type->kind == STR_SPE)//与结构类型重名不行
            {
                return p;
            }
		}
		key=(++key)%HASH_SIZE;
		p=hashTable[key];
	}
	return NULL;
}


void printSymbol(){
    printf("-------------\n");
	for(int i=0;i<HASH_SIZE;i++)
    {
		if(hashTable[i]!=NULL)printf("%d %s\n",hashTable[i]->type->kind,hashTable[i]->type);
    }
    printf("-------------\n");

}

int TypeEqual(Type t1,Type t2){
    //printf("kind:%d %d\n",t1->kind,t2->kind);
    //printf("debug");
    //if(t1 == NULL) printf("1\n");
    //if(t1 == NULL) printf("2\n");
    //if(t1 == NULL && t2 == NULL) return 1;
	if((t1==NULL)||(t2==NULL)) return 0;
	if(t1->kind!=t2->kind) return 0;
    if(t1->kind == BASIC)
    {
        //printf("basic:%d %d\n",t1->u.basic,t2->u.basic);
        return (t1->u.basic == t2->u.basic);
    }
    if(t1->kind == ARRAY)
    {
        return (TypeEqual(t1->u.array.elem,t2->u.array.elem));
    }
    if(t1->kind == STRUCTURE || t1->kind == STR_SPE)
    {
        //针对结构体中的每个域逐个进行类型比较
        FieldList f1 = t1->u.structure;
        FieldList f2 = t2->u.structure;
        //两个都为NULL?
        if(f1 == NULL && f2 == NULL) return 1;
        if(f1 == NULL || f2 == NULL) return 0;
        while(f1 != NULL)
        {
            if(f2 == NULL) return 0;
            if(TypeEqual(f1->type,f2->type) == 0) return 0;
            f1 = f1->tail;
            f2 = f2->tail;
        }
        if(f1 == NULL && f2 == NULL) return 1;
        
    }
    if(t1 ->kind ==FUNCTION)
    {
        
        //参数类型和个数相等
        if(t1->u.function.paramNum != t2->u.function.paramNum) return 0;
        //printf("kind:%d %d\n",t1->u.function.funcType->kind,t2->u.function.funcType->kind);
        if(TypeEqual(t1->u.function.funcType,t2->u.function.funcType) == 0) return 0;

        FieldList p1 = t1->u.function.params;
        FieldList p2 = t2->u.function.params;
        for(int i = 0; i<t1->u.function.paramNum;i++)
        {
            if(TypeEqual(p1->type,p2->type) == 0) return 0;
            p1 = p1->tail; p2 = p2->tail;
        }
        return 1;
    }
    printf("debug\n");
    return 0;
}

//Program     : ExtDefList
void Program(ast_node *root){
    if(root==NULL)
        return;
    if(!strcmp("ExtDefList" , root->children[0]->type))
    {
        ExtDefList(root ->children[0]);
    }
}


// ExtDefList  : ExtDef ExtDefList  
//             |  /* empty */       
//             ;
void ExtDefList(ast_node *node)
{
    if(node == NULL )return;
    if(node->child_count ==2)
    {
        ExtDef(node->children[0]);
        ExtDefList(node->children[1]);  
    }
}


// ExtDef      : Specifier ExtDecList SEMI  
//             | Specifier SEMI             
//             | Specifier FunDec CompSt   
//             | Specifier FunDec SEMI  
void ExtDef(ast_node *node)
{
    //函数返回值类型
    Type specifier = Specifier(node->children[0]);

    //Specifier ExtDecList SEMI  
    if(strcmp(node->children[1]->type,"ExtDecList") == 0)
    {
        ExtDecList(node->children[1],specifier);
    }
    //Specifier SEMI   不用管
    else if(strcmp(node->children[1]->type,"FunDec") == 0) 
    //Specifier FunDec CompSt 
    //Specifier FunDec SEMI  
    //FunDec是函数头，CompSt表示函数体
    {
        enter_scope();
        if(strcmp(node->children[2]->type,"CompSt")==0)//定义
        {
            //printf("22");
            FunDec(node->children[1],specifier,DEFIN);
            CompSt(node->children[2],specifier);
        }
        else
        {
            //printf("11");
        FunDec(node->children[1],specifier,DECLA);
        }
        exit_scope();
    }
}       

// FunDec      : ID LP VarList RP             
//             | ID LP RP                             
//             ;
void FunDec(ast_node *node,Type spec,int state)
{
    //ID
    FieldList field = (FieldList)malloc(sizeof(FieldList_));
    field->name = node->children[0]->type;
    //注意函数名和后面的不在一个作用域
    field->scope_id = sc_table[current_id].parent_id;
    //要用sizeof(Type_)而不是Type
    Type type = (Type)malloc(sizeof(Type_));
    type->kind = FUNCTION;
    type->u.function.lineno = node->linenumber;
    type->u.function.funcType = spec;
    //             | ID LP RP                 
    //printf("%d",type->u.function.paramNum);
    type->u.function.paramNum = 0;
    type->u.function.params = NULL;
    type->u.function.state = state;
    //ID LP VarList RP 
    if(strcmp(node->children[2]->type,"VarList")==0)
    {
        
        //填充type
    //    VarList     : ParamDec COMMA VarList 
                //    | ParamDec                    
                //    ;
        ast_node * varList = node->children[2];
        while(1)
        {
            // ParamDec    : Specifier VarDec
            ast_node * paramDec =varList->children[0];
            Type t = Specifier(paramDec->children[0]);
            FieldList p =VarDec(paramDec->children[1],t);
            //查看是否重复定义 函数内部
            if (ifexist(p->name,p->scope_id) != NULL)
                printf("Error type 3 at Line %d: Redefined variable %s.\n", varList->linenumber, p->name);
            else
                insert(p);
            type->u.function.paramNum++;
            //头插入
            p->tail = type->u.function.params;
            type->u.function.params = p;

            if(varList->child_count == 3)
            {
                varList=varList->children[2];
            }
            else
            {
                break;
            }
        }
        
    }
    //将函数加入
    field->type = type;
    FieldList temp =ifexist(field->name,field->scope_id) ;
    if(temp !=NULL)
    {
        if(temp->type->u.function.state == DEFIN && field->type->u.function.state == DEFIN)//看函数是否被重复定义
            printf("Error type 4 at Line %d: Redefined function %s.\n", node->linenumber, temp->type);
        else if(TypeEqual(temp->type,field->type) == 0)//类型是否一致
            printf("Error type 19 at Line %d: Inconsistent declaration of function %s.\n", node->linenumber, temp->type);
        else if(field->type->u.function.state == DEFIN)//注意了 只有自己是定义 其他是声明才用insert 声明不能覆盖掉定义
            insert(field);
    }
    else
    insert(field);
}

// CompSt      : LC DefList StmtList RC                   
//             ;
void CompSt(ast_node *node,Type ftype)
{
    enter_scope();
    DefList(node->children[1]);
    ////
    ast_node * stmtlist =node->children[2];
    // StmtList    : Stmt StmtList               
    //         | /* empty */                   
    //         ;
    while(stmtlist!=NULL)
    {
        Stmt(stmtlist->children[0],ftype);
        stmtlist = stmtlist->children[1];
    }
    exit_scope();
}

// Stmt    : Exp SEMI                                
//         | CompSt                                  
//         | RETURN Exp SEMI                         
//         | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE 
//         | IF LP Exp RP Stmt ELSE Stmt                        
//         | WHILE LP Exp RP Stmt                    
//         ;   
//语句  传进来ftype是因为返回值
void Stmt(ast_node *node,Type ftype)
{
    if (strcmp(node->children[0]->type, "CompSt") == 0)
    {
        CompSt(node->children[0],ftype);
    }
    else if (strcmp(node->children[0]->type, "Exp") == 0)
    {//Exp SEMI 
        Exp(node->children[0]);
    }
    else if (strcmp(node->children[0]->type, "RETURN") == 0)
    {
        Type rtype = Exp(node->children[1]);
        if(TypeEqual(ftype,rtype)== 0)
        {
            if(rtype !=NULL)//可能有问题
            printf("Error type 8 at Line %d: Type mismatched for return.\n", node->linenumber);
        }
    }
    else
    //仅有int型变量才能进行逻辑运算或者作为if和while语句的条件；
    {
        //WHILE LP Exp RP Stmt 
        //IF LP Exp RP Stmt
        Exp(node->children[2]);
        Stmt(node->children[4],ftype);
        //IF LP Exp RP Stmt ELSE Stmt 
        if(node->child_count ==7)
        Stmt(node->children[6],ftype);
    }
    
}


// DefList : Def DefList             
//         | /* empty */              
//         ;
// 每个Def就是一条变量定义
void DefList(ast_node *node)
{
    if(node !=NULL)
    {
        Def(node->children[0]);
        DefList(node->children[1]);
    }
}

// Def     : Specifier DecList SEMI
//         ;
void Def(ast_node *node)
{
    Type spec = Specifier(node->children[0]);
    DecList(node->children[1],spec);
}

// DecList : Dec                 
//         | Dec COMMA DecList        
//         ;
void DecList(ast_node *node,Type spec)
{
    if(node !=NULL)
    {
        Dec(node->children[0],spec);
        if(node->child_count == 3)
        {
            DecList(node->children[2],spec);
        }
    }
}

// Dec     : VarDec               
//         | VarDec ASSIGNOP Exp  a = 5
//         ;
void Dec(ast_node *node,Type spec)
{
    if(node == NULL) return;
    FieldList field = VarDec(node->children[0],spec);
    if(node->child_count == 3)
    {
        // 如果在struct内部 则要报错 但我这里分开了
        // 故而必然不在struct内部
        // 考虑类型匹配
        // 这里的类型匹配考虑的是初始化的时候

        Type right = Exp(node->children[2]);
        if(TypeEqual(field->type,right) == 0)
        {
			printf("Error type 5 at Line %d: mismatch in assignment.\n",node->linenumber);
        }
    }
    if(ifexist(field->name,field->scope_id)!=NULL)
    {
        //函数内部
        printf("Error type 3 at Line %d: Redefined variable %s.\n", node->linenumber, field->type);
    }
    else
    insert(field);
}


// Exp     : Exp ASSIGNOP Exp  a = 5
//         | Exp AND Exp       a&b
//         | Exp OR Exp        a|b
//         | Exp RELOP Exp     a>b
//         | Exp PLUS Exp      a+b
//         | Exp MINUS Exp     a-b
//         | Exp STAR Exp      a*b
//         | Exp DIV Exp       a/b
//         | LP Exp RP         (a)
//         | MINUS Exp         -a
//         | NOT Exp           ~a

//         | ID LP Args RP     a(b)
//         | ID LP RP          a()
//         | Exp LB Exp RB     a[b]  左值
//         | Exp DOT ID        a.b   左值
//         | ID                a     左值
//         | INT               1
//         | FLOAT             1.0
//         ;
Type Exp(ast_node *node)
{
    if(node == NULL) return NULL;
    if (node->child_count ==3 && strcmp(node->children[1]->type, "ASSIGNOP") == 0)
    {   
        ast_node * exp1 = node->children[0];
        ast_node * exp2 = node->children[2];
        //赋值号左边出现一个只有右值的表达式。
        //ID | Exp DOT ID  |  Exp LB Exp RB
        if(exp1->child_count == 1 && !(strcmp(exp1->children[0]->type, "ID") == 0) )
        {
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->linenumber);
        }
        if(exp1->child_count == 3 && !(strcmp(exp1->children[1]->type, "DOT") == 0) )
        {
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->linenumber);
        }
        if(exp1->child_count == 4 && !(strcmp(exp1->children[1]->type, "LB") == 0) )
        {
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a right variable.\n", exp1->linenumber);
        }
        //赋值号两边的表达式类型不匹配。
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if(TypeEqual(t1,t2) == 0)
        {
            //printf("debug:%d  t1:%d t2:%d\n",exp1->linenumber,t1->kind,t2->kind);
            //if(t2 == NULL) printf("2\n");
            //防止重复报错
            if(t1!=NULL && t2!=NULL)
			printf("Error type 5 at Line %d: mismatch in assignment\n",node->linenumber);
            return NULL;
        }
        else 
        return t1;
    }
    //Exp AND|OR|RELOP Exp
    if (node->child_count ==3 &&
       ( strcmp(node->children[1]->type, "AND") == 0 | strcmp(node->children[1]->type, "OR") == 0 
       |strcmp(node->children[1]->type, "RELOP") == 0 ))
    {
// 操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变
// 量相加减，或数组（或结构体）变量与数组（或结构体）变量相加减）。
        ast_node * exp1 = node->children[0];
        ast_node * exp2 = node->children[2];
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if(TypeEqual(t1,t2) == 0)
        {
            if(t1!=NULL) //todo:可能有问题
			printf("Error type 7 at Line %d: mismatch in operands\n",node->linenumber);
            return NULL;
        }
        else 
        {
            Type t = (Type)malloc(sizeof(Type_));
            t ->kind =BASIC;
            t->u.basic=INT_TYPE;
            return t;
        }
    }
    // +-*/
    if (node->child_count ==3 &&(
(strcmp(node->children[1]->type, "PLUS") == 0) || (strcmp(node->children[1]->type, "MINUS") == 0) || (strcmp(node->children[1]->type, "STAR") == 0) || (strcmp(node->children[1]->type, "DIV") == 0))
    )
    {
        ast_node * exp1 = node->children[0];
        ast_node * exp2 = node->children[2];
        Type t1 = Exp(exp1);
        Type t2 = Exp(exp2);
        if (TypeEqual(t1, t2) == 0)
        {
            printf("Error type 7 at Line %d: mismatch in operands.\n", node->linenumber);
            return NULL;
        }
        else
            return t1;
    }
    //         | LP Exp RP         (a)
    //         | MINUS Exp         -a
    //         | NOT Exp           ~a
    if ((strcmp(node->children[0]->type, "LP") == 0) || (strcmp(node->children[0]->type, "MINUS") == 0) || (strcmp(node->children[0]->type, "NOT") == 0) )
    {
        ast_node * exp1 = node->children[1];
        Type t1 = Exp(exp1);
        return t1;
    }

//         | ID                a     左值
//         | INT               1
//         | FLOAT             1.0
    if(node->child_count == 1 && (strcmp(node->children[0]->type, "ID") == 0) )
    {//ID
    //找变量
        FieldList field = search(node->children[0]->type,0);
        if(field == NULL)
        {
            printf("Error type 1 at Line %d: Undefined variable %s.\n",node->linenumber, node->children[0]->type);
            return NULL;
        }
        return field->type;
    }
    if(strcmp(node->children[0]->type, "INT") == 0)
    {
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = INT_TYPE;
        return t;
    }
    if(strcmp(node->children[0]->type, "FLOAT") == 0)
    {
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = FLOAT_TYPE;
        return t;
    }


    if(strcmp(node->children[0]->type, "ID") == 0)
    {
//         | ID LP Args RP     a(b)
//         | ID LP RP          a()
        //找函数名
        FieldList field = search(node->children[0]->type,1);
        //printf("debug:%d",node->children[0]->linenumber);
        //todo:解决函数与变量同名问题
        if(field == NULL)
        {
            printf("Error type 2 at Line %d: Undefined function %s.\n", node->linenumber, node->children[0]->type);
            return NULL;
        }
        if(field->type->kind!= FUNCTION)
        {
            printf("Error type 11 at Line %d: %s is not a function.\n", node->children[0]->linenumber, field->type);
            return NULL;
        }
        Type rtype = field->type;
        
        //printf("%d",rtype->u.function.funcType->kind);
        
        //类型9 实参与形参匹配
        Type t = (Type)malloc(sizeof(Type_));
        t->kind = FUNCTION;
        t->u.function.paramNum =0;
        t->u.function.params = NULL;
        if(strcmp(node->children[2]->type, "Args") == 0)
        {
        //     Args    : Exp COMMA Args  
                    // | Exp             
                    // ;
            //填充type 跟前面struct类似
            ast_node * args = node->children[2];
            while(1)
            {
                Type p = Exp(args->children[0]);
                FieldList fp = (FieldList)malloc(sizeof(FieldList_));
                fp->scope_id = current_id;

                //todo:名字应该在Exp内 但是不重要 只需检查type
                //fp->type = args->children[0]->children[0]->type;
                fp->name = "temp";
                fp->type = p;
                t->u.function.paramNum++;
                fp->tail = t->u.function.params;
                t->u.function.params = fp;

                if(args->child_count == 3)
                {
                    args= args->children[2];
                }
                else
                {
                    break;
                }
            }
        }
       // printf("t:%d num:%d r:%d num:%d\n",t->kind,t->u.function.paramNum,rtype->kind,rtype->u.function.paramNum);
        t->u.function.funcType= rtype->u.function.funcType;//假设返回值一致便于比较
        if(TypeEqual(t,rtype) == 0)
        {
            if(!(t->u.function.paramNum==0 && rtype->u.function.paramNum==0)   )
            {
                printf("Error type 9 at Line %d: Params wrong in function %s.\n", node->linenumber, node->children[0]->type);
                t->u.function.funcType=NULL;//取消假设
                return NULL;
            }
            else//注意这里也要返回
            {
                return rtype->u.function.funcType;
            }
        }
        else
        {
          return rtype->u.function.funcType;
        }
    }
//         | Exp LB Exp RB     a[b]  左值
    if ( node->child_count ==4 &&
        ( strcmp(node->children[1]->type, "LB") == 0))
    {
        //Exp LB Exp RB 
        ast_node * exp1 = node->children[0];
       
        Type t1 = Exp(exp1);
        if(t1 == NULL) //说明前面a不存在
        {return NULL;}
        //对非数组型变量使用“[…]”（数组访问）操作符。
        if(t1->kind != ARRAY)
        {
            //todo : 看这个变量是否被定义
            printf("Error type 10 at Line %d: %s is not an array.\n", node->linenumber, exp1->children[0]->type);
            return NULL;
        }
        Type t2 = Exp(node->children[2]);
        if( !(t2->kind ==BASIC && t2->u.basic == INT_TYPE))
        {
            printf("Error type 12 at Line %d: there is not an integer in [" "].\n", node->linenumber);
            return NULL;
        }
        return t1->u.array.elem;
    }

    //         | Exp DOT ID        a.b   左值
    if (node->child_count ==3 &&(
        strcmp(node->children[1]->type, "DOT") == 0))
    {
        ast_node * exp1 = node->children[0];
        Type t1 = Exp(exp1);
        if(t1->kind != STRUCTURE)
        {
            //或许todo : 看这个变量是否被定义
            printf("Error type 13 at Line %d: %s is not a struct.\n", node->linenumber,exp1->children[0]->type);
            return NULL;
        }
        FieldList p = t1->u.structure;
        char * str = node->children[2]->type; 
        while(p!=NULL)
        {
            if(strcmp(p->name,str) == 0)
            return p->type;
            p=p->tail;
        }
        printf("Error type 14 at Line %d: Non-existent field %s.\n", node->linenumber, node->children[2]->type);
        return NULL;
    }

    //printf("debug\n");
    return NULL;
}


// ExtDecList  : VarDec                  
//             | VarDec COMMA ExtDecList 
//             ;
void ExtDecList(ast_node * node,Type spec)
{
    // 定义全局变量
    FieldList field = VarDec(node->children[0],spec);
    
    if(ifexist(field->name,field->scope_id) != NULL)
        printf("Error type 3 at Line %d: Redefined variable %s.\n",node->children[0]->linenumber,field->name);
    else
        insert(field);
    
    if(node->child_count == 3)
    {
        ExtDecList(node->children[2],spec);
    }
}


// VarDec      : ID                
//             | VarDec LB INT RB  
//             ;
// a a[10][2]
//将变量返回 无需做检查
FieldList VarDec(ast_node *node,Type spec)
{
    ast_node * temp = node;
    int num =0 ;
    // VarDec 循环到最后的ID得到标识名
    while(strcmp(temp->children[0]->type,"ID") != 0)
    {
        temp = temp->children[0];
        num++;
    }
    FieldList field = (FieldList)malloc(sizeof(FieldList_));
    field->scope_id = current_id;
    field->name = temp->children[0]->type;


    //num = 0
    if(strcmp(node->children[0]->type,"ID") == 0)
    {
        field->type = spec;
        return field;
    }
    //num > 0
    ast_node * temp2 = node;
    Type last = spec;
    for(int i=0;i<num;i++)
    {
        Type ti = (Type)malloc(sizeof(Type_));
        ti->kind = ARRAY;
        //值每一维都要递进
        // TODO: INT8 INT16
        ti->u.array.size = atoi(temp2->children[2]->type);
        temp2 = temp2->children[0];
        //类型每一维都要递进
        ti->u.array.elem = last;
        last = ti;

        field->type = ti;
    }
    return field;

}

// Specifier   : TYPE            
//             | StructSpecifier 
//             ;
Type Specifier(ast_node *node)
{
    // TYPE
    if(strcmp(node->children[0]->type,"TYPE")==0)
    {
        Type spec = (Type)malloc(sizeof(Type_));
        spec->kind = BASIC;
        if(strcmp(node->children[0]->type,"float")==0)
            spec->u.basic=FLOAT_TYPE;
        else // INT INT8 INT16
            spec->u.basic=INT_TYPE;
        return spec;
    }
    // StructSpecifier
    else
    {
        if(strcmp(node->children[0]->type,"StructSpecifier")!=0)
            printf("debug in Specifier: %s\n",node->children[0]->type);
        //printf("goto StructSpecifier:line %d \n",node->children[0]->linenumber);
        //todo : 区分结构体类型和结构体变量
        Type t = StructSpecifier(node->children[0]);
        Type t2 = (Type)malloc(sizeof(Type_));
        t2->kind =STRUCTURE;
        t2->u.structure = t->u.structure;
        return t2;
    }
}

// StructSpecifier : STRUCT OptTag LC DefList RC
//                 | STRUCT Tag                 
//                 ;
// struct Complex { int real, image; }
// 或 struct { int real, image; }
// struct Complex(Tag) a, b;
// 返回结构体类型
Type StructSpecifier(ast_node *node)
{
    Type spec = (Type)malloc(sizeof(Type_));
    spec->kind = STRUCTURE;
    //printf("debug : %s\n",node->children[1]->type);
    //这里注意 如果opttag为空就会是NULL 所以会出错
    if(node->children[1] !=NULL && strcmp(node -> children[1]->type ,"Tag") == 0 )
    {
        // char * str = node->children[1]//Tag
        // ->children[0]//ID
        // ->type;
        //printf("gotoTag\n");
        ast_node * Tag = node->children[1];
        ast_node * ID = Tag->children[0];
        char *str = ID->type;
        //找结构体类型
        FieldList field = search(str,2);
        if(field == NULL)
        {
            printf("Error type 17 at Line %d: Undefined structure %s.\n",ID->linenumber,str);
            spec->u.structure = NULL;
            return spec;
        }
        else
        {
            if(field->type !=NULL)
            return field->type;
        }
        spec->u.structure=NULL;
        return spec;
    }
    //STRUCT (OptTag) LC DefList RC
    //OptTag为NULL应该也占一个位置 这里以防万一debug
    if(node->child_count !=5) printf("debug struct opttag");
    //这里作用域在struct内
    enter_scope();
    ast_node * defList = node->children[3];
    spec->u.structure = NULL;
    while(defList != NULL)
    {//Def DefList
        ast_node *def = defList->children[0];
        // Def     : Specifier DecList SEMI
        Type t = Specifier(def->children[0]);
        ast_node * decList = def->children[1];
        // DecList : Dec                 
        //         | Dec COMMA DecList        
        //         ;
        
        while(1)
        {
            
            // Dec     : VarDec               
            //         | VarDec ASSIGNOP Exp  a = 5
            //         ;
            ast_node * dec = decList->children[0];
            ast_node * varDec = dec->children[0];
            FieldList field = VarDec(varDec,t);
            if(dec->child_count != 1)//在struct内部初始化
            {
                printf("Error type 15 at Line %d: Variable %s is initialized in struct.\n", def->linenumber, field->type);
            }
            FieldList p = spec->u.structure;
            //确保域名没有重复定义
            while(p != NULL)
            {
                if(strcmp(p->name,field->name) == 0)
                {
                    printf("Error type 15 at Line %d: Redefined field %s.\n",varDec->linenumber,field->name);
                    break;
                }
                p = p->tail;
            }
            //开始定义 struct 内部
            if( p == NULL)
            {
                if(ifexist(field->name,field->scope_id)!=NULL)
                {
                    printf("Error type 3 at Line %d: Redefined variable %s.\n", varDec->linenumber, field->type);          
                }
                else
                {
                    insert(field);
                    //追加到头
                    field->tail = spec->u.structure;
                    spec->u.structure = field;
                }

            }
            if(decList->child_count == 3)
            {
            decList = decList->children[2];
            }
            else
            {
                break;
            }
        }
        defList = defList->children[1];
    }
    exit_scope();

    if(node->children[1] != NULL)//OptTag 类型名
    {
        OptTag(node->children[1],spec);
    }
    return spec;
}


// OptTag  : ID          
//         | /* empty */ 
//         ;
void OptTag(ast_node *node,Type spec)
//结构体类型名 必须唯一
{
    if(node == NULL) return;
    FieldList field = (FieldList)malloc(sizeof(FieldList_));
    field->scope_id = current_id;
    field->type =spec;
    field->type->kind = STR_SPE;//这表示是类型名 必须唯一
    char *s =node->children[0]->type;
    field->name = s;
    if(ifexist(field->name ,current_id) !=NULL)
    printf("Error type 16 at Line %d: Duplicated type %s.\n",node->children[0]->linenumber,field->name);
    else
    insert(field);
}