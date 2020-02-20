BASE = vortex
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OUT = out
SOURCE = src
INTER_INCLUDES =  $(PRECOMP)/parser.cc $(PRECOMP)/parser.hh $(PRECOMP)/lexer.cc \
$(shell find $(SOURCE) -path $(SOURCE)/Flex-and-Bison -prune -o -name '*.*' -print)

all: $(BASE)

$(PRECOMP)/%.cc $(PRECOMP)/%.hh %.gv: $(SOURCE)/Flex-and-Bison/*.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/parser.hh -o $(PRECOMP)/parser.cc $<

$(PRECOMP)/lexer.cc: $(SOURCE)/Flex-and-Bison/*.l
	$(FLEX) $(FLEXFLAGS) -o $(PRECOMP)/lexer.cc $<

$(BASE): $(INTER_INCLUDES) main.cc
	$(CXX) $^ -g -o $(OUT)/$@ 

lexer: $(INTER_INCLUDES) debugMain.cc
	$(CXX) $^ -g -o $(OUT)/$@

run: $(BASE)
	@echo "Started:"
	./$(OUT)/$< -

tests: $(INTER_INCLUDES) tests/*.cpp 
	$(CXX) $^ -g -o $(OUT)/$@

CLEANFILES =										\
  $(BASE) *.o										\
  parser.hh parser.cc parser.output parser.xml parser.html parser.gv location.hh	\
  scanner.cc
clean:
	rm -f $(PRECOMP)/*
