#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags

SRCS        := Model/Calculator.cc Model/Converter.cc Model/Model.cc Model/Parser.cc
TEST_SRCS	:= tests.cc

CC          := gcc
CFLAGS      := -lstdc++ -std=c++17 -Wall -Werror -Wextra

all: clean install

tests: clean
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRCS) -lgtest -o tests
	./$@

install: uninstall
	mkdir Build
	cd View && qmake && make && make clean && rm -rf Makefile && cd ../ && mv View/SmartCalc.app Build

uninstall:
	rm -rf Build*

dist:
	rm -rf SmartCalc/
	mkdir SmartCalc/
	mkdir SmartCalc/src
	cp -r ./Build/SmartCalc.app SmartCalc/src
	tar cvzf SmartCalc.tgz SmartCalc/
	rm -rf SmartCalc

dvi:
	open README.md

clean:
	rm -rf Build/
	rm -rf *.tgz
	rm -rf SmartCalc/
	rm -rf tests