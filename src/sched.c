#include <sched.h>
#define NT  3
void schedule()
{

	int tmp=current;
	LOCK_INC(current,1);
	current=current%NT;
	if(tmp!=current)
	{
	switch_to(current);
	}
	else 
	{
		panic("try to jump to tss busy");
	}
}
