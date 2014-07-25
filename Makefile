all:
	g++ -framework OpenGL -framework GLUT main.cpp -o mosca

clean:
	rm mosca
