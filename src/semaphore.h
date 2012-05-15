/*
 * =====================================================================================
 *
 *       Filename:  semaphore.h
 *
 *    Description:  kernel sync using semaphore
 *
 *        Version:  1.0
 *        Created:  2012年02月06日 17时02分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xie (), cuiweixie@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
struct wait_item {
	struct wait_list *next;
	struct wait_list *pre;
	struct task_struct *waitting;
};

struct semaphore{
	unsigned int count;
	struct wait_item *wait_list;
};
#endif
