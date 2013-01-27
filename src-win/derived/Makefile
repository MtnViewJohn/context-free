# Build the common derived files

DERIVED = lex.yy.cpp cfdg.tab.cpp cfdg.tab.hpp FlexLexer.h

all: $(DERIVED)

lex.yy.cpp FlexLexer.h: ../../src-common/cfdg.l cfdg.tab.hpp
	flex -o lex.yy.cpp ../../src-common/cfdg.l
	cp `which flex | xargs dirname | xargs dirname`/include/FlexLexer.h .

cfdg.tab.cpp cfdg.tab.hpp: ../../src-common/cfdg.ypp
	bison -o cfdg.tab.cpp ../../src-common/cfdg.ypp

clean:
	rm $(DERIVED)
