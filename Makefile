CXX=g++

CXXFLAGS=-c -O3 -w -DLINUX -I./amx
LDFLAGS=-Os -shared

all: nativechecker.so

nativechecker.so: amxplugin.o nativechecker.o
	$(CXX) $(LDFLAGS) $? -o $@	

clean:
	rm -f *.o *.so
