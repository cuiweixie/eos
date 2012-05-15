/*
 * =====================================================================================
 *
 *       Filename:  semaphore.c
 *
 *    Description:  semaphore operation
 *
 *        Version:  1.0
 *        Created:  2012年02月06日 17时15分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <sched.h>
extern struct wait_item wait_item_res[1024*2]={{0,0,0},};
extern struct semaphore sem_res[1024*2]={{0,0},};

void down(struct semaphore *sem)
{
	 cli();
   if(sem->count>0)
	 {
		 sem->count--;
		 return;
	 }
	 else
	 {
		 struct wait_item *wait=get_wait_item();
		 struct wait_item  *tail=sem->wait_list;
		 for(;tail->next!=0;tail=wait_list->next);
		 wait->pre=tail;
		 tail->next=wait;
		 wait->waitting=current;
		 current->state=TASK_UNITERRUPTIBLE;
	 sti();
	   
		 sleep_on_sem(sem);
	 }
}
