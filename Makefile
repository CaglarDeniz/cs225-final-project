CXX=clang++

CXXFLAGS= -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic

LD=clang++

LDFLAGS= -std=c++1y -stdlib=libc++ -lc++abi -lm 

OBJS= Parse.o Edge.o Graph.o Node.o main.o

EXE_OBJ=main.o

TEST_CPP = $(wildcard tests/*.cpp)  catch/catchmain.cpp

OBJS_TEST = $(patsubst %.cpp, %.o , $(TEST_CPP))  $(filter-out $(EXE_OBJ) , $(OBJS))

OBJS_DIR = .objs

all:main

$(OBJS_DIR) : 
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tests
	@mkdir -p $(OBJS_DIR)/catch

$(OBJS_DIR)/%.o : %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


main: $(patsubst %.o,$(OBJS_DIR)/%.o,$(OBJS))
	$(LD) $^ $(LDFLAGS)  -o $@ 


test: $(patsubst %.o, $(OBJS_DIR)/%.o , $(OBJS_TEST))
	$(LD) $(LDFLAGS) $^  -o $@


clean: 
	rm -rf main test $(OBJS_DIR) *.o test_write*

