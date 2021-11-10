#http://blog.pgxn.org/post/4783001135/extension-makefiles pg makefiles

EXTENSION = pgs2
PG_CONFIG ?= pg_config
DATA = $(wildcard *--*.sql)
PGXS := $(shell $(PG_CONFIG) --pgxs)
MODULE_big = pgs2
OBJS = libs2c.o $(patsubst %.c,%.o,$(wildcard src/pgs2.c))
PG_LDFLAGS = -lstdc++

TESTS        = $(wildcard test/sql/*.sql)
REGRESS      = $(patsubst test/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test --load-language=plpgsql
include $(PGXS)

libs2c.o:
	g++ -c -I./src -I./s2geometry/src src/s2c/s2c.cpp -o libs2c.o
