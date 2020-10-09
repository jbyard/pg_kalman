#include "pg_kalman.h"

int staticSystemInit(struct StaticSystem **obj) {

	if((*obj = palloc(sizeof(struct StaticSystem))) == NULL )
		return -1;

	(*obj)->error      = 0;
	(*obj)->estimate   = 0;
	(*obj)->gain       = 0;
	(*obj)->previous   = 0;

	return 0;
}


/* Filter a single dimension */
Datum filterStaticSystem(PG_FUNCTION_ARGS) {

	struct StaticSystem *stash;
	MemoryContext old_context;

	float observation   = PG_GETARG_FLOAT8(0);
	float variance      = PG_GETARG_FLOAT8(1);
	float estimation    = 0;

	/* Initialize a staticSystem object in a shared, function memory context */
	if (fcinfo->flinfo->fn_extra == NULL) {

		old_context = MemoryContextSwitchTo(fcinfo->flinfo->fn_mcxt);

		if (staticSystemInit(&stash) != 0) {
			elog(ERROR,"Could not allocate object");				
		}

		MemoryContextSwitchTo(old_context);
		fcinfo->flinfo->fn_extra = stash;
	}

	/* Use our stashed object from the function memory context */
	stash = fcinfo->flinfo->fn_extra;

	/* Make our estimation */ 
	stash->gain = stash->previous / ( stash->previous + variance );
	estimation = stash->previous + (stash->gain * (observation - stash->previous));

	/* This observation becomes the previous for the next */
	stash->previous = observation;

	PG_RETURN_FLOAT8(estimation);
}
