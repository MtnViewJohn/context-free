
all: cfdg


#
# Dirs
#

OBJ_DIR = objs

COMMON_DIR = src-common
UNIX_DIR = src-unix
DERIVED_DIR = $(OBJ_DIR)
AGG_DIR = src-agg
FFMPEG_DIR = src-ffmpeg

SRC_DIRS = $(COMMON_DIR) $(UNIX_DIR) $(DERIVED_DIR) $(AGG_DIR)/src
vpath %.cpp $(SRC_DIRS)

INC_DIRS = $(COMMON_DIR) $(UNIX_DIR) $(DERIVED_DIR) $(AGG_DIR)/include $(COMMON_DIR)/agg-extras $(FFMPEG_DIR)/include

LIB_DIRS = $(FFMPEG_DIR)/lib /usr/local/lib

#
# Sources and Objects
#

COMMON_SRCS = cfdg.cpp Rand64.cpp makeCFfilename.cpp \
	cfdgimpl.cpp renderimpl.cpp builder.cpp shape.cpp \
	variation.cpp countable.cpp tempfile.cpp \
	aggCanvas.cpp HSBColor.cpp SVGCanvas.cpp \
	primShape.cpp bounds.cpp shape.cpp shapeSTL.cpp tiledCanvas.cpp \
	astexpression.cpp astreplacement.cpp pathIterator.cpp \
	stacktype.cpp CmdInfo.cpp abstractPngCanvas.cpp ast.cpp
COMMON_SRCS += ffCanvasDummy.cpp
# COMMON_SRCS += ffCanvas.cpp

UNIX_SRCS = pngCanvas.cpp posixSystem.cpp main.cpp posixTimer.cpp \
    posixVersion.cpp

DERIVED_SRCS = lex.yy.cpp cfdg.tab.cpp

AGG_SRCS = agg_trans_affine.cpp agg_curves.cpp agg_vcgen_contour.cpp \
    agg_vcgen_stroke.cpp agg_bezier_arc.cpp agg_color_rgba.cpp

SRCS = $(COMMON_SRCS) $(UNIX_SRCS) $(DERIVED_SRCS) $(AGG_SRCS)
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst %.o,%.d,$(OBJS))
LIBS = stdc++ png z
LIBS += avformat avcodec avutil

LINKFLAGS += $(patsubst %,-L%,$(LIB_DIRS))
LINKFLAGS += $(patsubst %,-l%,$(LIBS))
LINKFLAGS += -fexceptions

deps: $(OBJ_DIR) $(DEPS)
include $(DEPS)

$(OBJS): $(OBJ_DIR)/Sentry

#
# Executable
#
# Under Mac OS X replace $(LINK.o) with g++.
# Under Cygwin replace strip $@ with strip $@.exe

cfdg: $(OBJS)
	$(LINK.o) $^ $(LINKFLAGS) -o $@
	strip $@


#
# Derived
#

$(DERIVED_DIR)/lex.yy.cpp: $(COMMON_DIR)/cfdg.l
	flex -o $@ $^

$(DERIVED_DIR)/cfdg.tab.hpp: $(DERIVED_DIR)/cfdg.tab.cpp
$(DERIVED_DIR)/cfdg.tab.cpp: $(COMMON_DIR)/cfdg.ypp
	bison -o $(DERIVED_DIR)/cfdg.tab.cpp $(COMMON_DIR)/cfdg.ypp

$(OBJ_DIR)/lex.yy.o: $(DERIVED_DIR)/cfdg.tab.hpp

#
# Utility
#

clean :
	rm -f $(OBJ_DIR)/*
	rm -f cfdg

distclean: clean
	rmdir $(OBJ_DIR)

$(OBJ_DIR)/Sentry :
	mkdir -p $(OBJ_DIR) 2> /dev/null || true
	touch $@

#
# Tests
#

RTEST_CFDG = input/rendering-tests.cfdg
OUTPUT_DIR = output

rtests: $(OUTPUT_DIR)/rtest-700.png $(OUTPUT_DIR)/rtest-2k.png

$(OUTPUT_DIR)/rtest-700.png: cfdg $(RTEST_CFDG)
	./cfdg -s 700 $(RTEST_CFDG) $@
$(OUTPUT_DIR)/rtest-2k.png: cfdg $(RTEST_CFDG)
	./cfdg -s 2000 $(RTEST_CFDG) $@

#
# Rules
#

CPPFLAGS += $(patsubst %,-I%,$(INC_DIRS))
CPPFLAGS += -O3 -Wall -march=native -Wno-parentheses
#CPPFLAGS += -ggdb

$(OBJ_DIR)/%.o : %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(OBJ_DIR)/%.d : %.cpp
	mkdir -p $(OBJ_DIR) 2> /dev/null || true
	set -e; $(COMPILE.cpp) -MM $< \
	| sed 's,\(.*\.o\)\( *:\),$(OBJ_DIR)/\1 $@\2,g' > $@; \
	[ -s $@ ] || rm -f $@

$(OBJ_DIR)/cfdg.tab.d:

$(OBJ_DIR)/lex.yy.d:

