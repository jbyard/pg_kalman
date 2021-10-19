#include "dynamic.h"

int dynamicSystemInit(struct DynamicSystem **self) {

	if((*self = palloc(sizeof(struct DynamicSystem))) == NULL )
		return -1;

	(*self)->error      = 1;
	(*self)->previous   = 0;

	return 0;
}


float dynamicSystemEstimate( struct DynamicSystem **self, float measurement, float uncertainty ) {

	float estimation   = 0;

	float gain = (*self)->error / ( (*self)->error + uncertainty );

	(*self)->error = (1 - gain) * (*self)->error;

	estimation = (*self)->previous + gain * (measurement - (*self)->previous);

	(*self)->previous = estimation;

	return estimation;
}
