all:
	g++ -framework OpenGL -framework GLUT main.cpp mathutil.cpp model.cpp manager.cpp camera.cpp fileutil.cpp -o mosca

linux:
	g++ -std=c++11 -lGL -lGLU -lglut main.cpp mathutil.cpp model.cpp manager.cpp camera.cpp fileutil.cpp -o mosca

clean:
	rm mosca
