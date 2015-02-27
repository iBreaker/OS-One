/**
*	2015年02月27日11:02:23
*	V1.0 	By Breaker
*
*	文件名：memory.c
*    	内存相关
**/ 

#include "memory.h"
#include "Global.h"

/*
*	2014年12月6日18:16:02
*	V1.0 	By Breaker
*
*	初始化内存表
*	void momory_init(unsigned int addr,unsigned int size)			
*	return  
*/

void momory_init(unsigned int addr,unsigned int size)
{
	FreeMemoryTables->max_count = MAX_MEMORY_T;
	FreeMemoryTables->free_count = 0;
	FreeMemoryTables->max_free_size = 0;
	FreeMemoryTables->addr = addr;
	FreeMemoryTables->size = size;
	return;
} 

/*
*	2014年12月6日18:35:27
*	V1.0 	By Breaker
*
*	计算free内存总大小
*	unsigned int total_free_memory_size();
*	return  返回free内存总大小
*/

unsigned int total_free_memory_size()
{
	int i;
	unsigned int retuen_val = 0;
	for(i=0; i<(FreeMemoryTables->free_count); i++)
	{
		retuen_val += (FreeMemoryTables->FreeMemory[i]).size;
		
	}
	//sprintf(TestStr,"%X" ,FreeMemoryTables->FreeMemory[1].size);
	//boxfill8(TestBinfo->vram, TestBinfo->scrnx, COL8_C6C6C6, 0, 170, 100, 170 + 16);
	//printfont8_asc(TestBinfo->vram, TestBinfo->scrnx, 0, 170, COL8_FF0000,TestStr );
	return retuen_val;
} 


/*
*	2014年12月6日18:53:22
*	V1.0 	By Breaker
*
*	分配内存
*	void *malloc(unsigned int size);
*	return  返回分配内存的首地址
*/
void *os_malloc(unsigned int size)
{
	int i;
	void *addr = 0;
	for(i=0; i<(FreeMemoryTables->free_count); i++)
	{
		//找到了合适的内存，ps:应该先排序，然后再找，这个以后再做
		//有剩余内存，需要调整
		if((FreeMemoryTables->FreeMemory[i]).size > size)
		{
			//调整新的free结构，地址+size 大小-size
			addr = (void *)(FreeMemoryTables->FreeMemory[i]).addr;
			(FreeMemoryTables->FreeMemory[i]).addr += size;
			(FreeMemoryTables->FreeMemory[i]).size -= size;
			break;
		}
		
		//大小刚好，直接删掉free结构
		if((FreeMemoryTables->FreeMemory[i]).size == 0)
		{
			addr = (void *)(FreeMemoryTables->FreeMemory[i]).addr;
			
			//向前移位
			for(;i<(FreeMemoryTables->free_count); i++)
			{
				FreeMemoryTables->FreeMemory[i] = FreeMemoryTables->FreeMemory[i+1];
			}
			(FreeMemoryTables->FreeMemory[i]).size--;
			break;
		}
		
	}
	return addr;
}



