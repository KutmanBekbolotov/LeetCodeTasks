SFML_INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.2/include
SFML_LIB = -L/opt/homebrew/Cellar/sfml/2.6.2/lib -lsfml-graphics -lsfml-window -lsfml-system

CXX = g++
CXXFLAGS = -std=c++17 $(SFML_INCLUDE)

all: physics_engine

physics_engine: *.cpp
	$(CXX) $(CXXFLAGS) *.cpp -o physics_engine $(SFML_LIB)