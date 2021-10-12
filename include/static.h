/*
 * static.h
 *
 * A simple, one-dimensional static system.
 */

#include "postgres.h"

#ifndef PG_KALMAN_STATIC_H
#define PG_KALMAN_STATIC_H

struct StaticSystem {
	float   error;
	float   previous;
	float   variance;
};

int staticSystemInit(struct StaticSystem **obj, float variance);

float staticSystemEstimate(struct StaticSystem **obj, float observation);

#endif /* PG_KALMAN_STATIC_H */
