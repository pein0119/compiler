/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  创建链表
 *
 *        Version:  1.0
 *        Created:  2013年04月28日 16时55分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  pein (none), pein0119@gmail.com
 *   Organization:  none
 *
 * =====================================================================================
 */
#ifndef _LIST_H
#define _LIST_H
// #include "hash.h"

typedef struct
{
	int result;//存储结果地址
	int op; //记录操作的类型: 加 减 乘 除
	int arg1;//存储第一个操作数
	int arg2;//存储第二个操作数(有可能为空)
}tuple;

tuple tuTable[1000];//创建三地址码数组,存储相应的三地址码,最多存储999行

struct list 
{
	int src_label;
	//目标标号
	int aim_label; 
	struct list *next;
};

typedef struct list nextlist;

//创建一个只包含i的新链表,i是四元式数组的下标,makelist函数返回指向它它所创建的链表的指针
nextlist* makelist(int i )
{
	nextlist* head;
	head = (nextlist*)malloc(sizeof(nextlist));
	head->src_label = i;
	head->next = NULL;
	return head;
}

//合并由p1 p2指向的两个链表,并返回指向合并后的链表的指针
nextlist* merge(nextlist* p1, nextlist* p2)
{
	nextlist* temp;				// 定义一个用于迭代的指针
	// 找到p1链表的最后一个节点
	for(temp = p1; temp->next != NULL; ++temp);			

	temp->next = p2;			// 将p1链表的最后一个节点的next指针指向p2,完成p1和p2的合并
	
	return p1;
}

//将i插入到链表p中的每一条语句中,作为该语句的目标标号
void backpatch(nextlist* p, int i)
{
	nextlist* temp;				// 定义一个用于迭代的指针

	for (temp = p; ; ++temp)
	{
		tuTable[temp->src_label].arg1 = i;
		// 如果当前的next为NULL,说明已经是最后一个节点,退出
		if(temp->next == NULL)
			break;
	}
}


#endif
