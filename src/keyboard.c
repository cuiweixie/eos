/*
 * =====================================================================================
 *
 *       Filename:  keyboard.c
 *
 *    Description:  handle the keyboard input 
 *
 *        Version:  1.0
 *        Created:  2012年02月04日 21时11分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include	<keyboard.h>
#include	<klibc.h>
#define u32 unsigned int
#define X  25
#define Y  80
unsigned int *screen=0xb8000;
int p_out=0;
struct keyboard_buf  keyboard_buf={{'\0',},0,0,0};
void do_int_keyboard(unsigned int error_code)
{
	 unsigned short ch_scan=in_byte(0x60);
	 if(keyboard_buf.count<1024)
	 {
	   keyboard_buf.buf[(++keyboard_buf.head)%1024]=(char)ch_scan;
	   keyboard_buf.count++;
	 }
out_byte(0x20,0x20);
}

