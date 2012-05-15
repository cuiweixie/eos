/*
 * =====================================================================================
 *
 *       Filename:  hd.c
 *
 *    Description:  hardisk driver
 *
 *        Version:  1.0
 *        Created:  2012年02月01日 20时49分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <sched.h>
#include <klibc.h>
#include <hd.h>
struct hd_request{
	void (*do_hd)();
	int dev;
	u8 features;
	u8 device;
	u8 command;
	u32 count;
	u32 lba;
}hd_request[0xf];
struct hd_request *hd_rq_cur;
void init_hd()
{
	enable_irq(0x2);
	enable_irq(0xe);
}
extern long long int _tick;
int hd_out(u32 features,u32 device,u32 count,u32 lba,u32 cmd)
{
	 unsigned long long int _s=_tick;
	 unsigned char flags=0;
	 while(_tick-_s<100)
	 {
		 flags=in_byte(REG_STATUS);
		 if((flags&0xc0)==0x40)break;
	 }
		 if(flags&0xc0!=0x40)return -1;
	 send_hd_cmd(features,device,count,lba,cmd);
	 return 0;
}