/*
*	2014年12月11日08:55:37
*	V1.0 	By Breaker
*
*	释放内存
*	int free(unsigned int addr);
*	return  返回是否释放成功
*/
int os_free (unsigned int addr,unsigned int size)
{
	int i;
	//合起来描述两个点的具体位置（在第index号空闲内存之前之中或之后）
	int IsIn_start = -1 , IsIn_end = -1;   //-1之前 0之中  +1之后
	int index_start = 0, index_end = 0; //索引开始地址和结尾地址的索引
	int index_new = -1 ; //新的free结构的index
	int status; //四种状态 1 前有后无 ， 2 后有前无 ， 3 前有后有， 4 前无后无 
	struct free_memory_s TempFree;
	
	//1.1 找到addr的索引号
	if((addr >= FreeMemoryTables->addr) && (FreeMemoryTables->FreeMemory[0].addr > addr) && (FreeMemoryTables->free_count != 0))	//排除特殊情况
	{
		index_start = 0;
		IsIn_start = -1;  //只有这一个负数（在第0之前），其他都是正数，i表示第i个free内存之后计算
	}
	else if(addr < FreeMemoryTables->addr)
	{
		
		return -1; //起始地址错误，释放失败
		
	}
	
	for(i=0; i<(FreeMemoryTables->free_count); i++)
	{
		if(addr >= (FreeMemoryTables->FreeMemory[i]).addr)
		{
			index_start = i;   //需要释放的内存区域的索引
			if(addr <= (FreeMemoryTables->FreeMemory[i]).addr + (FreeMemoryTables->FreeMemory[i]).size)
			{
				IsIn_start = 0;  //在第i之中
			}
			else
			{
				IsIn_start = 1;  //在第i之后
			}
			break;
		}
		
	}

	
	//1.2 找到 addr+size 的索引号
	if((addr+size >= FreeMemoryTables->addr) && (FreeMemoryTables->FreeMemory[0].addr > addr+size) && (FreeMemoryTables->free_count != 0))	//排除特殊情况
	{
		index_end = 0;
		IsIn_end = -1;  //只有这一个负数（在第0之前），其他都是正数，i表示第i个free内存之后计算
		
	}
	else if((addr < FreeMemoryTables->addr) || (addr+size > FreeMemoryTables->addr + FreeMemoryTables->size))
	{
		//printfont8_asc(binfo->vram, binfo->scrnx, 120, 170, COL8_FF0000,"out of memory" );
		return -1; //起始地址错误，释放失败
	}
	
	for(; i<FreeMemoryTables->free_count; i++)
	{

		if(addr+size >= (FreeMemoryTables->FreeMemory[i]).addr+size)
		{
			index_end = i;   //需要释放的内存区域的索引
			if(addr+size  <= (FreeMemoryTables->FreeMemory[i]).addr + (FreeMemoryTables->FreeMemory[i]).size)
			{
				IsIn_end = 0;  //在第i之中
			}
			else
			{
				IsIn_end = 1;  //在第i之后
			}
			break;
		}
	}
	
	// 根据int IsIn_start,IsIn_end,index_start,index_end的值进行处理
	//2 四种状态 1 前有后无 ， 2 后有前无 ， 3 前有后有， 4 前无后无 
	if(IsIn_start == 0 &&  IsIn_start != 0) //1 前有后无
	{
		
		status = 1;
	}
	
	else if(IsIn_start != 0 &&  IsIn_start == 0) //2 后有前无
	{
		status = 2;
	}
	
	else if(IsIn_start == 0 &&  IsIn_start == 0) //3 前有后有
	{
		status = 3;
	}
	
	else if(IsIn_start != 0 &&  IsIn_start != 0) //4 前无后无 
	{
		status = 4;
	}
	
	//3 处理
	switch (status)
	{
		
		case 1: 		//1 前有后无
		{
			(FreeMemoryTables->FreeMemory[index_start]).size = (addr + size) - (FreeMemoryTables->FreeMemory[index_start]).addr;
		}
			break;
		case 2: 		 //2 后有前无
		{
			(FreeMemoryTables->FreeMemory[index_end]).size = (FreeMemoryTables->FreeMemory[index_end]).addr + (FreeMemoryTables->FreeMemory[index_end]).size - addr;
			(FreeMemoryTables->FreeMemory[index_end]).addr = addr;
		}
			break;
		case 3: 		 //3 前有后有
		{
			
			(FreeMemoryTables->FreeMemory[index_start]).size = (FreeMemoryTables->FreeMemory[index_end]).addr + (FreeMemoryTables->FreeMemory[index_end]).size - (FreeMemoryTables->FreeMemory[index_start]).addr;
			for(i=index_end+1; i<FreeMemoryTables->free_count; i++)
			{
				FreeMemoryTables->FreeMemory[i - (index_end - index_start)]  = FreeMemoryTables->FreeMemory[index_end + i] ;
			}
			FreeMemoryTables->free_count -= (index_end - index_start);
		}
			break;
		case 4: 		//4 前无后无 
		{
			
			//新增的free结构
			TempFree.addr = addr ;
			TempFree.size = size ;
			int include_count = 0;
			
			//计算新free结构所包含free结构个数
			if(IsIn_start == -1 && IsIn_start == -1)  //特殊情况先处理
			{
				include_count = 0;
			}
			else if(IsIn_start != -1 && IsIn_start != -1)
			{
				include_count =  index_end - index_start;
			}
			else if(IsIn_start == -1 && IsIn_start != -1)
			{
				include_count =  index_end - index_start + 1;
			}
			else if(IsIn_start != -1 && IsIn_start == -1)
			{
				//   impossible！！！
			}
			
			//根据i的情况处理
			if(include_count == 0) 		//加
			{
				if(FreeMemoryTables->free_count == FreeMemoryTables->max_count)
				{
					return -1;
				}
				FreeMemoryTables->free_count++;
				if(IsIn_start == -1 && IsIn_start == -1)  //特殊情况先处理
				{
					for(i=0; i<(FreeMemoryTables->free_count - 1); i++)		 //位移
					{
						FreeMemoryTables->FreeMemory[i + 1] = FreeMemoryTables->FreeMemory[i];
					}
					FreeMemoryTables->FreeMemory[0] = TempFree;
					index_new = 0;
					
				}
				else	
				{
					for(i=index_start; i<(FreeMemoryTables->free_count - 1); i++)        //往后挪一个位置
					{
						FreeMemoryTables->FreeMemory[i + 1] = FreeMemoryTables->FreeMemory[i];
					}
					FreeMemoryTables->FreeMemory[index_start + 1] = TempFree;
					
					index_new = index_start + 1;
				}
			}
			else if(include_count == 1)		//大小不变
			{
				FreeMemoryTables->FreeMemory[index_end] = TempFree;
				index_new = index_end;
			}
			else if(include_count > 1)		//减
			{
				for(i=0; i < (FreeMemoryTables->free_count - index_end); i++)   //位移
				{
					FreeMemoryTables->FreeMemory[index_start + i + 2] = FreeMemoryTables->FreeMemory[index_end + i + 1]  ;
				}
				FreeMemoryTables->FreeMemory[index_start + 1] = TempFree;
				FreeMemoryTables->free_count -= (include_count + 1); 
				index_new = index_start + 1;
			}
		}
		break;
	}
	if((TempFree.size > FreeMemoryTables->max_free_size) && (index_new != -1)) 
	{
		FreeMemoryTables->max_free_size = FreeMemoryTables->FreeMemory[index_new].size;
	}
	return 0;
}

/*
*	2015年02月27日17:13:21
*	V1.0 	By Breaker
*
*	复制内存
*	void os_memcpy(u32 from_addr, u32 to_addr, u32 size)
*	return  
*/
void os_memcpy(u32 from_addr, u32 to_addr, u32 size)
{
	u32 i ;
	u8 * from_addr_p = (u8 *)from_addr;
	u8 * to_addr_p = (u8 *)to_addr;
	for(i = 0; i < size; i++)
	{
		to_addr_p[i] = from_addr_p[i];
	}
	
}
