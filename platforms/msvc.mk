CXX = $(CC)
LD = $(CC)

STDC_FLAGS =
STDCXX_FLAGS =

INC_FLAGS = $(addprefix /I,$(INCLUDE_DIRS))
DEF_FLAGS = $(addprefix /D,$(DEFINES))
ifeq ($(OPT_LEVEL),0)
OPT_FLAGS = /Od
else ifeq ($(OPT_LEVEL),1)
OPT_FLAGS = /O1
else ifeq ($(OPT_LEVEL),2)
OPT_FLAGS = /O2
else ifeq ($(OPT_LEVEL),3)
OPT_FLAGS = /Ox
else
OPT_FLAGS =
endif
WARN_FLAGS = /W4
EXTRA_FLAGS += /nologo

test: version $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) test/crc_test.cpp /Fe:$(BUILD_DIR)/$@
	@$(BUILD_DIR)/$@
