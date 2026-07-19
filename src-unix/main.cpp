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
#include "args.hxx"
#include <cstdlib>
#include <cstdio>
#include "cfdg.h"
#include "variation.h"
#ifdef _WIN32
#include "WinBmpCanvas.h"
#include "WinPngCanvas.h"
using canvas_t = WinPngCanvas;
#else
#include "pngCanvas.h"
using canvas_t = pngCanvas;
using bmpCanvas = pngCanvas;
#endif
#include "SVGCanvas.h"
#include "commandLineSystem.h"
#include "version.h"
#include "makeCFfilename.h"
#include <memory>
#include <string>
#include "astexpression.h"
#include "prettyint.h"

using std::string;
using std::cerr;
using std::endl;

std::ostream* myCout = &cerr;

static std::weak_ptr<Renderer> gRenderer;

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

BOOL __stdcall CtrlHandler(DWORD ctrlType) 
{
    if (ctrlType != CTRL_C_EVENT && ctrlType != CTRL_BREAK_EVENT)
        return FALSE;
    return processInterrupt();
}
#else
#include <csignal>

void termination_handler(int)
{
    processInterrupt();
}
#endif

#ifdef _WIN32
#include "winTimer.h"
#define Timer WinTimer
#else
#include "posixTimer.h"
#define Timer PosixTimer
#endif

struct options {
    int   width = 500;
    int   height = 500;
    int   widthMult = 1;
    int   heightMult = 1;
    int   maxShapes = 0;
    double minSize = 0.3F;
    double borderSize = 2.0F;
    std::string definitions;
    
    int   variation = -1;
    bool  crop = false;
    bool  check = false;
    int   animationFrames = 0;
    int   animationTime = 0;
    int   animationFPS = 15;
    bool  animationZoom = false;
    int   animateFrame = 0;
    int   animationLoops = -1;
    pngCanvas::QTcodec animationCodec = pngCanvas::H264;
    
    std::string input;
    std::string output;
    pngCanvas::OutputFormat format = pngCanvas::PNGfile;
    std::string displayExec;
    
    bool quiet = false;
    bool outputTime = false;
    bool outputStdout = false;
    bool outputTemp = false;
    bool outputWallpaper = false;
    bool paramTest = false;
    bool deleteTemps = false;
    
    options()
    { }
};

int
intArg2(const std::string& arg, const std::string& sstr, int& x, int& y)
{
    char* end;
    const char* str = sstr.c_str();
    long int v = -1;
    
    v = strtol(str, &end, 10);
    if (end == str || v <= 0) {
        cerr << "Option " << arg << " takes a positive integer argument or a pair of positive integers (e.g., 500x300)" << endl;
        return 0;
    }
    x = static_cast<int>(v);
    if (*end == 'x') {
        str = end + 1;
        v = strtol(str, &end, 10);
        if (end == str || v <= 0) {
            cerr << "Option -" << arg << " takes a positive integer argument or a pair of positive integers (e.g., 500x300)" << endl;
            return 0;
        }
        y = static_cast<int>(v);
    } else {
        y = x;
        return 1;
    }
    return 2;
}

