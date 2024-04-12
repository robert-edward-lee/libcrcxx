TEST_CXX = g++
TEST_CXXFLAGS = -Wall -pedantic -Iinclude

.PHONY: test

test: $(BUILDDIR)
	@$(TEST_CXX) $(CXXFLAGS) $(TEST_CXXFLAGS) $(TEST_DIR)/crcxx_test.cxx -o $(TEST_DIR)/$@
	@$(TEST_DIR)/$@
