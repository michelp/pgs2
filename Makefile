#http://blog.pgxn.org/post/4783001135/extension-makefiles pg makefiles

EXTENSION = pgs2
PG_CONFIG ?= pg_config
DATA = $(wildcard *--*.sql)
PGXS := $(shell $(PG_CONFIG) --pgxs)
MODULE_big = pgs2
OBJS = $(patsubst %.c,%.o,$(wildcard src/pgs2.c))
PG_CPPFLAGS = -O0

TESTS        = $(wildcard test/sql/*.sql)
REGRESS      = $(patsubst test/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test --load-language=plpgsql
include $(PGXS)

sql: pgs2--0.0.1.sql
	bash pgs2--0.0.1-gen.sql.sh
