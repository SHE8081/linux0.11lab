/*************************************************************************
	> File Name: sem.c
	> Author: ben
	> Mail: benben5893@gmail.com 
	> Created Time: 2019年08月05日 星期一 13时23分17秒
 ************************************************************************/
#include<string.h>

#define SHM_COUNT 20
#define SHM_NAME_SIZE 20

//信号量定义
typedef struct  sem_t
{
	const char * name;
	unsigned int value;
	task_struct * queue;
} [SHM_COUNT] semtable;

//声明信号量
semtable stb;
/*
 *
name是信号量的名字。不同的进程可以通过提供同样的name而共享同一个信号量。如果该信号量不存在，就创建新的名为name的信号量；如果存在，就打开已经存在的名为name的信号量。 value是信号量的初值，仅当新建信号量时，此参数才有效，其余情况下它被忽略。 当成功时，返回值是该信号量的唯一标识（比如，在内核的地址、ID等），由另两个系统调用使用。如失败，返回值是NULL。
 *
 * */
int sys_sem_open(const char * name, unsigned int value)
{
	int i;
	char tmp[SHM_NAME_SIZE];
	for(i=0 ;i < SHM_NAME_SIZE;i++)
	{
		tmp[i]=get_fs_byte(name+i);
		if(tmp[i]=='\0') break;
	}
	//在SHM_COUNT内，按照name查询信号量
	for(i=0;i <SHM_COUNT;i++)
	{
		if(strcmp(stb[i].name, tmp)==0)
		{
			return &(stb+i) //找到返回信号量地址
		}
	}
	if(SHM_COUNT > i)	//没有找到需要新建
	{
		stb[i].name = tmp;
		stb[i].value =  value;
		stb[i].queue = NULL;
	}
	if(SHM_COUNT == i)
	{	
		return NULL;
	}
}
/*
 *
 sem_wait()就是信号量的P原子操作。如果继续运行的条件不满足，则令调用进程等待在信号量sem上。返回0表示成功，返回-1表示失败。
 */

int sys_sem_wait(sem_t * sem)
{
	cli();
	if(semtable[sd].value-- <0)
	{
		//设置自己为阻塞；将自己加入
		//semtable[sd].queue中；
		//schedule();
	}
	sti();
}


//
//sem_post()就是信号量的V原子操作。如果有等待sem的进程，它会唤醒其中的一个。返回0表示成功，返回-1表示失败。
int sys_sem_post(sem_t * sem)
{
	
}


//sem_unlink()的功能是删除名为name的信号量。返回0表示成功，返回-1表示失败。
int sys_sem_unlink(const char * name)
{
	
}
