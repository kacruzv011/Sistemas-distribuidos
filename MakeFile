CXX = g++
CXXFLAGS_DEBUG = -Wall -g
CXXFLAGS_RELEASE = -O3 -Wall
SRC = main.cpp Particula.cpp
HEADERS = Particula.h utils.h

all: release

debug:
	$(CXX) $(CXXFLAGS_DEBUG) -o simulacion_debug $(SRC)

release:
	$(CXX) $(CXXFLAGS_RELEASE) -o simulacion_release $(SRC)

clean:
	rm -f *.o simulacion_debug simulacion_release
