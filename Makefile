CFLAGS=-std=c89 -Wextra -Wall 
TEST_SRC=$(CURDIR)/test/test.c $(CURDIR)/jWrite.c
COV_FILES=jWrite.c
TEST_OUT=$(CURDIR)/test/test.out
COV_OUT=$(CURDIR)/test/*.gcda $(CURDIR)/test/*.gcov $(CURDIR)/test/*.gcno

.PHONY: test_build
test_build: $(TEST_SRC) 
	cd test; pwd; gcc $(CFLAGS) $(TEST_SRC) -o $(TEST_OUT)

.PHONY: test
test: test_build $(TEST_OUT)
	$(TEST_OUT)

.PHONY: test_cov_build
test_cov_build: $(TEST_SRC)
	@cd test; gcc $(CFLAGS) -fprofile-arcs -ftest-coverage $(TEST_SRC) -o $(TEST_OUT) > /dev/null 2>&1

.PHONY: test_cov_run
test_cov_run: test_cov_build
	@cd test; $(TEST_OUT) > /dev/null

.PHONY: test_cov
test_cov: test_clean test_cov_run
	@cd test; gcov $(COV_FILES) 

.PHONY: test_clean
test_clean:
	@rm -f $(COV_OUT) $(TEST_OUT) 

