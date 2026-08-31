#include "pthread_utils.h"


int pthread_create_detached(void* (*func)(void*), void* arg)
{
	pthread_t id;
	pthread_attr_t attr;
	int retval = pthread_attr_init(&attr);
	if(retval == 0)
	{
		retval = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		if(retval == 0)
		{
			retval = pthread_create(&id, &attr, func, arg);
		}
		pthread_attr_destroy(&attr);
	}
	return retval;
}
