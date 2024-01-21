###############################################
#	MACROS
###############################################

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Sorce file
# $(4) : Additional dependencies
# $(5) : Compiler Flags
define  COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Sorce file
define  C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1)))) 
endef

# $(1) : Sorce file
define  C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1))) 
endef

###############################################
#	CONFIG
###############################################


APP 	:= libimgui.a
CFLAGS := -Wall -pedantic 
CCFLAGS  := $(CFLAGS) -std=c++11
CC 		:= g++ 
C 		:= gcc
AR		:= ar
ARFLAGS	:= -crs	
RANLIB	:= ranlib
MKDIR	:= mkdir -p
SRC 	:= src
OBJ 	:= obj
LIBS	:= -lX11 -lXext

ifdef DEBUG 
	CCFLAGS += -g
else
	CCFLAGS += -O3
endif

ALLCPPS		:= $(shell find $(SRC) -type f	-iname *.cpp) 
ALLCS		:= $(shell find $(SRC) -type f	-iname *.c) 
ALLOBJ		:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C20,$(F)))
SUBDIRS 	:= $(shell find $(SRC) -type d) 
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

.PHONY: info

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)
#$(CC) -o $(APP) $(ALLOBJ) $(LIBS)

#generate rules for all objects
$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C20,$(F)),$(F),,$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C20,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))


info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))

$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)

## CLEAN rules
clean:
	$(RM) -r "./$(OBJ)"

cleanall: clean
	$(RM) "./$(APP)"
	$(RM) "./*.a"
