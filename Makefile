# contrib/srf/Makefile

MODULES = srf

EXTENSION = srf
DATA = srf--1.0.sql
PGFILEDESC = "srf - set returning function test"

REGRESS = srf

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
