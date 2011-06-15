CXX = g++ -g -Wall -O2
INCLUDES := -I./ -I/opt/local/include 
LIBRARIES := -L./ -L/opt/local/lib -lfreeimage
TARGET	:= mandelbrot

$(TARGET): mandelbrot.cpp
	$(CXX) $(INCLUDES) mandelbrot.cpp $(LIBRARIES) -o $(TARGET)

default: $(TARGET)

clean:
	/bin/rm -f *.o $(TARGET)