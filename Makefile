BASE = interpretator
BISON = bison
CXX = g++
FLEX = flex
PRECOMP = precompiled
OUT = out

all: $(BASE)

$(PRECOMP)/%.hh %.gv: %.yy
	$(BISON) $(BISONFLAGS) --graph=graphs/$*.gv --defines=$(PRECOMP)/parser.hh -o $(PRECOMP)/$*.cc $<

$(PRECOMP)/%.cc: %.l
	$(FLEX) $(FLEXFLAGS) -o $@ $<

$(BASE): $(PRECOMP)/parser.hh $(PRECOMP)/parser.cc $(PRECOMP)/lexer.cc main.cc driver.cc driver.hh
	$(CXX) $^ -o $(OUT)/$@


run: $(BASE)
	@echo "Started:"
	./$(OUT)/$< -


CLEANFILES =										\
  $(BASE) *.o										\
  parser.hh parser.cc parser.output parser.xml parser.html parser.gv location.hh	\
  scanner.cc
clean:
	rm -f $(PRECOMP)/*
