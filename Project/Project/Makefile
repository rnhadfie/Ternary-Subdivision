MAIN = Mainp
HALF=HalfEdgep
WIND=Window
OBJ=Object

LIBDIRS = 
INCDIRS = 

CC = g++
CFLAGS = -v 
LIBS = 

OS := $(shell uname)
ifeq ($(OS),Darwin)
	CFLAGS += -framework OpenGL 
else
	LIBDIRS += -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib 
	INCDIRS += -I/usr/include -I/usr/local/include -I/usr/include/GL
	CFLAGS += $(INCDIRS)	
	LIBS += -lGL -lglfw -lGLEW	
endif


all:
	$(CC) $(CFLAGS) -o $(MAIN) $(LIBDIRS) $(MAIN).cpp $(HALF).cpp $(WIND).cpp $(OBJ).cpp $(LIBS)
clean:
	rm -f *.o
