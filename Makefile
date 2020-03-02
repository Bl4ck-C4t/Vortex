BASE = vortex
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OUT = out
SOURCE = src
INTER_INCLUDES :=  $(PRECOMP)/parser.cc $(PRECOMP)/parser.hh $(PRECOMP)/lexer.cc 
ALL_SOURCES := $(shell find $(SOURCE) -path $(SOURCE)/Flex-and-Bison -prune -o -name '*.cpp' -print)
OUTS := $(ALL_SOURCES:.cpp=.o)

all: $(BASE) clean

$(PRECOMP)/%.cc $(PRECOMP)/%.hh: $(SOURCE)/Flex-and-Bison/*.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/parser.hh -o $(PRECOMP)/parser.cc $<


$(PRECOMP)/lexer.cc: $(SOURCE)/Flex-and-Bison/*.l
	$(FLEX) $(FLEXFLAGS) -o $(PRECOMP)/lexer.cc $<


%.o: $(SOURCE)/*/%.cpp
	$(CXX) $^  -c -o $(OUT)/$@ 


$(BASE): $(INTER_INCLUDES) $(notdir $(OUTS)) main.cc
	$(CXX) $(INTER_INCLUDES) main.cc $(addprefix $(OUT)/, $(notdir $(OUTS))) -g -o $(OUT)/$@ 

lexer: $(INTER_INCLUDES) debugMain.cc
	$(CXX) $^ -g -o $(OUT)/$@

run: $(BASE)
	@echo "Started:"
	./$(OUT)/$< -

CLEANFILES =										\
  $(BASE) *.o										\
  parser.hh parser.cc parser.output parser.xml parser.html parser.gv location.hh	\
  scanner.cc
wipe:
	rm -f $(PRECOMP)/*

clean: 
	rm -f out/*.o
