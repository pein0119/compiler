#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "error.h"
#include "hash.h"
#include "parser.h"
#include "list.h"

/**
 *将定义的的操作符映射为相应的数字
 -------------------------------------------
 '>'  1
 '<'  2
 ':=' 3
 '+'  4
 '-'  5
 '*'  6
 '\'  7
 'readln' 8
 'writeln' 9
 -------------------------------------------
 * 
 */

keyword sigTbl[ID_TABLE_LENGTH]; /* 定义存储id的hash表 */


void insert_id(Ele* ip)
{
	if(searchHash(ip->name, sigTbl) != -1)
		return ;
	
	if(ip->type == 1 || ip->type == 17)			/* 如果当前的输入是变量,则插入哈希表中 */
		createHash(ip->name, sigTbl);
	
	int index = searchHash(ip->name, sigTbl);

	if(strcmp("first", ip->name) != 0)
		sigTbl[index].id_type = 1;		/* 先假定为整型,稍后处理 */
}

/* 判断当前产生式是否需要处理 */
inline
int test_index(int index)
{
	return (index == 8)||(index == 9)||
		   (index == 12)||//(index == 13)||(index == 14)|| 
		   (index == 16)||(index == 17)||(index == 19)||
		   (index == 20)||(index == 23)||(index == 24);
}

/* 判断当前的符号是不是操作符号 */
inline
int test_op(int arg)
{
	return (arg >= 10)&&(arg <= 16);
}

/*为三地址码进行编号*/
int label;
/* 即tuTable的下标 */

//生成三元组
static int TupleNum;			/* 三元组的下标 */
char String[10] = "temp";		/* 三元组临时变量共同的部分 */

/* 通过这个函数来生成三元组临时变量名 */
void createTemp()
{
	char temp[5];
	
	sprintf(temp, "%d", TupleNum);
	strcat(String, temp);
}
void createTuple(int num, Stack1* sign)		/* num是产生式的标号 */
{
	int tempArg;				/* 用来临时存储从哈希表获得的标识符参数 */
	int key;					/* 用于存储从符号表中申请的表项的下标 */
	switch(num)
	{
	case 8:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 1;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;
	case 9:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 2;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;
	case 12:
		/* 赋值运算的结果已经在符号表中,不需要再构造临时变量 */
		key = searchHash( (sign->top - 3)->name, sigTbl);
		if(key != -1)
			tuTable[TupleNum].result = key;
		else
			printf("id在符号表中不存在!\n");

		
		tuTable[TupleNum].op = 3;
		tempArg = searchHash( (sign->top-1)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}
		tuTable[TupleNum].arg2 = -1;
		++TupleNum;
		break;
	case 16:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 4;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;
	case 17:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 5;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;
	
	case 19:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 6;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;		
	case 20:
		/* 生成一个新的变量名 */
		createTemp();
		/* 在符号表中为新的变量名申请一个表项 */
		key = createHash(String, sigTbl);
		/* 将三元组中的result赋值 */
		tuTable[TupleNum].result = key;
		tuTable[TupleNum].op = 7;
		/* 查找符号栈的栈顶id在符号表中的位置 */
		tempArg = searchHash( (sign->top)->name, sigTbl);
		
		if (tempArg != -1)
			tuTable[TupleNum].arg2 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		/* 取得符号栈中的第三个元素 */
		tempArg = searchHash((sign->top-2)->name, sigTbl);
		/* 将符号栈中的第三个id在符号表中的位置插入三元组中 */
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}

		++TupleNum;
		/* String字符串被改变了,将她改为原值temp */
		strcpy(String, "temp");
		break;
	case 23:					/* 对readln指令生成相应的三元组 */
		/* 取得要读取的变量名 */
		tuTable[TupleNum].op = 8;
		tempArg = searchHash((sign->top - 2)->name, sigTbl);
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}
		++TupleNum;
		break;
	case 24:					/* 对writeln指令生成相应的三元组 */
		/* 取得要读取的变量名 */
		tuTable[TupleNum].op = 9;
		tempArg = searchHash((sign->top - 2)->name, sigTbl);
		if(tempArg != -1)
			tuTable[TupleNum].arg1 = tempArg;
		else
		{
			printf("id在符号表中不存在!\n");
		}
		++TupleNum;
		break;
	default:
		printf ("参数不合法\n");
	}
}

