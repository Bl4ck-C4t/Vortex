BASE = interpretator
BISON = bison
CXX = g++ -std=c++1z
FLEX = flex
PRECOMP = precompiled
OUT = out
SOURCE = src
INTER_INCLUDES =  $(PRECOMP)/parser.hh $(PRECOMP)/parser.cc $(PRECOMP)/lexer.cc driver.cc driver.hh Variables/vars.cpp $(shell find $(SOURCE) -name '*.*')

all: $(BASE)

$(PRECOMP)/%.cc $(PRECOMP)/%.hh %.gv: %.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/parser.hh -o $(PRECOMP)/$*.cc $<

$(PRECOMP)/%.cc: %.l
	$(FLEX) $(FLEXFLAGS) -o $@ $<

$(BASE): $(INTER_INCLUDES) main.cc
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
