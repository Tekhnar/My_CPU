all: run
../Assembler/./main: ../Assembler/*
	g++ ../Assembler/main.cpp -o ../Assembler/./main
                 
../processor/./main: ../processor/*
	g++ ../processor/main.cpp -o ../processor/./main

run: ../Assembler/./main ../processor/./main

	../Assembler/./main  ../workspace_for_processor/text.txt
	../processor/./main
