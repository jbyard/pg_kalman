/*
 * dynamic.h
 *
 * A simple, one-dimensional dynamic system.
 */


#include "postgres.h"

#ifndef PG_KALMAN_DYNAMIC_H
#define PG_KALMAN_DYNAMIC_H

struct DynamicSystem {

};

int dynamicSystemInit( struct DynamicSystem **self );

float dynamicSystemEstimate( struct DynamicSystem **self );

#endif /* PG_KALMAN_DYNAMIC_H */
