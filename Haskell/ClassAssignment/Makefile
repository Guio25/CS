## File generated by the BNF Converter (bnfc 2.9.5).

# Makefile for building the parser and test program.

BUILD      = build
GHC        = ghc
GHC_OPTS   = -outputdir ${BUILD}
HAPPY      = happy
HAPPY_OPTS = --array --info --ghc --coerce
ALEX       = alex
ALEX_OPTS  = --ghc

# List of goals not corresponding to file names.

.PHONY : all clean demo

# Default goal.

all : Double String Evaluate

# Rules for building the parser.

%.hs : %.y
	${HAPPY} ${HAPPY_OPTS} $<

%.hs : %.x
	${ALEX} ${ALEX_OPTS} $<

Double : AbsDef.hs Lex.hs Utils.hs ParDouble.hs ExpectedTestsResults.hs Double.hs
	${GHC} ${GHC_OPTS} $@

String : AbsDef.hs Lex.hs Utils.hs ParString.hs ExpectedTestsResults.hs String.hs
	${GHC} ${GHC_OPTS} $@

Evaluate : AbsDef.hs Lex.hs Utils.hs ParString.hs Evaluate.hs
	${GHC} ${GHC_OPTS} $@

# demo

demo : Double String
	./String -test ./tests/testsString.txt
	./Double -test ./tests/testsDouble.txt


# Rules for cleaning generated files.

clean :
	-rm -rf ${BUILD}/*
	-rm -f Lex.hs Double ParDouble.hs ParDouble.info String ParString.hs ParString.info Evaluate

# EOF