/* 打印三元组 */
void printTuple()
{
	int i;
	for(i = 0; i < TupleNum; ++i)
	{
		/* 打印三元组的编号 */
		printf("%d: ", i);
		if(tuTable[i].result == -1) 
		{
			printf("goto ");
			printf("%d\n", tuTable[i].arg1);
		}
		else if(tuTable[i].result == -2)
			printf("end\n");
		else if(tuTable[i].op == 8 || tuTable[i].op == 9)
		{
			if(tuTable[i].op == 8)
			{
				printf ("readln ");
				printf ("%s\n", sigTbl[tuTable[i].arg1].str);
			}
			else
			{
				printf("writeln ");
				printf("%s\n", sigTbl[tuTable[i].arg1].str);
			}
		}
		else
		{
			/* 打印结果地址的名称 */
			printf("%s ", sigTbl[tuTable[i].result].str);
			/* 打印一个赋值操作符,无实际意义 */
			printf (":= ");
			/* 打印第一个参数的名称 */
			printf("%s ",sigTbl[tuTable[i].arg1].str);
			/* 打印操作符号 */
			switch(tuTable[i].op)
			{
			case 1:
				printf("> ");
				break;
			case 2:
				printf ("< ");
				break;
				/* case 3: */				/* 	printf(":= "); */
				/* 	break; */
			case 4:
				printf("+ ");
				break;
			case 5:
				printf("- ");
				break;
			case 6:
				printf("* ");
				break;
			case 7:
				printf("/ ");
				break;
			}
			/* 打印三元组的第二个参数 */
			if(tuTable[i].arg2 != -1)
				printf ("%s ", sigTbl[tuTable[i].arg2].str);
			printf("\n");
		}
	}
	
}
int main(int argc, char *argv[])
{
    init_Pro(produce);                  // 初始化产生式表
	init_w(w);							/* 初始化输入串 */
    init_acChart(acChart);              // 初始化动作表
    init_gtChart(gtChart);              // 初始化转移表

	nextlist *truelist, *falselist, *N;
	int M1, M2;					/* 回填时要用 */
	int flag = 0;				/* 我们定义一个标志,来分辨当前处理的是if还是while */
	/*flag为1时,表明当前处理的是if,为2表明当前处理的是while */
    Stack status;                       //建立状态栈
    Stack1 sign;                         // 建立符号栈

    InitStack(&status);                 // 初始化栈
    InitStack1(&sign);
	Item temp = 0;
	Push(&status, &temp);                  // 初始化，将开始状态压入栈中
	Ele temp1;
	temp1.type = 24;
	Push1(&sign, &temp1);

	// 打印栈中元素
	/* PrintStack(&status); */
	/* putchar(' '); */
    /* PrintStack1(&sign); */
    /* printf("\n"); */
    Ele *ip = w;                        // ip是一个指针,指向当前输入字符
    Item *Pstat;                // Pstat是状态栈的指针,Psig是符号栈的指针
	Ele *Psig;
	
    // 进行语法分析的循环
    while(1)
    {
        Pstat = GetTop(&status);        // 获取当前栈顶指针
        Action AcTemp;                  // 定义一个临时变量,存储当前的动作
		/* printf("%d\n",(*ip).type); */
        AcTemp = acChart[*Pstat][(*ip).type];  // 根据当前状态和输入符号得到下一个状态

		/* printf("wh=%c stat=%d\n",AcTemp.wh, AcTemp.stat); */
        if(AcTemp.wh == 's')
        {
            Push(&status, &AcTemp.stat); // 下一个状态压栈
            Push1(&sign, ip);             // 将当前的符号压栈

			if(ip->type == 7)
				flag = 1;		/* 当前处理的是if */
			if(ip->type == 25)
				flag = 2;		/* 当前处理的是while */
			
			/* 如果当前的输入是变量,就把它插入哈兮表 */
			insert_id(ip);
            //打印栈中元素
            /* PrintStack(&status); */
			/* putchar(' '); */
            /* PrintStack1(&sign); */
            /* /\* putchar('\n'); *\/ */
            /* printf("\n"); */
			/* if(ip->type == 8) 	/\* 当前输入的符号是'then' *\/ */
			/* { */
			/* 	printf ("N %d\n",TupleNum); */
			/* 	N = makelist(TupleNum); /\* 我们需要在then之前的表达式之后插入一条goto指令 *\/ */
			/* 	tuTable[TupleNum].result = -1;	  /\* result为-1,表明当前存储的是goto指令 *\/ */
			/* 	++TupleNum; */
			/* } */
			if(ip->type == 9)	/* 当前输入的符号是 'else' */
			{
				N = makelist(TupleNum); /* 我们需要在执行完布尔表达式为真时的指令之后加一条跳转指令 */
				tuTable[TupleNum].result = -1;
				++TupleNum;
				M2 = TupleNum; /* 记录下当前三元组的编号,回填时要用 */	
			}
			if(ip->type == 25)	/* 当前输入的符号是 'while' */
			{
				M1 = TupleNum;	/* 回填时要用 */
			}
			if(ip->type == 26)	/* 当前的输入符号是 'esle' */
			{
				truelist = makelist(TupleNum); /* 在布尔表达式后插入一条表达式为真时的跳转指令 */
				tuTable[TupleNum].result = -1; /* 表明当前的指令是一条goto跳转指令 */
				++TupleNum;

				falselist = makelist(TupleNum);	/* 在布尔表达式后插入一条表达式为假时的跳转指令 */
				tuTable[TupleNum].result = -1;	/* 表明当前的指令是一条goto跳转指令 */
				++TupleNum;

				M2 = TupleNum;	/* 记录下当前三元组的编号,回填时要用 */
				
			}
				
			++ip;                        // 令ip指向下一个输入符号
			/* printf ("%d\n", ip->type); */
        }
        else if(AcTemp.wh == 'r')
        {
            // 打印产生式
			/* printf("%s\n", produce[AcTemp.stat].Str); */

            //    // 打印栈中元素
            /* PrintStack(&status); */
			/* putchar(' '); */
            /* PrintStack1(&sign); */
            /* printf("\n"); */
			
            int LenTemp;                // 存储产生式长度的临时变量
            LenTemp = produce[AcTemp.stat].Length; // 获取当前要归约的长度
            /*printf("LenTemp=%d\n",LenTemp);*/

            int count;                  // 临时的计数变量,统计
			/* printf("count = %d\n", count); */

			Ele* temp_ele;
			temp_ele = GetTop1(&sign);

			Ele* tempSp;		/* 申请一个临时的符号栈指针 */
			/*printf("temp ");*/
			if(test_index(AcTemp.stat))
			{
				createTuple(AcTemp.stat, &sign);
			}
			/* 当前处理的是if then else产生式 */
			if(flag == 1)
			{
				/* 如果是布尔表达式,我们需要在布尔表达式的四元式之后插入一个新的四元式 */
				if((AcTemp.stat == 8) || (AcTemp.stat == 9))
				{
					printf ("TupleNum=%d\n",TupleNum);
					truelist = makelist(TupleNum); /* 布尔表达式为真时的链表 */
					/* 在三元组中处理相应的表项 */
					tuTable[TupleNum].result = -1; /* result为-1,表明这个表项是goto指令 */
					++TupleNum;
					falselist = makelist(TupleNum); /* 布尔表达式为假时的链表 */
					tuTable[TupleNum].result = -1;			  /* result为-1,表明这个表项是goto指令 */
					++TupleNum;
					M1 = TupleNum; /* M1记录下此时的标号 ,回填时要用*/
					printf ("M1 = %d\n",M1);
				}

			}
			else if (flag == 2)	/* 当前处理的是while do 产生式 */
			{
				/* if((AcTemp.stat == 8) || (AcTemp.stat == 9)) */
				/* { */
				/* 	M1 = TupleNum; /\* M1记录下此时的标号,回填时要用 *\/ */
				/* } */
			}
			if(AcTemp.stat == 13) /* 当前归约的是if then else 产生式 */
			{
				/* 开始回填 */
				printf("开始回填");
				backpatch(truelist, M1);
				backpatch(falselist, M2);
				backpatch(N, TupleNum); /* 将当前的三元组标号回填到N所在的链表中 */
				/* 回填完成后要释放相应的指针 */
			}
			if(AcTemp.stat == 14) /* 当前归约的是 while do 产生式 */
			{
				/* 在while 结构中的最后一条语句执行完之后插入一条goto指令 */
				tuTable[TupleNum].result = -1;
				tuTable[TupleNum].arg1 = M1;
				++TupleNum;
				/* 回填开始 */
				backpatch(truelist, M2);
				backpatch(falselist, TupleNum);
			}
			/* if(AcTemp.stat == 13 || AcTemp.stat == 14 ) */
			/* { */
				
			/* 	for(tempSp = (sign.top - LenTemp + 1); tempSp <= sign.top; ++tempSp) */
			/* 		printf("%s ",tempSp->name); */
			/* 	printf("\n"); */
			/* } */
				
	        for(count = 0; count < LenTemp; ++count)
                Pop(&status);           // 从状态栈中弹出LenTemp个元素

            for(count = 0; count < LenTemp; ++count)
                Pop1(&sign);             // 从符号栈中弹出LenTemp个元素
			
			//  // 打印栈中元素
            /* PrintStack(&status); */
			/* putchar(' '); */
            /* PrintStack1(&sign); */
            /* printf("\n"); */
            //putchar('\n');

            Pstat = GetTop(&status);    // 获取当前状态栈的栈顶状态
            int PlTemp = produce[AcTemp.stat].PL; // 获取归约的产生式的左部

			//为临时变量赋值
			temp1.type = PlTemp;
			temp1.property = temp_ele->property;
			/* 如果是按6 12 18 21 22产生式归约的,就直接将右部的名字穿给左部 */
			if(AcTemp.stat == 6 || AcTemp.stat == 18 || AcTemp.stat == 21||
			   AcTemp.stat == 22)
				strcpy(temp1.name, temp_ele->name);
			/* 如果是加减乘除运算,就要将临时结果的名字压入栈中 */
			else if(test_index(AcTemp.stat))
				strcpy(temp1.name, sigTbl[tuTable[TupleNum-1].result].str);
			
			/*printf("%s\n", temp_ele->name);*/
			/*strcpy(temp1.name, "temp");*/
		    Push(&status, &gtChart[*Pstat][PlTemp]); // 从gtChart表中得到新状态,并压入栈中
            Push1(&sign, &temp1); // 将归约的产生式的左部压入符号栈

            //  // 打印栈中元素
            /* PrintStack(&status); */
			/* putchar(' '); */
            /* PrintStack1(&sign); */
            /* printf("\n"); */
            //putchar('\n');
        }
        else if(AcTemp.wh == 'a')       // 产生式已经已经归约完成
        {
			/* 完成,在三元组中插入一条结束指令 */
			tuTable[TupleNum].result = -2;
			++TupleNum;
            printf("success!\n");
            break;
        }
        else
		{
			// error_handle(1);            // 出错处理,暂时未完成
            printf("出错了哦!\n");
			break;
		}
    }
	int i;
	for ( i = 0; i < ID_TABLE_LENGTH; ++i)
	{
		if(sigTbl[i].flag)
			printf ("%s\n",sigTbl[i].str);
	}
	printTuple();
    return 0;
	
}
