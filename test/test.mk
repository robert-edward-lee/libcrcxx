crc_test:
	@gcc -Wall -I$(CURDIR)/include $(CURDIR)/test/crc_test.c $(CURDIR)/src/crc.c -o $(CURDIR)/test/test
	@$(CURDIR)/test/test
