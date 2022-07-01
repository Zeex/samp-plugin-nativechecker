CXX=g++

CXXFLAGS=-m32 -c -O3 -w -DLINUX -I./amx
LDFLAGS=-m32 -Os -shared

all: nativechecker.so

nativechecker.so: amxplugin.o nativechecker.o
	$(CXX) $(LDFLAGS) $? -o $@	

clean:
	rm -f *.o *.so
