################################################################################
#                              НАСТРОЙКА ПРОЕКТА                               #
################################################################################
PROJECT_NAME = crc
PROJECT_VERSION_MAJOR = 1
PROJECT_VERSION_MINOR = 0
PROJECT_VERSION_PATCH = 1
PROJECT_VERSION = $(PROJECT_VERSION_MAJOR).$(PROJECT_VERSION_MINOR).$(PROJECT_VERSION_PATCH)

################################################################################
#                              ОПРЕДЕЛЕНИЯ ПАПОК                               #
################################################################################
BUILD_DIR = build\$(TOOLCHAIN_PREFIX)$(CXX)
SOURCE_DIRS = src
INCLUDE_DIRS = include src
TEST_DIR = test

WORK_DIRS = $(sort . $(TEST_DIR) \
			$(dir $(wildcard include/crc/*/)) \
			$(dir $(wildcard include/crc/*/*/)))

VPATH = $(TEST_DIR):$(BUILD_DIR):$(subst $() $(),:,$(SOURCE_DIRS)):$(subst $() $(),:,$(INCLUDE_DIRS))
SOURCES = $(wildcard $(SOURCE_DIRS)/*.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(patsubst %.cpp,%.o,$(SOURCES))))
DEPENDS = $(patsubst %.o,%.d,$(OBJECTS))
-include $(DEPENDS)

################################################################################
#                              НАСТРОЙКА ТУЛЧЕЙНА                              #
################################################################################
TOOLCHAIN_PREFIX =
CC = gcc
CFLAGS = \
	$(STDC_FLAGS) \
	$(INC_FLAGS) \
	$(DEF_FLAGS) \
	$(OPT_FLAGS) \
	$(WARN_FLAGS) \
	$(EXTRA_FLAGS)
CXXFLAGS = \
	$(STDCXX_FLAGS) \
	$(INC_FLAGS) \
	$(DEF_FLAGS) \
	$(OPT_FLAGS) \
	$(WARN_FLAGS) \
	$(EXTRA_FLAGS)

OPT_LEVEL = 3

ifeq ($(CC),gcc)
include platforms/gcc.mk
else ifeq ($(CC),clang)
include platforms/clang.mk
else ifeq ($(CC),cl)
include platforms/msvc.mk
else ifeq ($(CC),armcc)
include platforms/armcc.mk
else ifeq ($(CC),armclang)
include platforms/armclang.mk
else ifeq ($(CC),iccarm)
include platforms/iccarm.mk
else
$(error Unknown compiler!)
endif

################################################################################
#                                  ОБЩИЕ ЦЕЛИ                                  #
################################################################################
ifeq ($(TERM),)
MKDIR = cmd /E:ON /C mkdir
override BUILD_DIR:=$(subst /,\,$(BUILD_DIR))
else
MKDIR = mkdir -p
endif

$(BUILD_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.a,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.d,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.dll,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.exe,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.o,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.obj,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.tds,$(dir))) \
		$(BUILD_DIR)/*

format:
	@clang-format \
		-style=file:.clang-format -i \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.hpp,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.cpp,$(dir))) \
		2> /dev/null ||:

.PHONY: test version

version:
	@echo "#ifndef HPP_CRC_VERSION"								 > include/crc/version.hpp
	@echo "#define HPP_CRC_VERSION"								>> include/crc/version.hpp
	@echo ""													>> include/crc/version.hpp
	@echo "#define CRC_VERSION_MAJOR $(PROJECT_VERSION_MAJOR)"	>> include/crc/version.hpp
	@echo "#define CRC_VERSION_MINOR $(PROJECT_VERSION_MINOR)"	>> include/crc/version.hpp
	@echo "#define CRC_VERSION_PATCH $(PROJECT_VERSION_PATCH)"	>> include/crc/version.hpp
	@echo "#define CRC_VERSION_STRING \"$(PROJECT_VERSION)\""	>> include/crc/version.hpp
	@echo ""													>> include/crc/version.hpp
	@echo "#endif // HPP_CRC_VERSION"							>> include/crc/version.hpp
