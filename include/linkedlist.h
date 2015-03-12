/**
*	2015年01月19日10:24:09
*	V1.0 	By Breaker
*
*	文件名：LinkedList.h
*    	定义链表
**/ 

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "stdtype.h"

/*
 * 这个链表起始不是真正的链表, 在写这个链表的时候还没有实现os_malloc函数, 所以这些结点起始都不是
 * 动态申请的, 而是存在node[255]这个数组中.
 *
 * 由于当时没有动态申请内存的函数, 而且数组管理一些东西实在是不方便, 所以就有了这样一个奇葩的链表
 *每个结点都有一个next 和prior指针, 分别指向前一个节点和后一个节点. 里面保存的数据不是内存地址,而是
 *数组下标
 * */

//mode 节点结构体
typedef struct{
	u8	next;
	u8	prior;
	u32	value;
}linked_list_node_ctrl;

//链表管理
typedef struct{
	u32 count;
	u8	head ;
	u8	tail;
	u8 	max;
	u8 	min;
	linked_list_node_ctrl *node;
}linked_list_ctrl;


// 链表结构
typedef struct{
	linked_list_ctrl ctrl;
	linked_list_node_ctrl node[255];
}LinkedList;


void ll_init(LinkedList *ll);														//使用之前必须初始化

u8 ll_add_to_head(LinkedList *ll, u32 value);				//加新节点到头部
u8 ll_add_to_tail(LinkedList *ll, u32 value);					//加新节点到尾部
u8 ll_add_by_order(LinkedList *ll, u32 value, u32 sort_value);	//按sort_value的顺序加入链表(这个函数貌似有点问题)
u8 ll_add_after_id(LinkedList *ll,u32 value, u8 new_prior);			//加到所给id后面

u8 ll_remove_by_id(LinkedList *ll, u8 id);											//通过id删除结点
u8 ll_remove_head(LinkedList *ll);														//从头部删除
u8 ll_remove_tail(LinkedList *ll);															//从尾部删除

u8 ll_get_next_id(LinkedList *ll, u8 id);												//得到下一个节点的数组下标(id)
u8 ll_get_prior_id(LinkedList *ll, u8 id);												//得到上一个节点的数组下标
u32 ll_get_value(LinkedList *ll, u8 id); 													//取值
u8 ll_get_tail_id(LinkedList *ll);																//得到尾部节点id
u8 ll_get_head_id(LinkedList *ll);															//头节点id
u8 ll_set_value(LinkedList *ll, u8 id, u32 value);								//重新设置值

#endif
 
