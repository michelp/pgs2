#include "pgs2.h"
PG_MODULE_MAGIC;

void error_callback(const char *msg) {
	ereport(ERROR,
			(errcode(ERRCODE_DATA_EXCEPTION),
             errmsg("S2 library exception: \"%s\"", msg)));
}

#include "pgs2cell.c"
#include "pgs2point.c"
#include "pgs2latlng.c"
#include "pgs2latlngrect.c"
#include "pgs2cap.c"
#include "pgs2cellunion.c"
#include "casts.c"

void
_PG_init(void)
{
}
