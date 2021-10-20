/*
 * dynamic.h
 *
 * Filter a simple, one-dimensional dynamic system.  More of a Alpha/Beta/Gamma
 * filter than a Kalman filter.
 */


#include "postgres.h"

#ifndef PG_KALMAN_DYNAMIC_H
#define PG_KALMAN_DYNAMIC_H

struct DynamicSystem {
	float   alpha;
	float   beta;
	float   gamma;
	float   predicted;
	float   velocity;
	float   acceleration;
};

int dynamicSystemInit( struct DynamicSystem **self );

float dynamicSystemEstimate( struct DynamicSystem **self, float measurement, float uncertainty );

#endif /* PG_KALMAN_DYNAMIC_H */
