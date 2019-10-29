all:
../Assembler/./main: ../Assembler/*
	g++ ../Assembler/main.cpp -o ../Assembler/./main
                 
../processor/./main: ../processor/*
	g++ ../processor/main.cpp -o ../processor/main `txlin-macflags --cflags` `txlin-macflags --libs` 


factorial: ../Assembler/./main ../processor/./main

	../Assembler/./main  ../workspace_for_processor/factorial.txt
	../processor/./main

video: ../Assembler/./main ../processor/./main

	../Assembler/./main  ../workspace_for_processor/video.txt
	../processor/./main

video2: ../Assembler/./main ../processor/./main

	../Assembler/./main  ../workspace_for_processor/video2.txt
	../processor/./main

