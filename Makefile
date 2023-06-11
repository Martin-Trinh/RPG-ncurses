LOGIN = trinhdin
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -g -fsanitize=address -Wall -pedantic
FLAGS = -lncurses

ZIP = Makefile Doxyfile DOCUMENTATION.md zadani.txt prohlaseni.txt \
  .gitignore $(wildcard examples/*) $(wildcard src/*)

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEP_FILE = dependencies.dep

.PHONY: all compile run valgrind doc clean count zip

all: compile doc

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@
	@${CXX} -MM -MT "$@" $< > $(patsubst build/%.o, build/%.dep, $@)

-include ${DEP_FILE}

run: compile
	./${LOGIN}

valgrind: compile
	valgrind ./${LOGIN}

doc: doc/index.html

doc/index.html: Doxyfile DOCUMENTATION.md $(wildcard src/*)
	doxygen Doxyfile

count:
	wc -l src/* src/include/* 2>/dev/null

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip

zip: ${LOGIN}.zip

${LOGIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${LOGIN}/
	cp --parents -r $^ tmp/${LOGIN}/
	cd tmp/ && zip -r ../$@ ${LOGIN}/
	rm -rf tmp/
