#ifndef _KLIBC_C_
#define _KLIBC_C_
#include <klibc.h>
#include <stdarg.h>
char *itoa(char* buffer,unsigned long int n)
{
	    if(n==0)
			{
				buffer[0]='0';
				buffer[1]='\0';
				return buffer;
			}
			buffer[0]=n>0?'+':'-';
			int i=1;
		  n=n>0?n:-n;
      while(n!=0)
			{
				buffer[i++]=n%10+'0';
				n/=10;
			}
			i--;
			int j;
			char ch;
			for( j=1;j<i;j++,i--)
			{
				ch=buffer[i];
				buffer[i]=buffer[j];
				buffer[j]=ch;
			}
			return buffer;
}
char *itoah(char *buffer,unsigned long int n,int len)
{
	  buffer[0]='0';
		buffer[1]='x';
		int i,j,d;
		for(i=len-4,j=2;i>=0;i-=4,j++)
		{
	  	d=(n>>i)&0xf;
			if(d<10)
			{
				buffer[j]=d+'0';
			}
			else
			{
				buffer[j]=d-10+'A';
			}
		}
		buffer[j]='\0';
		return buffer;
}
int strcpy(char *dst,char *src,int size)
{
          while(size--)
          {
                 *dst++=*src++;           
          }
          return 0;
}
int strcmp(char *str1,char * str2,int n)
{
            int i=0,ret=0;
            for(i=0;i<n;i++)
                {
                   ret=(*str1)-(*str2);
                   if(ret!=0)
                   return ret;
                   str1++,str2++;
                 }
            return ret;
}
int vsprintf(char *str,char *fmt,va_list ap)
{
	int i=0,n;
	char *p;
	for(;*fmt;++fmt)
	{
		if(*fmt=='%')
		{
			fmt++;
			switch(*fmt)
			{
				case 'd':
					n=va_arg(ap,int);
					itoa(&str[i],n);
					while(str[i++]!='\0');
					break;
				case 's':
					p=va_arg(ap,char *);
					while(*p!='\0')
					{
						str[i++]=*p;
						p++;
					}
					break;
				case 'x':
					n=va_arg(ap,int);
					itoah(&str[i],n,32);
					while(str[i]!='\0')i++;
         break;
				default:
					return -1;
			}
		}
		else
		str[i++]=*fmt;
	}
	str[i]='\0';
}
int sprintf(char *str,char *fmt,...)
{
	va_list ap;
	char *p;
	va_start(ap,fmt);
	vsprintf(str,fmt,ap);
	va_end(ap);
}
//printf unfinish
int printf(char *fmt,...)
{
	char str[100]={'\0'};
	va_list ap;
	va_start(ap,fmt);
	vsprintf(str,fmt,ap);
	va_end(ap);
	return 0;
}

extern unsigned long long int _tick;
inline void wait_time(int sec)
{
	sec=sec*100;
	unsigned long long int cc=_tick;
	while((_tick-cc)<sec);
}
pos_panic=60;
void panic(char * str)
{
	show_str(pos_panic,str);
	pos_panic+=80;
	while(1);
}
#endif

