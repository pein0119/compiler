#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "error.h"

typedef struct
{
    char wh;                            // 表示当前要做什么，‘s’表示要转移，'r'要规约
    int  stat;                          // 表示下一个位置
}Action;

Action acChart[100][100];                    // 动作表
int gtChart[100][100];                    // 转移表

typedef struct
{
    int PL;                        // 存储产生式的左部
    char Str[100];                      // 存储产生式
    int Length;                         //存储产生式子右部的元素的个数
}Pro;

Pro produce[100];                  // 存储产生式

// 最多能接收10000个字符的串
int w[10000];                           // 构建一个整型数组来存储输入串,将每个符号都转换为相应的ascii值存储

int main(int argc, char *argv[])
{
    Stack status;                       //建立状态栈
    Stack sign;                         // 建立符号栈

    InitStack(&status);                 // 初始化栈
    InitStack(&sign);

    Item temp = 0;
    Push(&status, &temp);                  // 初始化，将开始状态压入栈中
    temp = '#';
    Push(&sign, &temp);

    int *ip = w;                        // ip是一个指针,指向当前输入串
    Item *Pstat, *Psig;                 // Pstat是状态栈的指针,Psig是符号栈的指针
    // 进行语法分析的循环
    while(1)
    {
        Pstat = GetTop(&status);        // 获取当前栈顶指针
        Action AcTemp;                  // 定义一个临时变量,存储当前的动作
        AcTemp = acChart[*Pstat][*ip];  // 根据当前状态和输入符号得到下一个状态

        if(AcTemp.wh == 's')
        {
            Push(&status, &AcTemp.stat); // 下一个状态压栈
            Push(&sign, ip);             // 将当前的符号压栈
            ++ip;                        // 令ip指向下一个输入符号
        }
        else if(AcTemp.wh == 'r')
        {
            int LenTemp;                // 存储产生式长度的临时变量
            LenTemp = produce[AcTemp.stat].Length; // 获取当前要归约的长度

            int count;                  // 临时的计数变量
            for(count = 0; count < LenTemp; ++count)
                Pop(&status);           // 从状态栈中弹出LenTemp个元素

            for(count = 0; count < LenTemp; ++count)
                Pop(&sign);             // 从符号栈中弹出LenTemp个元素

            Pstat = GetTop(&status);    // 获取当前状态栈的栈顶状态
            int PlTemp = produce[AcTemp.stat].PL; // 获取归约的产生式的左部

            Push(&status, &gtChart[*Pstat][PlTemp]); // 从gtChart表中得到新状态,并压入栈中
            Push(&sign, &PlTemp); // 将归约的产生式的左部压入符号栈
        }
        else if(AcTemp.wh == 'a')       // 产生式已经已经归约完成
            break;
        else
            error_handle(1);            // 出错处理,暂时未完成
    }
    return 0;
}
