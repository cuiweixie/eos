#include <klibc.h>
#include <asm_func.h>
#include <sched.h>
#include <time.h>
#include <hd.h>
#include <page.h>
extern void init_gdt();
extern void init_time();
#define read_cmos(addr) ({\
	out_byte(0x70,0x80|addr);\
	in_byte(0x71);\
  })
void Task0();
void kernel_main()
{
	init_gdt();
	init_idt();
	init_page();
	init_time();
	out_byte(0x21,0x00);
	out_byte(0xa1,0x00);
/*   unsigned char hd_status;
 * 	int pos=320;
 * 	int a=10;
 * while(a--){
 * 	char str[111];
 * 	hd_status=in_byte(REG_STATUS);
 * 	sprintf(str,"%x  %x",(u32)hd_status,0x80);
 * 	show_str(400,str);
 * 	if((hd_status&0x80)==0x0)
 *     hd_out(0,0xe0,1,0,0x20);
 *  }
 */
	switch_to_user(0xf,Task0,0x17,process[0].user_stack+STACK_SIZE);
}
#define S POS(5,0)
#define E POS(20,0)
#define POS(n,m) ((n)*80+m)
unsigned int pos=S;
void Task0()
{
	asm("push %eax\n"
			"mov $0x17,%eax\n"
			"mov %ax,%ds\n"
			"pop %eax\n");
	while(1)
 {
	 show_ch(pos,0xfc41);
	 LOCK_INC(pos,1);
  	 if(pos>=E)pos=S;
 }
}
void Task1()
{
	while(1)
 {
	 show_ch(pos,0x0a42);
	 LOCK_INC(pos,1);
	 if(pos>=E)pos=S;
 }
}
void Task2()
{
	while(1)
 {
	 show_ch(pos,0x0943);
	 LOCK_INC(pos,1);
	 if(pos>=E)pos=S;
 }
}
void reboot()
{
    unsigned char good = 0x02;
    while ((good & 0x02) != 0)
        good = in_byte(0x64);
    out_byte(0x64, 0xFE);

}
