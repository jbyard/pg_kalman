#include "dynamic.h"

int dynamicSystemInit(struct DynamicSystem **self) {

	if((*self = palloc(sizeof(struct DynamicSystem))) == NULL )
		return -1;

	(*self)->alpha          = 0.5;
	(*self)->beta           = 0.4;
	(*self)->gamma          = 0.1;

	(*self)->predicted      = 0;
	(*self)->velocity       = 0;
	(*self)->acceleration   = 0;

	return 0;
}


float dynamicSystemEstimate( struct DynamicSystem **self, float measurement, float uncertainty ) {

	/* State update */
	float estimation = (*self)->predicted + (*self)->alpha * (measurement - (*self)->predicted);
	float velocity = (*self)->velocity + (*self)->beta * (measurement - (*self)->predicted);
	float acceleration = (*self)->acceleration + (*self)->gamma * ((measurement - (*self)->predicted) / 0.5 );

	/* State extrapolation */
	(*self)->predicted = estimation + velocity + (acceleration * 0.5);
	(*self)->velocity = velocity + acceleration;
	(*self)->acceleration = acceleration;

	return estimation;
}
