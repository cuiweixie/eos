#ifndef _MM_H_
#define __MM_H_
#include <sched.h>
#include <klibc.h>
#define MM_SIZE  (1<<25)
#define SYSTEM_MM (4<<20)
#define PAGE_SIZE (1<<12)
#define SYSTEM_PAGES (SYSTE_MM/PAGE_SIZE)
#define PAGE_FRAMES (MM_SIZE/PAGE_SIZE)
#define PDE_SIZE 8
#define PTE_SIZE 1024
#ifndef u32
#define u32 unsigned int
#endif
unsigned short int mm_map[PAGE_FRAMES]={0,};
u32 *pde;
u32 *pte;
u32 *u_pde;
u32 *u_pte;
#define PG_ATTR_AVL 0x000008000
#define PG_ATTR_4K  0x000000000
#define PG_ATTR_ACCESS 0x00000040
void init_page()
{
  pte=0x1ff8000;// mm size: 32M pde item: 8 total pte size:32k 
  pde=0x1ff0000;
	int i=0,j=0;
	/*for(i=0;i<PDE_SIZE;i++)
	{
		*(pde+i)=((u32)pte+(i<<12))|0x003;
  for( j=0;j<PTE_SIZE;j++)
	{
		*(pte+(i<<10)+j)=((i<<22)+(j<<12))|0x003;
	}
	}*/
  u_pte=0x1fe8000;// mm size: 32M pde item: 8 total pte size:32k 
  u_pde=0x1fe0000;
	u32 tmp=0;
	for(i=0;i<PDE_SIZE;i++)
	{
		u_pde[i]=(u32)(&u_pte[i<<10])|0x007;
  for( j=0;j<PTE_SIZE;j++)
	{
		u_pte[(i<<10)+j]=tmp|0x007;
		tmp+=1<<12;
	}
	}
	set_page_dir(u_pde);
	asm("mov %cr0,%eax;\
			 orl 0x80000000,%eax;\
			 mov %eax,%cr0");
	for(i=256;i<256*3;i++)
	{
		mm_map[i]=0xff;
	}
}
int *get_pde_by_vir(unsigned int addr)
{
    register unsigned int cr3 asm("eax");
		asm("movl %cr3,%eax");
		return cr3+(addr>>22)<<2;
}
int pos_page_fault=40;
void do_page_fault(unsigned int error_code)
{
	show_str(pos_page_fault,"page fault occur!");
	pos_page_fault+=20;
	u_pde[1]|=1;
}
void put_page(unsigned int ph_pg_addr,unsigned int lnr_pg_addr)
{
	u32 *pg_dir_base,*pg_dir=(int *)((lnr_pg_addr>>20)&0xffc),*pg_frm=((lnr_pg_addr>>10)&0xffc);
	asm("movl %%cr3,%%eax;":"=a"(pg_dir_base));
	pg_dir=pg_dir_base+(u32)pg_dir;
	pg_frm=((*pg_dir)&(~0xfff))+pg_frm;
  *pg_frm=ph_pg_addr;
}
unsigned int kget_free_page()
{
  int i=256*3;
  for(;i<256*4;i++)
	{
		if(mm_map[i]==0)
			return i<<12;
	}
panic("run out of kernel dynamic memory!");
}
void kfree_page(int ph_pg_addr)
{
   int i=ph_pg_addr>>12;
	 if(i>=256*3&&i<256*4)
	 {
		 if(mm_map[i]--)return;
		 else
			 panic("try to free a free page");
	 }
	 else 
		 panic("not a dynamic memory");
}
#endif
