
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
vpath %.cfdg input

INC_DIRS = $(COMMON_DIR) $(UNIX_DIR) $(DERIVED_DIR) $(COMMON_DIR)/agg-extras
INC_DIRS += /usr/local/include
#INC_DIRS += /usr/local/include /emsdk/local/include

#
# Installation directories
#

prefix = /usr/local

BIN_DIR = $(DESTDIR)$(prefix)/bin
MAN_DIR = $(DESTDIR)$(prefix)/share/man

#
# Library directories for FFmpeg and libpng
#

LIB_DIRS = /usr/local/lib
#LIB_DIRS += /emsdk/local/lib

#
# Sources and Objects
#

COMMON_SRCS = cfdg.cpp Rand64.cpp makeCFfilename.cpp \
	cfdgimpl.cpp renderimpl.cpp builder.cpp shape.cpp \
	variation.cpp tempfile.cpp commandLineSystem.cpp \
	aggCanvas.cpp HSBColor.cpp SVGCanvas.cpp rendererAST.cpp \
	primShape.cpp bounds.cpp shape.cpp shapeSTL.cpp tiledCanvas.cpp \
	astexpression.cpp astreplacement.cpp pathIterator.cpp \
	stacktype.cpp CmdInfo.cpp abstractPngCanvas.cpp ast.cpp \
	prettyint.cpp

UNIX_SRCS = pngCanvas.cpp posixSystem.cpp main.cpp posixTimer.cpp \
    posixVersion.cpp

DERIVED_SRCS = cfdg.tab.cpp lex.yy.cpp

AGG_SRCS = agg_trans_affine.cpp agg_curves.cpp agg_vcgen_contour.cpp \
    agg_vcgen_stroke.cpp agg_bezier_arc.cpp agg_color_rgba.cpp

INPUT_SRCS = ciliasun_v2.cfdg demo1_v2.cfdg demo2_v2.cfdg funky_flower_v2.cfdg \
    i_curves_v2.cfdg i_pix_v2.cfdg i_polygons_v2.cfdg lesson2_v2.cfdg \
    lesson_v2.cfdg mtree_v2.cfdg octopi_v2.cfdg quadcity_v2.cfdg rose_v2.cfdg \
    sierpinski_v2.cfdg snowflake_v2.cfdg tangle_v2.cfdg triples_v2.cfdg \
    underground_v2.cfdg weighting_demo_v2.cfdg welcome_v2.cfdg ziggy_v2.cfdg \
    ciliasun.cfdg demo1.cfdg demo2.cfdg funky_flower.cfdg i_curves.cfdg \
    i_pix.cfdg i_polygons.cfdg lesson2.cfdg lesson.cfdg mtree.cfdg \
    octopi.cfdg quadcity.cfdg rose.cfdg sierpinski.cfdg snowflake.cfdg \
    tangle.cfdg triples.cfdg underground.cfdg weighting_demo.cfdg \
    welcome.cfdg ziggy.cfdg


LIBS = png m

# Use the first one for clang and the second one for gcc
ifeq ($(TARGET), wasm)
	LIBS += c++
	#LIBS += c++ icui18n icuuc icudata
else
ifeq ($(shell uname -s), Darwin)
  LIBS += c++ icucore
else
  LIBS += stdc++ atomic icui18n icuuc icudata
endif
endif


#
# FFmpeg support
#
# Uncomment these lines to enable FFmpeg support
#

# COMMON_SRCS += ffCanvas.cpp
# LIBS += avformat avcodec swscale swresample avutil z m x264 pthread dl

#
# Comment out this line to enable FFmpeg support
#

COMMON_SRCS += ffCanvasDummy.cpp

SRCS = $(DERIVED_SRCS) $(COMMON_SRCS) $(UNIX_SRCS)

#
# Configuration for local AGG
#
SRCS += $(AGG_SRCS)
INC_DIRS += $(AGG_DIR) $(AGG_DIR)/agg2


#
# Configuration for system AGG
#
#LIBS += agg


OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst %.o,%.d,$(OBJS))

LINKFLAGS += $(patsubst %,-L%,$(LIB_DIRS))
LINKFLAGS += $(patsubst %,-l%,$(LIBS))
LINKFLAGS += -fexceptions
ifeq ($(TARGET), wasm)
ifeq ($(WASM_DEBUG), 1)
	LINKFLAGS += -s EXCEPTION_DEBUG=1 -s SYSCALL_DEBUG=1 -s FS_DEBUG=1 -s ASSERTIONS=2 -g -gsource-map
