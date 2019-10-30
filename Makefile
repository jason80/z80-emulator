CFLAGS = -Wall -g

CORE_OBJ =		core/cpu.o \
				core/tables.o \
				core/execute.o \
				core/load.o \
				core/exchange.o \
				core/block_transfer.o \
				core/search.o

TEST_OBJ =		test/test.o \
				test/cpu_suite.o \
				test/load_8bit_suite.o \
				test/load_16bit_suite.o \
				test/exchange_suite.o \
				test/block_suite.o

TEST_LFLAGS =	-lcunit
TEST_BIN =		test/test

all: test

test: $(TEST_OBJ) $(CORE_OBJ)
	gcc $(CFLAGS) $(TEST_OBJ) $(CORE_OBJ) -o $(TEST_BIN) $(TEST_LFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean-core:
	rm -f $(CORE_OBJ)

clean-test:
	rm -f $(TEST_OBJ) $(TEST_BIN)
		
clean: clean-test clean-core
