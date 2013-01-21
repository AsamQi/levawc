# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.8 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C compiler 
CC = gcc

# Standard flags for CC 
CFLAGS ?= 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS ?= 

# Standard linker flags 
LDFLAGS ?= 

# Set to 1 to build debug version [0,1]
DEBUG ?= 0



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###

CPPDEPS = -MT$@ -MF$@.d -MD -MP
LEVAWC_CFLAGS = $(____DEBUG) $(____DEBUG_3) $(____DEBUG_1) $(____DEBUG_2) -I.\.. \
	$(CPPFLAGS) $(CFLAGS)
LEVAWC_OBJECTS =  \
	levawc_slist.o \
	levawc_dlist.o
DEMO1_CFLAGS = $(____DEBUG) $(____DEBUG_3) $(____DEBUG_1) $(____DEBUG_2) -I.\.. \
	$(CPPFLAGS) $(CFLAGS)
DEMO1_OBJECTS =  \
	demo1_demo1.o
DEMO2_CFLAGS = $(____DEBUG) $(____DEBUG_3) $(____DEBUG_1) $(____DEBUG_2) -I.\.. \
	$(CPPFLAGS) $(CFLAGS)
DEMO2_OBJECTS =  \
	demo2_demo2.o

### Conditionally set variables: ###

ifeq ($(DEBUG),0)
____DEBUG = -DNDEBUG
endif
ifeq ($(DEBUG),1)
____DEBUG = 
endif
ifeq ($(DEBUG),0)
____DEBUG_3 = -O2
endif
ifeq ($(DEBUG),1)
____DEBUG_3 = -O0
endif
ifeq ($(DEBUG),0)
____DEBUG_2 = 
endif
ifeq ($(DEBUG),1)
____DEBUG_2 = -W -Wall
endif
ifeq ($(DEBUG),0)
____DEBUG_1 = 
endif
ifeq ($(DEBUG),1)
____DEBUG_1 = -g
endif


### Targets: ###

all: liblevawc.a demo1.exe demo2.exe

clean: 
	-if exist .\*.o del .\*.o
	-if exist .\*.d del .\*.d
	-if exist liblevawc.a del liblevawc.a
	-if exist demo1.exe del demo1.exe
	-if exist demo2.exe del demo2.exe

liblevawc.a: $(LEVAWC_OBJECTS)
	if exist $@ del $@
	ar rcu $@ $(LEVAWC_OBJECTS)
	ranlib $@

demo1.exe: $(DEMO1_OBJECTS) liblevawc.a
	$(CC) -o $@ $(DEMO1_OBJECTS)  $(____DEBUG_1) $(LDFLAGS)  liblevawc.a

demo2.exe: $(DEMO2_OBJECTS) liblevawc.a
	$(CC) -o $@ $(DEMO2_OBJECTS)  $(____DEBUG_1) $(LDFLAGS)  liblevawc.a

levawc_slist.o: ./../slist.c
	$(CC) -c -o $@ $(LEVAWC_CFLAGS) $(CPPDEPS) $<

levawc_dlist.o: ./../dlist.c
	$(CC) -c -o $@ $(LEVAWC_CFLAGS) $(CPPDEPS) $<

demo1_demo1.o: ./demo1.c
	$(CC) -c -o $@ $(DEMO1_CFLAGS) $(CPPDEPS) $<

demo2_demo2.o: ./demo2.c
	$(CC) -c -o $@ $(DEMO2_CFLAGS) $(CPPDEPS) $<

.PHONY: all clean


SHELL := $(COMSPEC)

# Dependencies tracking:
-include ./*.d