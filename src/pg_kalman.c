#include "pg_kalman.h"

/* Filter a static system. */
Datum filterStaticSystem(PG_FUNCTION_ARGS) {

	struct StaticSystem *stash;
	MemoryContext old_context;

	float observation   = PG_GETARG_FLOAT8(0);
	float variance      = PG_GETARG_FLOAT8(1);

	/* Initialize a StaticSystem state object in the function memory context. */
	if (fcinfo->flinfo->fn_extra == NULL) {

		old_context = MemoryContextSwitchTo(fcinfo->flinfo->fn_mcxt);

		if (staticSystemInit(&stash, variance) != 0) {
			elog(ERROR,"Could not allocate object");				
		}

		MemoryContextSwitchTo(old_context);
		fcinfo->flinfo->fn_extra = stash;
	}

	/* Use the state object from the function memory context for each row. */
	stash = fcinfo->flinfo->fn_extra;

	PG_RETURN_FLOAT8(staticSystemEstimate(&stash, observation));
}


/* Filter a one-dimensional, dynamic system. */
Datum filterDynamicSystem(PG_FUNCTION_ARGS) {

	struct DynamicSystem *stash;
	MemoryContext old_context;

	float position   = PG_GETARG_FLOAT8(0);
	float velocity   = PG_GETARG_FLOAT8(1);

	/* Initialize a DynamicSystem state object in the function memory context. */
	if (fcinfo->flinfo->fn_extra == NULL) {

		old_context = MemoryContextSwitchTo(fcinfo->flinfo->fn_mcxt);

		if (dynamicSystemInit(&stash) != 0) {
			elog(ERROR,"Could not allocate object");
		}

		MemoryContextSwitchTo(old_context);
		fcinfo->flinfo->fn_extra = stash;
	}

	/* Use the state object from the function memory context for each row. */
	stash = fcinfo->flinfo->fn_extra;

	PG_RETURN_FLOAT8(dynamicSystemEstimate(&stash));
}
