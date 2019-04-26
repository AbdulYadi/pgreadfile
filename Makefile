MODULE_big = pgreadfile
OBJS = pgreadfile.o
EXTENSION = pgreadfile
DATA = pgreadfile--1.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)