void
processCommandLine(int argc, char* argv[], options& opt)
{
    std::ostringstream name, epilog;
    name << APP_NAME(argv[0]) << " - " << APP_VERSION() << "(v" << APP_BUILD()
         << ") - Context Free Design Grammar";
    epilog << "If '-' is specified for the CFDG FILE then the input cfdg file is piped "
              "from standard input. If the output file name is omitted and the "
           << APP_OPTCHAR() << "o option and the " << APP_OPTCHAR()
           << "C option are not used then the output will be sent to stdout.";
    args::ArgumentParser parser(name.str(), epilog.str());
    parser.ShortPrefix(APP_OPTCHAR());      // Set Windows/posix command syntax
    parser.LongPrefix(APP_OPTLONG());
    parser.LongSeparator(APP_OPTSEP());
    parser.Terminator(APP_OPTLONG());
    parser.Prog(APP_NAME(argv[0]));         // Set app name minus path
    args::HelpFlag help(parser, "HELP", "Show this help menu.", {'?', "help"});
    args::Flag version(parser, "version", "Output version and quit.", {"version"});
    args::ValueFlag<int> width(parser, "WIDTH", "Output width", {'w', "width"}, 500);
    args::ValueFlag<int> height(parser, "HEIGHT", "Output height", {'h', "height"}, 500);
    args::ValueFlag<string> size(parser, "SIZE or WIDTHxHEIGHT",
                                 "Set output size to SIZExSIZE or WIDTHxHEIGHT",
                                 {'s', "size"}, "");
    args::ValueFlag<string> tile(parser, "SIZE or WIDTHxHEIGHT",
                                 "Multiply output by SIZExSIZE or WIDTHxHEIGHT",
                                 {'T', "tile"}, "");
    args::ValueFlag<int> maxShapes(parser, "MAXSHAPES",
                                   "Maximum number of shapes", {'m', "maxshapes"}, 0);
    args::ValueFlag<double> minSize(parser, "MINIMUM SIZE",
                                    "Minimum size of shapes in pixels/mm (default 0.3)",
                                    {'x', "minimumsize"}, 0.3);
    args::ValueFlag<double> borderSize(parser, "BORDER SIZE", "Border size [-1,2]: "
                                       "-1=-8 pixel border, 0=no border, 1=8 pixel "
                                       "border, 2=variable-sized border",
                                       {'b', "bordersize"}, 2.0);
    args::ValueFlag<string> variation(parser, "VARIATION",
        "Set the variation code (default is random)", {'v', "variation"}, "");
    args::ValueFlagList<string> definition(parser, "NAME=VALUE",
        "Define a variable, configuration, or function. Overrides definitions in the input file.", {'D'});
    args::ValueFlag<string> animation(parser, "NUM or TIMExFPS",
        "Generate NUM animation frames at 15fps or TIMExFPS animation frames",
        {'a',"animate"}, "");
    args::ValueFlag<int> frame(parser, "FRAME", "Animate a particular frame", {'f', "frame"}, 0);
    args::Flag zoom(parser, "zoom", "Zoom out during animation", {'z', "zoom"});
    args::Flag makeSVG(parser, "SVG", "Generate SVG output (not allowed for animation)",
                       {'V', "svg"});
    args::Flag makeJSON(parser, "JSON", "Generate JSON output of parsed cfdg file",
                       {'J', "json"});
    args::Flag makeQT(parser, "quicktime", "Make QuickTime output", {'Q', "quicktime"});
    args::ValueFlag<int> makeGIF(parser, "GIF LOOPS", "Make GIF output w/specified loops", { 'G', "gif" });
    args::Flag makeProRes(parser, "ProRes", "Use ProRes codec for QuickTime output", { "prores" });
#ifdef _WIN32
    args::Flag wallpaper(parser, "wallpaper", "Generate desktop wallpaper output",
                         {'W', "wallpaper"});
#else
    const bool wallpaper = false;
#endif
    args::ValueFlag<string> display(parser, "display executable", "Display output with specified program", {"display"}, "");
    args::Flag crop(parser, "crop", "Crop output", {'c', "crop"});
    args::Flag quiet(parser, "quiet", "Quiet mode, suppress non-error output", {'q', "quiet"});
    args::Flag check(parser, "check", "Check syntax of cfdg file and exit", {'C', "check"});
    args::Flag timer(parser, "time", "Output the time taken to render the cfdg file", {'t', "time"});
    args::Flag paramDebug(parser, "param debug", "Parameter allocation debug, test "
        "whether all the parameter blocks were cleaned up", {'P', "paramdebug"});
    args::Flag cleanup(parser, "cleanup", "Delete old temporary files", {'d', "cleanup"});
    args::Positional<std::string> inputFile(parser, "CFDG FILE", "Input cfdg file. "
                                            "'-' takes input from standard input.", "");
    args::Positional<std::string> outputFile(parser, "OUTPUT FILE TEMPLATE",
         "Set the output file name, supports variable expansion %f expands to the "
         "animation frame number, %v and %V expands to the variation code in lower "
         "or upper case, %% expands to %. '-' sends output to standard output.", "");

    auto bailout = [&](const char * msg) {
        if (msg && *msg)
            cerr << msg << '\n' << endl;
        cerr << parser;
        exit(2);
    };
    
    try {
        if (!parser.ParseCLI(argc, argv))
            bailout("Too many arguments.");
    } catch (args::Help&) {
        std::cout << parser;
        exit(0);
    } catch (args::Error& e) {
        bailout(e.what());
    }
    
    if (version) {
        std::cout << name.str() << endl;
        exit(0);
    }
    if (width) opt.width = args::get(width);
    if (height) opt.height = args::get(height);
    if (opt.width < 10 || opt.height < 10)
        bailout("Minimum output dimensions are 10 pixels.");
    if (size && intArg2(parser.ShortPrefix() + 's', args::get(size), opt.width, opt.height) < 1)
        bailout(nullptr);
    if (tile && intArg2(parser.ShortPrefix() + 'T', args::get(tile), opt.widthMult, opt.heightMult) < 1)
        bailout(nullptr);
    if (maxShapes) {
        opt.maxShapes = args::get(maxShapes);
        if (opt.maxShapes < 1)
            bailout("Must specify at least one shape.");
    }
    if (minSize) opt.minSize = args::get(minSize);
    if (borderSize) {
        opt.borderSize = args::get(borderSize);
        if (opt.borderSize < -1.0 || opt.borderSize > 2.0)
            bailout("Border size must be between -1 and 2");
    }
    if (variation) {
        opt.variation = Variation::fromString(args::get(variation));
        if (opt.variation == -1)
            bailout("Error parsing variation");
    }
    if (definition) {
        auto defs = definition.Get();
        for (auto&& def: defs) {
            auto equal = def.find("=");
            if (equal == std::string::npos || equal == 0 || equal == def.length() - 1)
                bailout("Definitions must be of the form -Dname=value");
            opt.definitions.append(def);
            opt.definitions += ' ';
        }
    }
    if (display) opt.displayExec = args::get(display);
    if (animation) {
        if (makeSVG) bailout("Animation cannot output to SVG files.");
        if (crop) bailout("Animation cannot output cropped files.");
        if (makeQT) opt.format = pngCanvas::MOVfile;
        if (makeGIF) {
            opt.format = pngCanvas::GIFfile;
            opt.animationCodec = pngCanvas::GIF;
            opt.animationLoops = makeGIF.Get();
            if (opt.animationLoops == 1)
                opt.animationLoops = -1;
            if (opt.animationLoops > 1)
                --opt.animationLoops;
        }
        if (makeQT && makeGIF) bailout("Cannot encode QuickTime and GIF at the same time.");
        if (makeProRes) opt.animationCodec = pngCanvas::ProRes;
        opt.animationZoom = zoom;
        int fps = 15, time = 0;
        switch (intArg2(parser.ShortPrefix() + 'a', args::get(animation), time, fps)) {
            case 2:
                opt.animationTime = time;
                opt.animationFPS = fps;
                opt.animationFrames = time * fps;
                break;
            case 1:
                opt.animationTime = time / opt.animationFPS;
                opt.animationFrames = time;
                break;
            default:
                bailout(nullptr);
        }
        if (display && !(makeQT || makeGIF))
            bailout("Only QuickTime/GIF animations can be displayed.");
        if ((makeQT || makeGIF) && !canvas_t::ffAvailable())
            bailout("FFmpeg not found, QuickTime/GIF output is unavailable.");
        if (makeProRes && !makeQT)
            bailout("ProRes codec only available with QuickTime output.");
        if (frame) {
            if (makeQT || makeGIF)
                bailout("Single frame animation only outputs PNG files.");
            opt.animateFrame = args::get(frame);
            if (opt.animateFrame < 1)
                bailout("Animation frame must be a positive integer.");
            if (opt.animateFrame > opt.animationFrames)
                bailout("Animation frame is after the end of the animation.");
        }
    } else {
        if (makeQT)
            bailout("QuickTime output is only available when animating.");
        if (makeGIF)
            bailout("GIF output is only available when animating.");
        if (zoom)
            bailout("Zoomed output is only available when animating.");
        if (frame)
            bailout("Animation frame can only be rendered when animating.");
    }
    if (makeSVG) opt.format = pngCanvas::SVGfile;
    if (wallpaper) {
        if (makeSVG || animation || crop)
            bailout("Wallpaper output must be uncropped, not animated, and not SVG.");
        opt.format = pngCanvas::BMPfile;
        opt.outputWallpaper = true;
    }
    if (makeJSON) opt.format = pngCanvas::JSONfile;
    opt.crop = crop;
    opt.check = check;
    opt.quiet = quiet;
    opt.outputTime = timer;
    opt.paramTest = paramDebug;
    opt.deleteTemps = cleanup;
    if (quiet && cleanup)
        bailout("Cannot clean up temporary files quietly.");
    if (inputFile) opt.input = args::get(inputFile);
    if (outputFile) opt.output = args::get(outputFile);
    if (!inputFile && !cleanup)
        bailout("Missing input file.");
    if (!outputFile && display)
        opt.outputTemp = true;
    if ((!outputFile || opt.output == "-") && !check && !opt.outputTemp) {
        opt.outputStdout = true;
        opt.output = "-";
        opt.quiet = true;
    }
    if (opt.format == pngCanvas::PNGfile && animation && !frame) {
        if (!opt.output.ends_with(".png"))
            bailout("PNG animation frame files must end with .png");
        if (opt.output.find("%f") == std::string::npos)
            bailout("PNG animation frame template must contain %f");
    }
    if (opt.format != pngCanvas::PNGfile || !animation || frame)
        if (opt.output.find("%f") != std::string::npos)
            bailout("Only PNG animation frame templates can contain %f");
    if (makeQT || makeGIF) {
        if (opt.outputStdout)
            bailout("Animation output requires an output file.");
        if (makeQT && !opt.output.ends_with(".mov"))
            bailout("QuickTime files must end with .mov");
        if (makeGIF && !opt.output.ends_with(".gif"))
            bailout("GIF files must end with .gif");
    }
}

