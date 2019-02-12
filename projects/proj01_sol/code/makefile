PROJECT_BUILD_PATH := ./build

# Set the include, source, and build directories for the library
PROJECT_LIBRARY_NAME ?= imageproc
PROJECT_LIBRARY_INCLUDE_PATH := ./include
PROJECT_LIBRARY_SOURCE_PATH := ./src
PROJECT_LIBRARY_BUILD_PATH := $(PROJECT_BUILD_PATH)/lib$(PROJECT_LIBRARY_NAME)
PROJECT_LIBRARY_PATH := ./lib

# Set the include, source, and build directories for the driver
PROJECT_APP_INCLUDE_PATH := ./apps
PROJECT_APP_SOURCE_PATH := ./apps
PROJECT_APP_BUILD_PATH := $(PROJECT_BUILD_PATH)/apps
PROJECT_APP_PATH := ./bin


# Choose the compiler and linker
CC = gcc
LD = gcc

#libpng
LIBPNG_INCLUDE_PATH := /usr/include/libpng
LIBPNG_PATH := /usr/lib/x86_64-linux-gnu
LIBPNG := png

#liblapacke
# The include and lib directories are system directories
LIBLAPACKE := lapacke

# Optimizations, only on if debug is off
OPT_FLAGS := -O3

# Turn on debug with `make DEBUG=1 <rule>`
DEBUG_FLAGS :=
ifneq ($(DEBUG),)
	DEBUG_FLAGS := -g -O0 -Wall
	OPT_FLAGS :=

endif 


INCL_PATHS := -I$(PROJECT_LIBRARY_INCLUDE_PATH) \
              -I$(LIBPNG_INCLUDE_PATH)

LD_PATHS := -L$(PROJECT_LIBRARY_PATH) \
            -L$(LIBPNG_PATH)

LIBS := -l$(PROJECT_LIBRARY_NAME) \
        -l$(LIBPNG) \
        -l$(LIBLAPACKE) -lm


CFLAGS := $(INCL_PATHS) $(DEBUG_FLAGS) $(OPT_FLAGS)
LDFLAGS := $(LD_PATHS) $(LIBS)

# Get all the c files from the source directory and build object names in the build directory
OBJECTS := $(patsubst %.c,%.o,$(wildcard $(PROJECT_LIBRARY_SOURCE_PATH)/*.c))
OBJECTS := $(subst $(PROJECT_LIBRARY_SOURCE_PATH),$(PROJECT_LIBRARY_BUILD_PATH),$(OBJECTS))

# Get all the applications from the apps directory
APPS := $(patsubst $(PROJECT_APP_SOURCE_PATH)/%.c,%,$(wildcard $(PROJECT_APP_SOURCE_PATH)/*.c))

all: project_lib $(APPS)

.DEFAULT:
	mkdir -p $(PROJECT_APP_BUILD_PATH)/$@
	$(CC) -c $(PROJECT_APP_SOURCE_PATH)/$@.c -o $(PROJECT_APP_BUILD_PATH)/$@.o $(CFLAGS)
	mkdir -p $(PROJECT_APP_PATH)
	$(LD) $(LDFLAGS) $(PROJECT_APP_BUILD_PATH)/$@.o  -o $(PROJECT_APP_PATH)/$@ $(LIBS)

$(PROJECT_LIBRARY_BUILD_PATH)/%.o: $(PROJECT_LIBRARY_SOURCE_PATH)/%.c
	mkdir -p $(PROJECT_LIBRARY_BUILD_PATH)
	$(CC) -c $< -o $@ $(CFLAGS)

project_lib: $(OBJECTS)
	mkdir -p $(PROJECT_LIBRARY_PATH)
	ar rcs $(PROJECT_LIBRARY_PATH)/lib$(PROJECT_LIBRARY_NAME).a $(OBJECTS)

clean:
	rm -rf $(PROJECT_BUILD_PATH)
	rm -rf $(PROJECT_LIBRARY_PATH)
	rm -rf $(PROJECT_APP_PATH)

