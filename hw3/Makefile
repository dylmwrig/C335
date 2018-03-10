#Makefile for homework 3
CC=gcc
CFLAGS= -O1 -g

disassembler: hw3.c
	$(CC) $(CFLAGS) -o disassembler hw3.c 

run: disassembler
	./disassembler

#typing make test should 
# 1) compile disassembler
# 2) translate test program to test.hex
# 3) execute disassembler on this input to generate test.out
# 4) compare test program with test.out using test.diff
#calling the test file by the same name given in the prompt as there is no reason not to

test: disassembler
	arm-none-eabi-as test_case_file -o test.o
	arm-none-eabi-objcopy test.o -O binary --only-section=.text test.bin
	hexdump -x test.bin |sed -e 's/^[^ ]*//' > test.hex
	./disassembler < test.hex
	diff test.out test_case_file
