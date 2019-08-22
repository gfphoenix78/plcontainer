# plcontainer/src/Makefile

MODULE_big = plc_coordinator

EXTENSION = plc_coordinator
SRCDIR = ./
FILES = co_coordinator.c plc_configuration.c
OBJS = co_coordinator.o plc_configuration.o
SHLIB_LINK = $(libpq)

PGXS := $(shell pg_config --pgxs)
include $(PGXS)
