/**
*	2015年01月19日10:24:09
*	V1.0 	By Breaker
*
*	文件名：LinkedList.c
*    	定义链表
**/ 

#include "linkedlist.h"
#include "Graphic.h"

u8 ll_get_free_id(LinkedList *ll);
void ll_reflash_head_and_tail(LinkedList *ll);
void ll_link(LinkedList *ll, u8 new_prior, u8 id);
void ll_rm_link(LinkedList *ll, u8 id);
u8 ll_get_max(LinkedList *ll);
u8 ll_get_min(LinkedList *ll);


/*****************************************************************
*	2015年01月19日12:35:38
*	V1.0 	By Breaker
*
*	void ll_init(LinkedList *ll)
*   	链表初始化
*	return void
*/
void ll_init(LinkedList *ll)
{
	ll->ctrl.count = 0;
	ll->ctrl.head = 0;
	ll->ctrl.tail = 0;
	ll->ctrl.max = 0;
	ll->ctrl.min = 0;
	
	/*添加一个默认节点,纯粹是为了简化代码*/
	ll->node[0].next = 0;
	ll->node[0].prior = 0;
	ll->node[0].value = 0xFFFFFFFF;
}

/*****************************************************************
*	2015年01月19日13:44:02
*	V1.0 	By Breaker
*
*	u8 ll_add_to_head(LinkedList *ll, u32 value)
*   	插入新节点到头部
*	return id
*/
u8 ll_add_to_head(LinkedList *ll, u32 value)
{
	/*1.获取id*/
	u8 id = ll_get_free_id(ll);
	
	/*2.验证*/
	if( 0 == id )
	{
		return 0;
	}
	
	/*3.改指针*/
	u8 new_prior = ll->ctrl.tail;
	u8 new_next =  ll->ctrl.head;
	
	/*共改4个指针(不算首尾指针)*/
	ll_link( ll, new_prior, id);
	
	ll_reflash_head_and_tail(ll);
	
	/*4.改值*/
	ll->node[id].value = value;
	
	ll->ctrl.max = ll_get_max(ll);
	ll->ctrl.min = ll_get_min(ll);
	ll->ctrl.count ++;
	return id;
}

/*****************************************************************
*	2015年01月19日14:12:26
*	V1.0 	By Breaker
*
*	u8 ll_add_to_tail(LinkedList *ll, u32 value)
*   	插入新节点到尾部(node[0] 之前)
*	return id
*/
u8 ll_add_to_tail(LinkedList *ll, u32 value)
{
	/*1.获取id*/
	u8 id = ll_get_free_id(ll);
	
	/*2.验证*/
	if( id == 0)
	{
		return 0;
	}
	
	/*3.改指针*/
	u8 new_prior = ll_get_prior_id(ll, ll->ctrl.tail);
	u8 new_next = ll->ctrl.tail;
	
	/*共改4个指针(不算首尾指针)*/
	ll_link( ll, new_prior, id);
	
	ll_reflash_head_and_tail(ll);
	
	/*4.改值*/
	ll->node[id].value = value;

	ll->ctrl.max = ll_get_max(ll);
	ll->ctrl.min = ll_get_min(ll);
	ll->ctrl.count ++;
	return id;
}

u8 ll_add_by_order(LinkedList *ll, u32 value, u32 sort_value)
{
	/*1.获取id*/
	u8 id = ll_get_free_id(ll);
	
	/*2.验证*/
	if( id == 0)
	{
		return 0;
	}
	
	int tmp_id = ll_get_head_id(ll);
	
	while( sort_value > ll_get_value(ll, tmp_id))
	{
		tmp_id = ll_get_next_id(ll, tmp_id);
	}
	
	u8 new_prior;
	u8 new_next;
		
	if(sort_value < ll_get_value(ll, ll_get_head_id(ll)) )
	{
		new_prior = ll_get_tail_id(ll);
		new_next = ll_get_head_id(ll);
	}
	else
	{
		new_prior = ll_get_prior_id (ll, tmp_id);
		new_next = tmp_id;
	}

	
	/*共改4个指针(不算首尾指针)*/
	ll_link( ll, new_prior, id);
	
	ll_reflash_head_and_tail(ll);
	
	/*4.改值*/
	ll->node[id].value = value;

	ll->ctrl.max = ll_get_max(ll);
	ll->ctrl.min = ll_get_min(ll);
	ll->ctrl.count ++;
	return id;
}

