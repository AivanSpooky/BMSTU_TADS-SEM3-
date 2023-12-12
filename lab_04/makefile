INCDIR := ./inc
SRCDIR := ./src
OUTDIR := ./out
UNITDIR := ./unit_tests

vpath %.c $(SRCDIR) $(UNITDIR)

CC := gcc
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wfloat-conversion
LDFLAGS := -I/usr/include/json-c -ljson-c -lm
#UNFLAGS := -I -L -lcheck -lpthread -lrt -lsubunit -lm
UNFLAGS := -I -L -lcheck -lpthread -lrt -lm

SRCS := $(wildcard $(SRCDIR)/*.c)  # список файлов .c из src
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)  # список файлов .o из src

TEST_SRCS := $(wildcard $(UNITDIR)/*.c)
ALL_OBJS := $(OBJS) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)
DEPS := $(ALL_OBJS:.o=.d)
TEST_OBJS := $(filter-out $(OUTDIR)/main.o, $(ALL_OBJS))

.PHONY: release
release: app.exe

.PHONY: debug
debug: CFLAGS += -O0 -g
debug: app.exe

.PHONY: sanitize_check
sanitize: asan
sanitize: func
sanitize: clean
sanitize: msan
sanitize: func
sanitize: clean
sanitize: ubsan
sanitize: func
sanitize: clean

.PHONY: asan
asan: CC := clang
asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
asan: app.exe

.PHONY: msan
msan: CC := clang
msan: CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer -g
msan: app.exe

.PHONY: ubsan
ubsan: CC := clang
ubsan: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer -g
ubsan: app.exe

.PHONY: gcov
gcov: CFLAGS += -O0 -g3 --coverage
gcov: LDFLAGS += --coverage
gcov: app.exe

.PHONY: func
func: release
func:
	./func_tests/scripts/func_tests.sh

.PHONY: collect_coverage
collect_coverage:
	cd out && gcov -o ./ ../$(SRCDIR)/*.c

.PHONY: unit
unit: unit_tests.exe
unit:
	./unit_tests.exe

.PHONY: all
all: sanitize_check
all: unit

app.exe: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

unit_tests.exe: $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(UNFLAGS)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -fr $(OUTDIR)
	rm -f ./*.exe ./*.txt
