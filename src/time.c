#include "klibc.h"
struct tm {
	int tm_sec,tm_min,tm_hour,tm_mday,tm_mon,tm_year;
};
unsigned long startup_time;
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
int mons[12]={
	0,
	31*DAY,
	(31+28)*DAY,
	(31+28+31)*DAY,
	(31+28+31+30)*DAY,
	(31+28+31+30+31)*DAY,
	(31+28+31+30+31+30)*DAY,
	(31+28+31+30+31+30+31)*DAY,
	(31+28+31+30+31+30+31+31)*DAY,
	(31+28+31+30+31+30+31+31+30)*DAY,
	(31+28+31+30+31+30+31+31+30+31)*DAY,
	(31+28+31+30+31+30+31+31+30+31+30)*DAY,
};
	struct tm time;
void mk_time();
char buf[1024];
void init_time()
{
		time.tm_sec=read_cmos(0);
		time.tm_min=read_cmos(2);
		time.tm_hour=read_cmos(4);
		time.tm_mday=read_cmos(7);
		time.tm_mon=read_cmos(8);
		time.tm_year=read_cmos(9);
		time.tm_sec=bcd_to_bin(time.tm_sec);
		time.tm_min=bcd_to_bin(time.tm_min);
		time.tm_hour=bcd_to_bin(time.tm_hour);
		time.tm_mday=bcd_to_bin(time.tm_mday);
		time.tm_mon=bcd_to_bin(time.tm_mon);
		time.tm_year=bcd_to_bin(time.tm_year);
		tm_to_str(&time,buf);
		print_str(buf,17,0);
		time.tm_mon--;
		mk_time(&time);
    itoa(buf,startup_time);
		print_str(buf,15,80);
}
#define LEAR(year) ((year)/4-(year)/100+(year)/400)
#define is_lear(year) ((year)/4==0&&(year)/100!=0||(year)%400==0)
void mk_time(struct tm *tm)
{
	int year=tm->tm_year+30;
	startup_time=year*YEAR+LEAR(tm->tm_year-1+2000)-LEAR(1969);
	if(is_lear(tm->tm_year+2000))
		startup_time+=DAY;
	startup_time+=mons[tm->tm_mon];
	startup_time+=tm->tm_mday*DAY;
	startup_time+=tm->tm_hour*HOUR;
	startup_time+=tm->tm_min*MIN;
	startup_time+=tm->tm_sec;
}
