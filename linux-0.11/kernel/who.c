
/**
 *
 *
 完成的功能是将字符串参数name的内容拷贝到内核中保存下来。
 要求name的长度不能超过23个字符。返回值是拷贝的字符数。
 如果name的字符个数超过了23，则返回“-1”，并置errno为EINVAL。*
 *
 *
 * */

#include<asm/segment.h>
#define NAME_LEN  23
int sys_iam(const char * name)
{
	char tmp[23];
	int i = 0 ;
	char c;
	for(i=0 ;i < NAME_LEN;i++)
	{
		if ((c = get_fs_byte(name+i))!= '\0')
			tmp[i] = c;
		break;
	}
	if(i>= NAME_LEN)
	{
		printk("Name is too long!");
		return -1;
	}
	return i;
}

int sys_whoami()
{
	return 0;
}
