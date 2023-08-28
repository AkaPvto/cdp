##################################
# 	MACROS
##################################

# $(1) : Compiler 
# $(2) : Object file to generate (*.o)
# $(3) : Source file (*.c, *.cpp)
# $(4) : Additional dependencies (*.h, *.hpp)
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

define C2O		# Turns source files into object files
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H		# Turns source files into header files
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

##################################
# 	CONFIG
##################################

APP 	:= collisions
CCFLAGS := -Wall -pedantic
CFLAGS	:= $(CCFLAGS)-std=c++20
CC		:= g++
C		:= gcc
MKDIR	:= mkdir -p # Create sub-folders in one shot
SRC		:= src
OBJ		:= obj
LIBDIR	:= lib

# -L to set folders to search libraries | -l to add libraries to the link processs | -Wl,-rpath= to set the folder priority to include libraries
LIBS		:= -Llib -Wl,-rpath=lib/
# Include directories, to use relative includes (the ones with "<>") and get the static libraries from the proyect
INCDIRS		:= -I$(SRC) -I$(LIBDIR)
# Get all directories and subdirectories of src
SUBDIRS		:= $(shell find $(SRC)/ -type d)
# Substitute all src directories and subdirectories with obj/ as it's root
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
# Get all the .cpp files bellow src
ALLCPP		:= $(shell find $(SRC)/ -type f -iname *.cpp)
# Get all the .c files bellow src
ALLC		:= $(shell find $(SRC)/ -type f -iname *.c)
# All object files in their folders
ALLOBJ		:= $(foreach F,$(ALLCPP) $(ALLC),$(call C2O,$(F)))

# Objectives that won't generate files neither will be thrown every time
.PHONY: routes clean cleanall recode

##################################
# RULES
##################################

# Linking process
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS)

# C++ compiling
$(foreach F,$(ALLCPP),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) $(INCDIRS))))

# C compiling
$(foreach F,$(ALLC),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS) $(INCDIRS))))

$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)


##################################
# UTILITIES
##################################

routes: 
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLC))
	$(info $(ALLCPP))
	$(info $(ALLOBJ))

clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"

recode:
	$(MAKE) cleanall
	$(MAKE)