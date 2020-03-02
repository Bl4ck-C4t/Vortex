BASE = vortex
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OUT = out
OBJS = objs
SOURCE = src
INTER_INCLUDES :=  $(PRECOMP)/parser.cc $(PRECOMP)/parser.hh $(PRECOMP)/lexer.cc 
ALL_SOURCES := $(shell find $(SOURCE) -path $(SOURCE)/Flex-and-Bison -prune -o -name '*.cpp' -print)
OUTS := $(ALL_SOURCES:.cpp=.o)

all: $(BASE) clean

$(PRECOMP)/%.cc $(PRECOMP)/%.hh: $(SOURCE)/Flex-and-Bison/*.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/parser.hh -o $(PRECOMP)/parser.cc $<


$(PRECOMP)/lexer.cc: $(SOURCE)/Flex-and-Bison/*.l
	$(FLEX) $(FLEXFLAGS) -o $(PRECOMP)/lexer.cc $<


%.o $(OBJS)/%.o: $(SOURCE)/*/%.cpp
	$(CXX) $^ -c -o $(addprefix $(OBJS)/,$(notdir $@))


$(BASE): $(INTER_INCLUDES) $(addprefix $(OBJS)/, $(notdir $(OUTS))) main.cc
	$(CXX) $^ -g -o $(OUT)/$@ 

tester: main.cc

lexer: $(INTER_INCLUDES) debugMain.cc
	$(CXX) $^ -g -o $(OUT)/$@

run: $(BASE)
	@echo "Started:"
	./$(OUT)/$< -

wipe: clean
	rm -f objs/*
	rm -f $(PRECOMP)/*

clean: 
	rm -f out/*.o
