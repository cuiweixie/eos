/*
 * =====================================================================================
 *
 *       Filename:  extern void asm_func.h(unsigned int error_code);
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年01月23日 20时45分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
extern void print_str(char *str,int len,int pos);
extern void print_str_stack(char *str,int len,int pos);
extern void *memcpy(void *dst,void *src,int len);
extern void *memset(void *p,int ch,int len);
extern void Init8259A();
//interrupts
extern void asm_div_error(unsigned int error_code);
extern void asm_debug(unsigned int error_code);
extern void asm_mon(unsigned int error_code);
extern void asm_breakpoint(unsigned int error_code);
extern void asm_overflow(unsigned int error_code);
extern void asm_overbound(unsigned int error_code);
extern void asm_undefine(unsigned int error_code);
extern void asm_nm(unsigned int error_code);
extern void asm_doublefault(unsigned int error_code);
extern void asm_cop(unsigned int error_code);
extern void asm_tss(unsigned int error_code);
extern void asm_seg_fault(unsigned int error_code);
extern void asm_stack_fault(unsigned int error_code);
extern void asm_general_protect(unsigned int error_code);
extern void asm_page_fault(unsigned int error_code);
extern void asm_reserve(unsigned int error_code);
extern void asm_fpu_error(unsigned int error_code);
extern void asm_align_check(unsigned int error_code);
extern void asm_machine_check(unsigned int error_code);
extern void asm_simd_fault(unsigned int error_code);
extern void asm_int_timer(unsigned int error_code);
extern void asm_int_keyboard(unsigned int error_code);
extern void asm_int_hd(unsigned int error_code);
extern void asm_sys_call();
