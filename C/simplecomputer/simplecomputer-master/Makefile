INCLUDE_PATH = include
LIBDIR = $(INCLUDE_PATH)/libs
mSC_DIR = mySimpleComputer
PRINT_DIR = myPrint
TERM_DIR = myTerm
CHARS_DIR = myBigChars
RK_DIR = myReadKey
SIGNAL_DIR = mySignal
CONSOLE_DIR = console
BIN_DIR = bin

OBJECTS_mSC = $(wildcard $(BIN_DIR)/$(mSC_DIR)/*.o)
OBJECTS_PRINT = $(wildcard $(BIN_DIR)/$(PRINT_DIR)/*.o)
OBJECTS_TERM = $(wildcard $(BIN_DIR)/$(TERM_DIR)/*.o)
OBJECTS_CHARS = $(wildcard $(BIN_DIR)/$(CHARS_DIR)/*.o)
OBJECTS_RK = $(wildcard $(BIN_DIR)/$(RK_DIR)/*.o)
OBJECTS_SIGNAL = $(wildcard $(BIN_DIR)/$(SIGNAL_DIR)/*.o)

CFLAGS = -I include -c -Wall -Wextra

.PHONY: all

all: clean objects libs console lab3

console: console.o
	gcc -I $(INCLUDE_PATH) -o $(CONSOLE_DIR)/$@ $(BIN_DIR)/console.o -L $(LIBDIR) -lmyPrint -lmyTerm -lmSC -lmyBigChars -lmyReadKey -lmySignal

console.o:
	gcc $(CFLAGS) $(CONSOLE_DIR)/console.c -o $(BIN_DIR)/$@

font: font.o
	gcc -I $(INCLUDE_PATH) -o $(CONSOLE_DIR)/$@ $(BIN_DIR)/font.o -L $(INCLUDE_PATH) -lmyBigChars -lmyTerm

font.o:
	gcc $(CFLAGS) $(CONSOLE_DIR)/font.c -o $(BIN_DIR)/$@

objects: obj_mSC obj_print obj_term obj_chars obj_rk obj_signal

libs: libmSC.a libmyPrint.a libmyTerm.a libmyBigChars.a libmyReadKey.a libmySignal.a

obj_mSC:
	gcc $(CFLAGS) -c $(mSC_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(mSC_DIR)
	mv *.o $(BIN_DIR)/$(mSC_DIR)

obj_print:
	gcc $(CFLAGS) -c $(PRINT_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(PRINT_DIR)
	mv *.o $(BIN_DIR)/$(PRINT_DIR)

obj_term:
	gcc $(CFLAGS) -c $(TERM_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(TERM_DIR)
	mv *.o $(BIN_DIR)/$(TERM_DIR)

obj_chars:
	gcc $(CFLAGS) -c $(CHARS_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(CHARS_DIR)
	mv *.o $(BIN_DIR)/$(CHARS_DIR)

obj_rk:
	gcc $(CFLAGS) -c $(RK_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(RK_DIR)
	mv *.o $(BIN_DIR)/$(RK_DIR)

obj_signal:
	gcc $(CFLAGS) -c $(SIGNAL_DIR)/*.c
	mkdir -p $(BIN_DIR)/$(SIGNAL_DIR)
	mv *.o $(BIN_DIR)/$(SIGNAL_DIR)

libmSC.a:
	mkdir -p $(LIBDIR)
	ar rcs $(LIBDIR)/$@ $(OBJECTS_mSC)

libmyPrint.a:
	ar rcs $(LIBDIR)/$@ $(OBJECTS_PRINT)

libmyTerm.a:
	ar rcs $(LIBDIR)/$@ $(OBJECTS_TERM)

libmyBigChars.a:
	ar rcs $(LIBDIR)/$@ $(OBJECTS_CHARS)

libmyReadKey.a:
	ar rcs $(LIBDIR)/$@ $(OBJECTS_RK)

libmySignal.a:
	ar rcs $(LIBDIR)/$@ $(OBJECTS_SIGNAL)

.PHONY: lab1
lab3:
	./$(CONSOLE_DIR)/console

clang:
	clang-format -i $(mSC_DIR)/*.c
	clang-format -i $(PRINT_DIR)/*.c
	clang-format -i $(TERM_DIR)/*.c
	clang-format -i $(CHARS_DIR)/*.c
	clang-format -i $(RK_DIR)/*.c
	clang-format -i $(SIGNAL_DIR)/*.c
	clang-format -i $(INCLUDE_PATH)/*.h
	clang-format -i $(CONSOLE_DIR)/*.c

.PHONY: clean
clean:
	rm -rf bin *.bin *.o console/font console/console