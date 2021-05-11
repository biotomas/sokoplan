WSPACE = 	..

CXXFLAGS = -std=c++11 -g -D_GLIBCXX_USE_CXX11_ABI=0 -o3

OBJS = block.o board.o direction.o move.o level_reader.o main.o checker.o

TARGET =	SokobanChecker

CXX = 		g++

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	# ./$(TARGET)
	./run.sh

compileAndRun: all run
