IDIR = $(TFG)/include
SDIR = $(TFG)/src
ODIR = $(TFG)/build
LDIR = $(TFG)/lib

CC = g++
CFLAGS = -g -I$(IDIR) -L$(LDIR) -Wall

LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXext -lGLU -lXxf86vm -lXinerama -lXcursor -lassimp

_DEPS = glad.h glfw3.h mesh.h model.h shader.h camera.h image.h vertexLoader.h vertex.h modes.h object.h BezierCurve.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tfg.o glad.o BezierCurve.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tfg: $(OBJ)
	$(CC) -o $(TFG)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
