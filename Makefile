INCLUDE_DIR = include

TEST_DIR = test

WORK_DIRS = $(sort . $(TEST_DIR)/ $(INCLUDE_DIR)/ $(dir $(wildcard $(INCLUDE_DIR)/*/) $(wildcard $(INCLUDE_DIR)/*/*/)))


clean:
	@$(RM) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.a,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.d,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.dll,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.exe,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.o,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.obj,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.tds,$(dir)))

format:
	@clang-format \
		-style=file:.clang-format -i \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.hxx,$(dir))) \
		$(foreach dir,$(WORK_DIRS),$(addsuffix /*.cpp,$(dir))) \
		2> /dev/null ||:

include $(TEST_DIR)/test.mk
