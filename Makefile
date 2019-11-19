CFLAGS = -Wall -g

CORE_OBJ =		core/cpu.o \
				core/tables.o \
				core/execute.o \
				core/mem_loader.o \
				core/load.o \
				core/exchange.o \
				core/block_transfer.o \
				core/search.o \
				core/alu.o \
				core/misc.o \
				core/arithm16.o \

TEST_OBJ =		test/test.o \
				test/cpu_suite.o \
				test/load_8bit_suite.o \
				test/load_16bit_suite.o \
				test/exchange_suite.o \
				test/block_suite.o \
				test/search_suite.o \
				test/add_suite.o \
				test/adc_suite.o \
				test/sub_suite.o \
				test/sbc_suite.o \
				test/bitwise_suite.o \
				test/cp_suite.o \
				test/inc_dec_suite.o \
				test/misc_suite.o \
				test/arithm_16bit_suite.o

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
