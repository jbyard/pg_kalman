#include "pg_kalman.h"

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


/* Filter a single dimension */
Datum filterStaticSystem(PG_FUNCTION_ARGS) {

	struct StaticSystem *stash;
	MemoryContext old_context;

	float observation   = PG_GETARG_FLOAT8(0);
	float variance      = PG_GETARG_FLOAT8(1);

	/* Initialize a staticSystem object in a shared, function memory context */
	if (fcinfo->flinfo->fn_extra == NULL) {

		old_context = MemoryContextSwitchTo(fcinfo->flinfo->fn_mcxt);

		if (staticSystemInit(&stash, variance) != 0) {
			elog(ERROR,"Could not allocate object");				
		}

		MemoryContextSwitchTo(old_context);
		fcinfo->flinfo->fn_extra = stash;
	}

	/* Use our stashed object from the function memory context */
	stash = fcinfo->flinfo->fn_extra;

	PG_RETURN_FLOAT8(staticSystemEstimate(&stash, observation));
}
