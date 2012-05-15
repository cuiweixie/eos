#include <sched.h>
#define NT  3
void schedule()
{
	int tmp=current;
	LOCK_INC(current,1);
	current=current%NT;
	switch_to(current);
	panic("try to jump to tss busy");
}
