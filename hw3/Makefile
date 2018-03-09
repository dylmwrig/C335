#Makefile for homework 3
CC=gcc
CFLAGS= -O1 -g

#typing make test should 
# 1) compile disassembler
# 2) translate test program to test.hex
# 3) execute disassembler on this input to generate test.out
# 4) compare test program with test.out using test.diff
disassembler: hw3.c
	$(CC) $(CFLAGS) -o disassembler hw3.c 

run: disassembler
	./disassembler

test: disassembler
	./disassembler 
