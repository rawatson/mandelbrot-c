CXX = gcc -std=c99 -g -Wall -O2
INCLUDES := -I./ -I/opt/local/include 
LIBRARIES := -L./ -L/opt/local/lib -lfreeimage
TARGET	:= mandelbrot

$(TARGET): mandelbrot.c
	$(CXX) $(INCLUDES) mandelbrot.c $(LIBRARIES) -o $(TARGET)

default: $(TARGET)

clean:
	/bin/rm -f *.o $(TARGET)
