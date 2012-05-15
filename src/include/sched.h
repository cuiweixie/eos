/*
 * =====================================================================================
 *
 *       Filename:  sched.h
 *
 *    Description: process management  
 *
 *        Version:  1.0
 *        Created:  2012年01月23日 20时21分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _SCHED_H_
#define _SCHED_H_
#ifndef u8 
#define u8 unsigned char
#endif
#ifndef u16
#define u16 unsigned short int
#endif
#ifndef u32
#define u32 unsigned int
#endif
#define pu8(p) ((u8*)(p))
#define pu16(p) ((u16*)(p))
#define pu32(p) ((u32*)(p))
#define lgdt(p) asm("lgdtl (%%eax)"::"a"(p))
#define sgdt(p) asm("sgdtl (%%eax)"::"a"(p))
#define lidt(p) asm("lidtl (%%eax)"::"a"(p))
#define sidt(p) asm("sidtl (%%eax)"::"a"(p))
#define lldt(p) asm("lldt %%ax"::"a"(p))
#define sldt(p) asm("sldt (%%eax)"::"a"(p))
#define ltr(selector) asm("ltr %%ax"::"a"(selector))
#define str(selector) asm("str %%ax"::"a"(selector))
#define set_page_dir(p) asm("movl %%eax,%%cr3"::"a"(p))
#define lsl(selector)  asm("lsl %%eax,%1":"=a":"m"(selector))
#define switch_to_user(cs,eip,ss,esp) \
	asm("clts;\
			pushl %0;\
			pushl %1;\
			pushfl;\
			pushl %2;\
			pushl %3;\
			iret"::"a"(ss),"b"(esp),"c"(cs),"d"(eip))
#define set_esp(esp) asm("mov %0,%%esp"::"a"(esp))
#define set_ebp(esp) asm("mov %0,%%ebp"::"a"(ebp))

#define set_dpl(desc,dpl) ({u8*p=(((u8*)(&desc))+5) ;*p|=(dpl<<5);})
#define __set_gate(gate,selector,offset,attr) asm("movw %%bx,(%%eax);\
			add $2,%%eax;\
			movw %%cx,(%%eax);\
			add $2,%%eax;\
			movw %%dx,(%%eax);\
			add $2,%%eax;\
			shr $16,%%ebx;\
			movw %%bx,(%%eax)"::"a"(&gate),"b"(offset),"c"(selector),"d"(attr))
	#define set_intr_gate(n,func) __set_gate(idt[n],0x08,func,0x8e00)
#define set_trap_gate(n,func) __set_gate(idt[n],0x08,func,0x8f00)
#define set_irq_handler(n,handler) ({ idt[n].offset_l=handler,\
		idt[n].offset_h=(handler>>16);})

#define __set_desc(gdt,base,limit,attr) asm("cli;\
		      movw %%cx,(%%eax);\
		      add $2,%%eax;\
		      movw %%bx,(%%eax);\
		      add $2,%%eax;\
		      shr $16,%%ebx;\
		      movb %%bl,(%%eax);\
		      add $1,%%eax;\
					movw %%dx,(%%eax);\
					add $2,%%eax;\
					movb %%bh,(%%eax);\
					sti"\
					::"a"(&gdt),"b"(base),"c"(limit),"d"((attr)&0xf0ff|(((limit)&0xf0000)>>8)))
#define set_ldt_seg(n,base) __set_desc(gdt[n],(u32)base,0xfffff,0xc0e2)
#define set_tss_seg(n,base) __set_desc(gdt[n],(u32)base,104,0x00e9)
#define set_desc_base(desc,base) ({\
		u16 *p=&(desc);\
		*p=base&0xffff;\
		p+=2;\
		*((u8*)p)=(((base)>>16)&0xff);\
		p++;\
		*((u8*)p)=(((base)>>24)&0xff);\
   })

 struct descriptor{
  u16 limit_l;
	u16 base_l;
	u16 base_m:8;
	u16 type:4;
	u16 s:1;
	u16 dpl:2;
	u16 p:1;
	u16 limit_h:4;
	u16 attr_h:4;
	u16 base_h:8;
} __attribute__ ((aligned(8)));
#define __CODE_SEG_DESC {\
/*limit 0~15*/	0xffff,\
/* base 0~15 */  0x0000,\
/* base 16~23 */	0x00,\
/* type 4bits*/   0xa,\
/*system 1 bit, 1 for code/data segement,0 for system seg */  0x1,\
/* dpl 2bits */   0x0,\
/*present 1bit*/ 0x1,\
/* limit 16~19 */0xf,\
/* attr high 4 bits*/0xc,\
	/*base high 4 bits*/0x0\
}
#define __DATA_SEG_DESC {\
/*limit 0~15*/	0xffff,\
/* base 0~15 */  0x0000,\
/* base 16~23 */	0x00,\
/* type 4bits*/   0x2,\
/*system 1 bit, 1 for code/data segement,0 for system seg */  0x1,\
/* dpl 2bits */   0x0,\
/*present 1bit*/ 0x1,\
/* limit 16~19 */0xf,\
/* attr high 4 bits*/0xc,\
	/*base high 4 bits*/0x0\
}
#define __VIDEO_SEG_DESC {\
/*limit 0~15*/	0xffff,\
/* base 0~15 */  0x8000,\
/* base 16~23 */	0x0b,\
/* type 4bits*/   0x2,\
/*system 1 bit, 1 for code/data segement,0 for system seg */  0x1,\
/* dpl 2bits */   0x3,\
/*present 1bit*/ 0x1,\
/* limit 16~19 */0x0,\
/* attr high 4 bits*/0xc,\
	/*base high 4 bits*/0x0\
}
#define __TASK0_LDT_SEG_DESC {\
/*limit 0~15*/	0xffff,\
/* base 0~15 */  0x0000,\
/* base 16~23 */	0x00,\
/* type 4bits*/   0x2,\
/*system 1 bit, 1 for code/data segement,0 for system seg */  0x0,\
/* dpl 2bits */   0x3,\
/*present 1bit*/ 0x1,\
/* limit 16~19 */0x0,\
/* attr high 4 bits*/0x0,\
	/*base high 4 bits*/0x0\
}

