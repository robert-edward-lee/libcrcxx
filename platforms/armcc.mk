CXX = $(CC)
LD = $(CXX)

STDC_FLAGS = --gnu89
STDCXX_FLAGS = --gnu++98

INC_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))
DEF_FLAGS = $(addprefix -D,$(DEFINES))
OPT_FLAGS = $(addprefix -O,$(OPT_LEVEL))
WARN_FLAGS =
EXTRA_FLAGS +=

test: version $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) test/crc_test.cpp -o $(BUILD_DIR)/$@
