/*
 * =====================================================================================
 *
 *       Filename:  shell.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年02月04日 23时09分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <keyboard.h>
#include <keymap.h>
#include <klibc.h>
#include <sched.h>
extern void reboot();
char hint[]="cui@os:";
unsigned int output_pos=0;
#define POS(x,y) ((x)*160+y*2)
#define ctrl_flag  0x01
#define shift_flag 0x02
#define alt_flag   0x04
#define cap_flag   0x08
#define enter_flag 0x10
#define fix_cursor(pos) asm("int $0xab"::"a"(1),"b"(pos))
unsigned int key_flags=enter_flag;
unsigned short int color=0x0900;
extern struct keyboard_buf keyboard_buf;
void move_to_top(int row);
void task_shell()
{   
	  char scan_code;
		unsigned int ch;
    while(1)
		{
			if((key_flags&enter_flag)!=0)
			{
				output_pos=(output_pos/80+1)*80;
				show_str(output_pos,hint);
			  output_pos+=sizeof(hint);
				if(output_pos/80>24)
				{
				 move_to_top(24);	
				 output_pos=0+sizeof(hint);
				}
				fix_cursor(output_pos);
				key_flags&=~(enter_flag);
			}
			if(keyboard_buf.count>0)
			{
			scan_code=keyboard_buf.buf[keyboard_buf.tail];
			keyboard_buf.tail=(keyboard_buf.tail+1)%1024;
			keyboard_buf.count--;
      ch=keymap[scan_code*3];
			if((scan_code&0x80)==0)
			{
				switch(ch)
				{
			     case 'a'...'z':
					 case ' ':
						 show_ch(output_pos,ch|color);
						 output_pos++;
						 fix_cursor(output_pos);
             break;
					 case BACKSPACE:
						 ch=' ';
						 output_pos--;
						 show_ch(output_pos,ch|color);
						 fix_cursor(output_pos);
						 break;
					 case ENTER:
						 key_flags|=enter_flag;
				}
			}
			else /* break code */
			{
				switch(ch)
				{
					case CTRL_L:
					case CTRL_R:
						key_flags&=~(ctrl_flag);
						break;
					case SHIFT_L:
					case SHIFT_R:
						key_flags&=~(shift_flag);
					  break;
					case ALT_L:
					case ALT_R:
						key_flags&=~(alt_flag);
						break;
					case CAPS_LOCK:
						key_flags&=~(cap_flag);
					default:;
				}
			}
		}
	}
}
void init_shell()
{
   __startup_process(8,2,2,task_shell);
	process[2].tss.eflags|=(3<<12);
	asm("pushf;\
			orl $0x3000,(%esp);\
			popf;");
	 int i=0;
/* 	 for(;i<80*25*2;i+=2)
 * 	 {
 * 	    asm("movb %%al, %%gs:(%%edx)"::"a"(' '),"d"(i));
 * 	 }
 * 	 fix_cursor(0);
 */
}
void move_to_top(int row)
{
   char* from=row*80*2;
   char* to=0;
	 char* end=80*25*2;
	 asm("cld;rep;movsw;"::"S"(from),"D"(to),"c"(end-from));
	 asm("loop1: movw %%ax,%%gs:(%%edi);\
			  add $2,%%edi;\
				loop loop1"::"D"(end-from),"c"(from),"a"(' '|color));
}
