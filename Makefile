OUT = out
BASE = $(OUT)/vortex
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OBJS = objs
SOURCE = src
<<<<<<< HEAD
TESTS = tests
=======
>>>>>>> 4adf511... [fix-progress] Driver compiles
INTER_INCLUDES :=  $(OBJS)/parser.o $(OBJS)/lexer.o
ALL_SOURCES := $(shell find $(SOURCE) -path $(SOURCE)/Flex-and-Bison -prune -o -name '*.cpp' -print)
OUTS := $(ALL_SOURCES:.cpp=.o)
OUTS := $(addprefix $(OBJS)/, $(notdir $(OUTS)))
<<<<<<< HEAD
TEST_OBJ := $(wildcard $(TESTS)/*.cpp)
TEST_OBJ := $(addprefix $(OBJS)/, $(notdir $(TEST_OBJ)))
TEST_OBJ := $(TEST_OBJ:.cpp=.o)
=======
>>>>>>> 4adf511... [fix-progress] Driver compiles

all: $(BASE)

$(PRECOMP)/%.cc $(PRECOMP)/%.hh: $(SOURCE)/Flex-and-Bison/*.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/$*.hh -o $(PRECOMP)/$*.cc $<


$(PRECOMP)/lexer.cc: $(SOURCE)/Flex-and-Bison/*.l
	$(FLEX) $(FLEXFLAGS) -o $(PRECOMP)/lexer.cc $<


<<<<<<< HEAD
%.o $(OBJS)/%.o: $(SOURCE)/*/%.cpp $(SOURCE)/*/%.hpp
	$(CXX) $< -c -o $(OBJS)/$(@F)

$(TEST_OBJ): $(OBJS)/%.o: $(TESTS)/%.cpp
	$(CXX) $^ -c -o $@
=======
%.o $(OBJS)/%.o: $(SOURCE)/*/%.cpp
	$(CXX) $^ -c -o $(OBJS)/$(@F)
>>>>>>> 4adf511... [fix-progress] Driver compiles

$(INTER_INCLUDES): $(OBJS)/%.o: $(PRECOMP)/%.cc
	$(CXX) $^ -c -o $@

<<<<<<< HEAD
$(OBJS)/%.o: %.cc
	$(CXX) $^ -c -o $@

$(BASE): $(INTER_INCLUDES) $(OUTS) $(OBJS)/main.o
	$(CXX) $^ -g -o $@ 
=======
$(OBJS)/main.o: main.cc
	$(CXX) $^ -c -o $@

$(BASE): $(INTER_INCLUDES) $(OUTS) $(OBJS)/main.o
	$(CXX) $^ -g -o $(OUT)/$@ 
>>>>>>> 4adf511... [fix-progress] Driver compiles

parser: $(INTER_INCLUDES)

tests: %: $(OUT)/%

$(OUT)/tests: $(INTER_INCLUDES) $(OUTS) $(TEST_OBJ) $(TESTS)/*.hpp
	$(CXX) $^ -g -o $@

run: $(BASE)
	@echo "Started:"
	./$< -

wipe: clean
	rm -f objs/*
	rm -f $(PRECOMP)/*

clean: 
	rm -f out/*.o
