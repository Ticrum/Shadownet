#names
OUT=Shadowclient
LIBDYOUT=lib$(OUT).so
LIBSTAOUT=lib$(OUT).a

#flags
CPPFLAGS= -std=c++20
CXXFLAGS= -W -Wall
DFLAGS= -O0 -g -g3
GCOVFLAGS= -O0 --coverage
OPTIFLAGS= -O3

#links
LAPINLINKS= -llapin -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++ -lm -ldl -lpthread -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_core -lavcall -lusb
LIB=-L./ -lgtest_main -lgtest -lpthread -l$(OUT) -lgcov

#options
ifeq ($(DEBUG), 1)
	OPTFLAGS = $(DFLAGS)
endif
ifeq ($(GCOV), 1)
	OPTFLAGS += $(GCOVFLAGS)
endif
ifeq ($(OPTFLAGS),)
	OPTFLAGS = $(OPTIFLAGS)
endif

#others
INCLUDE=-I./include/
TESTINCLUDE=-I./test/include/

FLAGS=$(CPPFLAGS) $(CXXFLAGS) $(OPTFLAGS)

SRC=$(shell find src/ -name "*.cpp")
TESTSRC=$(shell find test/ -name "*.cpp")

OBJ=$(SRC:.cpp=.o)
TESTOBJ=$(TESTSRC:.cpp=.o)
TESTOUT=$(TESTOBJ:.o=.test)

MAKE=make re
##Rules##

all: cc test

cc: $(OUT)

$(OUT): $(OBJ)
ifeq ($(LIBLAPIN), 1)
	g++ $(OBJ) $(INCLUDE) $(FLAGS) $(LAPINLINKS) -o $(OUT)
else
	g++ $(OBJ) $(INCLUDE) $(FLAGS) -o $(OUT)
endif

lib: $(LIBSTAOUT)

$(LIBSTAOUT): $(OBJ)
	ar cr $(LIBSTAOUT) $(OBJ)

$(LIBDYOUT): $(OBJ)
	g++ -shared -o $(LIBDYOUT) $(OBJ)

test: $(LIBSTAOUT) $(TESTOBJ)

report:
	gcov $(SRC)
	lcov --capture --directory . --output-file man_coverage.info
	genhtml main_coverage.info --output-directory report

.cpp.o:
	g++ -c $< $(INCLUDE) -o $@ -fpic $(FLAGS)
ifeq ($(TEST), 1)
	g++ $(INCLUDE) $@ $(LIB) -o $($@:.o=.test)
endif

.o.test:
	g++ $(INCLUDE) $< $(LIB) -o $@

clean:
	@rm -f $(OBJ)
	@rm -f $(TESTOBJ)
	@rm -f $(shell find ./ -name "*~")
	@rm -f $(shell find ./ -name "*.gcno")
	@rm -f $(shell find ./ -name "*.gcov")
	@rm -f vgcore*
	@rm -f man_coverage.info
	@rm -f -r report

fclean: clean
	@rm -f $(OUT)
	@rm -f test/test$(OUT)
	@rm -f $(LIBSTAOUT)
	@rm -f $(LIBDYOUT)

re: fclean all

resta: fclean lib
