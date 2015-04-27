/*
 *
 
 Context Free Design Grammar - version 0.1
 
 Copyright (C) 2005 Chris Coyne - ccoyne77@gmail.com
 Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
 Copyright (C) 2008-2014 John Horigan - john@glyphic.com
 
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

#define NOMINMAX 1
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#ifdef _WIN32
#include "getopt.h"
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <cstdio>
#include "cfdg.h"
#include "variation.h"
#ifdef _WIN32
#include "WinPngCanvas.h"
#else
#include "pngCanvas.h"
#endif
#include "SVGCanvas.h"
#include "ffCanvas.h"
#include "commandLineSystem.h"
#include "version.h"
#include "Rand64.h"
#include "makeCFfilename.h"
#include <cassert>
#include <memory>

using namespace std;

void setupTimer(shared_ptr<Renderer>& renderer);
void cleanupTimer();

const char* prettyInt(unsigned long);

ostream* myCout = &cerr;

const char* invokeName = "";

static weak_ptr<Renderer> gRenderer;

static bool processInterrupt()
{
    auto TheRenderer = gRenderer.lock();
    if (!TheRenderer) return false;
    
    if (!TheRenderer->requestFinishUp) {
        TheRenderer->requestFinishUp = true;
        cerr << endl << "Render interrupted, drawing current shapes" << endl;
    } else if (!TheRenderer->requestStop) {
        TheRenderer->requestStop = true;
        cerr << endl << "Render interrupted, skipping drawing, cleaning up temporary files" << endl;
    } else {
        exit(9);
    }
    return true;
}

#ifdef _WIN32
#include <Windows.h>

BOOL CtrlHandler(DWORD ctrlType) 
{
    if (ctrlType != CTRL_C_EVENT && ctrlType != CTRL_BREAK_EVENT)
        return FALSE;
    return processInterrupt();
}
#else
#include <csignal>

void termination_handler(int signum)
{
    processInterrupt();
}
#endif


const char*
prettyInt(unsigned long v)
{
    if (!v) return "0";
    
    static char temp[32];
    temp[31] = '\0';
    int i = 0;
    char* pos = temp + 30;
    for(;;) {
        *pos = '0' + (v % 10);
        v = v / 10;
        if (!v) return pos;
        ++i;
        --pos;
        if (i % 3 == 0) {
            *pos = ',';
            --pos;
        }
    }
}

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
#ifdef _WIN32
    out << "    " << APP_OPTCHAR()
        << "W        generate desktop wallpaper output" << endl;
#endif
    out << "    " << APP_OPTCHAR()
        << "c        crop image output" << endl;
    out << "    " << APP_OPTCHAR()
        << "q        quiet mode, suppress non-error output" << endl;
    out << "    " << APP_OPTCHAR()
        << "C        Check syntax, check syntax of cfdg file and exit" << endl;
    out << "    " << APP_OPTCHAR()
        << "t        time output, output the time taken to render the cfdg file" << endl;
    out << "    " << APP_OPTCHAR()
        << "P        Parameter allocation debug, test whether all the parameter blocks were cleaned up" << endl;
    out << "    " << APP_OPTCHAR()
        << "d        Delete old temporary files" << endl;
    out << "    " << APP_OPTCHAR()
        << "?        show this message, then exit" << endl;
    out << endl;
    
    exit(inError ? 2 : 0);
}

struct options {
    enum OutputFormat { PNGfile = 0, SVGfile = 1, MOVfile = 2, BMPfile = 3 };
    int   width;
    int   height;
    int   widthMult;
    int   heightMult;
    int   maxShapes;
    double minSize;
    double borderSize;
    
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
    bool outputWallpaper;
    bool paramTest;
    bool deleteTemps;
    
    options()
    : width(500), height(500), widthMult(1), heightMult(1), maxShapes(0), 
      minSize(0.3F), borderSize(2.0F), variation(-1), crop(false), check(false), 
      animationFrames(0), animationTime(0), animationFPS(15), animationZoom(false), 
      input(nullptr), output(nullptr), output_fmt(nullptr), format(PNGfile), quiet(false),
      outputTime(false), outputStdout(false), outputWallpaper(false),
      paramTest(false), deleteTemps(false)
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
    x = static_cast<int>(v);
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
        y = static_cast<int>(v);
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
    return static_cast<int>(v);
}

double
floatArg(char arg, const char* str)
{
    double v = atof(str);
    
    if (v < 0) {
        if (arg == '-')
            cerr << "Argument must be a positive float" << endl;
        else
            cerr << "Option -" << arg << " takes a positive float argument" << endl;
        usage(true);
    }
    return v;
}

#ifdef _WIN32
#define OPTCHARS ":w:h:s:m:x:b:v:a:o:T:cCdVzqQPtW?"
#else
#define OPTCHARS ":w:h:s:m:x:b:v:a:o:T:cCdVzqQPt?"
#endif

void
processCommandLine(int argc, char* argv[], options& opt)
{
    extern char *optarg;
    extern int optind, optopt;
    
    invokeName = argv[0];
    
    int i;
    while ((i = getopt(argc, argv, OPTCHARS)) != -1) {
        char c = static_cast<char>(i);
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
                opt.borderSize = atof(optarg);
                if (opt.borderSize < -1 || opt.borderSize > 2) usage(true);
                break;
            case 'v':
                opt.variation = Variation::fromString(optarg);
                if (opt.variation == -1) {
                    cerr << "Error parsing variation" << endl;
                    exit(99);
                }
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
                if (opt.format != options::PNGfile) usage(true);
                opt.format = options::SVGfile;
                break;
            case 'Q':
                if (opt.format != options::PNGfile || opt.crop) usage(true);
                opt.format = options::MOVfile;
                break;
            case 'W':
                if (opt.format != options::PNGfile || opt.crop) usage(true);
                opt.format = options::BMPfile;
                opt.outputWallpaper = true;
                break;
            case 'c':
                if (opt.format == options::MOVfile) usage(true);
                opt.crop = true;
                break;
            case 'C':
                opt.check = true;
                break;
            case 'z':
                opt.animationZoom = true;
                break;
            case ':':
                cerr << "Option -" << static_cast<char>(optopt) << " requires an argument" << endl;
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
            case 'P':
                opt.paramTest = true;
                break;
            case 'd':
                opt.deleteTemps = true;
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
    
    if (!opt.input && !opt.deleteTemps) {
        cerr << "Missing input file" << endl;
        usage(true);
    }
    if ((!opt.output || strcmp(opt.output, "-") == 0) && 
        !opt.output_fmt && !opt.check)
    {
        opt.outputStdout = true;
        opt.output_fmt = "-";
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

static nullostream cnull;

int main (int argc, char* argv[]) {
    options opts;
    int var = Variation::random(6);
    
#ifdef _WIN32
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
#else
    struct sigaction new_action, old_action;
    new_action.sa_handler = termination_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    sigaction(SIGINT, nullptr, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction(SIGINT, &new_action, nullptr);
#endif    
    
    processCommandLine(argc, argv, opts);
    
    if (opts.quiet) myCout = &cnull;
    
    clock_t startTime = clock();
    clock_t fromTime = startTime;
    clock_t clocksPerMsec = CLOCKS_PER_SEC / 1000;
    
    if (opts.variation < 0) opts.variation = var;
    std::string code = Variation::toString(opts.variation, false);
    
    CommandLineSystem system(opts.quiet);
    
    if (!opts.quiet || opts.deleteTemps) {
        vector<string> temps = system.findTempFiles();
        if (temps.empty()) {
            if (opts.deleteTemps)
                cerr << "No temporary files found." << endl;
        } else {
            if (opts.deleteTemps) {
                cerr << "Old temporary files deleted:\n";
                for (string& temp: temps)
                    if (remove(temp.c_str()))
                        cerr << "Failed to delete: " << temp << '\n';
                    else
                        cerr << temp << '\n';
                cerr << endl;
            } else {
                cerr << "Old temporary files found:\n";
                for (string& temp: temps)
                    cerr << temp << '\n';
                cerr << endl;
            }
        }
        
        if (!opts.input) exit(0);
    }
    
    CFDG* myDesign = CFDG::ParseFile(opts.input, &system, opts.variation);
    if (!myDesign) return 3;
    if (opts.check) return 0;
    if (opts.widthMult != 1 || opts.heightMult != 1) {
        if (!myDesign->isTiled() && !myDesign->isFrieze()) {
            cerr << "Tiled output multiplication only allowed for tiled or frieze designs." << endl;
            return 6;
        }
        if (opts.format != options::PNGfile && opts.format != options::BMPfile) {
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
    bool use16bit = (pixfmt & aggCanvas::Has_16bit_Color) != 0;
    const char* fmtnames[4] = { "PNG image", "SVG vector output", "Quicktime movie", "Wallpaper BMP image" };
    
    *myCout << "Generating " << (use16bit ? "16bit " : "8bit ") 
        << (useRGBA ? "color" : "gray-scale")
        << ' ' << fmtnames[opts.format]
        << ", variation " 
        << code << "..." << endl;
    
    { // Scope for canvas & renderer
    unique_ptr<pngCanvas> png;
    unique_ptr<SVGCanvas> svg;
    unique_ptr<ffCanvas>  mov;
    Canvas* myCanvas = nullptr;
        
    shared_ptr<Renderer> TheRenderer(myDesign->renderer(opts.width, opts.height, opts.minSize,
                                     opts.variation, opts.borderSize));
    
    if (TheRenderer == nullptr) {
        return 9;
    }
        
    gRenderer = TheRenderer;    // weak pointer for interrupt signal handler

    if (!opts.quiet) setupTimer(TheRenderer);
    
    TheRenderer->setMaxShapes(opts.maxShapes);
    TheRenderer->run(nullptr, false);
    
    opts.width = TheRenderer->m_width;
    opts.height = TheRenderer->m_height;
    opts.crop = opts.crop && !(myDesign->isTiled() || myDesign->isFrieze());
    
    switch (opts.format) {
        case options::BMPfile:
        case options::PNGfile: {
            png.reset(new pngCanvas(opts.output_fmt, opts.quiet, opts.width, opts.height,
                                    pixfmt, opts.crop, opts.animationFrames, opts.variation,
                                    opts.format == options::BMPfile, TheRenderer.get(),
                                    opts.widthMult, opts.heightMult));
            myCanvas = static_cast<Canvas*>(png.get());
            if (png->mWidth != opts.width || png->mHeight != opts.height) {
                TheRenderer->resetSize(png->mWidth, png->mHeight);
                opts.width = TheRenderer->m_width;
                opts.height = TheRenderer->m_height;
            }
            break;
        }
        case options::SVGfile: {
            string name = makeCFfilename(opts.output_fmt, 0, 0, opts.variation);
            svg.reset(new SVGCanvas(name.c_str(), opts.width, opts.height, opts.crop));
            myCanvas = static_cast<Canvas*>(svg.get());
            if (svg->mError)
                cerr << "Failed to open SVG file." << endl;
            break;
        }
        case options::MOVfile: {
            string name = makeCFfilename(opts.output_fmt, 0, 0, opts.variation);
            mov.reset(new ffCanvas(name.c_str(), pixfmt, opts.width, opts.height,
                                   opts.animationFPS));
            if (mov->mErrorMsg) {
                cerr << "Failed to create movie file: " << mov->mErrorMsg << endl;
                exit(8);
            }
            myCanvas = static_cast<Canvas*>(mov.get());
            break;
        }
    }
    
    if (myCanvas->mError || system.error(false) || TheRenderer->requestStop) {
        cleanupTimer();
        Renderer::AbortEverything = true;
        return 5;
    }
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << prettyInt(runTime) << " msec to execute." << endl;
        fromTime = toTime;
    }
    
    if (opts.animationFrames) {
        TheRenderer->animate(myCanvas, opts.animationFrames, opts.animationZoom);
    } else {
        TheRenderer->draw(myCanvas);
    }
    *myCout << endl;
    
    if (!opts.quiet) cleanupTimer();
    
    *myCout << "DONE!" << endl;
    *myCout << "The output file name is " << 
    makeCFfilename(opts.output_fmt, 0, 0, opts.variation) << endl;
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << prettyInt(runTime) << " msec to render." << endl;
        runTime = (toTime - startTime) / clocksPerMsec;
        *myCout << "The cfdg file took a total of " << prettyInt(runTime) << " msec to process." << endl;
    }
    
        Renderer::AbortEverything = !(opts.paramTest);
    }   // delete canvas & renderer
    
    if (opts.paramTest) {
        if (Renderer::ParamCount)
            cerr << "Left-over parameter blocks in memory:" << prettyInt(static_cast<unsigned long>(Renderer::ParamCount)) << endl;
        else
            *myCout << "All parameter blocks deleted" << endl;
    }
    
    return 0;
}