class nullstreambuf : public std::streambuf
{
protected:
    int overflow(int c) { return c; }
};
class nullostream : public std::ostream
{
public:
    nullostream() : std::ostream(new nullstreambuf()) {}
};

static nullostream cnull;

namespace {
    struct OstreamCloser
    {
        void operator()(std::ostream* ptr) const {
            if (ptr != &std::cout)
                delete ptr;        // Not called if nullptr
        }
    };
}


int main (int argc, char* argv[]) {
    options opts;
    int var = Variation::random(6);
    Timer timer;
    
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
        auto temps = system.findTempFiles();
        if (temps.empty()) {
            if (opts.deleteTemps)
                cerr << "No temporary files found." << endl;
        } else {
            if (opts.deleteTemps) {
                cerr << "Old temporary files deleted:\n";
                for (auto&& temp : temps)
                    if (system.deleteTempFile(temp))
                        fprintf(stderr, "Failed to delete: " FileFormat "\n", temp.c_str());
                    else 
                        fprintf(stderr, FileFormat "\n", temp.c_str());
                cerr << endl;
            } else {
                cerr << "Old temporary files found:\n";
                for (auto&& temp: temps)
                    fprintf(stderr, FileFormat "\n", temp.c_str());
                cerr << endl;
            }
        }
        
        if (opts.input.empty()) exit(0);
    }
    
    AST::ASTfunction::RandStaticIsConst = opts.format != pngCanvas::JSONfile;
    cfdg_ptr myDesign = CFDG::ParseFile(opts.input.c_str(), &system,
                                        opts.variation, opts.definitions);
    if (!myDesign) return 3;
    if (opts.check) return 0;
    if (opts.format == pngCanvas::JSONfile) {
        std::unique_ptr<std::ostream, OstreamCloser> out(nullptr);
        if (opts.outputStdout)
            out.reset(&std::cout);
        else
            out.reset(new std::ofstream(opts.output));
        myDesign->serialize(*out);
        return 0;
    }
    if (opts.widthMult != 1 || opts.heightMult != 1) {
        if (!myDesign->isTiled() && !myDesign->isFrieze()) {
            cerr << "Tiled output multiplication only allowed for tiled or frieze designs." << endl;
            return 6;
        }
        if (opts.format != pngCanvas::PNGfile && opts.format != pngCanvas::BMPfile) {
            cerr << "Tiled output multiplication only allowed for PNG output." << endl;
            return 6;
        }
    }

    bool useRGBA = myDesign->usesColor;
    aggCanvas::PixelFormat pixfmt = aggCanvas::SuggestPixelFormat(myDesign.get());
    bool use16bit = (pixfmt & aggCanvas::Has_16bit_Color) != 0;
    bool usecustom = (pixfmt & aggCanvas::Has_Custom_Blend) != 0;
    const char* fmtnames[5] = { "PNG image", "SVG vector output", "Quicktime movie", "Wallpaper BMP image", "Animated GIF" };
    
    *myCout << "Generating " << (use16bit ? "16bit " : "8bit ") 
        << (useRGBA ? "color" : "gray-scale")
        << (usecustom ? ", custom blend" : "")
        << ' ' << fmtnames[opts.format]
        << ", variation " 
        << code << "..." << endl;

    std::string actualFileName;

    { // Scope for canvas & renderer
    std::unique_ptr<canvas_t> png;
    std::unique_ptr<SVGCanvas> svg;
    std::unique_ptr<bmpCanvas> bmp;
    Canvas* myCanvas = nullptr;
        
    std::shared_ptr<Renderer> TheRenderer(myDesign->renderer(myDesign,
                                          opts.width, opts.height, opts.minSize,
                                          opts.variation, opts.borderSize));
    
    if (TheRenderer == nullptr) {
        return 9;
    }
        
    gRenderer = TheRenderer;    // weak pointer for interrupt signal handler

    if (!opts.quiet) timer.Start(TheRenderer);
    
    if (opts.maxShapes > 0)
        TheRenderer->setMaxShapes(opts.maxShapes);
        
    if (opts.animationFrames == 0)
        TheRenderer->run(nullptr, false);
    
    opts.width = TheRenderer->m_width;
    opts.height = TheRenderer->m_height;
    opts.crop = opts.crop && !(myDesign->isTiled() || myDesign->isFrieze());
    string animfile;
    
    switch (opts.format) {
        case pngCanvas::BMPfile: {
            bmp = std::make_unique<bmpCanvas>(
                    opts.output.c_str(), opts.quiet, opts.width, opts.height,
                    pixfmt, opts.crop, opts.animationFrames, opts.variation,
                    true, TheRenderer.get(),
                    opts.widthMult, opts.heightMult, opts.outputTemp, system);
            myCanvas = static_cast<Canvas*>(bmp.get());
            if (bmp->mWidth != opts.width || bmp->mHeight != opts.height) {
                TheRenderer->resetSize(bmp->mWidth, bmp->mHeight);
                opts.width = TheRenderer->m_width;
                opts.height = TheRenderer->m_height;
            }
            break;
        }
        case pngCanvas::PNGfile: {
            png = std::make_unique<canvas_t>(
                                    opts.output.c_str(), opts.quiet, opts.width, opts.height,
                                    pixfmt, opts.crop, opts.animationFrames, opts.variation,
                                    false, TheRenderer.get(),
                                    opts.widthMult, opts.heightMult, opts.outputTemp, system);
            myCanvas = static_cast<Canvas*>(png.get());
            if (png->mWidth != opts.width || png->mHeight != opts.height) {
                TheRenderer->resetSize(png->mWidth, png->mHeight);
                opts.width = TheRenderer->m_width;
                opts.height = TheRenderer->m_height;
            }
            break;
        }
        case pngCanvas::SVGfile: {
            string name = makeCFfilename(opts.output.c_str(), 0, 0, opts.variation);
            svg = std::make_unique<SVGCanvas>(name.c_str(), opts.width, opts.height, opts.crop, 
                                              nullptr, -1, opts.outputTemp);
            myCanvas = static_cast<Canvas*>(svg.get());
            break;
        }
        case pngCanvas::GIFfile: {
            animfile = makeCFfilename(opts.output.c_str(), 0, 0, opts.variation);
            png = std::make_unique<canvas_t>(
                animfile.c_str(), opts.quiet, opts.width, opts.height,
                pixfmt, opts.crop, opts.animationFrames, opts.variation,
                false, TheRenderer.get(),
                opts.widthMult, opts.heightMult, true, system);
            myCanvas = static_cast<Canvas*>(png.get());
            break;
        }
        case pngCanvas::MOVfile: {
            animfile = makeCFfilename(opts.output.c_str(), 0, 0, opts.variation);
            png = std::make_unique<canvas_t>(
                animfile.c_str(), opts.quiet, opts.width, opts.height,
                pixfmt, opts.crop, opts.animationFrames, opts.variation,
                false, TheRenderer.get(),
                opts.widthMult, opts.heightMult, true, system);
            myCanvas = static_cast<Canvas*>(png.get());
            break;
        }
        case pngCanvas::JSONfile:
            break;
    }
    
    if (myCanvas->mError || system.error(false) || TheRenderer->requestStop) {
        timer.Stop();
        Renderer::AbortEverything = true;
        cerr << "Failed to create output file." << endl;
        return 5;
    }
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << prettyInt(runTime) << " msec to execute." << endl;
        fromTime = toTime;
    }
    
    if (opts.animationFrames) {
        TheRenderer->animate(myCanvas, opts.animationFrames, opts.animateFrame, opts.animationZoom);
        if (!png->completeMovie(opts.animationFPS, opts.animationLoops, 
            opts.format, opts.animationCodec, myDesign->usesAlpha))
        {
            cerr << "\n\nError creating the output animation file.\n" << endl;
            return 4;
        }
    } else {
        TheRenderer->draw(myCanvas);
    }
    *myCout << endl;
    
    if (!opts.quiet) timer.Stop();
    
    *myCout << "DONE!" << endl;
    *myCout << "The output file name is " << 
    makeCFfilename(opts.output.c_str(), 0, 0, opts.variation) << endl;
    
    if (opts.outputTime) {
        clock_t toTime = clock();
        clock_t runTime = (toTime - fromTime) / clocksPerMsec;
        *myCout << "The cfdg file took " << prettyInt(runTime) << " msec to render." << endl;
        runTime = (toTime - startTime) / clocksPerMsec;
        *myCout << "The cfdg file took a total of " << prettyInt(runTime) << " msec to process." << endl;
    }

        Renderer::AbortEverything = !(opts.paramTest);
        actualFileName = myCanvas->mFileName;
    }   // delete canvas & renderer
    
    if (!opts.displayExec.empty()) {
        opts.displayExec += ' ';
        opts.displayExec += actualFileName;
        if (std::system(opts.displayExec.c_str()) != 0)
            cerr << "\n\nError viewing the output file.\n" << endl;
    }
    
    if (opts.paramTest) {
        myDesign.reset();   // Delete the AST and its parameters before checking
        if (Renderer::ParamCount) {
            cerr << "Left-over parameter blocks in memory:" << prettyInt(static_cast<unsigned long>(Renderer::ParamCount)) << endl;
			return 88;
		} else {
            *myCout << "All parameter blocks deleted" << endl;
		}
    }
    
    return 0;
}


