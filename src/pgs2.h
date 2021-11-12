#ifndef PGS2_H
#define PGS2_H

#include "postgres.h"
#include "utils/builtins.h"
#include "libpq/pqformat.h"
#include "funcapi.h"
#include "access/htup_details.h"
#include "utils/array.h"
#include "utils/arrayaccess.h"
#include "catalog/pg_type_d.h"
#include "catalog/pg_type.h"
#include "utils/lsyscache.h"
#include "nodes/pg_list.h"
#include "utils/varlena.h"
#include "utils/float.h"
#include "lib/stringinfo.h"
#include "s2c/s2c.h"

#define DELIM       ','
#define LDELIM		'('
#define RDELIM		')'
#define LCURLY		'{'
#define RCURLY		'}'
#define COLON       ':'

void error_callback(const char *msg);

#include "pgs2cell.h"
#include "pgs2point.h"
#include "pgs2latlng.h"
#include "pgs2latlngrect.h"
#include "pgs2cap.h"
#include "casts.h"

void
_PG_init(void);

#endif /* PGS2_H */
