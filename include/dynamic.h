/*
 * dynamic.h
 *
 * A simple, one-dimensional dynamic system.
 */


#include "postgres.h"

#ifndef PG_KALMAN_DYNAMIC_H
#define PG_KALMAN_DYNAMIC_H

struct DynamicSystem {
	float   error;
	float   previous;
	float   variance;
};

int dynamicSystemInit( struct DynamicSystem **self );

float dynamicSystemEstimate( struct DynamicSystem **self, float measurement, float uncertainty );

#endif /* PG_KALMAN_DYNAMIC_H */
