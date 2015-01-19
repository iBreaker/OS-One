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

typedef struct{
	u8	next;
	u8	prior;
	u32	value;
}linked_list_node_ctrl;


typedef struct{
	u32 count;
	u8	head ;
	u8	tail;
	u8 	max;
	u8 	min;
	linked_list_node_ctrl *node;
}linked_list_ctrl;


// 自定义链表结构
typedef struct{
	linked_list_ctrl ctrl;
	linked_list_node_ctrl node[255];
}LinkedList;


void ll_init(LinkedList *ll);

u8 ll_add_to_head(LinkedList *ll, u32 value);
u8 ll_add_to_tail(LinkedList *ll, u32 value);
u8 ll_add_by_order(LinkedList *ll, u32 value, u32 sort_value);
u8 ll_add_after_id(LinkedList *ll,u32 value, u8 new_prior);

u8 ll_remove_by_id(LinkedList *ll, u8 id);
u8 ll_remove_head(LinkedList *ll);
u8 ll_remove_tail(LinkedList *ll);

u8 ll_get_next_id(LinkedList *ll, u8 id);
u8 ll_get_prior_id(LinkedList *ll, u8 id);
u32 ll_get_value(LinkedList *ll, u8 id); 
u8 ll_get_tail_id(LinkedList *ll);
u8 ll_get_head_id(LinkedList *ll);

#endif
 
