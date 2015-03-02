PROJECT=rule110
CXX=clang++
CPPFLAGS=-std=c++11 -Wall -pedantic

all: $(PROJECT)

clean:
	rm -f $(PROJECT)

$(PROJECT):
	$(CXX) $(CPPFLAGS) $@.cpp -o $@

