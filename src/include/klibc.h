#ifndef _KLIBC_H_
#define _KLIBC_H_
#ifndef u8 
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned short int
#endif
#ifndef u32
#define u32 unsigned int
#endif
#define _debug asm("int $0x3")
extern char *itoa(char* my_buffer,unsigned long int n);
extern char *itoah(char *buffer,unsigned long int n,int len);
extern int strcpy(char *dst,char *src,int size);
extern int strcmp(char *str1,char * str2,int n);
extern int printf(char *fmt,...);
extern int sprintf(char *str,char *fmt,...);
#define  in_byte(port)\
({\
	unsigned char data;\
	asm("inb %%dx,%%al\n"\
		"nop\n"\
		"nop\n"\
		"nop\n"\
		"nop\n"\
			:"=a"(data)\
			:"d"(port));\
 data;\
 })
#define  out_byte(port,data)\
({\
	asm("outb %%al,%%dx\n"\
		"nop\n"\
		"nop\n"\
		"nop\n"\
		"nop\n"\
			::"d"(port),"a"(data));\
})
#define INT_M 0x21
#define INT_S 0xa1
#define INT_TIMER 0
#define INT_KEYBOARD 1
#define INT_HD     0xe
#define enable_irq(n) ({\
		u8 _m=in_byte(INT_M);\
		u8 _s=in_byte(INT_S);\
		u16 mask=_m|(_s<<8);\
		mask&=~(1<<n);\
		_m=mask; _s=mask>>8;\
		out_byte(INT_M,_m);\
		out_byte(INT_S,_s);\
		})
#define disable_irq(n) ({\
	  u8 _m=in_byte(INT_M);\
		u8 _s=in_byte(INT_S);\
		u16 mask=_m|(_s<<8);\
		mask|=(1<<n);\
		_m=mask; _s=mask>>8;\
		out_byte(INT_M,_m);\
		out_byte(INT_S,_s);\
		})

#define show_ch(pos,ch) ({\
		asm("movw %%ax,%%gs:(%1)"\
			::"a"(ch),"d"((pos)*2));\
      })
#define show_str(p,str) ({\
		char *_tmp=(char *)str;int pos=p;short int ch;\
		while(*_tmp!='\0')\
		{\
		  ch=*_tmp|0x0c00;\
		  show_ch(pos,ch);_tmp++,pos+=1;\  
		}\
		})
extern inline void wait_time(int sec);
#define  set_cursor(pos) \
{\
	unsigned short position=pos;\
	out_byte(0x3d4,0x0f);\
	out_byte(0x3d5,(position&0xff));\
	out_byte(0x3d4,0x0e);\
	position=position>>8;\
	out_byte(0x3d5,(position&0xff));\
}
extern int pos_panic;
#endif
