all:
	g++ -framework OpenGL -framework GLUT main.cpp -o mosca

linux:
	g++ -lGL -lGLU -lglut main.cpp -o mosca

clean:
	rm mosca
