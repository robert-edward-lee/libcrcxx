override CC:=$(TOOLCHAIN_PREFIX)gcc
CXX = $(TOOLCHAIN_PREFIX)g++
LD = $(CXX)

STDC_FLAGS = -ansi
STDCXX_FLAGS = -ansi

INC_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))
DEF_FLAGS = $(addprefix -D,$(DEFINES))
OPT_FLAGS = $(addprefix -O,$(OPT_LEVEL))
WARN_FLAGS = -Wall -Wextra -pedantic
EXTRA_FLAGS +=

test: version $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) test/crc_test.cpp -o $(BUILD_DIR)/$@
	@$(BUILD_DIR)/$@
