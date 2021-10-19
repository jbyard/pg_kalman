/*
 * pg_kalman.h
 *
 * A Kalman filter extension for PostgreSQL.
 */

#include "postgres.h"
#include "libpq-fe.h"
#include "fmgr.h"

#include <fcntl.h>

#include "static.h"
#include "dynamic.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(filterStaticSystem);
PG_FUNCTION_INFO_V1(filterDynamicSystem);
