OUT = out
BASE = $(OUT)/vortex
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OBJS = objs
SOURCE = src
TESTS = tests
INTER_INCLUDES :=  $(OBJS)/parser.o $(OBJS)/lexer.o
ALL_SOURCES := $(shell find $(SOURCE) -path $(SOURCE)/Flex-and-Bison -prune -o -name '*.cpp' -print)
OUTS := $(ALL_SOURCES:.cpp=.o)
OUTS := $(addprefix $(OBJS)/, $(notdir $(OUTS)))
TEST_OBJ := $(wildcard $(TESTS)/*.cpp)
TEST_OBJ := $(addprefix $(OBJS)/, $(notdir $(TEST_OBJ)))
TEST_OBJ := $(TEST_OBJ:.cpp=.o)
define make_obj= 
$(CXX) $^ -c -g -o $@
endef

all: $(BASE)

$(PRECOMP)/%.cc $(PRECOMP)/%.hh: $(SOURCE)/Flex-and-Bison/*.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/$*.hh -o $(PRECOMP)/$*.cc $<


$(PRECOMP)/lexer.cc: $(SOURCE)/Flex-and-Bison/*.l
	$(FLEX) $(FLEXFLAGS) -o $(PRECOMP)/lexer.cc $<


%.o $(OBJS)/%.o: $(SOURCE)/*/%.cpp $(SOURCE)/*/%.hpp
	$(CXX) $< -c -o $(OBJS)/$(@F)

$(TEST_OBJ): $(OBJS)/%.o: $(TESTS)/%.cpp
	$(make_obj)

$(INTER_INCLUDES): $(OBJS)/%.o: $(PRECOMP)/%.cc
	$(make_obj)

$(OBJS)/%.o: %.cc
	$(make_obj)

$(BASE): $(INTER_INCLUDES) $(OUTS) $(OBJS)/main.o
	$(CXX) $^ -g -o $@ 

debug: $(ALL_SOURCES) $(INTER_INCLUDES) $(OBJS)/main.o
	$(CXX) $^ -g -o $(OUT)/vortex

parser: $(INTER_INCLUDES)

lexer: $(OUT)/lexer

$(OUT)/lexer: $(INTER_INCLUDES) $(OUTS) $(OBJS)/debugMain.o
	$(CXX) $^ -g -o $@

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
