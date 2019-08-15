
/**
 *
 *
 完成的功能是将字符串参数name的内容拷贝到内核中保存下来。
 要求name的长度不能超过23个字符。返回值是拷贝的字符数。
 如果name的字符个数超过了23，则返回“-1”，并置errno为EINVAL。*
 *
 *
 * */
#include<linux/kernel.h>
#include<asm/segment.h>
#define NAME_LEN  23

char kernelarray[NAME_LEN];
int reallen = 0;

int sys_iam(const char * name)
{
	int i = 0 ;
	char c;
	for(i=0 ;i < NAME_LEN;i++)
	{
		if ((c = get_fs_byte(name+i))!= '\0')
			kernelarray[i] = c;
		else
			break;
	}
	if(i>= NAME_LEN)
	{
		printk("Name is too long!");
		return -1;
	}
	reallen = i ;
	return reallen;
}

int sys_hellokernel()
{
	printk("Hello kernel! \n");
	return 0;
}

int sys_whoami(char * name, unsigned int size)
{	
	int i = 0;
	if(reallen > size)
	{
		printk("size of name is out of bound! \n");
		return -1;
	}else
	{
		while (kernelarray[i]!='\0')
		{
			put_fs_byte(kernelarray[i],(name+i));
			i++;
		}
		return i;
	}
}