u8 ll_add_after_id(LinkedList *ll,u32 value, u8 id_after)
{
	if( (0 == ll->node[id_after].next ) && (0 == ll->node[id_after].prior ) && (0 == ll->node[id_after].value ))
	{
		return 0;
	}
	
	/*1.获取id*/
	u8 id = ll_get_free_id(ll);
	
	/*2.验证*/
	if( id == 0)
	{
		return 0;
	}
	
	u8 new_next =  ll_get_next_id(ll, id_after);
	
	/*共改4个指针(不算首尾指针)*/
	ll_link( ll, id_after, id);
	
	ll_reflash_head_and_tail(ll);
	
	/*4.改值*/
	ll->node[id].value = value;

	ll->ctrl.max = ll_get_max(ll);
	ll->ctrl.min = ll_get_min(ll);
	ll->ctrl.count ++;
	return id;
}

//2015年01月19日15:35:40
u8 ll_remove_by_id(LinkedList *ll, u8 id)
{
	if(( 0 == id ) || (id > 255))
	{
		return 0;
	}
	
	ll_rm_link(ll, id);
	
	ll->node[id].value = 0;
	ll->node[id].prior = 0;
	ll->node[id].next = 0;

	ll->ctrl.max = ll_get_max(ll);
	ll->ctrl.min = ll_get_min(ll);
	ll->ctrl.count --;
	return 1;
}

//2015年01月19日15:36:45
u8 ll_remove_head(LinkedList *ll)
{
	return ll_remove_by_id(ll, ll_get_head_id(ll));
}

//2015年01月19日15:36:59
u8 ll_remove_tail(LinkedList *ll)
{
	return ll_remove_by_id(ll, ll_get_prior_id(ll, ll_get_tail_id(ll)));
}

/*****************************************************************
*	2015年01月19日13:46:18
*	V1.0 	By Breaker
*
*	u32 ll_get_next_id(LinkedList *ll, u8 id)
*   	得到下个节点的id
*	return u8 id号,返回0申请失败
*/
u8 ll_get_next_id(LinkedList *ll, u8 id)
{
	if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
	{
		return 0;
	}
	return ll->node[id].next; 
}


u32 ll_get_next_value(LinkedList *ll, u8 id)
{
	if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
	{
		return 0;
	}
	u8 next = ll_get_next_id(ll, id);
	return   ll->node[next].value; ;
}

/*****************************************************************
*	2015年01月19日13:46:18
*	V1.0 	By Breaker
*
*	u32 ll_get_prior_id(LinkedList *ll, u8 id)
*   	得到下个节点的id
*	return u8 id号,返回0申请失败
*/
u8 ll_get_prior_id(LinkedList *ll, u8 id)
{
	if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
	{
		return 0;
	}
	
	return ll->node[id].prior; 
}

u32 ll_get_prior_value(LinkedList *ll, u8 id)
{
	if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
	{
		return 0;
	}
	u8 prior = ll_get_prior_id(ll, id);
	return   ll->node[prior].value; ;
}

u32 ll_get_count(LinkedList *ll)
{
	return ll->ctrl.count;
}

u8 ll_get_head_id(LinkedList *ll)
{
	return ll->ctrl.head;
}

u8 ll_get_tail_id(LinkedList *ll)
{
	return ll->ctrl.tail;
}

u8 ll_get_max_id(LinkedList *ll)
{
	return ll->ctrl.max;
}

u8 ll_get_min_id(LinkedList *ll)
{
	return ll->ctrl.min;
}





/*****************************************************************
*	2015年01月19日13:46:18
*	V1.0 	By Breaker
*
*	u32 ll_get_value_by_id(LinkedList *ll, u8 id)
*   	取值
*	return u8 id号,返回0申请失败
*/
u32 ll_get_value (LinkedList *ll, u8 id)
{
	if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
	{
		return 0;
	}
	return ll->node[id].value; 
}



