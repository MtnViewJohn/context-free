/*
 *
 
 Context Free Design Grammar - version 0.1
 
 Copyright (C) 2005 Chris Coyne - ccoyne77@gmail.com
 
 [Send me anything cool you make with it or of it.]
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published
 by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307  USA
 
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#ifdef _WIN32
#include "getopt.h"
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include "cfdg.h"
#include "variation.h"
#ifdef _WIN32
#include "WinPngCanvas.h"
#else
#include "pngCanvas.h"
#endif
#include "SVGCanvas.h"
#include "ffCanvas.h"
#include "posixSystem.h"
#include "version.h"
#include "Rand64.h"
#include "makeCFfilename.h"
#include <cassert>

using namespace std;

void setupTimer(Renderer* renderer);

ostream* myCout = &cout;

const char* invokeName = "";

void
usage(bool inError)
{
    ostream& out = inError ? cerr : *myCout;
    
    out << APP_NAME(invokeName) << " - " << APP_VERSION() << "(v" << APP_BUILD() << ")" << endl;
    out << endl;
    out << "Usage: " << endl << APP_NAME(invokeName)
        << " [options] input.cfdg [output.png/svg]" << endl;
    out << "    or to pipe a cfdg file on standard input:" << endl;
    out << APP_NAME(invokeName)
        << " [options] - [output.png/svg]" << endl;
    out << "If the output file name is omitted and the " << APP_OPTCHAR() << "o option and the " << APP_OPTCHAR() << "C option are not used" << endl;
    out << "then the output will be sent to stdout." << endl << endl;
    out << "Options: " << endl;
    out << "    " << APP_OPTCHAR()
        << "w num    width in pixels(png) or mm(svg) (default 500)" << endl;
    out << "    " << APP_OPTCHAR()
        << "h num    height in pixels(png) or mm(svg) (default 500)" << endl;
    out << "    " << APP_OPTCHAR()
        << "s num    set both width and height in pixels/mm" << endl;
    out << "    " << APP_OPTCHAR()
        << "s WIDTHxHEIGHT" << endl;
    out << "              set width to WIDTH and height to HEIGHT in pixels/mm" << endl;
    out << "    " << APP_OPTCHAR()
        << "T num    multiply tiled output size by num in width and height" << endl;
    out << "    " << APP_OPTCHAR()
        << "T WIDTHxHEIGHT" << endl;
    out << "              multiply tiled output size by WIDTH in width and HEIGHT in height" << endl;
    out << "    " << APP_OPTCHAR()
        << "m num    maximum number of shapes (default none)" << endl;
    out << "    " << APP_OPTCHAR()
        << "x float  minimum size of shapes in pixels/mm (default 0.3)" << endl;
    out << "    " << APP_OPTCHAR()
        << "b float  border size [-1,2]: -1=-8 pixel border, 0=no border," << endl;
    out << "              1=8 pixel border, 2=variable-sized border" << endl;
    out << "    " << APP_OPTCHAR()
        << "v str    set the variation code (default is random)" << endl;
    out << "    " << APP_OPTCHAR()
        << "o str    set the output file name, supports variable expansion" << endl;
    out << "              %f expands to the animation frame number," << endl;
    out << "              %v and %V expands to the variation code in lower or upper case," << endl;
    out << "              %% expands to %" << endl;
    out << "    " << APP_OPTCHAR()
        << "a num    generate num animation frames at 15fps (PNG or Quicktime only)" << endl;
    out << "    " << APP_OPTCHAR()
        << "a TIMExFPS" << endl;
    out << "              generate TIMExFPS animation frames at specified fps (PNG or Quicktime only)" << endl;
    out << "    " << APP_OPTCHAR()
        << "z        zoom out during animation" << endl;
    out << "    " << APP_OPTCHAR()
        << "V        generate SVG (vector) output" << endl;
    out << "    " << APP_OPTCHAR()
        << "Q        generate Quicktime movie output" << endl;
    out << "    " << APP_OPTCHAR()
        << "c        crop image output" << endl;
    out << "    " << APP_OPTCHAR()
        << "q        quiet mode, suppress non-error output" << endl;
    out << "    " << APP_OPTCHAR()
        << "C        Check syntax, check syntax of cfdg file and exit" << endl;
    out << "    " << APP_OPTCHAR()
        << "t        time output, output the time taken to render the cfdg file" << endl;
    out << "    " << APP_OPTCHAR()
        << "?        show this message, then exit" << endl;
    out << endl;
    
    exit(inError ? 2 : 0);
}

struct options {
    enum OutputFormat { PNGfile = 0, SVGfile = 1, MOVfile = 2 };
    int   width;
    int   height;
    int   widthMult;
    int   heightMult;
    int   maxShapes;
    float minSize;
    float borderSize;
    
    int   variation;
    bool  crop;
    bool  check;
    int   animationFrames;
	int   animationTime;
	int   animationFPS;
    bool  animationZoom;
    
    const char* input;
    const char* output;
    const char* output_fmt;
    OutputFormat format;
    
    bool quiet;
    bool outputTime;
    bool outputStdout;
    
    options()
    : width(500), height(500), widthMult(1), heightMult(1), maxShapes(0), 
      minSize(0.3F), borderSize(2.0F), variation(-1), crop(false), check(false), 
      animationFrames(0), animationTime(0), animationFPS(15), animationZoom(false), 
	  input(0), output(0), output_fmt(0), format(PNGfile), quiet(false), 
	  outputTime(false), outputStdout(false)
    { }
};

int
intArg2(char arg, const char* str, int& x, int& y)
{
    char* end;
    long int v = -1;
    
    v = strtol(str, &end, 10);
    if (end == str || v <= 0) {
        if (arg == '-')
            cerr << "Argument must be a positive integer or a pair of positive integers (e.g., 500x300)" << endl;
        else
            cerr << "Option -" << arg << " takes a positive integer argument or a pair of positive integers (e.g., 500x300)" << endl;
        usage(true);
    }
    x = (int)v;
    if (*end == 'x') {
        str = end + 1;
        v = strtol(str, &end, 10);
        if (end == str || v <= 0) {
            if (arg == '-')
                cerr << "Argument must be a positive integer or a pair of positive integers (e.g., 500x300)" << endl;
            else
                cerr << "Option -" << arg << " takes a positive integer argument or a pair of positive integers (e.g., 500x300)" << endl;
            usage(true);
        }
        y = (int)v;
    } else {
        y = x;
		return 1;
    }
	return 2;
}

int
intArg(char arg, const char* str)
{
    char* end;
    long int v = -1;
    
    v = strtol(str, &end, 10);
    if (end == str || v <= 0) {
        if (arg == '-')
            cerr << "Argument must be a positive integer" << endl;
        else
            cerr << "Option -" << arg << " takes a positive integer argument" << endl;
        usage(true);
    }
    return (int)v;
}

float
floatArg(char arg, const char* str)
{
    float v = (float)atof(str);
    
    if (v < 0) {
        if (arg == '-')
            cerr << "Argument must be a positive float" << endl;
        else
            cerr << "Option -" << arg << " takes a positive float argument" << endl;
        usage(true);
    }
    return v;
}

void
processCommandLine(int argc, char* argv[], options& opt)
{
    extern char *optarg;
    extern int optind, optopt;
    
    invokeName = argv[0];
    
    int i;
    while ((i = getopt(argc, argv, ":w:h:s:m:x:b:v:a:o:T:cCVzqQt?")) != -1) {
        char c = (char)i;
        switch(c) {
            case 'w':
                opt.width = intArg(c, optarg);
                break;
            case 'h':
                opt.height = intArg(c, optarg);
                break;
            case 's':
                intArg2(c, optarg, opt.width, opt.height);
                break;
            case 'T':
                intArg2(c, optarg, opt.widthMult, opt.heightMult);
                break;
            case 'm':
                opt.maxShapes = intArg(c, optarg);
                break;
            case 'x':
                opt.minSize = floatArg(c, optarg);
                break;
            case 'b':
                opt.borderSize = (float)atof(optarg);
                if (opt.borderSize < -1 || opt.borderSize > 2) usage(true);
                break;
            case 'v':
                opt.variation = Variation::fromString(optarg);
                break;
            case 'o':
                opt.output_fmt = optarg;
                break;
            case 'a': {
				int fps = 15, time = 0;
                if (opt.format == options::SVGfile) usage(true);
				if (intArg2(c, optarg, time, fps) == 2) {
					opt.animationTime = time;
					opt.animationFPS = fps;
					opt.animationFrames = time * fps;
				} else {
					opt.animationTime = time / opt.animationFPS;
					opt.animationFrames = time;
				}
                break;
			}
            case 'V':
                if (opt.animationFrames) usage(true);
                opt.format = options::SVGfile;
                break;
            case 'Q':
                opt.format = options::MOVfile;
                break;
            case 'c':
                opt.crop = true;
                break;
            case 'C':
                opt.check = true;
                break;
            case 'z':
                opt.animationZoom = true;
                break;
            case ':':
                cerr << "Option -" << (char)optopt << " requires an argument" << endl;
                usage(true);
                break;
            case '?':
                if (optopt == '?')
                    usage(false);
                cerr << "Unrecognized option: -" << optopt << endl;
                usage(true);
                break;
            case 'q':
                opt.quiet = true;
                break;
            case 't':
                opt.outputTime = true;
                break;
        }
    }
    
    if (optind < argc) {
        opt.input = argv[optind++];
    }
    if (optind < argc && !opt.output_fmt) {
        opt.output = argv[optind++];
    }
    if (optind < argc) {
        cerr << "Too many arguments" << endl;
        usage(true);
    }
    
    if (!opt.input) {
        cerr << "Missing input file" << endl;
        usage(true);
    }
    if (!opt.output && !opt.output_fmt && !opt.check) {
        opt.outputStdout = true;
        opt.output_fmt = "";
        opt.quiet = true;
    }
}

class nullstreambuf : public streambuf
{
protected:
	int overflow(int c) { return c; }
};
class nullostream : public ostream
{
public:
	nullostream() : ostream (new nullstreambuf()) {}
};


int main (int argc, char* argv[]) {
    options opts;
    int var = Variation::random(6);
    
    processCommandLine(argc, argv, opts);
    
    if (opts.quiet) myCout = new nullostream();
    
    clock_t startTime = clock();
    clock_t fromTime = startTime;
    clock_t clocksPerMsec = CLOCKS_PER_SEC / 1000;
    
    if (opts.variation < 0) opts.variation = var;
    char code[Variation::maxStringLength];
    Variation::toString(opts.variation, code, false);
    
    PosixSystem system(opts.quiet);;
    CFDG* myDesign = CFDG::ParseFile(opts.input, &system, opts.variation);
    if (!myDesign) return 1;
    if (opts.check) return 0;
    if (opts.widthMult != 1 || opts.heightMult != 1) {
        if (!myDesign->isTiled() && !myDesign->isFrieze()) {
            cerr << "Tiled output multiplication only allowed for tiled or frieze designs." << endl;
            return 6;
        }
        if (opts.format != options::PNGfile) {
            cerr << "Tiled output multiplication only allowed for PNG output." << endl;
            return 6;
        }
    }
    
    // If a static output file name is provided then generate an output
    // file name format string by escaping any '%' characters. If this is 
    // an animation run then add "_%f" before the extension.
    string newOutput;
    if (!opts.output_fmt) {
        stringstream escname(stringstream::out);
        for (const char* p = opts.output; *p; ) {
            const char* perc = strchr(p, '%');
            if (perc) {
                escname.write(p, perc-p);
                escname << "%%";
                p = perc + 1;
            } else {
                escname << p;
                break;
            }
        }
        newOutput = escname.str();
        if (opts.animationFrames && opts.format != options::MOVfile) {
#ifdef _WIN32
            const char dirchar = '\\';
#else
            const char dirchar = '/';
#endif
            size_t ext = newOutput.find_last_of('.');
            size_t dir = newOutput.find_last_of(dirchar);
            if (ext != string::npos && (dir == string::npos || ext > dir)) {
                newOutput.insert(ext, "_%f");
            } else {
                newOutput.append("_%f");
            }
        }
        opts.output_fmt = newOutput.c_str();
    }
    
    bool useRGBA = myDesign->usesColor;
    aggCanvas::PixelFormat pixfmt = aggCanvas::SuggestPixelFormat(myDesign);
    bool use16bit = pixfmt & aggCanvas::Has_16bit_Color;
	const char* fmtnames[3] = { "PNG image", "SVG vector output", "Quicktime movie" };
    
    *myCout << "Generating " << (use16bit ? "16bit " : "8bit ") 
        << (useRGBA ? "color" : "gray-scale")
		<< ' ' << fmtnames[opts.format]
        << ", variation " 
        << code << "..." << endl;
    
    pngCanvas* png = 0;
    SVGCanvas* svg = 0;
    ffCanvas*  mov = 0;
    Canvas* myCanvas = 0;
    
    Renderer* myRenderer = myDesign->renderer(opts.width, opts.height, opts.minSize,
                                              opts.variation, opts.borderSize);
    
    if (myRenderer == 0) {
        delete myDesign;
        return 9;
    }
    myRenderer->setMaxShapes(opts.maxShapes);
    opts.width = myRenderer->m_width;
    opts.height = myRenderer->m_height;
    opts.crop = opts.crop || myDesign->isTiled() || myDesign->isFrieze();
    
    switch (opts.format) {
        case options::PNGfile: {
            png = new pngCanvas(opts.output_fmt, opts.quiet, opts.width, opts.height, 
                                pixfmt, opts.crop, opts.animationFrames, opts.variation);
            myCanvas = (Canvas*)png;
            break;
        }
        case options::SVGfile: {
            string name = makeCFfilename(opts.output_fmt, 0, 0, opts.variation);
            svg = new SVGCanvas(name.c_str(), opts.width, opts.height, opts.crop);
            myCanvas = (Canvas*)svg;
            break;
        }
        case options::MOVfile: {
            string name = makeCFfilename(opts.output_fmt, 0, 0, opts.variation);
            mov = new ffCanvas(name.c_str(), pixfmt, opts.width, opts.height, 
					           opts.animationFPS);
			if (mov->mError) {
				cerr << "Failed to create movie file: " << mov->mError << endl;
				exit(8);
			}
            myCanvas = (Canvas*)mov;
            break;
        }
    }
    
    if (opts.widthMult != 1 || opts.heightMult != 1) {
        assert(png);
        png->setTiler(myRenderer, opts.widthMult, opts.heightMult);
    }
    
    
    myRenderer->run(opts.animationFrames ? 0 : myCanvas, false);
    
    if (system.error(false)) {
        delete myRenderer;
        delete myDesign;
        return 5;
    }
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << runTime << " msec to execute." << endl;
        fromTime = toTime;
    }
    
    if (!opts.quiet) setupTimer(myRenderer);
    
    if (opts.animationFrames) {
        myRenderer->animate(myCanvas, opts.animationFrames, opts.animationZoom);
    }
    *myCout << endl;
    
    if (!opts.quiet) setupTimer(0);
    
    *myCout << "DONE!" << endl;
    *myCout << "The output file name is " << 
    makeCFfilename(opts.output_fmt, 0, 0, opts.variation) << endl;
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << runTime << " msec to render." << endl;
        runTime = (toTime - startTime) / clocksPerMsec;
        *myCout << "The cfdg file took a total of " << runTime << " msec to process." << endl;
    }
    
    
    delete png;
    delete svg;
    delete mov;
    delete myRenderer;
    delete myDesign;
    
    return 0;
}


