/**
 * @file   stack.h
 * @author pein <pein0119@gmail.com>
 * @date   Tue Mar 26 15:13:18 2013
 *
 * @brief  为语法分析建栈
 *
 *
 */

#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE    500                    // 定义栈的存储元素的最大数量,最多能存储500个元素
#define STATUS            int                    // 定义栈的状态
#define OVERFLOW          -1                     // 定义栈的状态，溢出
#define OK                 1                     // 定义栈的状态，正常
#define EMPTY              2                     // 定义栈的状态，栈空
#define NOT_EMPTY          3                     // 定义栈的状态，栈不空

// 为栈定义元素
// typedef struct
// {
//     int S;                              // 状态符号
//     int X;                              // 文法符号
// }Item;
typedef int Item;
typedef struct
{
    Item item[STACK_MAX_SIZE];          // 为栈开辟存储空间
    Item *top, *base;                 // 定义栈顶、栈底
}Stack;

// 初始化栈
STATUS InitStack(Stack* s)
{
    s->top = s->base = s->item;            // 将栈顶指针和栈底指针都指向栈的存储数组的首部

    return OK;                          // 栈的第一个元素是空的，作为哨兵
}

// 压栈操作
STATUS Push(Stack* s, Item* i)
{
    if((++s->top) == s->item + STACK_MAX_SIZE)
    {
        --s->top;
        return OVERFLOW;                // 存储的元素超过了栈的最大存储容量,上溢
    }

    *(s->top) = *i;
    return OK;
}

// 弹栈操作
STATUS Pop(Stack* s)
{
    if(s->top == s->base)
        return OVERFLOW;                // 栈已经空了，无法继续弹出元素，下溢

    --(s->top);                        // 将栈顶的指针下移
}

// 返回栈顶的指针
Item* GetTop(Stack* s)
{
    return s->top;
}


// 判断栈是否为空
STATUS IsEmpty(Stack* s)
{
    if(s->top == s-> base)
        return EMPTY;

    return NOT_EMPTY;
}

// 打印栈中元素

void PrintStack(Stack* s)
{
    Item *temp;
    for(temp = s->base+1; temp <= s->top; ++temp)
        printf("%d", *temp);
    // printf("\n");
}


#endif
