CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.87.0/include/ -I/opt/homebrew/Cellar/sfml@2/2.6.2/include/
LIBDIR = -L/opt/homebrew/Cellar/boost/1.87.0/lib/ -L/opt/homebrew/Cellar/sfml@2/2.6.2/lib/
DEPS = Universe.hpp CelestialBody.hpp
# Your compiled .o files
OBJECTS = Universe.o CelestialBody.o
# The name of your program
PROGRAM = NBody
# The name of your test program
TEST_EXEC = test
# The name of your static library
STATIC_LIB = NBody.a

.PHONY: all clean lint


all: $(PROGRAM) $(TEST_EXEC) $(STATIC_LIB)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $^

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR) -DTEST

$(TEST_EXEC): test.o Universe.o CelestialBody.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

clean:
	rm *.o $(PROGRAM) $(TEST_EXEC) $(STATIC_LIB)

lint:
	cpplint *.cpp *.hpp
