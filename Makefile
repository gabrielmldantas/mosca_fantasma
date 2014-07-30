all:
	g++ -framework OpenGL -framework GLUT main.cpp mathutil.cpp model.cpp manager.cpp camera.cpp -o mosca

linux:
	g++ -lGL -lGLU -lglut main.cpp mathutil.cpp model.cpp manager.cpp camera.cpp -o mosca

clean:
	rm mosca
