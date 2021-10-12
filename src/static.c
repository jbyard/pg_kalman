#include "static.h"

int staticSystemInit(struct StaticSystem **self, float variance) {

	if((*self = palloc(sizeof(struct StaticSystem))) == NULL )
		return -1;

	(*self)->error      = 1;
	(*self)->previous   = 0;
	(*self)->variance   = variance;

	return 0;
}

float staticSystemEstimate(struct StaticSystem **self, float observation) {

	float estimation   = 0;

	float gain = (*self)->error / ( (*self)->error + (*self)->variance );

	(*self)->error = (1 - gain) * (*self)->error;

	estimation = (*self)->previous + gain * (observation - (*self)->previous);

	/* This estimation becomes the previous for the next observation */
	(*self)->previous = estimation;

	return estimation;
}