/*****************************************************************
*	2015年01月19日12:35:38
*	V1.0 	By Breaker
*
*	u8 ll_get_free_id(LinkedList *ll)
*   	申请id
*	return u8 id号,返回0申请失败
*/
u8 ll_get_free_id(LinkedList *ll)
{
	int id = 1;
	for(id = 1; id < 256; id++)
	{
		if( (0 == ll->node[id].next ) && (0 == ll->node[id].prior ) && (0 == ll->node[id].value ))
		{
			return id;
		}
	}
	
	return 0;
}

/*****************************************************************
*	2015年01月19日13:35:33
*	V1.0 	By Breaker
*
*	void ll_reflash_head_and_tail(LinkedList *ll)
*   	刷新收尾指针
*	return void
*/
void ll_reflash_head_and_tail(LinkedList *ll)
{
	ll->ctrl.head = ll->node[0].next;
	ll->ctrl.tail = 0;
}

/*****************************************************************
*	2015年01月19日13:35:33
*	V1.0 	By Breaker
*
*	void ll_link(LinkedList *ll, u8 new_prior, u8 id)
*   	改变四个指针, 将新node与前后两个node链接起来
*	return void
*/
void ll_link(LinkedList *ll, u8 new_prior, u8 id)
{
	u8 new_next = ll->node[new_prior].next;
	
	/*共改4个指针(不算首尾指针)*/
	ll->node[id].next = new_next;
	ll->node[id].prior = new_prior;
	
	ll->node[new_prior].next = id;
	ll->node[new_next].prior = id;
}

/*****************************************************************
*	2015年01月19日15:25:29
*	V1.0 	By Breaker
*
*	void ll_rm_link(LinkedList *ll, u8 id)
*   	改变2个指针, 删除节点
*	return void
*/
void ll_rm_link(LinkedList *ll, u8 id)
{
	u8 prior = ll_get_prior_id(ll, id);
	u8 next = ll_get_next_id(ll, id);
	
	/*共改2个指针(不算首尾指针)*/	
 	ll->node[prior].next = next;
 	ll->node[next].prior = prior;
}

/*****************************************************************
*	2015年01月22日11:13:23
*	V1.0 	By Breaker
*
*	u8 ll_get_max(LinkedList *ll)
*   	获取最大值
*	return u8 返回最大值id
*/
u8 ll_get_max(LinkedList *ll)
{
	int id = 0;
	u32 max_value = 0;
	u8 max_id = ll_get_head_id(ll);
	
	u8 tmp = 0;
	while(( 0 != ll->node[id].next ||  0 != ll->node[id].prior || 0 != ll->node[id].value ) && tmp < 255 )
	{
		if ( ( max_value <= ll_get_value(ll, id) )&&  ( id != 0 ))
		{
			max_value = ll_get_value(ll, id) ;
			max_id = id;
		}
		
		id = ll_get_next_id(ll, id); 
		tmp ++;
	}
	
	os_printf("|%d-%d",max_id, max_value);
	return max_id;
}

/*****************************************************************
*	2015年01月22日11:23:50
*	V1.0 	By Breaker
*
*	u8 ll_get_min(LinkedList *ll)
*   	获取最小值
*	return u8 返回最小值id
*/
u8 ll_get_min(LinkedList *ll)
{
	int id = 0;
	u32 min_value = 0xFFFFFFFF;
	u8 min_id = ll_get_head_id(ll);
	
	u8 tmp = 0;
	while(( 0 != ll->node[id].next ||  0 != ll->node[id].prior || 0 != ll->node[id].value ) && tmp < 255 )
	{
		if (( min_value >= ll_get_value(ll, id) ) &&  ( id != 0 ))
		{
			min_value = ll_get_value(ll, id) ;
			min_id = id;
		}
		
		id = ll_get_next_id(ll, id);
		tmp ++;
	}
	
	return min_id;
}
