#ifndef _GDT_C_
#define  _GDT_C_
#include <sched.h>
/*
gdt:  Descriptor 0,0,0
seg_desc_code32: dd 0x0000ffff,0x00cf9a00
seg_desc_data:  dd  0x0000ffff,0x00cf9200
seg_desc_video: dd  0x8000ffff,0x0000920b
seg_desc_stack: dd  0x0000000f,0x00809201
*/
extern void Task0();
extern void Task1();
void init_gdt()
{
 lgdt(gdt_ptr);
 process[0].pid=0;
 process[0].state=TASK_RUNNING;
 process[0].n_gdt=4;
 process[0].tss=tss0;
 process[0].ldt[1]=ldt0[1];
 process[0].ldt[2]=ldt0[2];
 process[0].tss.eip=(u32)Task0;
 process[0].tss.esp0=process[0].kernel_stack+STACK_SIZE;
 set_ldt_seg(4,process[0].ldt);
 set_tss_seg(5,&process[0].tss);

 process[1].pid=1;
 process[1].state=TASK_RUNNING;
 process[1].n_gdt=6;
 process[1].tss=tss1;
 process[1].ldt[1]=ldt1[1];
 process[1].ldt[2]=ldt1[2];
 process[1].tss.eip=(u32)Task1;
 process[1].tss.esp0=process[1].kernel_stack+STACK_SIZE;
 set_ldt_seg(6,process[1].ldt);
 set_tss_seg(7,&process[1].tss);
 lldt(__LDT(0));
 ltr(__TSS(0));
 asm("movw %%ax,%%gs"::"a"(0x18));

}
#endif
