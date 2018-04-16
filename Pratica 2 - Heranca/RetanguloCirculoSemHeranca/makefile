all: TestaAgenda.exe

TestaAgenda.exe: TestaAgenda.o Agenda.o Horario.o Data.o 
	g++  TestaAgenda.o Agenda.o Horario.o Data.o -o TestaAgenda.exe
	rm Data.o Horario.o Agenda.o TestaAgenda.o

TestaAgenda.o: TestaAgenda.cpp Agenda.h Horario.h Data.h
	g++ -c TestaAgenda.cpp

Agenda.o: Agenda.h Agenda.cpp Horario.h Data.h
	g++ -c Agenda.cpp

Horario.o: Horario.h Horario.cpp
	g++ -c Horario.cpp

Data.o: Data.h Data.cpp
	g++ -c Data.cpp
