#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "error.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    init_Pro(produce);                  // 初始化产生式表
    init_w(w);                          // 初始化输入串
    init_acChart(acChart);              // 初始化动作表
    init_gtChart(gtChart);              // 初始化转移表

    Stack status;                       //建立状态栈
    Stack sign;                         // 建立符号栈

    InitStack(&status);                 // 初始化栈
    InitStack(&sign);


	Item temp = 0;
	Push(&status, &temp);                  // 初始化，将开始状态压入栈中
	temp = 24;
	Push(&sign, &temp);

	// 打印栈中元素
	PrintStack(&status);
	putchar(' ');
    PrintStack(&sign);
    printf("\n");

    int *ip = w;                        // ip是一个指针,指向当前输入字符
    Item *Pstat, *Psig;                 // Pstat是状态栈的指针,Psig是符号栈的指针
    // 进行语法分析的循环
    while(1)
    {
        Pstat = GetTop(&status);        // 获取当前栈顶指针
        Action AcTemp;                  // 定义一个临时变量,存储当前的动作
        AcTemp = acChart[*Pstat][*ip];  // 根据当前状态和输入符号得到下一个状态

        printf("wh=%c stat=%d\n",AcTemp.wh, AcTemp.stat);
        if(AcTemp.wh == 's')
        {
            Push(&status, &AcTemp.stat); // 下一个状态压栈
            Push(&sign, ip);             // 将当前的符号压栈

            // 打印栈中元素
            PrintStack(&status);
			putchar(' ');
            PrintStack(&sign);
            // putchar('\n');
            printf("\n");

            ++ip;                        // 令ip指向下一个输入符号
        }
        else if(AcTemp.wh == 'r')
        {
            // 打印产生式
            printf("%s\n", produce[AcTemp.stat].Str);

            //    // 打印栈中元素
            PrintStack(&status);
			putchar(' ');
            PrintStack(&sign);
            printf("\n");


            int LenTemp;                // 存储产生式长度的临时变量
            LenTemp = produce[AcTemp.stat].Length; // 获取当前要归约的长度
            printf("LenTemp=%d\n",LenTemp);

            int count;                  // 临时的计数变量
            for(count = 0; count < LenTemp; ++count)
                Pop(&status);           // 从状态栈中弹出LenTemp个元素

            for(count = 0; count < LenTemp; ++count)
                Pop(&sign);             // 从符号栈中弹出LenTemp个元素

            //  // 打印栈中元素
            PrintStack(&status);
			putchar(' ');
            PrintStack(&sign);
            printf("\n");
            //putchar('\n');

            Pstat = GetTop(&status);    // 获取当前状态栈的栈顶状态
            int PlTemp = produce[AcTemp.stat].PL; // 获取归约的产生式的左部

            Push(&status, &gtChart[*Pstat][PlTemp]); // 从gtChart表中得到新状态,并压入栈中
            Push(&sign, &PlTemp); // 将归约的产生式的左部压入符号栈

            //  // 打印栈中元素
            PrintStack(&status);
			putchar(' ');
            PrintStack(&sign);
            printf("\n");
            //putchar('\n');
        }
        else if(AcTemp.wh == 'a')       // 产生式已经已经归约完成
        {
            printf("归约完成!\n");
            break;
        }
        else
		{
			 // error_handle(1);            // 出错处理,暂时未完成
            printf("出错了哦!\n");
			break;
		}
    }
    return 0;
}
