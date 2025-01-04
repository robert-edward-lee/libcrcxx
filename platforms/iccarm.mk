CXX = $(CC)
LD = $(CXX)

STDC_FLAGS = --c89
STDCXX_FLAGS = --c++98

INC_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))
DEF_FLAGS = $(addprefix -D,$(DEFINES))
ifeq ($(OPT_FLAGS),0)
OPT_FLAGS = -On
else ifeq ($(OPT_FLAGS),1)
OPT_FLAGS = -Ol
else ifeq ($(OPT_FLAGS),2)
OPT_FLAGS = -Om
else ifeq ($(OPT_FLAGS),3)
OPT_FLAGS = -Oh
else
OPT_FLAGS =
endif
WARN_FLAGS =
EXTRA_FLAGS +=

test: version $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) test/crc_test.cpp -o $(BUILD_DIR)/$@
