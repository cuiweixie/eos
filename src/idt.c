#ifndef _IDT_C_
#define  _IDT_C_
#include <klibc.h>
#include <sched.h>
#include <asm_func.h>
#include <time.h>
#include <hd.h>
unsigned long long int _tick=0;
//#define print_intr(pos,str) print_str(str,sizeof(str),pos)
#define print_intr(pos,str) show_str(pos,str)
//#DE vector 0
void do_div_error(unsigned int error_code);
//#DB vector 1
void do_debug(unsigned int error_code);
//no monster int vector 2
void do_nom(){}
//BP breakpoint vector 3
void do_breakpoint(unsigned int error_code);
//#OF overflow vector 4
void do_overflow(unsigned int error_code);
//#BR overbound vector 5
void do_overbound(unsigned int error_code);
//#UD undefine opcode vector 6
void do_undefine(unsigned int error_code);
//#NM device no found vector 7
void do_nm(unsigned int error_code);
//#DF vector 8
void do_doublefault(unsigned int error_code);
// coprocessor segment overflow vector 9
void do_cop(unsigned int error_code);
//#TS invalid tss vector 10
void do_tss(unsigned int error_code);
//#NP segment no present vector 11
void do_seg_fault(unsigned int error_code);
//#SS  stack segment fault vector 12
void do_stack_fault(unsigned int error_code);
//#GP  general protect vector 13 
void do_general_protect(unsigned int error_code);
//#PF page fault vector 14
extern void do_page_fault(unsigned int error_code);
//#reserve vector 15
void do_reserve(){}
//#MF x87 fpu error vector 16
void do_fpu_error(unsigned int error_code);
//#AC align fault vector 17
void do_align_check(unsigned int error_code);
//#MC machine check  vector 18
void do_machine_check(unsigned int error_code);
//#Xf vector 19
void do_simd_fault(unsigned int error_code);
//20~31 is reserved by intel
//timer interrupt vector 32 0x20
void do_int_timer(unsigned int error_code);
//keyboard interrupt vector 33
extern void do_int_keyboard(unsigned int error_code);
//hardisk interrupt vector 0x2e
void do_int_hd(unsigned int error_code);
unsigned int handlers[255]={
(unsigned int) asm_div_error,
(unsigned int) asm_debug,
(unsigned int) asm_mon,
(unsigned int) asm_breakpoint,
(unsigned int) asm_overflow,
(unsigned int) asm_overbound,
(unsigned int) asm_undefine,
(unsigned int) asm_nm,
(unsigned int) asm_doublefault,
(unsigned int) asm_cop,
(unsigned int) asm_tss,
(unsigned int) asm_seg_fault,
(unsigned int) asm_stack_fault,
(unsigned int) asm_general_protect,
(unsigned int) asm_page_fault,
(unsigned int) asm_reserve,
(unsigned int) asm_fpu_error,
(unsigned int) asm_align_check,
(unsigned int) asm_machine_check,
(unsigned int) asm_simd_fault,
};
void init_idt()
{
	// 0x20~0x27 IRQ0-ORQ7 0x28~0x2f IRQ8~IRQ15
	handlers[0x20]=(u32)asm_int_timer;
	handlers[0x21]=(u32)asm_int_keyboard;
	handlers[0x2e]=(u32)asm_int_hd;
  Init8259A();
	int i;
	for(i=0x30;i<0xff;i++,handlers[i]=(u32)asm_general_handler);
	for(i=0;i<256;i++)
	{
		set_intr_gate(i,handlers[i]);
	}
	set_dpl(idt[0x3],3);
	set_dpl(idt[0xab],3);
  set_irq_handler(0xab,(unsigned int)asm_sys_call);
	lidt(idt_ptr);
	out_byte(0x21,0xff);
	out_byte(0xa1,0xff);
}

int p_int=0;
#define next_line(p) (p=p+20)
//#DE vector 0
void do_div_error(unsigned int error_code)
{
print_intr(p_int,"div_error occur!");
next_line(p_int);
}
//#DB vector 1
void do_debug (unsigned int error_code)
{
print_intr(p_int,"do_debug ocurr");
next_line(p_int);
}
//no monster int vector 2
//BP breakpoint vector 3
void do_breakpoint (unsigned int error_code)
{
//print_intr(p_int,"do_breakpoint ocurr");
//next_line(p_int);
}
//#OF overflow vector 4
void do_overflow (unsigned int error_code)
{
print_intr(p_int,"do_overflow ocurr");
next_line(p_int);
}
//#BR overbound vector 5
void do_overbound (unsigned int error_code)
{
print_intr(p_int,"do_overbound ocurr");
next_line(p_int);
}
//#UD undefine opcode vector 6
void do_undefine (unsigned int error_code)
{
print_intr(p_int,"do_undefine ocurr");
next_line(p_int);
}
//#NM device no found vector 7
void do_nm (unsigned int error_code)
{
print_intr(p_int,"do_nm ocurr");
next_line(p_int);
}
//#DF vector 8
void do_doublefault (unsigned int error_code)
{
print_intr(p_int,"do_doublefault ocurr");
next_line(p_int);
}
// coprocessor segment overflow vector 9
void do_cop (unsigned int error_code)
{
print_intr(p_int,"do_cop ocurr");
next_line(p_int);
}
//#TS invalid tss vector 10
void do_tss (unsigned int error_code)
{
print_intr(p_int,"do_tss ocurr");
next_line(p_int);
}
//#NP segment no present vector 11
void do_seg_fault (unsigned int error_code)
{
print_intr(p_int,"do_seg_fault ocurr");
next_line(p_int);
}
//#SS  stack segment fault vector 12
void do_stack_fault (unsigned int error_code)
{
print_intr(p_int,"do_stack_fault ocurr");
next_line(p_int);
}
//#GP  general protect vector 13 
void do_general_protect (unsigned int error_code)
{
print_intr(p_int,"do_general_protect ocurr");
next_line(p_int);
}
//#PF page fault vector 14
void do_page_fault (unsigned int error_code);
//#reserve vector 15
//#MF x87 fpu error vector 16
void do_fpu_error (unsigned int error_code)
{
print_intr(p_int,"do_fpu_error ocurr");
next_line(p_int);
}
//#AC align fault vector 17
void do_align_check (unsigned int error_code)
{
print_intr(p_int,"do_align_check ocurr");
next_line(p_int);
}
//#MC machine check  vector 18
void do_machine_check (unsigned int error_code)
{
print_intr(p_int,"do_machine_check ocurr");
next_line(p_int);
}
//#Xf vector 19
void do_simd_fault (unsigned int error_code)
{
print_intr(p_int,"do_simd_fault ocurr");
next_line(p_int);
}
//20~31 is reserved by intel
//timer interrupt vector 32 0x20
void do_int_timer (unsigned int error_code)
{
print_intr(p_int,"do_int_timer ocurr");
next_line(p_int);

 _tick++;
 schedule();
}
//keyboard interrupt vector 33
//hardisk interrupt vector 0x2e
char hd_buf[1024];
void do_int_hd (unsigned int error_code)
{
show_str(p_int,"do_int_hd ocurr");
read_sector(hd_buf);
out_byte(0x20,0x20);
out_byte(0xa0,0x20);
next_line(p_int);
}
#define _CALL_CURSOR  1
void sys_call(int eax,int ebx,int ecx,int edx)
{
	if(eax==_CALL_CURSOR)
		set_cursor(ebx);
}
#endif

