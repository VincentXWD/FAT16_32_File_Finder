main: main.o mbr.o vbr.o dir.o file.o analyse.o
	g++ -o main main.o mbr.o vbr.o dir.o file.o analyse.o
main.o: main.cc
	g++ -c main.cc -std=c++11
dir.o: dir.cc dir.h vbr.h
	g++ -c dir.cc
mbr.o: mbr.cc mbr.h fstype.h
	g++ -c mbr.cc
vbr.o: vbr.cc vbr.h
	g++ -c vbr.cc
file.o: file.cc file.h
	g++ -c file.cc
analyse.o: analyse.cc analyse.h
	g++ -c analyse.cc

c:
	rm *.o main
co:
	rm *.o
clean:
	rm *.o main

