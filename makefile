main.o: main.c
	gcc -c main.c -o main.o

card.o: Payment_System/Card/card.c Payment_System/Card/card.h
	gcc -c Payment_System/Card/card.c -o card.o

terminal.o: Payment_System/Terminal/terminal.c Payment_System/Terminal/terminal.h
	gcc -c Payment_System/Terminal/terminal.c -o terminal.o

server.o: Payment_System/Server/server.c Payment_System/Server/server.h
	gcc -c Payment_System/Server/server.c -o server.o

Data_Structures.o: Data_Structures/List/list.c Data_Structures/List/list.h
	gcc -c Data_Structures/List/list.c -o Data_Structures.o

Data_Bases.o: Data_Bases/File_Handling/file_handling.c Data_Bases/File_Handling/file_handling.h
	gcc -c Data_Bases/File_Handling/file_handling.c -o Data_Bases.o

Application.o: Application/application.c Application/application.h
	gcc -c Application/application.c -o Application.o

All: main.o card.o terminal.o server.o Data_Structures.o Data_Bases.o Application.o
	gcc main.o card.o terminal.o server.o Data_Structures.o Data_Bases.o Application.o -o out.exe