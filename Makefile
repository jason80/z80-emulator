CFLAGS := -Wall -g

BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep
BINDIR := $(BUILDDIR)/bin

CORE_SRC := core/cpu.c \
			core/tables.c \
			core/stack.c \
			core/execute.c \
			core/mem_loader.c \
			core/load.c \
			core/exchange.c \
			core/block_transfer.c \
			core/search.c \
			core/alu.c \
			core/misc.c \
			core/arithm16.c \
			core/rot_shift.c \
			core/bit.c \
			core/jump.c \
			core/call_ret.c
CORE_OBJ := $(CORE_SRC:%.c=$(OBJDIR)/%.o)
CORE_DEP:= $(CORE_SRC:%.c=$(DEPDIR)/%.d)

TEST_SRC := test/test.c \
			test/cpu_suite.c \
			test/load_8bit_suite.c \
			test/load_16bit_suite.c \
			test/exchange_suite.c \
			test/block_suite.c \
			test/search_suite.c \
			test/add_suite.c \
			test/adc_suite.c \
			test/sub_suite.c \
			test/sbc_suite.c \
			test/bitwise_suite.c \
			test/cp_suite.c \
			test/inc_dec_suite.c \
			test/misc_suite.c \
			test/arithm_16bit_suite.c \
			test/rot_shift_suite.c \
			test/bit_suite.c \
			test/jump_suite.c \
			test/call_ret_suite.c
TEST_OBJ := $(TEST_SRC:%.c=$(OBJDIR)/%.o)
TEST_DEP:= $(TEST_SRC:%.c=$(DEPDIR)/%.d)

TEST_LFLAGS =	-lcunit
DEPFLAGS = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

.PHONY: all
all: $(BINDIR)/test

$(BINDIR)/test: $(TEST_OBJ) $(CORE_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(CORE_OBJ) -o $@ $(TEST_LFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p $(DEPDIR)/$(<D)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

.PHONY: clean-core
clean-core:
	rm -f $(CORE_OBJ)

.PHONY: clean-test
clean-test:
	rm -f $(TEST_OBJ) $(BINDIR)/test

.PHONY: clean
clean: clean-test clean-core

.PHONY: distclean
distclean:
	rm -rf $(BUILDDIR)

-include $(CORE_DEP)
-include $(TEST_DEP)
