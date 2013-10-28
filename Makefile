CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DOSX
INCFLAGS = -I./glm-0.9.2.7 -I/usr/X11/include -I./include/
LDFLAGS = -L./osxlib/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.2.7 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
all: transform
transform: main.o readfile.o RayTracer.o GeometricPrimitive.o Light.o Film.o Camera.o Sample.o Transform.o BRDF.o Shape.o LocalGeo.o Ray.o Matrix4.o Color.o Vertex.o readfile.h variables.h
	$(CC) $(CFLAGS) -o transforms main.o readfile.o RayTracer.o GeometricPrimitive.o Light.o Film.o Camera.o Sample.o Transform.o BRDF.o Shape.o LocalGeo.o Ray.o Matrix4.o Color.o Vertex.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
readfile.o: readfile.cpp readfile.h variables.h Camera.o Vertex.o GeometricPrimitive.o Light.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
RayTracer.o: RayTracer.cpp RayTracer.h GeometricPrimitive.o Light.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c RayTracer.cpp
GeometricPrimitive.o: GeometricPrimitive.cpp GeometricPrimitive.h Shape.o BRDF.o Ray.o LocalGeo.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c GeometricPrimitive.cpp
Light.o: Light.cpp Light.h Vertex.o Color.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c Light.cpp
Film.o: Film.cpp Film.h Sample.o Color.o Variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp
Camera.o: Camera.cpp Camera.h Sample.o Vertex.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
Sample.o: Sample.cpp Sample.h Variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sample.cpp
Transform.o: Transform.cpp Transform.h Matrix4.h Vertex.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
BRDF.o: BRDF.cpp BRDF.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c BRDF.cpp
Shape.o: Shape.cpp Shape.h LocalGeo.o Ray.o Vertex.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp
LocalGeo.o: LocalGeo.cpp LocalGeo.h Vertex.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c LocalGeo.cpp
Ray.o: Ray.cpp Ray.h Vertex.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c Ray.cpp
Matrix4.o: Matrix4.cpp Matrix4.h Vertex.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c Matrix4.cpp
Color.o: Color.cpp Color.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Color.cpp
Vertex.o: Vertex.cpp Vertex.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Vertex.cpp
clean: 
	$(RM) *.o transforms *.png


 
