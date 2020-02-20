CXX = g++
CXXFLAGS = -std=c++0x -Wall

OBJECTS = ParamSet.o  

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o paramset $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

$(OBJECTS): ParamSet.cpp ParamSet.h