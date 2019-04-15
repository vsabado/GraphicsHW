# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif
LIB2 = libim/libim.a jpeg/libjpeg.a

# define makefile targets
CC = g++ -Wall -Wno-deprecated-declarations -O3
BIN = main
all: $(BIN)


clean: 
	/bin/rm -f $(BIN)

jpeg/libjpeg.a:
	cd jpeg;make;cd ..

libim/libim.a:
	cd libim;make;cd ..

main: main.cpp 
	$(CC) -o main main.cpp $(LIB) $(LIB2)