endif
	LINKFLAGS += -fexceptions -s SUPPORT_LONGJMP=emscripten -s USE_LIBPNG=1 -s USE_ICU=1 -s INVOKE_RUN=0 -s EXPORTED_RUNTIME_METHODS=callMain,FS -s ALLOW_MEMORY_GROWTH=1 -s STACK_SIZE=104857600
endif

deps: $(OBJ_DIR) $(DEPS)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),src-common/examples.h)
include $(DEPS)
endif
endif
endif

$(OBJS): $(OBJ_DIR)/Sentry

#
# Executable
#
# Under Cygwin replace strip $@ with strip $@.exe

ifeq ($(TARGET), wasm)
STRIP = echo
else
STRIP = strip
endif

cfdg: $(OBJS)
	$(LINK.o) $^ $(LINKFLAGS) -o $@
	$(STRIP) $@


#
# Derived
#

$(DERIVED_DIR)/lex.yy.cpp: $(COMMON_DIR)/cfdg.l
	flex -o $@ $^

$(DERIVED_DIR)/cfdg.tab.hpp: $(DERIVED_DIR)/cfdg.tab.cpp
$(DERIVED_DIR)/location.hh: $(DERIVED_DIR)/cfdg.tab.cpp
$(DERIVED_DIR)/cfdg.tab.cpp: $(COMMON_DIR)/cfdg.ypp $(OBJ_DIR)/Sentry
	bison -o $(DERIVED_DIR)/cfdg.tab.cpp $(COMMON_DIR)/cfdg.ypp

$(OBJ_DIR)/lex.yy.o: $(DERIVED_DIR)/cfdg.tab.hpp

src-common/examples.h: $(INPUT_SRCS)
	python3 makeexamples.py $(INPUT_SRCS) > src-common/examples.h

#
# Utility
#

.PHONY: clean distclean install uninstall
clean :
	rm -f $(OBJ_DIR)/*
	rm -f cfdg

distclean: clean
	rmdir $(OBJ_DIR) 2> /dev/null || true
	rm -fr output 2> /dev/null || true

$(OBJ_DIR)/Sentry :
	mkdir -p $(OBJ_DIR) 2> /dev/null || true
	touch $@

install: cfdg cfdg.1
	install -d $(BIN_DIR) $(MAN_DIR)/man1
	install -m 755 cfdg $(BIN_DIR)
	install -m 644 cfdg.1 $(MAN_DIR)/man1

uninstall:
	-rm -f $(BIN_DIR)/cfdg
	-rm -f $(MAN_DIR)/man1/cfdg.1

#
# Tests
#

.PHONY: test test-mpeg check
test: cfdg
	./runtests.sh

test-mpeg: cfdg
	./runtests-mpeg.sh

check: cfdg
	./runtests.sh

#
# Rules
#

CXXFLAGS += $(patsubst %,-I%,$(INC_DIRS))
CXXFLAGS += -O2 -Wall -Wextra -Wno-parentheses -std=c++17
CXXFLAGS += -D_GLIBCXX_USE_C99_MATH=1
#CPPFLAGS += -DNDEBUG

# Add this for clang
ifeq ($(shell uname -s), Darwin)
  CXXFLAGS += -stdlib=libc++

# Uncomment this line to enable FFmpeg support on macos
# LDFLAGS += -framework CoreFoundation -framework CoreVideo -framework CoreMedia -framework VideoToolbox
endif

ifeq ($(TARGET), wasm)
CXXFLAGS += -DNOSYSCTL=1 -DNONORMALIZE=1 -fexceptions -s SUPPORT_LONGJMP=emscripten
ifeq ($(WASM_DEBUG), 1)
CXXFLAGS += -g -gsource-map
endif
endif

$(OBJ_DIR)/%.o : %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(OBJ_DIR)/%.d : %.cpp $(OBJ_DIR)/location.hh
	mkdir -p $(OBJ_DIR) 2> /dev/null || true
	set -e; $(COMPILE.cpp) -MM $< \
	| sed 's,\(.*\.o\)\( *:\),$(OBJ_DIR)/\1 $@\2,g' > $@; \
	[ -s $@ ] || rm -f $@

$(OBJ_DIR)/cfdg.tab.d:
	mkdir -p $(OBJ_DIR) 2> /dev/null || true

$(OBJ_DIR)/lex.yy.d:
	mkdir -p $(OBJ_DIR) 2> /dev/null || true

