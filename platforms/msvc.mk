CXX = $(CC)
LD = $(CC)

STDC_FLAGS = /std:clatest
STDCXX_FLAGS = /std:c++latest

INC_FLAGS = $(addprefix /I,$(INCLUDE_DIRS))
DEF_FLAGS = $(addprefix /D,$(DEFINES))
# OPT_FLAGS = $(addprefix /O,$(OPT_LEVEL))
WARN_FLAGS = /W4
EXTRA_FLAGS += /nologo

test: version $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) test/crc_test.cpp /Fe:$(BUILD_DIR)/$@
	@$(BUILD_DIR)/$@
