CC=g++

default: marktweetgen marktweetgen.cpp

marktweetgen: marktweetgen.cpp
	$(CC) marktweetgen.cpp -o marktweetgen

clean:
	-rm -f marktweetgen
