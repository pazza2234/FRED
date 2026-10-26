# VEXcode makefile 2019_03_26_01

# show compiler output
VERBOSE = 0
SLOT = 1
VEX_DEVICE ?= $(firstword $(wildcard /dev/serial/by-id/*VEX_Robotics_V5_Brain* /dev/serial/by-id/*VEX_Robotics_V5_CR_Brain*))

# include toolchain options
include vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard src/*.cpp) 
SRC_C += $(wildcard src/*.c)
SRC_C += $(wildcard src/*/*.cpp) 
SRC_C += $(wildcard src/*/*.c)

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  = $(wildcard include/*.h)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include

# Add the VEXcode SDK and Linux toolchains to PATH for this make invocation.
# it... kinda is designed around arch but you know what it does not break
# mac os so its fine
ifneq ($(OS),Windows_NT)
VEXCODE_TOOLS ?= $(HOME)/.config/Code/User/globalStorage/vexrobotics.vexcode
export PATH := $(VEX_SDK_PATH):$(VEXCODE_TOOLS)/tools/cpp/toolchain_linux64/gcc/bin:$(VEXCODE_TOOLS)/tools/cpp/toolchain_linux64/clang/bin:$(VEXCODE_TOOLS)/tools/vexcom/1_0_2_2/linux-x64:$(PATH)
endif

# build targets
all: $(BUILD)/$(PROJECT).bin

.PHONY: upload configure run
# build and upload
upload: all
	vexcom -s $(SLOT) -w ./build/FRED.bin $(if $(VEX_DEVICE), $(VEX_DEVICE))

# configure a new brain
configure:
	vexcom --team 3695C $(if $(VEX_DEVICE), $(VEX_DEVICE))

# for other brain management, just invoke the vexcom command

# include build rules
include vex/mkrules.mk
