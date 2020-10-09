/*
 * pg_kalman.h
 *
 * A Kalman filter extension for PostgreSQL.
 */

#include "postgres.h"
#include "libpq-fe.h"
#include "fmgr.h"

#include <fcntl.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

struct StaticSystem {
	float   error;
	float   estimate;
	float   gain;
	float   previous;
};

int staticSystemInit(struct StaticSystem **obj);

PG_FUNCTION_INFO_V1(filterStaticSystem);
