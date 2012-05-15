/*
 * =====================================================================================
 *
 *       Filename:  page.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年02月13日 16时23分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _PAGE_H_
#define _PAGE_H_
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

unsigned short int mm_map[PAGE_FRAMES];
void put_page(unsigned int ph_pg_addr,unsigned int lnr_pg_addr);
unsigned int kget_free_page();
void kfree_page(int ph_pg_addr);
#endif
