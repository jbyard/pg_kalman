#include "pg_kalman.h"

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
