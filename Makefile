LOGIN = trinhdin
CXX = g++
LD = g++
BASIC_FLAGS = -std=c++17 -O2 -g -fsanitize=address -Wall -pedantic
LIB_FLAGS = -lncurses

ZIP = Makefile Doxyfile zadani.txt prohlaseni.txt \
  .gitignore $(wildcard examples/*) $(wildcard src/*)

DEPS = Makefile.d
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})

.PHONY: all compile run valgrind doc clean zip

all: compile doc

compile: deps ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${LD} ${BASIC_FLAGS} ${LIB_FLAGS} $^ -o $@

build/%.o: src/%.cpp 
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${LIB_FLAGS} -c $< -o $@

run: compile
	./${LOGIN}

valgrind: compile
	valgrind ./${LOGIN}

doc:
	doxygen Doxyfile

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip ${DEPS}

zip: ${LOGIN}.zip

${LOGIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${LOGIN}/
	cp --parents -r $^ tmp/${LOGIN}/
	cd tmp/ && zip -r ../$@ ${LOGIN}/
	rm -rf tmp/

deps: 
	${CXX} -MM ${SOURCES} > ${DEPS}

-include ${DEPS}

