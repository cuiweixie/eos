/*
 * =====================================================================================
 *
 *       Filename:  time.h
 *
 *    Description:  time.h
 *
 *        Version:  1.0
 *        Created:  2012年01月31日 00时29分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _TIME_H_
#define _TIME_H_
#define HZ 100
struct tm {
	int tm_sec,tm_min,tm_hour,tm_mday,tm_mon,tm_year;
};
#define read_cmos(addr) ({\
	out_byte(0x70,0x80|addr);\
	in_byte(0x71);\
  })
#define bcd_to_bin(val) ((val&15)+(val>>4)*10)
#define tm_to_str(time,buf) do {\
	int *p=&(time)->tm_year;\
	char *pb=buf;\
	int i;\
	for(i=0;i<6;i++,pb+=3,p-=1)\
	{\
		*pb=*p/10+'0';\
		*(pb+1)=*p%10+'0';\
		*(pb+2)='-';\
	}\
}while(0)
#define MIN 60
#define HOUR (MIN*60)
#define DAY  (24*HOUR)
#define YEAR (365*DAY)
#define div(a,b) ({\
		unsigned int *p=&a;unsigned int l=*p/b,h=*(p+1)/b;\
		unsigned long long int ret=(unsigned long long int)h<<32|l;\
		ret;\
		})
#define rem(a,b) ({\
unsigned int *p=&a;unsigned int l=*p%b,h=*(p+1)%b;\
		unsigned int ret=0xffffffff;ret=ret/b;ret=(ret+1)*h+l;ret%=b;\
		ret;\
		})
#define LEAR(year) ((year)/4-(year)/100+(year)/400)
#define is_lear(year) ((year)/4==0&&(year)/100!=0||(year)%400==0)
struct tm time;
unsigned long long  mk_time(struct tm *tm);
extern unsigned long long int get_time();
extern unsigned long long int _startup_time;
extern unsigned long long int _tick;
#endif