struct tss{
	u32 ex_tss;
	u32 esp0,ss0,esp1,ss1,esp2,ss2;
	u32 cr3,eip,eflags,eax,ecx,edx,ebx,esp,ebp,esi,edi;
	u32 es,cs,ss,ds,fs,gs,ldt,io_base;
} __attribute__ ((aligned(4)));
struct gate{
	u16 offset_l;
  u16 selector;
	u16 p_count:5;
	u16 res:3;
	u16 type:4;
	u16 s:1;
	u16 dpl:2;
	u16 p:1;
	u16 offset_h;
} __attribute__ ((aligned(8)));
#define TASK_RUNNING 0
#define TASK_INTERRUPTABLE 2
#define TASK_UNINTERRUPTABLE 4
#define TASK_STOP    8
#define GDT_SIZE 255
#define IDT_SIZE 255
extern u8 gdt_ptr[6];
extern struct descriptor gdt[GDT_SIZE],ldt0[3],ldt1[3];
extern struct tss tss0,tss1;
extern u8 gdt_ptr[6];
extern u8 idt_ptr[8];
extern struct gate idt[IDT_SIZE];
extern void asm_general_handler();
#define STACK_SIZE 1024
struct task_struct {
u32 pid;
u32 n_gdt;
u32 state;
u32 slice_used;
u32 slice_left;
u32 priority;
u32 signal;
u16 tss_selector;
struct tss tss;
u16 ldt_selector;
struct descriptor ldt[4];
u8 kernel_stack[STACK_SIZE];
u8 user_stack[STACK_SIZE];
};
#define FIRST_TSS_ENTRY  5
#define FIRST_LDT_ENTRY  4
#define __TSS(n) ((((u32)n)<<4)+(FIRST_TSS_ENTRY<<3))
#define __LDT(n) ((((u32)n)<<4)+(FIRST_LDT_ENTRY<<3))
#define MAX_PROC 128
extern u32 current;
struct task_struct process[MAX_PROC];
#define sti() asm("sti")
#define cli() asm("cli")
#define switch_to(n) ({\
		    struct { long a,b;}__tmp;\
				asm("mov %%dx,%1\n"\
					"ljmp *%0;"\
					::"m"(*&__tmp.a),"m"(*&__tmp.b),"d"(__TSS(n)));\
		})
#define LOCK_INC(a,i) asm("lock;add %1,%0"::"m"(a),"i"(i))
#define __startup_process(n_gdt,_pid,i,_eip) {\
	process[i].ldt[1]=process[1].ldt[1];\
	process[i].ldt[2]=process[1].ldt[2];\
	process[i].tss=process[1].tss;\
	process[i].tss.eip=_eip;\
	process[i].tss.esp0=process[i].kernel_stack+STACK_SIZE;\
	process[i].tss.esp=process[i].user_stack+STACK_SIZE;\
	set_ldt_seg(n_gdt,process[i].ldt);\
	set_tss_seg(n_gdt+1,&process[i].tss);\
	process[i].pid=_pid;\
	process[i].state=TASK_RUNNING;\
}
#endif
