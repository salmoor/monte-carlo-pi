all: main-parallel

main-parallel: main.c helper.h
	mpicc -Wall main.c helper.h -o mcpi

