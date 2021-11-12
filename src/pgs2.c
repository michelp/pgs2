#include "pgs2.h"
PG_MODULE_MAGIC;

#include "pgs2cell.c"
#include "pgs2point.c"
#include "pgs2latlng.c"
#include "pgs2latlngrect.c"
#include "pgs2cap.c"
#include "casts.c"

void
_PG_init(void)
{
}
