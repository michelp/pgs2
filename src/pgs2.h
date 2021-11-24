#ifndef PGS2_H
#define PGS2_H

#include <math.h>
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

#define DELIM ','
#define LPAREN '('
#define RPAREN ')'
#define LCURLY '{'
#define RCURLY '}'
#define COLON ':'

#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians)*180.0 / M_PI)

void error_callback(const char *msg);

#include "s2types.h"
#include "pgs2cell.h"
#include "pgs2point.h"
#include "pgs2latlng.h"
#include "pgs2latlngrect.h"
#include "pgs2cap.h"
#include "pgs2cellunion.h"
#include "casts.h"

void _PG_init(void);

#endif /* PGS2_H */
