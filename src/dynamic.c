#include "dynamic.h"

int dynamicSystemInit(struct DynamicSystem **self) {

	if((*self = palloc(sizeof(struct DynamicSystem))) == NULL )
		return -1;

	return 0;
}


float dynamicSystemEstimate( struct DynamicSystem **self ) {

	return 0;
}
