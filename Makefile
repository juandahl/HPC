# -------------- #
# -- Makefile -- #
# -------------- #


# -- Lile list ----------
FILE = main.c nrutil.c mouvement.c test_mouvement.c morpho.c test_morpho.c ROC.c 

# -- Paths ----------
SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = include

# -- OS ----------
OS = MACH_OSX
#OS = LINUX

# -- Config ----------
# if CONFIG = CLI  (Command Line Interface, no Apple Framework)
CONFIG = CLI

# -- Macros ----------
CC = gcc
AR = ar -rc

# -- Flags ----------
C_DEBUG_FLAGS = -O0
C_CC_FLAGS = -std=c99 -DNOALIAS -DALIGNED
C_OPTIMISATION_FLAGS = -O3 -fstrict-aliasing

#C_ARCH_FLAGS = -xSSE4.2
C_ARCH_FLAGS =

C_OS_FLAGS = -D$(OS)
C_CONFIG_FLAGS = -D$(CONFIG)
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS =  $(C_CC_FLAGS) $(C_DEBUG_FLAGS)        $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH) 
CFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
LDFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_LIB_PATH)

# -- Final product ----------
PRODUCT   = hpc

# -- src and obj List ----------
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

# -- Base rules ----------
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
   
#-----Main rule ----------
$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG) $(INC) $(LIB) -lm -pthread

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ)
	rm -f ${EXE_PATH}/${PRODUCT}

