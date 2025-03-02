/*
Module : ScintillaCtrl.cpp
Purpose: Defines the implementation for an MFC wrapper class for the Scintilla edit control (www.scintilla.org)
Created: PJN / 19-03-2004
History: PJN / 19-03-2004 1. Initial implementation synchronized to the v1.59 release of Scintilla
         PJN / 19-03-2004 1. Updated the sample app's Find Next and Find Previous marker functions. Now correctly
                          goes to the next and previous markers when a marker is on the current line.
                          2. Updated the sample app's passing of messages to Scintilla from the top level
                          CMainFrame window
         PJN / 06-06-2004 1. Updated class to work with Scintilla v1.61
         PJN / 20-12-2004 1. Updated class to work with Scintilla v1.62.
                          2. Sample app now includes a common control 6 manifest
                          3. Sample app now includes an example of scintilla autocompletion. When you type 
                          "scintilla is " case insensitively a autocompletion list is displayed which allows 
                          "very cool", "easy" or "way cool!!" to be entered. 
                          4. Sample app now includes an example of scintilla calltips. Whenever you hover
                          over text which is "author " case insensitively, a call tip with the text 
                          "PJ Naughter" is displayed.
         PJN / 10-07-2005 1. Updated class to work with Scintilla v1.64.
                          2. Fixed a number of warnings when the code is compiled using Visual Studio .NET 2003. 
         PJN / 03-01-2006.1. Updated class to work with Scintilla v1.67. New messages wrapped include: 
                          SCI_MARKERADDSET, SCI_SETPASTECONVERTENDINGS, SCI_GETPASTECONVERTENDINGS,
                          SCI_SELECTIONDUPLICATE and SCI_GETSTYLEBITSNEEDED. 
                          2. Updated copyright messages
         PJN / 14-03-2006 1. Updated class to work with Scintilla v1.68. New messages wrapped include:
                          SCI_CALLTIPUSESTYLE, SCI_SETCARETLINEBACKALPHA and SCI_GETCARETLINEBACKALPHA.
         PJN / 05-06-2006 1. Updated class to work with Scintilla v1.69. New messages wrapped include:
                          SCI_MARKERSETALPHA, SCI_GETSELALPHA and SCI_SETSELALPHA. 
         PJN / 06-06-2006 1. Updated the wrapper class to work correctly when compiled for Unicode.
         PJN / 29-06-2006 1. Code now uses new C++ style casts rather than old style C casts where necessary. 
                          2. Optimized CScintillaCtrl constructor code
                          3. Updated the code to clean compile in VC 2005
                          4. Fixed a bug in the sample program when you invoke Print Preview when compiled
                          using VC 2005
         PJN / 27-07-2006 1. Minor update to the sample app to fix an ASSERT related to the formatting of the
                          IDR_SCINTITYPE string resource. Thanks to Matt Spear for reporting this issue.
         PJN / 17-09-2006 1. Fixed a bug in UTF82W (and W2UTF8) where if GetLine is called in a Unicode build
                          for the end of the file (i.e. a line having a length of 0), the UTF82W function would
                          allocate no buffer, but still erroneously write a one character terminating null. In 
                          addition, the caller (GetLine) will try to deallocate the buffer that was never 
                          allocated. Thanks to Scott Kelley for spotting this nasty bug.
                          2. Added of a GetLineEx method which explicitly sets the first WORD value in the text 
                          string to the maximum size. This avoids client code from having to deal with the
                          weird semantics of the EM_GETLINE message. Thanks to Scott Kelley for providing this
                          nice addition.
                          3. Verified code implements all the functionality of Scintilla v1.71
         PJN / 11-06-2007 1. Updated copyright details.
                          2. CScintillaCtrl::GetSelText now uses CString::GetBufferSetLength to avoid having to
                          allocate an intermediate buffer. Thanks to Jochen Neubeck for reporting this 
                          optimization
                          3. Addition of a SCINTILLACTRL_EXT_CLASS preprocessor macro to allow the classes to be 
                          more easily used in an extension DLL.
                          4. Updated class to work with Scintilla v1.73. New messages wrapped include:
                          SCI_STYLEGETFORE, SCI_STYLEGETBACK, SCI_STYLEGETBOLD, SCI_STYLEGETITALIC, SCI_STYLEGETSIZE,
                          SCI_STYLEGETFONT, SCI_STYLEGETEOLFILLED, SCI_STYLEGETUNDERLINE, SCI_STYLEGETCASE,
                          SCI_STYLEGETCHARACTERSET, SCI_STYLEGETVISIBLE, SCI_STYLEGETCHANGEABLE, SCI_STYLEGETHOTSPOT,
                          SCI_GETSELEOLFILLED, SCI_SETSELEOLFILLED, SCI_GETHOTSPOTACTIVEFORE, SCI_GETHOTSPOTACTIVEBACK,
                          SCI_GETHOTSPOTACTIVEUNDERLINE & SCI_GETHOTSPOTSINGLELINE
         PJN / 28-11-2007 1. Updated class to work with Scintilla v1.75. New messages wrapped include: SCI_INDICSETUNDER, 
                          SCI_INDICGETUNDER, new behavior for SCI_SETINDENTATIONGUIDES & SCI_GETINDENTATIONGUIDES, 
                          SCI_SETSCROLLWIDTHTRACKING, SCI_GETSCROLLWIDTHTRACKING, SCI_DELWORDRIGHTEND, SCI_SETCARETSTYLE, 
                          SCI_GETCARETSTYLE, SCI_SETINDICATORCURRENT, SCI_SETINDICATORVALUE, SCI_INDICATORFILLRANGE, 
                          SCI_INDICATORCLEARRANGE, SCI_INDICATORALLONFOR, SCI_INDICATORVALUEAT, SCI_INDICATORSTART, 
                          SCI_INDICATOREND, SCI_SETPOSITIONCACHE & SCI_GETPOSITIONCACHE.
                          2. The auto completion sample in CScintillaDemoView::OnCharAdded has been extended to show
                          another style of auto completion. Thanks to Alessandro Limonta for suggesting this update.
         PJN / 19-03-2008 1. Updated class to work with Scintilla v1.76. New messages wrapped include: SCI_COPYALLOWLINE.
                          2. Updated copyright details.
                          3. Updated code to clean compile on VC 2008.
                          4. Removed VC 6 style classwizard comments from the code.
                          5. Updated the sample apps document icon.
                          6. Fixed a level 4 warning when the code is compiled on VC 6.
         PJN / 15-06-2008 1. Code now compiles cleanly using Code Analysis (/analyze)
                          2. Updated code to compile correctly using _ATL_CSTRING_EXPLICIT_CONSTRUCTORS define
                          3. The code now only supports VC 2005 or later.
         PJN / 01-11-2008 1. Updated class to work with Scintilla v1.77. New messages wrapped include: 
                          SCI_GETCHARACTERPOINTER, SCI_SETKEYSUNICODE & SCI_GETKEYSUNICODE
                          2. Reworked all the key Unicode functions which expose string length management and 
                          reimplemented them to use CScintillaCtrl::StringW output parameters. Equivalent ASCII versions have also been 
                          provided. This new approach helps to raise the level of abstraction provided by the wrapper 
                          class. In the process the need for the GetLineEx function has been removed. Thanks to Alexei 
                          Letov for prompting this update.
         PJN / 20-01-2009 1. Updated copyright details.
         PJN / 03-10-2009 1. Fixed a bug in CScintillaCtrl::Create where a crash can occur in a Unicode build if the CreateEx
                          call fails (for example, if the Scintilla DLL was not loaded). Thanks to Simon Smith for reporting
                          this bug
                          2. Updated class to work with Scintilla v2.01. New messages wrapped include:
                          SCI_SETWRAPINDENTMODE, SCI_GETWRAPINDENTMODE, SCI_INDICSETALPHA, SCI_INDICGETALPHA, SCI_SETEXTRAASCENT, 
                          SCI_GETEXTRAASCENT, SCI_SETEXTRADESCENT, SCI_GETEXTRADESCENT, SCI_MARKERSYMBOLDEFINED, SCI_MARGINSETTEXT, 
                          SCI_MARGINGETTEXT, SCI_MARGINSETSTYLE, SCI_MARGINGETSTYLE, SCI_MARGINSETSTYLES, SCI_MARGINGETSTYLES, 
                          SCI_MARGINTEXTCLEARALL, SCI_MARGINSETSTYLEOFFSET, SCI_MARGINGETSTYLEOFFSET, SCI_ANNOTATIONSETTEXT, 
                          SCI_ANNOTATIONGETTEXT, SCI_ANNOTATIONSETSTYLE, SCI_ANNOTATIONGETSTYLE, SCI_ANNOTATIONSETSTYLES, 
                          SCI_ANNOTATIONGETSTYLES, SCI_ANNOTATIONGETLINES, SCI_ANNOTATIONCLEARALL, SCI_ANNOTATIONSETVISIBLE, 
                          SCI_ANNOTATIONGETVISIBLE, SCI_ANNOTATIONSETSTYLEOFFSET, SCI_ANNOTATIONGETSTYLEOFFSET, 
                          SCI_ADDUNDOACTION, SCI_CHARPOSITIONFROMPOINT, SCI_CHARPOSITIONFROMPOINTCLOSE, SCI_SETMULTIPLESELECTION, 
                          SCI_GETMULTIPLESELECTION, SCI_SETADDITIONALSELECTIONTYPING, SCI_GETADDITIONALSELECTIONTYPING, 
                          SCI_SETADDITIONALCARETSBLINK, SCI_GETADDITIONALCARETSBLINK, SCI_GETSELECTIONS, SCI_CLEARSELECTIONS, 
                          SCI_SETSELECTION, SCI_ADDSELECTION, SCI_SETMAINSELECTION, SCI_GETMAINSELECTION, SCI_SETSELECTIONNCARET, 
                          SCI_GETSELECTIONNCARET, SCI_SETSELECTIONNANCHOR, SCI_GETSELECTIONNANCHOR, SCI_SETSELECTIONNCARETVIRTUALSPACE, 
                          SCI_GETSELECTIONNCARETVIRTUALSPACE, SCI_SETSELECTIONNANCHORVIRTUALSPACE, SCI_GETSELECTIONNANCHORVIRTUALSPACE, 
                          SCI_SETSELECTIONNSTART, SCI_GETSELECTIONNSTART, SCI_SETSELECTIONNEND, SCI_GETSELECTIONNEND, 
                          SCI_SETRECTANGULARSELECTIONCARET, SCI_GETRECTANGULARSELECTIONCARET, SCI_SETRECTANGULARSELECTIONANCHOR, 
                          SCI_GETRECTANGULARSELECTIONANCHOR, SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE, SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE, 
                          SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE, SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE, 
                          SCI_SETVIRTUALSPACEOPTIONS, SCI_GETVIRTUALSPACEOPTIONS, SCI_SETRECTANGULARSELECTIONMODIFIER, 
                          SCI_GETRECTANGULARSELECTIONMODIFIER, SCI_SETADDITIONALSELFORE, SCI_SETADDITIONALSELBACK, SCI_SETADDITIONALSELALPHA, 
                          SCI_GETADDITIONALSELALPHA, SCI_SETADDITIONALCARETFORE, SCI_GETADDITIONALCARETFORE, SCI_ROTATESELECTION &
                          SCI_SWAPMAINANCHORCARET
         PJN / 22-11-2010 1. Updated copyright details.
                          2. Updated sample app to clean compile on VC 2010
                          3. Updated class to work with Scintilla v2.22. New messages wrapped include:
                          SCI_SETWHITESPACESIZE, SCI_GETWHITESPACESIZE, SCI_SETFONTQUALITY, SCI_GETFONTQUALITY, SCI_SETFIRSTVISIBLELINE, 
                          SCI_SETMULTIPASTE, SCI_GETMULTIPASTE, SCI_GETTAG, SCI_AUTOCGETCURRENTTEXT, SCI_SETADDITIONALCARETSVISIBLE,
                          SCI_GETADDITIONALCARETSVISIBLE, SCI_CHANGELEXERSTATE, SCI_CONTRACTEDFOLDNEXT, SCI_VERTICALCENTRECARET,
                          SCI_GETLEXERLANGUAGE, SCI_PRIVATELEXERCALL, SCI_PROPERTYNAMES, SCI_PROPERTYTYPE, SCI_DESCRIBEPROPERTY, 
                          SCI_DESCRIBEKEYWORDSETS. Also there were some parameter changes to existing messages.
         PJN / 01-04-2011 1. Updated copyright details.
                          2. Updated class to work with Scintilla v2.25. New messages wrapped include:
                          SCI_SETMARGINCURSORN & SCI_GETMARGINCURSORN
         PJN / 09-12-2011 1. Updated class to work with Scintilla v3.0.2. New messages wrapped include: SCI_MARKERSETBACKSELECTED, 
                          SCI_MARKERENABLEHIGHLIGHT, SCI_STYLESETSIZEFRACTIONAL, SCI_STYLEGETSIZEFRACTIONAL, SCI_STYLESETWEIGHT, 
                          SCI_STYLEGETWEIGHT, SCI_COUNTCHARACTERS, SCI_SETEMPTYSELECTION, SCI_CALLTIPSETPOSITION, SCI_GETALLLINESVISIBLE,
                          SCI_BRACEHIGHLIGHTINDICATOR, SCI_BRACEBADLIGHTINDICATOR, SCI_INDICSETOUTLINEALPHA, SCI_INDICGETOUTLINEALPHA,
                          SCI_SETMARGINOPTIONS, SCI_GETMARGINOPTIONS, SCI_MOVESELECTEDLINESUP, SCI_MOVESELECTEDLINESDOWN, SCI_SETIDENTIFIER, 
                          SCI_GETIDENTIFIER, SCI_RGBAIMAGESETWIDTH, SCI_RGBAIMAGESETHEIGHT, SCI_MARKERDEFINERGBAIMAGE, SCI_REGISTERRGBAIMAGE, 
                          SCI_SCROLLTOSTART, SCI_SCROLLTOEND, SCI_SETTECHNOLOGY, SCI_GETTECHNOLOGY & SCI_CREATELOADER
                          Messages dropped include: SCI_SETUSEPALETTE & SCI_GETUSEPALETTE
         PJN / 15-08-2012 1. Updated copyright details
                          2. Updated class to work with Scintilla v3.2.1 New Messaged wrapped include: SCI_DELETERANGE, SCI_GETWORDCHARS,
                          SCI_GETWHITESPACECHARS, SCI_SETPUNCTUATIONCHARS, SCI_GETPUNCTUATIONCHARS, SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR,
                          SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR, SCI_GETRANGEPOINTER, SCI_GETGAPPOSITION, SCI_FINDINDICATORSHOW, 
                          SCI_FINDINDICATORFLASH & SCI_FINDINDICATORHIDE.
                          3. SetDocPointer method now uses a void* parameter instead of an int. This prevents a pointer truncation issue
                          on 64bit platforms. Thanks to Kenny Liu for reporting this issue.
                          4. GetDocPointer method now also returns a void* instead of an int return value
                          5. Updated the code to clean compile on VC 2012
         PJN / 18-01-2013 1. Updated copyright details
                          2. Updated class to work with Scintilla v3.2.4. New messages wrapped include: SCI_GETSELECTIONEMPTY,
                          SCI_RGBAIMAGESETSCALE, SCI_VCHOMEDISPLAY, SCI_VCHOMEDISPLAYEXTEND, SCI_GETCARETLINEVISIBLEALWAYS & 
                          SCI_SETCARETLINEVISIBLEALWAYS.
                          3. The classes are now encapsulated in a Scintilla namespace if the SCI_NAMESPACE define
                          is defined. This is consistent with how the scintilla.h header file operates in the 
                          presence of this define. Thanks to Markus Nissl for prompting this update.
                          4. Updated the sample app to compile when the SCI_NAMESPACE define is defined.
                          5. The sample app is now built by default with the SCI_NAMESPACE defined. This means that all the 
                          classes of the author will appear in the "Scintilla" namespace.
                          6. The demo app now loads the SciLexer.dll from the application directory only. This avoids DLL planting security 
                          issues.
         PJN / 23-02-2013 1. PrivateLexerCall method now uses a void* parameter instead of an int. This prevents a pointer truncation issue
                          on 64bit platforms. Thanks to Simon Smith for reporting this issue.
         PJN / 18-01-2013 1. Updated class to work with Scintilla v3.3.3. New messages wrapped include: SCI_SCROLLRANGE, SCI_FOLDLINE, 
                          SCI_FOLDCHILDREN, SCI_EXPANDCHILDREN, SCI_FOLDALL, SCI_SETAUTOMATICFOLD, SCI_GETAUTOMATICFOLD, SCI_AUTOCSETORDER,
                          SCI_AUTOCGETORDER, SCI_RELEASEALLEXTENDEDSTYLES, SCI_ALLOCATEEXTENDEDSTYLES, SCI_SETLINEENDTYPESALLOWED, 
                          SCI_GETLINEENDTYPESALLOWED, SCI_GETLINEENDTYPESACTIVE, SCI_GETLINEENDTYPESSUPPORTED, SCI_ALLOCATESUBSTYLES,
                          SCI_GETSUBSTYLESSTART, SCI_GETSUBSTYLESLENGTH, SCI_FREESUBSTYLES, SCI_SETIDENTIFIERS, SCI_DISTANCETOSECONDARYSTYLES &
                          SCI_GETSUBSTYLEBASES.
                          2. Updated all the MFC MESSAGE_MAP's to use modern C++ style to reference methods of a class.
                          3. Fixed a heap overwrite bug in the two versions of the GetSelText(BOOL bDirect) method. The code now correctly uses
                          SCI_GETSELTEXT(0,0) to determine the buffer size to retrieve the data into. Thanks to Bengt Vagnhammar for reporting
                          this bug.
         PJN / 26-01-2015 1. Updated copyright details
                          2. Updated the code to clean compile on VC 2013
                          3. Updated class to work with Scintilla v3.5.3. New messages wrapped include: SCI_CHANGEINSERTION,
                          SCI_CLEARTABSTOPS, SCI_ADDTABSTOP, SCI_GETNEXTTABSTOP, SCI_GETIMEINTERACTION, SCI_SETIMEINTERACTION, 
                          SCI_CALLTIPSETPOSSTART, SCI_GETPHASESDRAW, SCI_SETPHASESDRAW, SCI_POSITIONRELATIVE, SCI_AUTOCSETMULTI, 
                          SCI_AUTOCGETMULTI, SCI_SETMOUSESELECTIONRECTANGULARSWITCH, SCI_GETMOUSESELECTIONRECTANGULARSWITCH, 
                          SCI_DROPSELECTIONN, SCI_SETREPRESENTATION, SCI_GETREPRESENTATION, SCI_CLEARREPRESENTATION, 
                          SCI_GETSTYLEFROMSUBSTYLE & SCI_GETPRIMARYSTYLEFROMSTYLE 
         PJN / 19-09-2015 1. Updated class to work with Scintilla v3.6.1. New messages wrapped include: SCI_INDICSETHOVERSTYLE, 
                          SCI_INDICGETHOVERSTYLE, SCI_INDICSETHOVERFORE, SCI_INDICGETHOVERFORE, SCI_INDICSETFLAGS, 
                          SCI_INDICGETFLAGS, SCI_SETTARGETRANGE, SCI_GETTARGETTEXT, SCI_TARGETWHOLEDOCUMENT, SCI_ISRANGEWORD.
                          SCI_MULTIPLESELECTADDNEXT & SCI_MULTIPLESELECTADDEACH. 
                          Removed messages include: SCI_SETKEYSUNICODE & SCI_GETKEYSUNICODE
                          2. All APIs which use a logical document position which previously used a C long has now been replaced with the 
                          Scintilla define "Sci_Position". This is to mirror the ongoing changes in Scintilla to enable support for documents
                          larger than 2GB.
         PJN / 23-01-2016 1. Updated copyright details.
                          2. Updated class to work with Scintilla v3.6.3. New messages wrapped include: SCI_SETIDLESTYLING &
                          SCI_GETIDLESTYLING
         PJN / 11-07-2016 1. Verified class against Scintilla v3.6.6. As no new messages were introduced between v3.6.3 and v3.6.6 no
                          changes were required in the code.
                          2. Removed the bDirect parameter from all the method calls and instead replaced this functionality with a 
                          new pair of getter / setter methods called GetCallDirect and SetCallDirect. Thanks to Chad Marlow for prompting this
                          update
         PJN / 25-07-2016 1. Added SAL annotations to all the code
         PJN / 16-10-2016 1. Replaced all occurrences of NULL with nullptr throughout the codebase. This now means that the minimum 
                          requirement to compile the code is Visual Studio 2010 or later. Thanks to Markus Nissl for requesting this update.
                          2. Updated class to work with Scintilla v3.7.0. New messages wrapped include: SCI_SETMARGINBACKN, 
                          SCI_GETMARGINBACKN, SCI_SETMARGINS, SCI_GETMARGINS, SCI_MULTIEDGEADDLINE, SCI_MULTIEDGECLEARALL, 
                          SCI_SETMOUSEWHEELCAPTURES & SCI_GETMOUSEWHEELCAPTURES.
         PJN / 20-12-2016 1. Updated class to work with Scintilla v3.7.1. New messages wrapped include: SCI_GETTABDRAWMODE, SCI_SETTABDRAWMODE, 
                          SCI_TOGGLEFOLDSHOWTEXT & SCI_FOLDDISPLAYTEXTSETSTYLE. The parameter to support the SCI_USEPOPUP message has been 
                          changed from a BOOL to an int.
                          2. Updated code to use Sci_RangeToFormat typedef instead of RangeToFormat
                          3. Updated code to use Sci_TextToFind typedef instead of TextToFind
                          4. Updated code to no longer use Scintilla namespace which has been removed from 
                          Scintilla.h
         PJN / 04-03-2017 1. Updated copyright details
                          2. Updated class to work with Scintilla v3.7.3. The only change to support this version was to have now no return 
                          value from the SetSelection and AddSelection methods
                          3. Updated the download to include the correct VC 2010 project files. Thanks to Kenny Lau for reporting this
                          issue.
         PJN / 03-04-2017 1. Updated class to work with Scintilla v3.7.4. New messages wrapped include: SCI_SETACCESSIBILITY & 
                          SCI_GETACCESSIBILITY
         PJN / 12-06-2017 1. Updated class to work with Scintilla v3.7.5. New messages wrapped include: SCI_GETCARETLINEFRAME, 
                          SCI_SETCARETLINEFRAME & SCI_LINEREVERSE
         PJN / 31-08-2017 1. Updated class to work with Scintilla v4.0.0. New messages wrapped include: SCI_GETNAMEDSTYLES, SCI_NAMEOFSTYLE,
                          SCI_TAGSOFSTYLE & SCI_DESCRIPTIONOFSTYLE. Messages removed include SCI_GETTWOPHASEDRAW & SCI_SETTWOPHASEDRAW
                          2. Fixed up a number of compiler warnings when the code is compiled for x64
         PJN / 27-12-2017 1. Updated class to work with Scintilla v4.0.2. Some messages have been removed in 4.0.2 including SCI_SETSTYLEBITS,
                          SCI_GETSTYLEBITS & SCI_GETSTYLEBITSNEEDED.
         PJN / 03-01-2018 1. Updated copyright details.
                          2. Removed Unicode versions of MarginSetStyles & AnnotationSetStyles methods as these methods take byte buffers
                          and do not take text data. Thanks to Karagoez Yusuf for reporting this issue.
         PJN / 18-03-2018 1. Updated class to work with Scintilla v4.0.3. New parameters to SCI_CREATEDOCUMENT & SCI_CREATELOADER messages.
                          New messages wrapped include: SCI_GETMOVEEXTENDSSELECTION message, SCI_GETBIDIRECTIONAL & SCI_SETBIDIRECTIONAL
                          2. SCI_ADDREFDOCUMENT and SCI_RELEASEDOCUMENT wrappers now use void* for the document parameter.
         PJN / 03-05-2018 1. Verified the code works with the latest Scintilla v4.0.4. No new messages were added for this release of
                          scintilla.
         PJN / 14-07-2018 1. Fixed a number of C++ core guidelines compiler warnings. These changes mean that
                          the code will now only compile on VC 2017 or later.
                          2. Code page is now explicitly set to ANSI when building for ANSI. This is necessary because as of Scintilla 4 the
                          default code page is now UTF-8. Thanks to Karagoez Yusuf for reporting this issue.
                          3. CScintillaCtrl::SetProperty has been renamed SetScintillaProperty to avoid clashing with CWnd::SetProperty
                          4. CScintillaCtrl::GetProperty has been renamed GetScintillaProperty to avoid clashing with CWnd::GetProperty
                          5. Updated class to work with Scintilla v4.1.0. New messages wrapped include: SCI_GETDOCUMENTOPTIONS
         PJN / 09-09-2018 1. Fixed a number of compiler warnings when using VS 2017 15.8.2
                          2. Updated class to work with Scintilla v4.1.1. New messages wrapped include: SCI_COUNTCODEUNITS,
                          SCI_POSITIONRELATIVECODEUNITS, SCI_GETLINECHARACTERINDEX, SCI_ALLOCATELINECHARACTERINDEX, 
                          SCI_RELEASELINECHARACTERINDEX, SCI_LINEFROMINDEXPOSITION & SCI_INDEXPOSITIONFROMLINE
         PJN / 19-01-2019 1. Updated copyright details
                          2. Updated class to work with Scintilla v4.1.3. New messages wrapped include: SCI_SETCOMMANDEVENTS & 
                          SCI_GETCOMMANDEVENTS.
                          3. Added code to suppress C4263 off by default compiler warning. Thanks to Karagoez Yusuf for reporting this issue.
         PJN / 23-02-2019 1. Fixed a number of compiler warnings when the code is compiled with VS 2019 Preview
         PJN / 02-04-2019 1. Verified the code works with the latest Scintilla v4.1.4. No new messages were added for this release of
                          scintilla.
         PJN / 25-06-2019 1. Updated class to work with Scintilla v4.1.7. New messages wrapped include: SCI_SETCHARACTERCATEGORYOPTIMIZATION,
                          SCI_GETCHARACTERCATEGORYOPTIMIZATION, SCI_FOLDDISPLAYTEXTGETSTYLE, SCI_SETDEFAULTFOLDDISPLAYTEXT &
                          SCI_GETDEFAULTFOLDDISPLAYTEXT.
         PJN / 23-08-2019 1. Updated class to work with Scintilla v4.2.0. Various API definitions have been updated to use Sci_Position 
                          instead of int parameters. No new actual messages were added.
         PJN / 03-11-2019 1. Updated class to work with Scintilla v4.2.1. New messages wrapper include: SCI_SETTABMINIMUMWIDTH and
                          SCI_GETTABMINIMUMWIDTH.
                          2. Updated initialization of various structs to use C++ 11 list initialization
         PJN / 27-12-2019 1. Updated class to work with Scintilla v4.2.3. New messages wrapped include: SCI_SETTARGETSTARTVIRTUALSPACE, 
                          SCI_GETTARGETSTARTVIRTUALSPACE, SCI_SETTARGETENDVIRTUALSPACE, SCI_GETTARGETENDVIRTUALSPACE, 
                          SCI_GETSELECTIONNSTARTVIRTUALSPACE & SCI_GETSELECTIONNENDVIRTUALSPACE.
                          2. Fixed various Clang-Tidy static code analysis warnings in the code.
         PJN / 21-03-2020 1. Updated copyright details.
                          2. Fixed more Clang-Tidy static code analysis warnings in the code.
                          3. Updated class to work with Scintilla v4.3.2. New messages wrapped include: SCI_SETILEXER
         PJN / 07-05-2020 1. Added missing static_casts in the GetSelectionNStartVirtualSpace and 
                          GetSelectionNEndVirtualSpace methods. Thanks to Yusuf Karagöz for reporting this issue.
                          2. Updated class to work with Scintilla v4.3.3. New messages wrapped include: SCI_MARKERHANDLEFROMLINE and 
                          SCI_MARKERNUMBERFROMLINE.
                          3. Changed two parameters to CallTipSetHlt method to be Sci_Position from int.
                          4. Changed return value from IndicatorStart method to be Sci_Position from int.
                          5. Changed return value from IndicatorEnd method to be Sci_Position from int.
         PJN / 14-06-2020 1. Verified the code against Scintilla v4.4.3.
         PJN / 15-08-2020 1. Updated class to work with Scintilla v4.4.4. New messages wrapped include: SCI_BRACEMATCHNEXT,
                          SCI_EOLANNOTATIONSETTEXT, SCI_EOLANNOTATIONGETTEXT, SCI_EOLANNOTATIONSETSTYLE, SCI_EOLANNOTATIONGETSTYLE, 
                          SCI_EOLANNOTATIONCLEARALL, SCI_EOLANNOTATIONSETVISIBLE, SCI_EOLANNOTATIONGETVISIBLE, 
                          SCI_EOLANNOTATIONSETSTYLEOFFSET & SCI_EOLANNOTATIONGETSTYLEOFFSET.
         PJN / 26-09-2020 1. Updated class to work with Scintilla v4.4.5. New messages wrapped include: SCI_GETMULTIEDGECOLUMN
         PJN / 10-05-2021 1. Updated class to work with Scintilla v5.0.2. New messages wrapped include: SCI_SETFONTLOCALE, 
                          SCI_GETFONTLOCALE, SCI_MARKERSETFORETRANSLUCENT, SCI_MARKERSETBACKTRANSLUCENT, SCI_MARKERSETBACKSELECTEDTRANSLUCENT,
                          SCI_MARKERSETSTROKEWIDTH, SCI_SETELEMENTCOLOUR, SCI_GETELEMENTCOLOUR, SCI_RESETELEMENTCOLOUR, SCI_GETELEMENTISSET, 
                          SCI_GETELEMENTALLOWSTRANSLUCENT, SCI_INDICSETSTROKEWIDTH, SCI_INDICGETSTROKEWIDTH & SCI_SUPPORTSFEATURE
                          2. Updated copyright details
         PJN / 05-06-2021 1. Updated class to work with Scintilla v5.0.3. New messages wrapped include: SCI_MARKERGETLAYER, 
                          SCI_MARKERSETLAYER, SCI_GETELEMENTBASECOLOUR, SCI_GETSELECTIONLAYER, SCI_SETSELECTIONLAYER, SCI_GETCARETLINELAYER
                          & SCI_SETCARETLINELAYER.
         PJN / 11-07-2021 1. Updated class to work with Scintilla v5.1.0. New messages wrapped include: SCI_GETDIRECTSTATUSFUNCTION,
                          SCI_REPLACERECTANGULAR, SCI_CLEARALLREPRESENTATIONS, SCI_SETREPRESENTATIONAPPEARANCE,
                          SCI_GETREPRESENTATIONAPPEARANCE, SCI_SETREPRESENTATIONCOLOUR & SCI_GETREPRESENTATIONCOLOUR
                          2. Changed the return values from GetDirectFunction & GetDirectPointer to less generic data types.
         PJN / 14-08-2021 1. Updated class to work with Scintilla v5.1.1. New messages wrapped include: SCI_AUTOCSETOPTIONS, 
                          SCI_AUTOCGETOPTIONS & SCI_ALLOCATELINES.
         PJN / 30-09-2021 1. Updated class to work with Scintilla v5.1.3. New messages wrapped include: 
                          SCI_STYLESETCHECKMONOSPACED, SCI_STYLEGETCHECKMONOSPACED, SCI_GETCARETLINEHIGHLIGHTSUBLINE & 
                          SCI_SETCARETLINEHIGHLIGHTSUBLINE.
         PJN / 31-03-2022 1. Updated copyright details.
                          2. Updated class to work with Scintilla v5.2.2. New messages wrapped include: 
                          SCI_GETSTYLEINDEXAT, SCI_SETLAYOUTTHREADS and SCI_GETLAYOUTTHREADS.
                          3. Updated the code to use C++ uniform initialization for all variable declarations.
         PJN / 31-03-2022 1. Updated class to work with Scintilla v5.2.4. New messages wrapped include:
                          SCI_FINDTEXTFULL, SCI_FORMATRANGEFULL & SCI_GETTEXTRANGEFULL.
         PJN / 10-08-2022 1. Updated all line parameters to use intptr_t instead of int. Thanks to Markus Nissl for reporting this issue.
         PJN / 12-09-2022 1. Updated class to work with Scintilla v5.3.0. New messages wrapped include:
                          SCI_SETCHANGEHISTORY, SCI_GETCHANGEHISTORY & SCI_GETSELECTIONHIDDEN.
                          2. Updated CScintillaCtrl class to support being compiled with WTL support. Thanks to Niek Albers for 
                          suggesting this update.
         PJN / 29-10-2022 1. Updated class to work with Scintilla v5.3.1. New messages wrapped include: 
                          SCI_STYLESETINVISIBLEREPRESENTATION & SCI_STYLEGETINVISIBLEREPRESENTATION.
         PJN / 13-12-2022 1. All classes are now contained in the workspace "Scintilla".
                          2. Updated code to use enums from Scintilla provided "ScintillaTypes.h" header file.
                          3. Updated class to work with Scintilla v5.3.2. New messages wrapped include: SCI_GETSTYLEDTEXTFULL and
                          SCI_REPLACETARGETMINIMAL.
         PJN / 14-12-2022 1. Fixed up issue with Regular expression checkbox not appearing in find and replace dialogs.
                          2. Replaced intptr_t type with Line typedef.
                          3. Updated code to use message values from Scintilla provided "ScintillaMessages.h" header file.
                          4. Renamed SetScintillaProperty method to SetSCIProperty.
                          5. Renamed GetScintillaProperty method to GetSCIProperty.
                          6. Updated code to use structs from Scintilla provided "ScintillaStructures.h" header file.
                          7. Updated code to use Scintilla provided "ScintillaCall.h" header file instead of the "Scintilla.h" 
                          which is designed for C clients.
                          8. Updated code to use Scintilla::Position instead of Sci_Position.
         PJN / 19-12-2022 1. Fixed a bug where the first parameter to SetXCaretPolicy and SetYCaretPolicy should be a 
                          CaretPolicy instead of VisiblePolicy. Thanks to Markus Nissl for reporting this issue.
                          2. Removed unnecessary Scintilla namespace usage in ScintillaCtrl.cpp. Thanks to Markus 
                          Nissl for reporting this issue.
         PJN / 21-03-2023 1. Updated modules to indicate that it needs to be compiled using /std:c++17. Thanks to Martin Richter for
                          reporting this issue.
         PJN / 28-12-2023 1. Updated class to work with Scintilla v5.4.1. New messages wrapped include: SCI_CHANGESELECTIONMODE,
                          SCI_SETMOVEEXTENDSSELECTION & SCI_SELECTIONFROMPOINT. Also updated the signatures of the following
                          methods: GetDocPointer, SetDocPointer, CreateDocument, AddRefDocument and ReleaseDocument.
         PJN / 29-03-2024 1. Updated copyright details.
                          2. Updated class to work with Scintilla v5.4.3. New messages wrapped include: SCI_GETUNDOACTIONS,
                          SCI_GETUNDOSAVEPOINT, SCI_SETUNDODETACH, SCI_SETUNDOTENTATIVE, SCI_SETUNDOCURRENT, SCI_PUSHUNDOACTIONTYPE,
                          SCI_CHANGELASTUNDOACTIONTEXT, SCI_GETUNDOACTIONTYPE, SCI_GETUNDOACTIONPOSITION & SCI_GETUNDOACTIONTEXT.
         PJN / 26-04-2024 1. Verified the code against Scintilla v5.5.0.
         PJN / 22-07-2024 1. Updated class to work with Scintilla v5.5.1. New messages wrapped include: SCI_AUTOCSETSTYLE,
                          SCI_AUTOCGETSTYLE & SCI_CUTALLOWLINE.
         PJN / 24-08-2024 1. Updated class to work with Scintilla v5.5.2. New messages wrapped include: SCI_STYLESETSTRETCH,
                          SCI_STYLEGETSTRETCH, SCI_GETUNDOSEQUENCE, SCI_LineIndent, SCI_LINEDEDENT, SCI_SETCOPYSEPARATOR & 
                          SCI_GETCOPYSEPARATOR.
         PJN / 26-10-2024 1. Verified the code against Scintilla v5.5.3.
         PJN / 21-12-2024 1. Verified the code against Scintilla v5.5.4.

Copyright (c) 2004 - 2025 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code.

*/


//////////////////// Includes /////////////////////////////////////////////////

#include "pch.h"
#include "ScintillaCtrl.h"

#ifndef SCINTILLAMESSAGES_H
#pragma message("To avoid this message, please put ScintillaMessages.h in your pre compiled header (normally stdafx.h)")
#include <ScintillaMessages.h>
#endif //#ifndef SCINTILLAMESSAGES_H


//////////////////// Statics / Macros /////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG


//////////////////// Implementation ///////////////////////////////////////////

using namespace Scintilla;

#ifdef _AFX
#pragma warning(suppress: 26433 26440 26477)
IMPLEMENT_DYNAMIC(CScintillaCtrl, CWnd)
#endif //#ifdef _AFX

CScintillaCtrl::CScintillaCtrl() noexcept : m_DirectStatusFunction{nullptr},
                                            m_DirectPointer{0},
                                            m_LastStatus{Status::Ok},
                                            m_dwOwnerThreadID{0},
                                            m_bDoneInitialSetup{false}
{
    TRACE0("In CScintillaCtrl ctor.\n");
}

#ifdef _AFX
BOOL CScintillaCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwExStyle, LPVOID lpParam)
{
  //Call our base class implementation of CWnd::CreateEx
  if (!CreateEx(dwExStyle, _T("scintilla"), nullptr, dwStyle, rect, pParentWnd, nID, lpParam))
    return FALSE;
#else
#pragma warning(suppress: 26434)
BOOL CScintillaCtrl::Create(_In_ HWND hWndParent, _In_ ATL::_U_RECT rect, _In_ DWORD dwStyle, _In_ UINT nID, _In_ DWORD dwExStyle, _In_opt_ LPVOID lpParam)
{
  //Call our base class implementation of ATL::CWindow::Create
  if (!__super::Create(GetWndClassName(), hWndParent, rect, nullptr, dwStyle, dwExStyle, nID, lpParam))
    return FALSE;
#endif //#ifdef _AFX

  //Setup the direct access data
  if (!m_bDoneInitialSetup)
  {
    m_bDoneInitialSetup = true;

    SetupDirectAccess();

    //If we are running as Unicode, then use the UTF8 codepage else disable multi-byte support
#ifdef _UNICODE
    SetCodePage(CpUtf8);
#else
    SetCodePage(0);
#endif //#ifdef _UNICODE

    //Cache the return value from GetWindowThreadProcessId in the m_dwOwnerThreadID member variable
    m_dwOwnerThreadID = GetWindowThreadProcessId(m_hWnd, nullptr);
  }

  return TRUE;
}

#ifdef _AFX
void CScintillaCtrl::PreSubclassWindow()
{
  //Let the base class do its thing
  __super::PreSubclassWindow();

  //Setup the direct access data
  if (!m_bDoneInitialSetup)
  {
    SetupDirectAccess();
    if ((m_DirectPointer == 0) || (m_DirectStatusFunction == nullptr))
      return;

    m_bDoneInitialSetup = true;

    //If we are running as Unicode, then use the UTF8 codepage else use the ANSI codepage
#ifdef _UNICODE
    SetCodePage(CpUtf8);
#else
    SetCodePage(0);
#endif //#ifdef _UNICODE

    //Cache the return value from GetWindowThreadProcessId in the m_dwOwnerThreadID member variable
    m_dwOwnerThreadID = GetWindowThreadProcessId(m_hWnd, nullptr);
  }
}
#endif //#ifdef _AFX

void CScintillaCtrl::SetupDirectAccess()
{
  //Setup the direct access data
  m_DirectPointer = GetDirectPointer();
  m_DirectStatusFunction = GetDirectStatusFunction();
}

#pragma warning(suppress: 26440)
sptr_t CScintillaCtrl::GetDirectPointer()
{
  return SendMessage(static_cast<UINT>(Message::GetDirectPointer), 0, 0);
}

#pragma warning(suppress: 26440)
FunctionDirect CScintillaCtrl::GetDirectStatusFunction()
{
#pragma warning(suppress: 26490)
  return reinterpret_cast<FunctionDirect>(SendMessage(static_cast<UINT>(Message::GetDirectStatusFunction), 0, 0));
}

Status CScintillaCtrl::GetLastStatus() const noexcept
{
  return m_LastStatus;
}

CScintillaCtrl::StringA CScintillaCtrl::W2UTF8(_In_NLS_string_(nLength) const wchar_t* pszText, _In_ int nLength)
{
  //First call the function to determine how much space we need to allocate
  int nUTF8Length{WideCharToMultiByte(CP_UTF8, 0, pszText, nLength, nullptr, 0, nullptr, nullptr)};

  //If the calculated length is zero, then ensure we have at least room for a null terminator
  if (nUTF8Length == 0)
    nUTF8Length = 1;

  //Now recall with the buffer to get the converted text
  StringA sUTF;
#pragma warning(suppress: 26429)
  char* const pszUTF8Text{sUTF.GetBuffer(nUTF8Length + 1)}; //include an extra byte because we may be null terminating the string ourselves
  int nCharsWritten{WideCharToMultiByte(CP_UTF8, 0, pszText, nLength, pszUTF8Text, nUTF8Length, nullptr, nullptr)};

  //Ensure we null terminate the text if WideCharToMultiByte doesn't do it for us
  if (nLength != -1)
  {
#pragma warning(suppress: 26477 26496)
    ATLASSUME(nCharsWritten <= nUTF8Length);
#pragma warning(suppress: 26481)
    pszUTF8Text[nCharsWritten] = '\0';
  }
  sUTF.ReleaseBuffer();

  return sUTF;
}

CScintillaCtrl::StringW CScintillaCtrl::UTF82W(_In_NLS_string_(nLength) const char* pszText, _In_ int nLength)
{
  //First call the function to determine how much space we need to allocate
  int nWideLength{MultiByteToWideChar(CP_UTF8, 0, pszText, nLength, nullptr, 0)};

  //If the calculated length is zero, then ensure we have at least room for a null terminator
  if (nWideLength == 0)
    nWideLength = 1;

  //Now recall with the buffer to get the converted text
  StringW sWideString;
#pragma warning(suppress: 26429)
  wchar_t* pszWText{sWideString.GetBuffer(nWideLength + 1)}; //include an extra byte because we may be null terminating the string ourselves
  int nCharsWritten{MultiByteToWideChar(CP_UTF8, 0, pszText, nLength, pszWText, nWideLength)};

  //Ensure we null terminate the text if MultiByteToWideChar doesn't do it for us
  if (nLength != -1)
  {
#pragma warning(suppress: 26477 26496)
    ATLASSUME(nCharsWritten <= nWideLength);
#pragma warning(suppress: 26481)
    pszWText[nCharsWritten] = '\0';
  }
  sWideString.ReleaseBuffer();

  return sWideString;
}

#ifdef _UNICODE
void CScintillaCtrl::AddText(_In_ int length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, length)};

  //Call the native scintilla version of the function with the UTF8 text
  AddText(sUTF8.GetLength(), sUTF8);
}

void CScintillaCtrl::InsertText(_In_ Position pos, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  InsertText(pos, sUTF8);
}

void CScintillaCtrl::ChangeInsertion(_In_ int length, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  ChangeInsertion(length, sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::GetSelText()
{
  //Work out the length of string to allocate
  const Position nUTF8Length{GetSelText(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
#pragma warning(suppress: 26472)
  GetSelText(sUTF8.GetBufferSetLength(static_cast<int>(nUTF8Length)));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetCurLine()
{
  //Work out the length of string to allocate
  const Position nUTF8Length{GetCurLine(0, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
#pragma warning(suppress: 26472)
  GetCurLine(nUTF8Length, sUTF8.GetBufferSetLength(static_cast<int>(nUTF8Length)));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

void CScintillaCtrl::StyleSetFont(_In_ int style, _In_z_ const wchar_t* fontName)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(fontName, -1)};

  StyleSetFont(style, sUTF8);
}

void CScintillaCtrl::SetWordChars(_In_z_ const wchar_t* characters)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(characters, -1)};

  SetWordChars(sUTF8);
}

void CScintillaCtrl::AutoCShow(_In_ int lenEntered, _In_z_ const wchar_t* itemList)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(itemList, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  AutoCShow(lenEntered, sUTF8);
}

void CScintillaCtrl::AutoCStops(_In_z_ const wchar_t* characterSet)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(characterSet, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  AutoCStops(sUTF8);
}

void CScintillaCtrl::AutoCSelect(_In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  AutoCSelect(sUTF8);
}

void CScintillaCtrl::AutoCSetFillUps(_In_z_ const wchar_t* characterSet)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(characterSet, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  AutoCSetFillUps(sUTF8);
}

void CScintillaCtrl::UserListShow(_In_ int listType, _In_z_ const wchar_t* itemList)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(itemList, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  UserListShow(listType, sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::GetLine(_In_ Line line)
{
  //Work out the length of string to allocate
  const Position nUTF8Length{GetLine(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
#pragma warning(suppress: 26472)
  GetLine(line, sUTF8.GetBufferSetLength(static_cast<int>(nUTF8Length)));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

void CScintillaCtrl::ReplaceSel(_In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  ReplaceSel(sUTF8);
}

void CScintillaCtrl::SetText(_In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetText(sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::GetText(_In_ int length)
{
  //Work out the length of string to allocate
  const int nUTF8Length{length * 4}; //A Unicode character can take up to 4 octets when expressed as UTF8

  //Call the function which does the work
  StringA sUTF8;
  GetText(nUTF8Length, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  StringW sWideText{UTF82W(sUTF8, -1)};

  return sWideText.Left(length-1);
}

Position CScintillaCtrl::ReplaceTarget(_In_ Position length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
#pragma warning(suppress: 26472)
  StringA sUTF8{W2UTF8(text, static_cast<int>(length))};

  //Call the native scintilla version of the function with the UTF8 text
  return ReplaceTarget(sUTF8.GetLength(), sUTF8);
}

Position CScintillaCtrl::ReplaceTargetRE(_In_ Position length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
#pragma warning(suppress: 26472)
  StringA sUTF8{W2UTF8(text, static_cast<int>(length))};

  //Call the native scintilla version of the function with the UTF8 text
  return ReplaceTargetRE(sUTF8.GetLength(), sUTF8);
}

Position CScintillaCtrl::ReplaceTargetMinimal(_In_ Position length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
#pragma warning(suppress: 26472)
  StringA sUTF8{W2UTF8(text, static_cast<int>(length))};

  //Call the native scintilla version of the function with the UTF8 text
  return ReplaceTargetMinimal(sUTF8.GetLength(), sUTF8);
}

Position CScintillaCtrl::SearchInTarget(_In_ Position length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
#pragma warning(suppress: 26472)
  StringA sUTF8{W2UTF8(text, static_cast<int>(length))};

  //Call the native scintilla version of the function with the UTF8 text
  return SearchInTarget(sUTF8.GetLength(), sUTF8);
}

void CScintillaCtrl::CallTipShow(_In_ Position pos, _In_z_ const wchar_t* definition)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(definition, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  CallTipShow(pos, sUTF8);
}

int CScintillaCtrl::TextWidth(_In_ int style, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  return TextWidth(style, sUTF8);
}

void CScintillaCtrl::AppendText(_In_ int length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, length)};

  //Call the native scintilla version of the function with the UTF8 text
  AppendText(sUTF8.GetLength(), sUTF8);
}

Position CScintillaCtrl::SearchNext(_In_ FindOption flags, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  return SearchNext(flags, sUTF8);
}

Position CScintillaCtrl::SearchPrev(_In_ FindOption flags, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  return SearchPrev(flags, sUTF8);
}

void CScintillaCtrl::CopyText(_In_ int length, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, length)};

  //Call the native scintilla version of the function with the UTF8 text
  CopyText(sUTF8.GetLength(), sUTF8);
}

void CScintillaCtrl::SetWhitespaceChars(_In_z_ const wchar_t* characters)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(characters, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetWhitespaceChars(sUTF8);
}

void CScintillaCtrl::SetSCIProperty(_In_z_ const wchar_t* key, _In_z_ const wchar_t* value)
{
  //Convert the unicode texts to UTF8
  StringA sUTF8Key{W2UTF8(key, -1)};
  StringA sUTF8Value{W2UTF8(value, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetSCIProperty(sUTF8Key, sUTF8Value);
}

void CScintillaCtrl::SetKeyWords(_In_ int keywordSet, _In_z_ const wchar_t* keyWords)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(keyWords, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetKeyWords(keywordSet, sUTF8);
}

void CScintillaCtrl::SetIdentifiers(_In_ int style, _In_z_ const wchar_t* identifiers)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(identifiers, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetIdentifiers(style, sUTF8);
}

void CScintillaCtrl::ChangeLastUndoActionText(_In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  ChangeLastUndoActionText(sUTF8.GetLength(), sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::GetSCIProperty(_In_z_ const wchar_t* key)
{
  //Validate our parameters
#pragma warning(suppress: 26477)
  ATLASSERT(key != nullptr);

  //Convert the Key value to UTF8
  StringA sUTF8Key{W2UTF8(key, -1)};

  //Work out the length of string to allocate
  const int nUTF8ValueLength{GetSCIProperty(sUTF8Key, nullptr)};

  //Call the function which does the work
  StringA sUTF8Value;
  GetSCIProperty(sUTF8Key, sUTF8Value.GetBufferSetLength(nUTF8ValueLength));
  sUTF8Value.ReleaseBuffer();

  return UTF82W(sUTF8Value, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetPropertyExpanded(_In_z_ const wchar_t* key)
{
  //Validate our parameters
#pragma warning(suppress: 26477)
  ATLASSERT(key != nullptr);

  //Convert the Key value to UTF8
  StringA sUTF8Key{W2UTF8(key, -1)};

  //Work out the length of string to allocate
  const int nUTF8ValueLength{GetPropertyExpanded(sUTF8Key, nullptr)};

  //Call the function which does the work
  StringA sUTF8Value;
  GetPropertyExpanded(sUTF8Key, sUTF8Value.GetBufferSetLength(nUTF8ValueLength));
  sUTF8Value.ReleaseBuffer();

  return UTF82W(sUTF8Value, -1);
}

int CScintillaCtrl::GetPropertyInt(_In_z_ const wchar_t* key, _In_ int defaultValue)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(key, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  return GetPropertyInt(sUTF8, defaultValue);
}

CScintillaCtrl::StringW CScintillaCtrl::StyleGetFont(_In_ int style)
{
  //Work out the length of string to allocate
  const int nUTF8Length{StyleGetFont(style, nullptr)};

  //Call the function which does the work
  StringA sUTF8FontName;
  StyleGetFont(style, sUTF8FontName.GetBufferSetLength(nUTF8Length));
  sUTF8FontName.ReleaseBuffer();
  return UTF82W(sUTF8FontName, -1);
}

void CScintillaCtrl::MarginSetText(_In_ Line line, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  MarginSetText(line, sUTF8);
}

void CScintillaCtrl::AnnotationSetText(_In_ Line line, _In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  AnnotationSetText(line, sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::AutoCGetCurrentText()
{
  //Work out the length of string to allocate
  const int nUTF8Length{AutoCGetCurrentText(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  AutoCGetCurrentText(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetLexerLanguage()
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetLexerLanguage(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetLexerLanguage(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::PropertyNames()
{
  //Work out the length of string to allocate
  const int nUTF8Length{PropertyNames(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  PropertyNames(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

TypeProperty CScintillaCtrl::PropertyType(_In_z_ const wchar_t* name)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(name, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  return PropertyType(sUTF8);
}

void CScintillaCtrl::ToggleFoldShowText(_In_ Line line, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  ToggleFoldShowText(line, sUTF8);
}

void CScintillaCtrl::SetDefaultFoldDisplayText(_In_z_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetDefaultFoldDisplayText(sUTF8);
}

void CScintillaCtrl::EOLAnnotationSetText(_In_ Line line, _In_ const wchar_t* text)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(text, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  EOLAnnotationSetText(line, sUTF8);
}

void CScintillaCtrl::StyleSetInvisibleRepresentation(_In_ int style, _In_z_ const wchar_t* representation)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(representation, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  StyleSetInvisibleRepresentation(style, sUTF8);
}

void CScintillaCtrl::SetCopySeparator(_In_z_ const wchar_t* separator)
{
  //Convert the unicode text to UTF8
  StringA sUTF8{W2UTF8(separator, -1)};

  //Call the native scintilla version of the function with the UTF8 text
  SetCopySeparator(sUTF8);
}

CScintillaCtrl::StringW CScintillaCtrl::EOLAnnotationGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nUTF8Length{EOLAnnotationGetText(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  EOLAnnotationGetText(line, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::DescribeProperty(_In_z_ const wchar_t* name)
{
  //Convert the name value to UTF8
  StringA sUTF8KName{W2UTF8(name, -1)};

  //Work out the length of string to allocate
  const int nUTF8Length{DescribeProperty(sUTF8KName, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  DescribeProperty(sUTF8KName, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::DescribeKeyWordSets()
{
  //Work out the length of string to allocate
  const int nUTF8Length{DescribeKeyWordSets(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  DescribeKeyWordSets(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetTag(_In_ int tagNumber)
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetTag(tagNumber, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetTag(tagNumber, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetWordChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetWordChars(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetWordChars(sUTF8.GetBufferSetLength(nValueLength));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetWhitespaceChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetWhitespaceChars(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetWhitespaceChars(sUTF8.GetBufferSetLength(nValueLength));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetPunctuationChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetPunctuationChars(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetPunctuationChars(sUTF8.GetBufferSetLength(nValueLength));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetTargetText()
{
  //Work out the length of string to allocate
  const Position nValueLength{GetTargetText(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
#pragma warning(suppress: 26472)
  GetTargetText(sUTF8.GetBufferSetLength(static_cast<int>(nValueLength)));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::NameOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nUTF8ValueLength{NameOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sUTF8Value;
  NameOfStyle(style, sUTF8Value.GetBufferSetLength(nUTF8ValueLength));
  sUTF8Value.ReleaseBuffer();

  return UTF82W(sUTF8Value, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::TagsOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nUTF8ValueLength{TagsOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sUTF8Value;
  TagsOfStyle(style, sUTF8Value.GetBufferSetLength(nUTF8ValueLength));
  sUTF8Value.ReleaseBuffer();

  return UTF82W(sUTF8Value, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::DescriptionOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nUTF8ValueLength{DescriptionOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sUTF8Value;
  DescriptionOfStyle(style, sUTF8Value.GetBufferSetLength(nUTF8ValueLength));
  sUTF8Value.ReleaseBuffer();

  return UTF82W(sUTF8Value, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetDefaultFoldDisplayText()
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetDefaultFoldDisplayText(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetDefaultFoldDisplayText(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::MarginGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nUTF8Length{MarginGetText(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetDefaultFoldDisplayText(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetFontLocale()
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetFontLocale(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetFontLocale(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::MarginGetStyles(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nUTF8Length{MarginGetStyles(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  MarginGetStyles(line, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::AnnotationGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nUTF8Length{AnnotationGetText(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  AnnotationGetText(line, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::AnnotationGetStyles(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nUTF8Length{AnnotationGetStyles(line, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  AnnotationGetStyles(line, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetSubStyleBases()
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetSubStyleBases(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetSubStyleBases(sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::StyleGetInvisibleRepresentation(_In_ int style)
{
  //Work out the length of string to allocate
  const int nUTF8Length{StyleGetInvisibleRepresentation(style, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  StyleGetInvisibleRepresentation(style, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetUndoActionText(_In_ int action)
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetUndoActionText(action, nullptr)};

  //Call the function which does the work
  StringA sUTF8;
  GetUndoActionText(action, sUTF8.GetBufferSetLength(nUTF8Length));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

CScintillaCtrl::StringW CScintillaCtrl::GetCopySeparator()
{
  //Work out the length of string to allocate
  const int nUTF8Length{GetCopySeparator(nullptr)};

  //Call the function which does the work
  StringA sUTF8;
#pragma warning(suppress: 26472)
  GetCopySeparator(sUTF8.GetBufferSetLength(static_cast<int>(nUTF8Length)));
  sUTF8.ReleaseBuffer();

  //Now convert the UTF8 text back to Unicode
  return UTF82W(sUTF8, -1);
}

#else

CScintillaCtrl::StringA CScintillaCtrl::GetSelText()
{
  //Work out the length of string to allocate
  const Position nLength{GetSelText(nullptr)};

  //Call the function which does the work
  StringA sSelText;
#pragma warning(suppress: 26472)
  GetSelText(sSelText.GetBufferSetLength(static_cast<int>(nLength)));
  sSelText.ReleaseBuffer();
  return sSelText;
}

CScintillaCtrl::StringA CScintillaCtrl::GetCurLine()
{
  //Call the function which does the work
  StringA sCurLine;
  const Position nLength{GetCurLine(0, nullptr)};
#pragma warning(suppress: 26472)
  char* pszCurLine{sCurLine.GetBufferSetLength(static_cast<int>(nLength))};
  GetCurLine(nLength, pszCurLine);
  sCurLine.ReleaseBuffer();
  return sCurLine;
}

CScintillaCtrl::StringA CScintillaCtrl::GetLine(_In_ Line line)
{
  //Call the function which does the work
  StringA sLine;
  const Position nLength{GetLine(line, nullptr)};
#pragma warning(suppress: 26472)
  char* pszLine{sLine.GetBufferSetLength(static_cast<int>(nLength))};
  GetLine(line, pszLine);
  sLine.ReleaseBuffer();
  return sLine;
}

CScintillaCtrl::StringA CScintillaCtrl::GetSCIProperty(_In_z_ const char* key)
{
  //Validate our parameters
#pragma warning(suppress: 26477)
  ATLASSERT(key != nullptr);

  //Work out the length of string to allocate
  const int nValueLength{GetSCIProperty(key, nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetSCIProperty(key, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetText(_In_ int length)
{
  //Call the function which does the work
  StringA sText;
  GetText(length, sText.GetBufferSetLength(length));
  sText.ReleaseBuffer();

  return sText;
}

CScintillaCtrl::StringA CScintillaCtrl::GetPropertyExpanded(_In_z_ const char* key)
{
  //Validate our parameters
#pragma warning(suppress: 26477)
  ATLASSERT(key != nullptr);

  //Work out the length of string to allocate
  const int nValueLength{GetPropertyExpanded(key, nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetPropertyExpanded(key, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::StyleGetFont(_In_ int style)
{
  //Work out the length of string to allocate
  const int nValueLength{StyleGetFont(style, nullptr)};

  //Call the function which does the work
  StringA sFontName;
  StyleGetFont(style, sFontName.GetBufferSetLength(nValueLength));
  sFontName.ReleaseBuffer();

  return sFontName;
}

CScintillaCtrl::StringA CScintillaCtrl::AutoCGetCurrentText()
{
  //Work out the length of string to allocate
  const int nLength{AutoCGetCurrentText(nullptr)};

  //Call the function which does the work
  StringA sText;
  AutoCGetCurrentText(sText.GetBufferSetLength(nLength));
  sText.ReleaseBuffer();

  return sText;
}

CScintillaCtrl::StringA CScintillaCtrl::GetLexerLanguage()
{
  //Work out the length of string to allocate
  const int nValueLength{GetLexerLanguage(nullptr)};

  //Call the function which does the work
  StringA sLanguage;
  GetLexerLanguage(sLanguage.GetBufferSetLength(nValueLength));
  sLanguage.ReleaseBuffer();

  return sLanguage;
}

CScintillaCtrl::StringA CScintillaCtrl::PropertyNames()
{
  //Work out the length of string to allocate
  const int nValueLength{PropertyNames(nullptr)};

  //Call the function which does the work
  StringA sPropertyNames;
  PropertyNames(sPropertyNames.GetBufferSetLength(nValueLength));
  sPropertyNames.ReleaseBuffer();

  return sPropertyNames;
}

CScintillaCtrl::StringA CScintillaCtrl::EOLAnnotationGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nValueLength{EOLAnnotationGetText(line, nullptr)};

  //Call the function which does the work
  StringA sText;
  EOLAnnotationGetText(line, sText.GetBufferSetLength(nValueLength));
  sText.ReleaseBuffer();

  return sText;
}

CScintillaCtrl::StringA CScintillaCtrl::DescribeProperty(_In_z_ const char* name)
{
  //Work out the length of string to allocate
  const int nValueLength{DescribeProperty(name, nullptr)};

  //Call the function which does the work
  StringA sDescribeProperty;
  DescribeProperty(name, sDescribeProperty.GetBufferSetLength(nValueLength));
  sDescribeProperty.ReleaseBuffer();

  return sDescribeProperty;
}

CScintillaCtrl::StringA CScintillaCtrl::DescribeKeyWordSets()
{
  //Work out the length of string to allocate
  const int nValueLength{DescribeKeyWordSets(nullptr)};

  //Call the function which does the work
  StringA sDescribeKeyWordSets;
  DescribeKeyWordSets(sDescribeKeyWordSets.GetBufferSetLength(nValueLength));
  sDescribeKeyWordSets.ReleaseBuffer();

  return sDescribeKeyWordSets;
}

CScintillaCtrl::StringA CScintillaCtrl::GetTag(_In_ int tagNumber)
{
  //Work out the length of string to allocate
  const int nValueLength{GetTag(tagNumber, nullptr)};

  //Call the function which does the work
  StringA sTag;
  GetTag(tagNumber, sTag.GetBufferSetLength(nValueLength));
  sTag.ReleaseBuffer();

  return sTag;
}

CScintillaCtrl::StringA CScintillaCtrl::GetWordChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetWordChars(nullptr)};

  //Call the function which does the work
  StringA sWordChars;
  GetWordChars(sWordChars.GetBufferSetLength(nValueLength));
  sWordChars.ReleaseBuffer();

  return sWordChars;
}

CScintillaCtrl::StringA CScintillaCtrl::GetWhitespaceChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetWhitespaceChars(nullptr)};

  //Call the function which does the work
  StringA sWhitespaceChars;
  GetWhitespaceChars(sWhitespaceChars.GetBufferSetLength(nValueLength));
  sWhitespaceChars.ReleaseBuffer();

  return sWhitespaceChars;
}

CScintillaCtrl::StringA CScintillaCtrl::GetPunctuationChars()
{
  //Work out the length of string to allocate
  const int nValueLength{GetPunctuationChars(nullptr)};

  //Call the function which does the work
  StringA sPunctuationChars;
  GetPunctuationChars(sPunctuationChars.GetBufferSetLength(nValueLength));
  sPunctuationChars.ReleaseBuffer();

  return sPunctuationChars;
}

CScintillaCtrl::StringA CScintillaCtrl::GetTargetText()
{
  //Work out the length of string to allocate
  const Position nValueLength{GetTargetText(nullptr)};

  //Call the function which does the work
  StringA sTargetText;
#pragma warning(suppress: 26472)
  GetTargetText(sTargetText.GetBufferSetLength(static_cast<int>(nValueLength)));
  sTargetText.ReleaseBuffer();

  return sTargetText;
}

CScintillaCtrl::StringA CScintillaCtrl::NameOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nValueLength{NameOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sValue;
  NameOfStyle(style, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::TagsOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nValueLength{TagsOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sValue;
  TagsOfStyle(style, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::DescriptionOfStyle(_In_ int style)
{
  //Work out the length of string to allocate
  const int nValueLength{DescriptionOfStyle(style, nullptr)};

  //Call the function which does the work
  StringA sValue;
  DescriptionOfStyle(style, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetDefaultFoldDisplayText()
{
  //Work out the length of string to allocate
  const int nValueLength{GetDefaultFoldDisplayText(nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetDefaultFoldDisplayText(sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::MarginGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nValueLength{MarginGetText(line, nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetDefaultFoldDisplayText(sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetFontLocale()
{
  //Work out the length of string to allocate
  const int nValueLength{GetFontLocale(nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetFontLocale(sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::MarginGetStyles(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nValueLength{MarginGetStyles(line, nullptr)};

  //Call the function which does the work
  StringA sValue;
  MarginGetStyles(line, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::AnnotationGetText(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nValueLength{AnnotationGetText(line, nullptr)};

  //Call the function which does the work
  StringA sValue;
  AnnotationGetText(line, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::AnnotationGetStyles(_In_ Line line)
{
  //Work out the length of string to allocate
  const int nValueLength{AnnotationGetStyles(line, nullptr)};

  //Call the function which does the work
  StringA sValue;
  AnnotationGetStyles(line, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetSubStyleBases()
{
  //Work out the length of string to allocate
  const int nValueLength{GetSubStyleBases(nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetSubStyleBases(sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::StyleGetInvisibleRepresentation(_In_ int style)
{
  //Work out the length of string to allocate
  const int nValueLength{StyleGetInvisibleRepresentation(style, nullptr)};

  //Call the function which does the work
  StringA sValue;
  StyleGetInvisibleRepresentation(style, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetUndoActionText(_In_ int action)
{
  //Work out the length of string to allocate
  const int nValueLength{GetUndoActionText(action, nullptr) };

  //Call the function which does the work
  StringA sValue;
  GetUndoActionText(action, sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

CScintillaCtrl::StringA CScintillaCtrl::GetCopySeparator()
{
  //Work out the length of string to allocate
  const int nValueLength{GetCopySeparator(nullptr)};

  //Call the function which does the work
  StringA sValue;
  GetCopySeparator(sValue.GetBufferSetLength(nValueLength));
  sValue.ReleaseBuffer();

  return sValue;
}

#endif //#ifdef _UNICODE


#pragma warning(push)
#pragma warning(disable : 26440 26461 26472 26490)
void CScintillaCtrl::AddText(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  Call(static_cast<UINT>(Message::AddText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::AddStyledText(_In_ Position length, _In_reads_bytes_(length) char* c)
{
  Call(static_cast<UINT>(Message::AddStyledText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(c));
}

void CScintillaCtrl::InsertText(_In_ Position pos, _In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::InsertText), static_cast<WPARAM>(pos), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::ChangeInsertion(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  Call(static_cast<UINT>(Message::ChangeInsertion), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::ClearAll()
{
  Call(static_cast<UINT>(Message::ClearAll), 0, 0);
}

void CScintillaCtrl::DeleteRange(_In_ Position start, _In_ Position lengthDelete)
{
  Call(static_cast<UINT>(Message::DeleteRange), static_cast<WPARAM>(start), static_cast<LPARAM>(lengthDelete));
}

void CScintillaCtrl::ClearDocumentStyle()
{
  Call(static_cast<UINT>(Message::ClearDocumentStyle), 0, 0);
}

Position CScintillaCtrl::GetLength()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLength), 0, 0));
}

int CScintillaCtrl::GetCharAt(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCharAt), static_cast<WPARAM>(pos), 0));
}

Position CScintillaCtrl::GetCurrentPos()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetCurrentPos), 0, 0));
}

Position CScintillaCtrl::GetAnchor()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetAnchor), 0, 0));
}

int CScintillaCtrl::GetStyleAt(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetStyleAt), static_cast<WPARAM>(pos), 0));
}

int CScintillaCtrl::GetStyleIndexAt(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetStyleIndexAt), static_cast<WPARAM>(pos), 0));
}

void CScintillaCtrl::Redo()
{
  Call(static_cast<UINT>(Message::Redo), 0, 0);
}

void CScintillaCtrl::SetUndoCollection(_In_ BOOL collectUndo)
{
  Call(static_cast<UINT>(Message::SetUndoCollection), static_cast<WPARAM>(collectUndo), 0);
}

void CScintillaCtrl::SelectAll()
{
  Call(static_cast<UINT>(Message::SelectAll), 0, 0);
}

void CScintillaCtrl::SetSavePoint()
{
  Call(static_cast<UINT>(Message::SetSavePoint), 0, 0);
}

Position CScintillaCtrl::GetStyledText(_Inout_ TextRange* tr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetStyledText), 0, reinterpret_cast<LPARAM>(tr)));
}

Position CScintillaCtrl::GetStyledTextFull(_Inout_ TextRangeFull* tr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetStyledTextFull), 0, reinterpret_cast<LPARAM>(tr)));
}

BOOL CScintillaCtrl::CanRedo()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::CanRedo), 0, 0));
}

Line CScintillaCtrl::MarkerLineFromHandle(_In_ int markerHandle)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::MarkerLineFromHandle), static_cast<WPARAM>(markerHandle), 0));
}

void CScintillaCtrl::MarkerDeleteHandle(_In_ int markerHandle)
{
  Call(static_cast<UINT>(Message::MarkerDeleteHandle), static_cast<WPARAM>(markerHandle), 0);
}

int CScintillaCtrl::MarkerHandleFromLine(_In_ Line line, _In_ int which)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarkerHandleFromLine), static_cast<WPARAM>(line), static_cast<LPARAM>(which)));
}

int CScintillaCtrl::MarkerNumberFromLine(_In_ Line line, _In_ int which)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarkerNumberFromLine), static_cast<WPARAM>(line), static_cast<LPARAM>(which)));
}

BOOL CScintillaCtrl::GetUndoCollection()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetUndoCollection), 0, 0));
}

WhiteSpace CScintillaCtrl::GetViewWS()
{
  return static_cast<WhiteSpace>(Call(static_cast<UINT>(Message::GetViewWS), 0, 0));
}

void CScintillaCtrl::SetViewWS(_In_ WhiteSpace viewWS)
{
  Call(static_cast<UINT>(Message::SetViewWS), static_cast<WPARAM>(viewWS), 0);
}

TabDrawMode CScintillaCtrl::GetTabDrawMode()
{
  return static_cast<TabDrawMode>(Call(static_cast<UINT>(Message::GetTabDrawMode), 0, 0));
}

void CScintillaCtrl::SetTabDrawMode(_In_ TabDrawMode tabDrawMode)
{
  Call(static_cast<UINT>(Message::SetTabDrawMode), static_cast<WPARAM>(tabDrawMode), 0);
}

Position CScintillaCtrl::PositionFromPoint(_In_ int x, _In_ int y)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionFromPoint), static_cast<WPARAM>(x), static_cast<LPARAM>(y)));
}

Position CScintillaCtrl::PositionFromPointClose(_In_ int x, _In_ int y)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionFromPointClose), static_cast<WPARAM>(x), static_cast<LPARAM>(y)));
}

void CScintillaCtrl::GotoLine(_In_ Line line)
{
  Call(static_cast<UINT>(Message::GotoLine), static_cast<WPARAM>(line), 0);
}

void CScintillaCtrl::GotoPos(_In_ Position caret)
{
  Call(static_cast<UINT>(Message::GotoPos), static_cast<WPARAM>(caret), 0);
}

void CScintillaCtrl::SetAnchor(_In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetAnchor), static_cast<WPARAM>(anchor), 0);
}

Position CScintillaCtrl::GetCurLine(_In_ Position length, _Inout_opt_z_ char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetCurLine), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::GetEndStyled()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetEndStyled), 0, 0));
}

void CScintillaCtrl::ConvertEOLs(_In_ EndOfLine eolMode)
{
  Call(static_cast<UINT>(Message::ConvertEOLs), static_cast<WPARAM>(eolMode), 0);
}

EndOfLine CScintillaCtrl::GetEOLMode()
{
  return static_cast<EndOfLine>(Call(static_cast<UINT>(Message::GetEOLMode), 0, 0));
}

void CScintillaCtrl::SetEOLMode(_In_ EndOfLine eolMode)
{
  Call(static_cast<UINT>(Message::SetEOLMode), static_cast<WPARAM>(eolMode), 0);
}

void CScintillaCtrl::StartStyling(_In_ Position start, _In_ int unused)
{
  Call(static_cast<UINT>(Message::StartStyling), static_cast<WPARAM>(start), static_cast<LPARAM>(unused));
}

void CScintillaCtrl::SetStyling(_In_ Position length, _In_ int style)
{
  Call(static_cast<UINT>(Message::SetStyling), static_cast<WPARAM>(length), static_cast<LPARAM>(style));
}

BOOL CScintillaCtrl::GetBufferedDraw()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetBufferedDraw), 0, 0));
}

void CScintillaCtrl::SetBufferedDraw(_In_ BOOL buffered)
{
  Call(static_cast<UINT>(Message::SetBufferedDraw), static_cast<WPARAM>(buffered), 0);
}

void CScintillaCtrl::SetTabWidth(_In_ int tabWidth)
{
  Call(static_cast<UINT>(Message::SetTabWidth), static_cast<WPARAM>(tabWidth), 0);
}

int CScintillaCtrl::GetTabWidth()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetTabWidth), 0, 0));
}

void CScintillaCtrl::SetTabMinimumWidth(_In_ int pixels)
{
  Call(static_cast<UINT>(Message::SetTabMinimumWidth), static_cast<WPARAM>(pixels), 0);
}

int CScintillaCtrl::GetTabMinimumWidth()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetTabMinimumWidth), 0, 0));
}

void CScintillaCtrl::ClearTabStops(_In_ Line line)
{
  Call(static_cast<UINT>(Message::ClearTabStops), static_cast<WPARAM>(line), 0);
}

void CScintillaCtrl::AddTabStop(_In_ Line line, _In_ int x)
{
  Call(static_cast<UINT>(Message::AddTabStop), static_cast<WPARAM>(line), static_cast<LPARAM>(x));
}

int CScintillaCtrl::GetNextTabStop(_In_ Line line, _In_ int x)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetNextTabStop), static_cast<WPARAM>(line), static_cast<LPARAM>(x)));
}

void CScintillaCtrl::SetCodePage(_In_ int codePage)
{
  Call(static_cast<UINT>(Message::SetCodePage), static_cast<WPARAM>(codePage), 0);
}

void CScintillaCtrl::SetFontLocale(_In_z_ const char* localeName)
{
  Call(static_cast<UINT>(Message::SetFontLocale), 0, reinterpret_cast<LPARAM>(localeName));
}

int CScintillaCtrl::GetFontLocale(_Inout_opt_z_ char* localeName)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetFontLocale), 0, reinterpret_cast<LPARAM>(localeName)));
}

IMEInteraction CScintillaCtrl::GetIMEInteraction()
{
  return static_cast<IMEInteraction>(Call(static_cast<UINT>(Message::GetIMEInteraction), 0, 0));
}

void CScintillaCtrl::SetIMEInteraction(_In_ IMEInteraction imeInteraction)
{
  Call(static_cast<UINT>(Message::SetIMEInteraction), static_cast<WPARAM>(imeInteraction), 0);
}

void CScintillaCtrl::MarkerDefine(_In_ int markerNumber, _In_ MarkerSymbol markerSymbol)
{
  Call(static_cast<UINT>(Message::MarkerDefine), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(markerSymbol));
}

void CScintillaCtrl::MarkerSetFore(_In_ int markerNumber, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::MarkerSetFore), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::MarkerSetBack(_In_ int markerNumber, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::MarkerSetBack), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(back));
}

void CScintillaCtrl::MarkerSetBackSelected(_In_ int markerNumber, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::MarkerSetBackSelected), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(back));
}

void CScintillaCtrl::MarkerSetForeTranslucent(_In_ int markerNumber, _In_ int fore)
{
  Call(static_cast<UINT>(Message::MarkerSetForeTranslucent), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::MarkerSetBackTranslucent(_In_ int markerNumber, _In_ int back)
{
  Call(static_cast<UINT>(Message::MarkerSetBackTranslucent), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(back));
}

void CScintillaCtrl::MarkerSetBackSelectedTranslucent(_In_ int markerNumber, _In_ int back)
{
  Call(static_cast<UINT>(Message::MarkerSetBackSelectedTranslucent), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(back));
}

void CScintillaCtrl::MarkerSetStrokeWidth(_In_ int markerNumber, _In_ int hundredths)
{
  Call(static_cast<UINT>(Message::MarkerSetStrokeWidth), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(hundredths));
}

void CScintillaCtrl::MarkerEnableHighlight(_In_ BOOL enabled)
{
  Call(static_cast<UINT>(Message::MarkerEnableHighlight), static_cast<WPARAM>(enabled), 0);
}

int CScintillaCtrl::MarkerAdd(_In_ Line line, _In_ int markerNumber)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarkerAdd), static_cast<WPARAM>(line), static_cast<LPARAM>(markerNumber)));
}

void CScintillaCtrl::MarkerDelete(_In_ Line line, _In_ int markerNumber)
{
  Call(static_cast<UINT>(Message::MarkerDelete), static_cast<WPARAM>(line), static_cast<LPARAM>(markerNumber));
}

void CScintillaCtrl::MarkerDeleteAll(_In_ int markerNumber)
{
  Call(static_cast<UINT>(Message::MarkerDeleteAll), static_cast<WPARAM>(markerNumber), 0);
}

int CScintillaCtrl::MarkerGet(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarkerGet), static_cast<WPARAM>(line), 0));
}

Line CScintillaCtrl::MarkerNext(_In_ Line lineStart, _In_ int markerMask)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::MarkerNext), static_cast<WPARAM>(lineStart), static_cast<LPARAM>(markerMask)));
}

Line CScintillaCtrl::MarkerPrevious(_In_ Line lineStart, _In_ int markerMask)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::MarkerPrevious), static_cast<WPARAM>(lineStart), static_cast<LPARAM>(markerMask)));
}

void CScintillaCtrl::MarkerDefinePixmap(_In_ int markerNumber, _In_ const char* pixmap)
{
  Call(static_cast<UINT>(Message::MarkerDefinePixmap), static_cast<WPARAM>(markerNumber), reinterpret_cast<LPARAM>(pixmap));
}

void CScintillaCtrl::MarkerAddSet(_In_ Line line, _In_ int markerSet)
{
  Call(static_cast<UINT>(Message::MarkerAddSet), static_cast<WPARAM>(line), static_cast<LPARAM>(markerSet));
}

void CScintillaCtrl::MarkerSetAlpha(_In_ int markerNumber, _In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::MarkerSetAlpha), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(alpha));
}

Layer CScintillaCtrl::MarkerGetLayer(_In_ int markerNumber)
{
  return static_cast<Layer>(Call(static_cast<UINT>(Message::MarkerGetLayer), static_cast<WPARAM>(markerNumber), 0));
}

void CScintillaCtrl::MarkerSetLayer(_In_ int markerNumber, _In_ Layer layer)
{
  Call(static_cast<UINT>(Message::MarkerSetLayer), static_cast<WPARAM>(markerNumber), static_cast<LPARAM>(layer));
}

void CScintillaCtrl::SetMarginTypeN(_In_ int margin, _In_ MarginType marginType)
{
  Call(static_cast<UINT>(Message::SetMarginTypeN), static_cast<WPARAM>(margin), static_cast<LPARAM>(marginType));
}

MarginType CScintillaCtrl::GetMarginTypeN(_In_ int margin)
{
  return static_cast<MarginType>(Call(static_cast<UINT>(Message::GetMarginTypeN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMarginWidthN(_In_ int margin, _In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::SetMarginWidthN), static_cast<WPARAM>(margin), static_cast<LPARAM>(pixelWidth));
}

int CScintillaCtrl::GetMarginWidthN(_In_ int margin)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMarginWidthN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMarginMaskN(_In_ int margin, _In_ int mask)
{
  Call(static_cast<UINT>(Message::SetMarginMaskN), static_cast<WPARAM>(margin), static_cast<LPARAM>(mask));
}

int CScintillaCtrl::GetMarginMaskN(_In_ int margin)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMarginMaskN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMarginSensitiveN(_In_ int margin, _In_ BOOL sensitive)
{
  Call(static_cast<UINT>(Message::SetMarginSensitiveN), static_cast<WPARAM>(margin), static_cast<LPARAM>(sensitive));
}

BOOL CScintillaCtrl::GetMarginSensitiveN(_In_ int margin)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMarginSensitiveN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMarginCursorN(_In_ int margin, _In_ CursorShape cursor)
{
  Call(static_cast<UINT>(Message::SetMarginCursorN), static_cast<WPARAM>(margin), static_cast<LPARAM>(cursor));
}

CursorShape CScintillaCtrl::GetMarginCursorN(_In_ int margin)
{
  return static_cast<CursorShape>(Call(static_cast<UINT>(Message::GetMarginCursorN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMarginBackN(_In_ int margin, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetMarginBackN), static_cast<WPARAM>(margin), static_cast<LPARAM>(back));
}

COLORREF CScintillaCtrl::GetMarginBackN(_In_ int margin)
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetMarginBackN), static_cast<WPARAM>(margin), 0));
}

void CScintillaCtrl::SetMargins(_In_ int margins)
{
  Call(static_cast<UINT>(Message::SetMargins), static_cast<WPARAM>(margins), 0);
}

int CScintillaCtrl::GetMargins()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMargins), 0, 0));
}

void CScintillaCtrl::StyleClearAll()
{
  Call(static_cast<UINT>(Message::StyleClearAll), 0, 0);
}

void CScintillaCtrl::StyleSetFore(_In_ int style, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::StyleSetFore), static_cast<WPARAM>(style), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::StyleSetBack(_In_ int style, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::StyleSetBack), static_cast<WPARAM>(style), static_cast<LPARAM>(back));
}

void CScintillaCtrl::StyleSetBold(_In_ int style, _In_ BOOL bold)
{
  Call(static_cast<UINT>(Message::StyleSetBold), static_cast<WPARAM>(style), static_cast<LPARAM>(bold));
}

void CScintillaCtrl::StyleSetItalic(_In_ int style, _In_ BOOL italic)
{
  Call(static_cast<UINT>(Message::StyleSetItalic), static_cast<WPARAM>(style), static_cast<LPARAM>(italic));
}

void CScintillaCtrl::StyleSetSize(_In_ int style, _In_ int sizePoints)
{
  Call(static_cast<UINT>(Message::StyleSetSize), static_cast<WPARAM>(style), static_cast<LPARAM>(sizePoints));
}

void CScintillaCtrl::StyleSetFont(_In_ int style, _In_z_ const char* fontName)
{
  Call(static_cast<UINT>(Message::StyleSetFont), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(fontName));
}

void CScintillaCtrl::StyleSetEOLFilled(_In_ int style, _In_ BOOL eolFilled)
{
  Call(static_cast<UINT>(Message::StyleSetEOLFilled), static_cast<WPARAM>(style), static_cast<LPARAM>(eolFilled));
}

void CScintillaCtrl::StyleResetDefault()
{
  Call(static_cast<UINT>(Message::StyleResetDefault), 0, 0);
}

void CScintillaCtrl::StyleSetUnderline(_In_ int style, _In_ BOOL underline)
{
  Call(static_cast<UINT>(Message::StyleSetUnderline), static_cast<WPARAM>(style), static_cast<LPARAM>(underline));
}

COLORREF CScintillaCtrl::StyleGetFore(_In_ int style)
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::StyleGetFore), static_cast<WPARAM>(style), 0));
}

COLORREF CScintillaCtrl::StyleGetBack(_In_ int style)
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::StyleGetBack), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetBold(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetBold), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetItalic(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetItalic), static_cast<WPARAM>(style), 0));
}

int CScintillaCtrl::StyleGetSize(_In_ int style)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::StyleGetSize), static_cast<WPARAM>(style), 0));
}

int CScintillaCtrl::StyleGetFont(_In_ int style, _Inout_opt_z_ char* fontName)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::StyleGetFont), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(fontName)));
}

BOOL CScintillaCtrl::StyleGetEOLFilled(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetEOLFilled), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetUnderline(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetUnderline), static_cast<WPARAM>(style), 0));
}

CaseVisible CScintillaCtrl::StyleGetCase(_In_ int style)
{
  return static_cast<CaseVisible>(Call(static_cast<UINT>(Message::StyleGetCase), static_cast<WPARAM>(style), 0));
}

CharacterSet CScintillaCtrl::StyleGetCharacterSet(_In_ int style)
{
  return static_cast<CharacterSet>(Call(static_cast<UINT>(Message::StyleGetCharacterSet), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetVisible(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetVisible), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetChangeable(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetChangeable), static_cast<WPARAM>(style), 0));
}

BOOL CScintillaCtrl::StyleGetHotSpot(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetHotSpot), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::StyleSetCase(_In_ int style, _In_ CaseVisible caseVisible)
{
  Call(static_cast<UINT>(Message::StyleSetCase), static_cast<WPARAM>(style), static_cast<LPARAM>(caseVisible));
}

void CScintillaCtrl::StyleSetSizeFractional(_In_ int style, _In_ int sizeInHundredthPoints)
{
  Call(static_cast<UINT>(Message::StyleSetSizeFractional), static_cast<WPARAM>(style), static_cast<LPARAM>(sizeInHundredthPoints));
}

int CScintillaCtrl::StyleGetSizeFractional(_In_ int style)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::StyleGetSizeFractional), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::StyleSetWeight(_In_ int style, _In_ FontWeight weight)
{
  Call(static_cast<UINT>(Message::StyleSetWeight), static_cast<WPARAM>(style), static_cast<LPARAM>(weight));
}

FontWeight CScintillaCtrl::StyleGetWeight(_In_ int style)
{
  return static_cast<FontWeight>(Call(static_cast<UINT>(Message::StyleGetWeight), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::StyleSetCharacterSet(_In_ int style, _In_ CharacterSet characterSet)
{
  Call(static_cast<UINT>(Message::StyleSetCharacterSet), static_cast<WPARAM>(style), static_cast<LPARAM>(characterSet));
}

void CScintillaCtrl::StyleSetHotSpot(_In_ int style, _In_ BOOL hotspot)
{
  Call(static_cast<UINT>(Message::StyleSetHotSpot), static_cast<WPARAM>(style), static_cast<LPARAM>(hotspot));
}

void CScintillaCtrl::StyleSetCheckMonospaced(_In_ int style, _In_ BOOL checkMonospaced)
{
  Call(static_cast<UINT>(Message::StyleSetCheckMonospaced), static_cast<WPARAM>(style), static_cast<LPARAM>(checkMonospaced));
}

BOOL CScintillaCtrl::StyleGetCheckMonospaced(_In_ int style)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::StyleGetCheckMonospaced), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::StyleSetStretch(_In_ int style, _In_ FontStretch stretch)
{
  Call(static_cast<UINT>(Scintilla::Message::StyleSetStretch), static_cast<WPARAM>(style), static_cast<LPARAM>(stretch));
}

FontStretch CScintillaCtrl::StyleGetStretch(_In_ int style)
{
  return static_cast<FontStretch>(Call(static_cast<UINT>(Scintilla::Message::StyleGetStretch), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::StyleSetInvisibleRepresentation(_In_ int style, _In_z_ const char* representation)
{
  Call(static_cast<UINT>(Message::StyleSetInvisibleRepresentation), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(representation));
}

int CScintillaCtrl::StyleGetInvisibleRepresentation(_In_ int style, _Inout_opt_z_ char* representation)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::StyleGetInvisibleRepresentation), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(representation)));
}

void CScintillaCtrl::SetElementColour(_In_ Element element, _In_ int colourElement)
{
  Call(static_cast<UINT>(Message::SetElementColour), static_cast<WPARAM>(element), static_cast<LPARAM>(colourElement));
}

int CScintillaCtrl::GetElementColour(_In_ Element element)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetElementColour), static_cast<WPARAM>(element), 0));
}

void CScintillaCtrl::ResetElementColour(_In_ Element element)
{
  Call(static_cast<UINT>(Message::ResetElementColour), static_cast<WPARAM>(element), 0);
}

BOOL CScintillaCtrl::GetElementIsSet(_In_ Element element)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetElementIsSet), static_cast<WPARAM>(element), 0));
}

BOOL CScintillaCtrl::GetElementAllowsTranslucent(_In_ Element element)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetElementAllowsTranslucent), static_cast<WPARAM>(element), 0));
}

int CScintillaCtrl::GetElementBaseColour(_In_ Element element)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetElementBaseColour), static_cast<WPARAM>(element), 0));
}

void CScintillaCtrl::SetSelFore(_In_ BOOL useSetting, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetSelFore), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::SetSelBack(_In_ BOOL useSetting, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetSelBack), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(back));
}

Alpha CScintillaCtrl::GetSelAlpha()
{
  return static_cast<Alpha>(Call(static_cast<UINT>(Message::GetSelAlpha), 0, 0));
}

void CScintillaCtrl::SetSelAlpha(_In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::SetSelAlpha), static_cast<WPARAM>(alpha), 0);
}

BOOL CScintillaCtrl::GetSelEOLFilled()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetSelEOLFilled), 0, 0));
}

void CScintillaCtrl::SetSelEOLFilled(_In_ BOOL filled)
{
  Call(static_cast<UINT>(Message::SetSelEOLFilled), static_cast<WPARAM>(filled), 0);
}

Layer CScintillaCtrl::GetSelectionLayer()
{
  return static_cast<Layer>(Call(static_cast<UINT>(Message::GetSelectionLayer), 0, 0));
}

void CScintillaCtrl::SetSelectionLayer(_In_ Layer layer)
{
  Call(static_cast<UINT>(Message::SetSelectionLayer), static_cast<WPARAM>(layer), 0);
}

Layer CScintillaCtrl::GetCaretLineLayer()
{
  return static_cast<Layer>(Call(static_cast<UINT>(Message::GetCaretLineLayer), 0, 0));
}

void CScintillaCtrl::SetCaretLineLayer(_In_ Layer layer)
{
  Call(static_cast<UINT>(Message::SetCaretLineLayer), static_cast<WPARAM>(layer), 0);
}

BOOL CScintillaCtrl::GetCaretLineHighlightSubLine()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetCaretLineHighlightSubLine), 0, 0));
}

void CScintillaCtrl::SetCaretLineHighlightSubLine(_In_ BOOL subLine)
{
  Call(static_cast<UINT>(Message::SetCaretLineHighlightSubLine), static_cast<WPARAM>(subLine), 0);
}

void CScintillaCtrl::SetCaretFore(_In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetCaretFore), static_cast<WPARAM>(fore), 0);
}

void CScintillaCtrl::AssignCmdKey(_In_ DWORD keyDefinition, _In_ int sciCommand)
{
  Call(static_cast<UINT>(Message::AssignCmdKey), static_cast<WPARAM>(keyDefinition), static_cast<LPARAM>(sciCommand));
}

void CScintillaCtrl::ClearCmdKey(_In_ DWORD keyDefinition)
{
  Call(static_cast<UINT>(Message::ClearCmdKey), static_cast<WPARAM>(keyDefinition), 0);
}

void CScintillaCtrl::ClearAllCmdKeys()
{
  Call(static_cast<UINT>(Message::ClearAllCmdKeys), 0, 0);
}

void CScintillaCtrl::SetStylingEx(_In_ Position length, _In_ const char* styles)
{
  Call(static_cast<UINT>(Message::SetStylingEx), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(styles));
}

void CScintillaCtrl::StyleSetVisible(_In_ int style, _In_ BOOL visible)
{
  Call(static_cast<UINT>(Message::StyleSetVisible), static_cast<WPARAM>(style), static_cast<LPARAM>(visible));
}

int CScintillaCtrl::GetCaretPeriod()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCaretPeriod), 0, 0));
}

void CScintillaCtrl::SetCaretPeriod(_In_ int periodMilliseconds)
{
  Call(static_cast<UINT>(Message::SetCaretPeriod), static_cast<WPARAM>(periodMilliseconds), 0);
}

void CScintillaCtrl::SetWordChars(_In_ const char* characters)
{
  Call(static_cast<UINT>(Message::SetWordChars), 0, reinterpret_cast<LPARAM>(characters));
}

int CScintillaCtrl::GetWordChars(_Inout_opt_z_ char* characters)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetWordChars), 0, reinterpret_cast<LPARAM>(characters)));
}

void CScintillaCtrl::SetCharacterCategoryOptimization(_In_ int countCharacters)
{
  Call(static_cast<UINT>(Message::SetCharacterCategoryOptimization), static_cast<WPARAM>(countCharacters), 0);
}

int CScintillaCtrl::GetCharacterCategoryOptimization()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCharacterCategoryOptimization), 0, 0));
}

void CScintillaCtrl::BeginUndoAction()
{
  Call(static_cast<UINT>(Message::BeginUndoAction), 0, 0);
}

void CScintillaCtrl::EndUndoAction()
{
  Call(static_cast<UINT>(Message::EndUndoAction), 0, 0);
}

int CScintillaCtrl::GetUndoSequence()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoSequence), 0, 0));
}

int CScintillaCtrl::GetUndoActions()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoActions), 0, 0));
}

void CScintillaCtrl::SetUndoSavePoint(_In_ int action)
{
  Call(static_cast<UINT>(Scintilla::Message::SetUndoSavePoint), static_cast<WPARAM>(action), 0);
}

int CScintillaCtrl::GetUndoSavePoint()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoSavePoint), 0, 0));
}

void CScintillaCtrl::SetUndoDetach(_In_ int action)
{
  Call(static_cast<UINT>(Scintilla::Message::SetUndoDetach), static_cast<WPARAM>(action), 0);
}

int CScintillaCtrl::GetUndoDetach()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoDetach), 0, 0));
}

void CScintillaCtrl::SetUndoTentative(_In_ int action)
{
  Call(static_cast<UINT>(Scintilla::Message::SetUndoTentative), static_cast<WPARAM>(action), 0);
}

int CScintillaCtrl::GetUndoTentative()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoTentative), 0, 0));
}

void CScintillaCtrl::SetUndoCurrent(_In_ int action)
{
  Call(static_cast<UINT>(Scintilla::Message::SetUndoCurrent), static_cast<WPARAM>(action), 0);
}

int CScintillaCtrl::GetUndoCurrent()
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoCurrent), 0, 0));
}

void CScintillaCtrl::PushUndoActionType(_In_ int type, Position pos)
{
  Call(static_cast<UINT>(Scintilla::Message::PushUndoActionType), static_cast<WPARAM>(type), static_cast<LPARAM>(pos));
}

void CScintillaCtrl::ChangeLastUndoActionText(_In_z_ const char* text)
{
  ChangeLastUndoActionText(strlen(text), text);
}

void CScintillaCtrl::ChangeLastUndoActionText(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  Call(static_cast<UINT>(Scintilla::Message::ChangeLastUndoActionText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

int CScintillaCtrl::GetUndoActionType(_In_ int action)
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoActionType), static_cast<WPARAM>(action), 0));
}

Position CScintillaCtrl::GetUndoActionPosition(_In_ int action)
{
  return Call(static_cast<UINT>(Scintilla::Message::GetUndoActionPosition), static_cast<WPARAM>(action), 0);
}

int CScintillaCtrl::GetUndoActionText(_In_ int action, _Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetUndoActionText), static_cast<WPARAM>(action), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::IndicSetStyle(_In_ int indicator, _In_ IndicatorStyle indicatorStyle)
{
  Call(static_cast<UINT>(Message::IndicSetStyle), static_cast<WPARAM>(indicator), static_cast<LPARAM>(indicatorStyle));
}

IndicatorStyle CScintillaCtrl::IndicGetStyle(_In_ int indicator)
{
  return static_cast<IndicatorStyle>(Call(static_cast<UINT>(Message::IndicGetStyle), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetFore(_In_ int indicator, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::IndicSetFore), static_cast<WPARAM>(indicator), static_cast<LPARAM>(fore));
}

COLORREF CScintillaCtrl::IndicGetFore(_In_ int indicator)
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::IndicGetFore), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetUnder(_In_ int indicator, _In_ BOOL under)
{
  Call(static_cast<UINT>(Message::IndicSetUnder), static_cast<WPARAM>(indicator), static_cast<LPARAM>(under));
}

BOOL CScintillaCtrl::IndicGetUnder(_In_ int indicator)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::IndicGetUnder), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetHoverStyle(_In_ int indicator, _In_ IndicatorStyle indicatorStyle)
{
  Call(static_cast<UINT>(Message::IndicSetHoverStyle), static_cast<WPARAM>(indicator), static_cast<LPARAM>(indicatorStyle));
}

IndicatorStyle CScintillaCtrl::IndicGetHoverStyle(_In_ int indicator)
{
  return static_cast<IndicatorStyle>(Call(static_cast<UINT>(Message::IndicGetHoverStyle), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetHoverFore(_In_ int indicator, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::IndicSetHoverFore), static_cast<WPARAM>(indicator), static_cast<LPARAM>(fore));
}

COLORREF CScintillaCtrl::IndicGetHoverFore(_In_ int indicator)
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::IndicGetHoverFore), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetFlags(_In_ int indicator, _In_ IndicFlag flags)
{
  Call(static_cast<UINT>(Message::IndicSetFlags), static_cast<WPARAM>(indicator), static_cast<LPARAM>(flags));
}

IndicFlag CScintillaCtrl::IndicGetFlags(_In_ int indicator)
{
  return static_cast<IndicFlag>(Call(static_cast<UINT>(Message::IndicGetFlags), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetStrokeWidth(_In_ int indicator, _In_ int hundredths)
{
  Call(static_cast<UINT>(Message::IndicSetStrokeWidth), static_cast<WPARAM>(indicator), static_cast<LPARAM>(hundredths));
}

int CScintillaCtrl::IndicGetStrokeWidth(_In_ int indicator)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::IndicGetStrokeWidth), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::SetWhitespaceFore(_In_ BOOL useSetting, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetWhitespaceFore), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::SetWhitespaceBack(_In_ BOOL useSetting, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetWhitespaceBack), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(back));
}

void CScintillaCtrl::SetWhitespaceSize(_In_ int size)
{
  Call(static_cast<UINT>(Message::SetWhitespaceSize), static_cast<WPARAM>(size), 0);
}

int CScintillaCtrl::GetWhitespaceSize()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetWhitespaceSize), 0, 0));
}

void CScintillaCtrl::SetLineState(_In_ Line line, _In_ int state)
{
  Call(static_cast<UINT>(Message::SetLineState), static_cast<WPARAM>(line), static_cast<LPARAM>(state));
}

int CScintillaCtrl::GetLineState(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetLineState), static_cast<WPARAM>(line), 0));
}

int CScintillaCtrl::GetMaxLineState()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMaxLineState), 0, 0));
}

BOOL CScintillaCtrl::GetCaretLineVisible()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetCaretLineVisible), 0, 0));
}

void CScintillaCtrl::SetCaretLineVisible(_In_ BOOL show)
{
  Call(static_cast<UINT>(Message::SetCaretLineVisible), static_cast<WPARAM>(show), 0);
}

COLORREF CScintillaCtrl::GetCaretLineBack()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetCaretLineBack), 0, 0));
}

void CScintillaCtrl::SetCaretLineBack(_In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetCaretLineBack), static_cast<WPARAM>(back), 0);
}

int CScintillaCtrl::GetCaretLineFrame()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCaretLineFrame), 0, 0));
}

void CScintillaCtrl::SetCaretLineFrame(_In_ int width)
{
  Call(static_cast<UINT>(Message::SetCaretLineFrame), static_cast<WPARAM>(width), 0);
}

void CScintillaCtrl::StyleSetChangeable(_In_ int style, _In_ BOOL changeable)
{
  Call(static_cast<UINT>(Message::StyleSetChangeable), static_cast<WPARAM>(style), static_cast<LPARAM>(changeable));
}

void CScintillaCtrl::AutoCShow(_In_ Position lengthEntered, _In_z_ const char* itemList)
{
  Call(static_cast<UINT>(Message::AutoCShow), static_cast<WPARAM>(lengthEntered), reinterpret_cast<LPARAM>(itemList));
}

void CScintillaCtrl::AutoCCancel()
{
  Call(static_cast<UINT>(Message::AutoCCancel), 0, 0);
}

BOOL CScintillaCtrl::AutoCActive()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCActive), 0, 0));
}

Position CScintillaCtrl::AutoCPosStart()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::AutoCPosStart), 0, 0));
}

void CScintillaCtrl::AutoCComplete()
{
  Call(static_cast<UINT>(Message::AutoCComplete), 0, 0);
}

void CScintillaCtrl::AutoCStops(_In_z_ const char* characterSet)
{
  Call(static_cast<UINT>(Message::AutoCStops), 0, reinterpret_cast<LPARAM>(characterSet));
}

void CScintillaCtrl::AutoCSetSeparator(_In_ int separatorCharacter)
{
  Call(static_cast<UINT>(Message::AutoCSetSeparator), static_cast<WPARAM>(separatorCharacter), 0);
}

int CScintillaCtrl::AutoCGetSeparator()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetSeparator), 0, 0));
}

void CScintillaCtrl::AutoCSelect(_In_z_ const char* select)
{
  Call(static_cast<UINT>(Message::AutoCSelect), 0, reinterpret_cast<LPARAM>(select));
}

void CScintillaCtrl::AutoCSetCancelAtStart(_In_ BOOL cancel)
{
  Call(static_cast<UINT>(Message::AutoCSetCancelAtStart), static_cast<WPARAM>(cancel), 0);
}

BOOL CScintillaCtrl::AutoCGetCancelAtStart()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCGetCancelAtStart), 0, 0));
}

void CScintillaCtrl::AutoCSetFillUps(_In_z_ const char* characterSet)
{
  Call(static_cast<UINT>(Message::AutoCSetFillUps), 0, reinterpret_cast<LPARAM>(characterSet));
}

void CScintillaCtrl::AutoCSetChooseSingle(_In_ BOOL chooseSingle)
{
  Call(static_cast<UINT>(Message::AutoCSetChooseSingle), static_cast<WPARAM>(chooseSingle), 0);
}

BOOL CScintillaCtrl::AutoCGetChooseSingle()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCGetChooseSingle), 0, 0));
}

void CScintillaCtrl::AutoCSetIgnoreCase(_In_ BOOL ignoreCase)
{
  Call(static_cast<UINT>(Message::AutoCSetIgnoreCase), static_cast<WPARAM>(ignoreCase), 0);
}

BOOL CScintillaCtrl::AutoCGetIgnoreCase()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCGetIgnoreCase), 0, 0));
}

void CScintillaCtrl::UserListShow(_In_ int listType, _In_z_ const char* itemList)
{
  Call(static_cast<UINT>(Message::UserListShow), static_cast<WPARAM>(listType), reinterpret_cast<LPARAM>(itemList));
}

void CScintillaCtrl::AutoCSetAutoHide(_In_ BOOL autoHide)
{
  Call(static_cast<UINT>(Message::AutoCSetAutoHide), static_cast<WPARAM>(autoHide), 0);
}

BOOL CScintillaCtrl::AutoCGetAutoHide()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCGetAutoHide), 0, 0));
}

void CScintillaCtrl::AutoCSetOptions(_In_ AutoCompleteOption options)
{
  Call(static_cast<UINT>(Message::AutoCSetOptions), static_cast<WPARAM>(options), 0);
}

AutoCompleteOption CScintillaCtrl::AutoCGetOptions()
{
  return static_cast<AutoCompleteOption>(Call(static_cast<UINT>(Message::AutoCGetOptions), 0, 0));
}

void CScintillaCtrl::AutoCSetDropRestOfWord(_In_ BOOL dropRestOfWord)
{
  Call(static_cast<UINT>(Message::AutoCSetDropRestOfWord), static_cast<WPARAM>(dropRestOfWord), 0);
}

BOOL CScintillaCtrl::AutoCGetDropRestOfWord()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::AutoCGetDropRestOfWord), 0, 0));
}

void CScintillaCtrl::RegisterImage(_In_ int type, _In_ const char* xpmData)
{
  Call(static_cast<UINT>(Message::RegisterImage), static_cast<WPARAM>(type), reinterpret_cast<LPARAM>(xpmData));
}

void CScintillaCtrl::ClearRegisteredImages()
{
  Call(static_cast<UINT>(Message::ClearRegisteredImages), 0, 0);
}

int CScintillaCtrl::AutoCGetTypeSeparator()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetTypeSeparator), 0, 0));
}

void CScintillaCtrl::AutoCSetTypeSeparator(_In_ int separatorCharacter)
{
  Call(static_cast<UINT>(Message::AutoCSetTypeSeparator), static_cast<WPARAM>(separatorCharacter), 0);
}

void CScintillaCtrl::AutoCSetMaxWidth(_In_ int characterCount)
{
  Call(static_cast<UINT>(Message::AutoCSetMaxWidth), static_cast<WPARAM>(characterCount), 0);
}

int CScintillaCtrl::AutoCGetMaxWidth()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetMaxWidth), 0, 0));
}

void CScintillaCtrl::AutoCSetMaxHeight(_In_ int rowCount)
{
  Call(static_cast<UINT>(Message::AutoCSetMaxHeight), static_cast<WPARAM>(rowCount), 0);
}

int CScintillaCtrl::AutoCGetMaxHeight()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetMaxHeight), 0, 0));
}

void CScintillaCtrl::AutoCSetStyle(_In_ int style)
{
  Call(static_cast<UINT>(Message::AutoCSetStyle), static_cast<WPARAM>(style), 0);
}

int CScintillaCtrl::AutoCGetStyle()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetStyle), 0, 0));
}

void CScintillaCtrl::SetIndent(_In_ int indentSize)
{
  Call(static_cast<UINT>(Message::SetIndent), static_cast<WPARAM>(indentSize), 0);
}

int CScintillaCtrl::GetIndent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetIndent), 0, 0));
}

void CScintillaCtrl::SetUseTabs(_In_ BOOL useTabs)
{
  Call(static_cast<UINT>(Message::SetUseTabs), static_cast<WPARAM>(useTabs), 0);
}

BOOL CScintillaCtrl::GetUseTabs()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetUseTabs), 0, 0));
}

void CScintillaCtrl::SetLineIndentation(_In_ Line line, _In_ int indentation)
{
  Call(static_cast<UINT>(Message::SetLineIndentation), static_cast<WPARAM>(line), static_cast<LPARAM>(indentation));
}

int CScintillaCtrl::GetLineIndentation(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetLineIndentation), static_cast<WPARAM>(line), 0));
}

Position CScintillaCtrl::GetLineIndentPosition(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLineIndentPosition), static_cast<WPARAM>(line), 0));
}

Position CScintillaCtrl::GetColumn(_In_ Position pos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetColumn), static_cast<WPARAM>(pos), 0));
}

Position CScintillaCtrl::CountCharacters(_In_ Position start, _In_ Position end)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::CountCharacters), static_cast<WPARAM>(start), static_cast<LPARAM>(end)));
}

Position CScintillaCtrl::CountCodeUnits(_In_ Position start, _In_ Position end)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::CountCodeUnits), static_cast<WPARAM>(start), static_cast<LPARAM>(end)));
}

void CScintillaCtrl::SetHScrollBar(_In_ BOOL visible)
{
  Call(static_cast<UINT>(Message::SetHScrollBar), static_cast<WPARAM>(visible), 0);
}

BOOL CScintillaCtrl::GetHScrollBar()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetHScrollBar), 0, 0));
}

void CScintillaCtrl::SetIndentationGuides(_In_ IndentView indentView)
{
  Call(static_cast<UINT>(Message::SetIndentationGuides), static_cast<WPARAM>(indentView), 0);
}

IndentView CScintillaCtrl::GetIndentationGuides()
{
  return static_cast<IndentView>(Call(static_cast<UINT>(Message::GetIndentationGuides), 0, 0));
}

void CScintillaCtrl::SetHighlightGuide(_In_ Position column)
{
  Call(static_cast<UINT>(Message::SetHighlightGuide), static_cast<WPARAM>(column), 0);
}

Position CScintillaCtrl::GetHighlightGuide()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetHighlightGuide), 0, 0));
}

Position CScintillaCtrl::GetLineEndPosition(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLineEndPosition), static_cast<WPARAM>(line), 0));
}

int CScintillaCtrl::GetCodePage()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCodePage), 0, 0));
}

COLORREF CScintillaCtrl::GetCaretFore()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetCaretFore), 0, 0));
}

BOOL CScintillaCtrl::GetReadOnly()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetReadOnly), 0, 0));
}

void CScintillaCtrl::SetCurrentPos(_In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetCurrentPos), static_cast<WPARAM>(caret), 0);
}

void CScintillaCtrl::SetSelectionStart(_In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetSelectionStart), static_cast<WPARAM>(anchor), 0);
}

Position CScintillaCtrl::GetSelectionStart()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionStart), 0, 0));
}

void CScintillaCtrl::SetSelectionEnd(_In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetSelectionEnd), static_cast<WPARAM>(caret), 0);
}

Position CScintillaCtrl::GetSelectionEnd()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionEnd), 0, 0));
}

void CScintillaCtrl::SetEmptySelection(_In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetEmptySelection), static_cast<WPARAM>(caret), 0);
}

void CScintillaCtrl::SetPrintMagnification(_In_ int magnification)
{
  Call(static_cast<UINT>(Message::SetPrintMagnification), static_cast<WPARAM>(magnification), 0);
}

int CScintillaCtrl::GetPrintMagnification()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPrintMagnification), 0, 0));
}

void CScintillaCtrl::SetPrintColourMode(_In_ PrintOption mode)
{
  Call(static_cast<UINT>(Message::SetPrintColourMode), static_cast<WPARAM>(mode), 0);
}

PrintOption CScintillaCtrl::GetPrintColourMode()
{
  return static_cast<PrintOption>(Call(static_cast<UINT>(Message::GetPrintColourMode), 0, 0));
}

Position CScintillaCtrl::FindText(_In_ FindOption searchFlags, _Inout_ TextToFind* ft)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::FindText), static_cast<WPARAM>(searchFlags), reinterpret_cast<LPARAM>(ft)));
}

Position CScintillaCtrl::FindTextFull(_In_ FindOption searchFlags, _Inout_ TextToFindFull* ft)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::FindTextFull), static_cast<WPARAM>(searchFlags), reinterpret_cast<LPARAM>(ft)));
}

Position CScintillaCtrl::FormatRange(_In_ BOOL draw, _In_ RangeToFormat* fr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::FormatRange), static_cast<WPARAM>(draw), reinterpret_cast<LPARAM>(fr)));
}

Position CScintillaCtrl::FormatRangeFull(_In_ BOOL draw, _In_ RangeToFormatFull* fr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::FormatRangeFull), static_cast<WPARAM>(draw), reinterpret_cast<LPARAM>(fr)));
}

void CScintillaCtrl::SetChangeHistory(_In_ ChangeHistoryOption changeHistory)
{
  Call(static_cast<UINT>(Message::SetChangeHistory), static_cast<WPARAM>(changeHistory), 0);
}

int CScintillaCtrl::GetChangeHistory()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetChangeHistory), 0, 0));
}

Line CScintillaCtrl::GetFirstVisibleLine()
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::GetFirstVisibleLine), 0, 0));
}

Position CScintillaCtrl::GetLine(_In_ Line line, _Inout_opt_z_ char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLine), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text)));
}

Line CScintillaCtrl::GetLineCount()
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::GetLineCount), 0, 0));
}

void CScintillaCtrl::AllocateLines(_In_ Line lines)
{
  Call(static_cast<UINT>(Message::AllocateLines), static_cast<WPARAM>(lines), 0);
}

void CScintillaCtrl::SetMarginLeft(_In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::SetMarginLeft), 0, static_cast<LPARAM>(pixelWidth));
}

int CScintillaCtrl::GetMarginLeft()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMarginLeft), 0, 0));
}

void CScintillaCtrl::SetMarginRight(_In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::SetMarginRight), 0, static_cast<LPARAM>(pixelWidth));
}

int CScintillaCtrl::GetMarginRight()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMarginRight), 0, 0));
}

BOOL CScintillaCtrl::GetModify()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetModify), 0, 0));
}

void CScintillaCtrl::SetSel(_In_ Position anchor, _In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetSel), static_cast<WPARAM>(anchor), static_cast<LPARAM>(caret));
}

Position CScintillaCtrl::GetSelText(_Inout_opt_z_ char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelText), 0, reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::GetTextRange(_Inout_ TextRange* tr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTextRange), 0, reinterpret_cast<LPARAM>(tr)));
}

Position CScintillaCtrl::GetTextRangeFull(_Inout_ TextRangeFull* tr)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTextRangeFull), 0, reinterpret_cast<LPARAM>(tr)));
}

void CScintillaCtrl::HideSelection(_In_ BOOL hide)
{
  Call(static_cast<UINT>(Message::HideSelection), static_cast<WPARAM>(hide), 0);
}

BOOL CScintillaCtrl::GetSelectionHidden()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetSelectionHidden), 0, 0));
}

int CScintillaCtrl::PointXFromPosition(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::PointXFromPosition), 0, static_cast<LPARAM>(pos)));
}

int CScintillaCtrl::PointYFromPosition(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::PointYFromPosition), 0, static_cast<LPARAM>(pos)));
}

Line CScintillaCtrl::LineFromPosition(_In_ Position pos)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::LineFromPosition), static_cast<WPARAM>(pos), 0));
}

Position CScintillaCtrl::PositionFromLine(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionFromLine), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::LineScroll(_In_ Position columns, _In_ Line lines)
{
  Call(static_cast<UINT>(Message::LineScroll), static_cast<WPARAM>(columns), static_cast<LPARAM>(lines));
}

void CScintillaCtrl::ScrollCaret()
{
  Call(static_cast<UINT>(Message::ScrollCaret), 0, 0);
}

void CScintillaCtrl::ScrollRange(_In_ Position secondary, _In_ Position primary)
{
  Call(static_cast<UINT>(Message::ScrollRange), static_cast<WPARAM>(secondary), static_cast<LPARAM>(primary));
}

void CScintillaCtrl::ReplaceSel(_In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::ReplaceSel), 0, reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::SetReadOnly(_In_ BOOL readOnly)
{
  Call(static_cast<UINT>(Message::SetReadOnly), static_cast<WPARAM>(readOnly), 0);
}

void CScintillaCtrl::Null()
{
  Call(static_cast<UINT>(Message::Null), 0, 0);
}

BOOL CScintillaCtrl::CanPaste()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::CanPaste), 0, 0));
}

BOOL CScintillaCtrl::CanUndo()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::CanUndo), 0, 0));
}

void CScintillaCtrl::EmptyUndoBuffer()
{
  Call(static_cast<UINT>(Message::EmptyUndoBuffer), 0, 0);
}

void CScintillaCtrl::Undo()
{
  Call(static_cast<UINT>(Message::Undo), 0, 0);
}

void CScintillaCtrl::Cut()
{
  Call(static_cast<UINT>(Message::Cut), 0, 0);
}

void CScintillaCtrl::Copy()
{
  Call(static_cast<UINT>(Message::Copy), 0, 0);
}

void CScintillaCtrl::Paste()
{
  Call(static_cast<UINT>(Message::Paste), 0, 0);
}

void CScintillaCtrl::Clear()
{
  Call(static_cast<UINT>(Message::Clear), 0, 0);
}

void CScintillaCtrl::SetText(_In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::SetText), 0, reinterpret_cast<LPARAM>(text));
}

Position CScintillaCtrl::GetText(_In_ Position length, _Inout_updates_opt_(length+1) char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::GetTextLength()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTextLength), 0, 0));
}

void CScintillaCtrl::SetOvertype(_In_ BOOL overType)
{
  Call(static_cast<UINT>(Message::SetOvertype), static_cast<WPARAM>(overType), 0);
}

BOOL CScintillaCtrl::GetOvertype()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetOvertype), 0, 0));
}

void CScintillaCtrl::SetCaretWidth(_In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::SetCaretWidth), static_cast<WPARAM>(pixelWidth), 0);
}

int CScintillaCtrl::GetCaretWidth()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetCaretWidth), 0, 0));
}

void CScintillaCtrl::SetTargetStart(_In_ Position start)
{
  Call(static_cast<UINT>(Message::SetTargetStart), static_cast<WPARAM>(start), 0);
}

Position CScintillaCtrl::GetTargetStart()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTargetStart), 0, 0));
}

void CScintillaCtrl::SetTargetStartVirtualSpace(_In_ Position space)
{
  Call(static_cast<UINT>(Message::SetTargetStartVirtualSpace), static_cast<WPARAM>(space), 0);
}

Position CScintillaCtrl::GetTargetStartVirtualSpace()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTargetStartVirtualSpace), 0, 0));
}

void CScintillaCtrl::SetTargetEnd(_In_ Position end)
{
  Call(static_cast<UINT>(Message::SetTargetEnd), static_cast<WPARAM>(end), 0);
}

void CScintillaCtrl::SetTargetRange(_In_ Position start, _In_ Position end)
{
  Call(static_cast<UINT>(Message::SetTargetRange), static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

Position CScintillaCtrl::GetTargetText(_Inout_opt_z_ char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTargetText), 0, reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::TargetFromSelection()
{
  Call(static_cast<UINT>(Message::TargetFromSelection), 0, 0);
}

void CScintillaCtrl::TargetWholeDocument()
{
  Call(static_cast<UINT>(Message::TargetWholeDocument), 0, 0);
}

Position CScintillaCtrl::GetTargetEnd()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTargetEnd), 0, 0));
}

void CScintillaCtrl::SetTargetEndVirtualSpace(_In_ Position space)
{
  Call(static_cast<UINT>(Message::SetTargetEndVirtualSpace), static_cast<WPARAM>(space), 0);
}

Position CScintillaCtrl::GetTargetEndVirtualSpace()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetTargetEndVirtualSpace), 0, 0));
}

Position CScintillaCtrl::ReplaceTarget(_In_ Position length, _In_ const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::ReplaceTarget), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::ReplaceTargetRE(_In_ Position length, _In_ const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::ReplaceTargetRE), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::ReplaceTargetMinimal(_In_ Position length, _In_ const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::ReplaceTargetMinimal), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::SearchInTarget(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::SearchInTarget), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::SetSearchFlags(_In_ FindOption searchFlags)
{
  Call(static_cast<UINT>(Message::SetSearchFlags), static_cast<WPARAM>(searchFlags), 0);
}

FindOption CScintillaCtrl::GetSearchFlags()
{
  return static_cast<FindOption>(Call(static_cast<UINT>(Message::GetSearchFlags), 0, 0));
}

void CScintillaCtrl::CallTipShow(_In_ Position pos, _In_z_ const char* definition)
{
  Call(static_cast<UINT>(Message::CallTipShow), static_cast<WPARAM>(pos), reinterpret_cast<LPARAM>(definition));
}

void CScintillaCtrl::CallTipCancel()
{
  Call(static_cast<UINT>(Message::CallTipCancel), 0, 0);
}

BOOL CScintillaCtrl::CallTipActive()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::CallTipActive), 0, 0));
}

Position CScintillaCtrl::CallTipPosStart()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::CallTipPosStart), 0, 0));
}

void CScintillaCtrl::CallTipSetPosStart(_In_ Position posStart)
{
  Call(static_cast<UINT>(Message::CallTipSetPosStart), static_cast<WPARAM>(posStart), 0);
}

void CScintillaCtrl::CallTipSetHlt(_In_ Position highlightStart, _In_ Position highlightEnd)
{
  Call(static_cast<UINT>(Message::CallTipSetHlt), static_cast<WPARAM>(highlightStart), static_cast<LPARAM>(highlightEnd));
}

void CScintillaCtrl::CallTipSetBack(_In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::CallTipSetBack), static_cast<WPARAM>(back), 0);
}

void CScintillaCtrl::CallTipSetFore(_In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::CallTipSetFore), static_cast<WPARAM>(fore), 0);
}

void CScintillaCtrl::CallTipSetForeHlt(_In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::CallTipSetForeHlt), static_cast<WPARAM>(fore), 0);
}

void CScintillaCtrl::CallTipUseStyle(_In_ int tabSize)
{
  Call(static_cast<UINT>(Message::CallTipUseStyle), static_cast<WPARAM>(tabSize), 0);
}

void CScintillaCtrl::CallTipSetPosition(_In_ BOOL above)
{
  Call(static_cast<UINT>(Message::CallTipSetPosition), static_cast<WPARAM>(above), 0);
}

Line CScintillaCtrl::VisibleFromDocLine(_In_ Line docLine)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::VisibleFromDocLine), static_cast<WPARAM>(docLine), 0));
}

Line CScintillaCtrl::DocLineFromVisible(_In_ Line displayLine)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::DocLineFromVisible), static_cast<WPARAM>(displayLine), 0));
}

Line CScintillaCtrl::WrapCount(_In_ Line docLine)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::WrapCount), static_cast<WPARAM>(docLine), 0));
}

void CScintillaCtrl::SetFoldLevel(_In_ Line line, _In_ FoldLevel level)
{
  Call(static_cast<UINT>(Message::SetFoldLevel), static_cast<WPARAM>(line), static_cast<LPARAM>(level));
}

FoldLevel CScintillaCtrl::GetFoldLevel(_In_ Line line)
{
  return static_cast<FoldLevel>(Call(static_cast<UINT>(Message::GetFoldLevel), static_cast<WPARAM>(line), 0));
}

Line CScintillaCtrl::GetLastChild(_In_ Line line, _In_ FoldLevel level)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::GetLastChild), static_cast<WPARAM>(line), static_cast<LPARAM>(level)));
}

Line CScintillaCtrl::GetFoldParent(_In_ Line line)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::GetFoldParent), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::ShowLines(_In_ Line lineStart, _In_ Line lineEnd)
{
  Call(static_cast<UINT>(Message::ShowLines), static_cast<WPARAM>(lineStart), static_cast<LPARAM>(lineEnd));
}

void CScintillaCtrl::HideLines(_In_ Line lineStart, _In_ Line lineEnd)
{
  Call(static_cast<UINT>(Message::HideLines), static_cast<WPARAM>(lineStart), static_cast<LPARAM>(lineEnd));
}

BOOL CScintillaCtrl::GetLineVisible(_In_ Line line)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetLineVisible), static_cast<WPARAM>(line), 0));
}

BOOL CScintillaCtrl::GetAllLinesVisible()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetAllLinesVisible), 0, 0));
}

void CScintillaCtrl::SetFoldExpanded(_In_ Line line, _In_ BOOL expanded)
{
  Call(static_cast<UINT>(Message::SetFoldExpanded), static_cast<WPARAM>(line), static_cast<LPARAM>(expanded));
}

BOOL CScintillaCtrl::GetFoldExpanded(_In_ Line line)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetFoldExpanded), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::ToggleFold(_In_ Line line)
{
  Call(static_cast<UINT>(Message::ToggleFold), static_cast<WPARAM>(line), 0);
}

void CScintillaCtrl::ToggleFoldShowText(_In_ Line line, _In_ const char* text)
{
  Call(static_cast<UINT>(Message::ToggleFoldShowText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::FoldDisplayTextSetStyle(_In_ FoldDisplayTextStyle style)
{
  Call(static_cast<UINT>(Message::FoldDisplayTextSetStyle), static_cast<WPARAM>(style), 0);
}

FoldDisplayTextStyle CScintillaCtrl::FoldDisplayTextGetStyle()
{
  return static_cast<FoldDisplayTextStyle>(Call(static_cast<UINT>(Message::FoldDisplayTextGetStyle), 0, 0));
}

void CScintillaCtrl::SetDefaultFoldDisplayText(_In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::SetDefaultFoldDisplayText), 0, reinterpret_cast<LPARAM>(text));
}

int CScintillaCtrl::GetDefaultFoldDisplayText(_Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetDefaultFoldDisplayText), 0, reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::FoldLine(_In_ Line line, _In_ FoldAction action)
{
  Call(static_cast<UINT>(Message::FoldLine), static_cast<WPARAM>(line), static_cast<LPARAM>(action));
}

void CScintillaCtrl::FoldChildren(_In_ Line line, _In_ FoldAction action)
{
  Call(static_cast<UINT>(Message::FoldChildren), static_cast<WPARAM>(line), static_cast<LPARAM>(action));
}

void CScintillaCtrl::ExpandChildren(_In_ Line line, _In_ FoldLevel level)
{
  Call(static_cast<UINT>(Message::ExpandChildren), static_cast<WPARAM>(line), static_cast<LPARAM>(level));
}

void CScintillaCtrl::FoldAll(_In_ FoldAction action)
{
  Call(static_cast<UINT>(Message::FoldAll), static_cast<WPARAM>(action), 0);
}

void CScintillaCtrl::EnsureVisible(_In_ Line line)
{
  Call(static_cast<UINT>(Message::EnsureVisible), static_cast<WPARAM>(line), 0);
}

void CScintillaCtrl::SetAutomaticFold(_In_ AutomaticFold automaticFold)
{
  Call(static_cast<UINT>(Message::SetAutomaticFold), static_cast<WPARAM>(automaticFold), 0);
}

AutomaticFold CScintillaCtrl::GetAutomaticFold()
{
  return static_cast<AutomaticFold>(Call(static_cast<UINT>(Message::GetAutomaticFold), 0, 0));
}

void CScintillaCtrl::SetFoldFlags(_In_ FoldFlag flags)
{
  Call(static_cast<UINT>(Message::SetFoldFlags), static_cast<WPARAM>(flags), 0);
}

void CScintillaCtrl::EnsureVisibleEnforcePolicy(_In_ Line line)
{
  Call(static_cast<UINT>(Message::EnsureVisibleEnforcePolicy), static_cast<WPARAM>(line), 0);
}

void CScintillaCtrl::SetTabIndents(_In_ BOOL tabIndents)
{
  Call(static_cast<UINT>(Message::SetTabIndents), static_cast<WPARAM>(tabIndents), 0);
}

BOOL CScintillaCtrl::GetTabIndents()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetTabIndents), 0, 0));
}

void CScintillaCtrl::SetBackSpaceUnIndents(_In_ BOOL bsUnIndents)
{
  Call(static_cast<UINT>(Message::SetBackSpaceUnIndents), static_cast<WPARAM>(bsUnIndents), 0);
}

BOOL CScintillaCtrl::GetBackSpaceUnIndents()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetBackSpaceUnIndents), 0, 0));
}

void CScintillaCtrl::SetMouseDwellTime(_In_ int periodMilliseconds)
{
  Call(static_cast<UINT>(Message::SetMouseDwellTime), static_cast<WPARAM>(periodMilliseconds), 0);
}

int CScintillaCtrl::GetMouseDwellTime()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMouseDwellTime), 0, 0));
}

Position CScintillaCtrl::WordStartPosition(_In_ Position pos, _In_ BOOL onlyWordCharacters)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::WordStartPosition), static_cast<WPARAM>(pos), static_cast<LPARAM>(onlyWordCharacters)));
}

Position CScintillaCtrl::WordEndPosition(_In_ Position pos, _In_ BOOL onlyWordCharacters)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::WordEndPosition), static_cast<WPARAM>(pos), static_cast<LPARAM>(onlyWordCharacters)));
}

BOOL CScintillaCtrl::IsRangeWord(_In_ Position start, _In_ Position end)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::IsRangeWord), static_cast<WPARAM>(start), static_cast<LPARAM>(end)));
}

void CScintillaCtrl::SetIdleStyling(_In_ IdleStyling idleStyling)
{
  Call(static_cast<UINT>(Message::SetIdleStyling), static_cast<WPARAM>(idleStyling), 0);
}

IdleStyling CScintillaCtrl::GetIdleStyling()
{
  return static_cast<IdleStyling>(Call(static_cast<UINT>(Message::GetIdleStyling), 0, 0));
}

void CScintillaCtrl::SetWrapMode(_In_ Wrap wrapMode)
{
  Call(static_cast<UINT>(Message::SetWrapMode), static_cast<WPARAM>(wrapMode), 0);
}

Wrap CScintillaCtrl::GetWrapMode()
{
  return static_cast<Wrap>(Call(static_cast<UINT>(Message::GetWrapMode), 0, 0));
}

void CScintillaCtrl::SetWrapVisualFlags(_In_ WrapVisualFlag wrapVisualFlags)
{
  Call(static_cast<UINT>(Message::SetWrapVisualFlags), static_cast<WPARAM>(wrapVisualFlags), 0);
}

WrapVisualFlag CScintillaCtrl::GetWrapVisualFlags()
{
  return static_cast<WrapVisualFlag>(Call(static_cast<UINT>(Message::GetWrapVisualFlags), 0, 0));
}

void CScintillaCtrl::SetWrapVisualFlagsLocation(_In_ WrapVisualLocation wrapVisualFlagsLocation)
{
  Call(static_cast<UINT>(Message::SetWrapVisualFlagsLocation), static_cast<WPARAM>(wrapVisualFlagsLocation), 0);
}

WrapVisualLocation CScintillaCtrl::GetWrapVisualFlagsLocation()
{
  return static_cast<WrapVisualLocation>(Call(static_cast<UINT>(Message::GetWrapVisualFlagsLocation), 0, 0));
}

void CScintillaCtrl::SetWrapStartIndent(_In_ int indent)
{
  Call(static_cast<UINT>(Message::SetWrapStartIndent), static_cast<WPARAM>(indent), 0);
}

int CScintillaCtrl::GetWrapStartIndent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetWrapStartIndent), 0, 0));
}

void CScintillaCtrl::SetWrapIndentMode(_In_ WrapIndentMode wrapIndentMode)
{
  Call(static_cast<UINT>(Message::SetWrapIndentMode), static_cast<WPARAM>(wrapIndentMode), 0);
}

WrapIndentMode CScintillaCtrl::GetWrapIndentMode()
{
  return static_cast<WrapIndentMode>(Call(static_cast<UINT>(Message::GetWrapIndentMode), 0, 0));
}

void CScintillaCtrl::SetLayoutCache(_In_ LineCache cacheMode)
{
  Call(static_cast<UINT>(Message::SetLayoutCache), static_cast<WPARAM>(cacheMode), 0);
}

LineCache CScintillaCtrl::GetLayoutCache()
{
  return static_cast<LineCache>(Call(static_cast<UINT>(Message::GetLayoutCache), 0, 0));
}

void CScintillaCtrl::SetScrollWidth(_In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::SetScrollWidth), static_cast<WPARAM>(pixelWidth), 0);
}

int CScintillaCtrl::GetScrollWidth()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetScrollWidth), 0, 0));
}

void CScintillaCtrl::SetScrollWidthTracking(_In_ BOOL tracking)
{
  Call(static_cast<UINT>(Message::SetScrollWidthTracking), static_cast<WPARAM>(tracking), 0);
}

BOOL CScintillaCtrl::GetScrollWidthTracking()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetScrollWidthTracking), 0, 0));
}

int CScintillaCtrl::TextWidth(_In_ int style, _In_z_ const char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::TextWidth), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::SetEndAtLastLine(_In_ BOOL endAtLastLine)
{
  Call(static_cast<UINT>(Message::SetEndAtLastLine), static_cast<WPARAM>(endAtLastLine), 0);
}

BOOL CScintillaCtrl::GetEndAtLastLine()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetEndAtLastLine), 0, 0));
}

int CScintillaCtrl::TextHeight(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::TextHeight), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::SetVScrollBar(_In_ BOOL visible)
{
  Call(static_cast<UINT>(Message::SetVScrollBar), static_cast<WPARAM>(visible), 0);
}

BOOL CScintillaCtrl::GetVScrollBar()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetVScrollBar), 0, 0));
}

void CScintillaCtrl::AppendText(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  Call(static_cast<UINT>(Message::AppendText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

PhasesDraw CScintillaCtrl::GetPhasesDraw()
{
  return static_cast<PhasesDraw>(Call(static_cast<UINT>(Message::GetPhasesDraw), 0, 0));
}

void CScintillaCtrl::SetPhasesDraw(_In_ PhasesDraw phases)
{
  Call(static_cast<UINT>(Message::SetPhasesDraw), static_cast<WPARAM>(phases), 0);
}

void CScintillaCtrl::SetFontQuality(_In_ FontQuality fontQuality)
{
  Call(static_cast<UINT>(Message::SetFontQuality), static_cast<WPARAM>(fontQuality), 0);
}

FontQuality CScintillaCtrl::GetFontQuality()
{
  return static_cast<FontQuality>(Call(static_cast<UINT>(Message::GetFontQuality), 0, 0));
}

void CScintillaCtrl::SetFirstVisibleLine(_In_ Line displayLine)
{
  Call(static_cast<UINT>(Message::SetFirstVisibleLine), static_cast<WPARAM>(displayLine), 0);
}

void CScintillaCtrl::SetMultiPaste(_In_ MultiPaste multiPaste)
{
  Call(static_cast<UINT>(Message::SetMultiPaste), static_cast<WPARAM>(multiPaste), 0);
}

MultiPaste CScintillaCtrl::GetMultiPaste()
{
  return static_cast<MultiPaste>(Call(static_cast<UINT>(Message::GetMultiPaste), 0, 0));
}

int CScintillaCtrl::GetTag(_In_ int tagNumber, _Inout_opt_z_ char* tagValue)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetTag), static_cast<WPARAM>(tagNumber), reinterpret_cast<LPARAM>(tagValue)));
}

void CScintillaCtrl::LinesJoin()
{
  Call(static_cast<UINT>(Message::LinesJoin), 0, 0);
}

void CScintillaCtrl::LinesSplit(_In_ int pixelWidth)
{
  Call(static_cast<UINT>(Message::LinesSplit), static_cast<WPARAM>(pixelWidth), 0);
}

void CScintillaCtrl::SetFoldMarginColour(_In_ BOOL useSetting, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetFoldMarginColour), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(back));
}

void CScintillaCtrl::SetFoldMarginHiColour(_In_ BOOL useSetting, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetFoldMarginHiColour), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(fore));
}

void CScintillaCtrl::SetAccessibility(_In_ Accessibility accessibility)
{
  Call(static_cast<UINT>(Message::SetAccessibility), static_cast<WPARAM>(accessibility), 0);
}

Accessibility CScintillaCtrl::GetAccessibility()
{
  return static_cast<Accessibility>(Call(static_cast<UINT>(Message::GetAccessibility), 0, 0));
}

void CScintillaCtrl::LineDown()
{
  Call(static_cast<UINT>(Message::LineDown), 0, 0);
}

void CScintillaCtrl::LineDownExtend()
{
  Call(static_cast<UINT>(Message::LineDownExtend), 0, 0);
}

void CScintillaCtrl::LineUp()
{
  Call(static_cast<UINT>(Message::LineUp), 0, 0);
}

void CScintillaCtrl::LineUpExtend()
{
  Call(static_cast<UINT>(Message::LineUpExtend), 0, 0);
}

void CScintillaCtrl::CharLeft()
{
  Call(static_cast<UINT>(Message::CharLeft), 0, 0);
}

void CScintillaCtrl::CharLeftExtend()
{
  Call(static_cast<UINT>(Message::CharLeftExtend), 0, 0);
}

void CScintillaCtrl::CharRight()
{
  Call(static_cast<UINT>(Message::CharRight), 0, 0);
}

void CScintillaCtrl::CharRightExtend()
{
  Call(static_cast<UINT>(Message::CharRightExtend), 0, 0);
}

void CScintillaCtrl::WordLeft()
{
  Call(static_cast<UINT>(Message::WordLeft), 0, 0);
}

void CScintillaCtrl::WordLeftExtend()
{
  Call(static_cast<UINT>(Message::WordLeftExtend), 0, 0);
}

void CScintillaCtrl::WordRight()
{
  Call(static_cast<UINT>(Message::WordRight), 0, 0);
}

void CScintillaCtrl::WordRightExtend()
{
  Call(static_cast<UINT>(Message::WordRightExtend), 0, 0);
}

void CScintillaCtrl::Home()
{
  Call(static_cast<UINT>(Message::Home), 0, 0);
}

void CScintillaCtrl::HomeExtend()
{
  Call(static_cast<UINT>(Message::HomeExtend), 0, 0);
}

void CScintillaCtrl::LineEnd()
{
  Call(static_cast<UINT>(Message::LineEnd), 0, 0);
}

void CScintillaCtrl::LineEndExtend()
{
  Call(static_cast<UINT>(Message::LineEndExtend), 0, 0);
}

void CScintillaCtrl::DocumentStart()
{
  Call(static_cast<UINT>(Message::DocumentStart), 0, 0);
}

void CScintillaCtrl::DocumentStartExtend()
{
  Call(static_cast<UINT>(Message::DocumentStartExtend), 0, 0);
}

void CScintillaCtrl::DocumentEnd()
{
  Call(static_cast<UINT>(Message::DocumentEnd), 0, 0);
}

void CScintillaCtrl::DocumentEndExtend()
{
  Call(static_cast<UINT>(Message::DocumentEndExtend), 0, 0);
}

void CScintillaCtrl::PageUp()
{
  Call(static_cast<UINT>(Message::PageUp), 0, 0);
}

void CScintillaCtrl::PageUpExtend()
{
  Call(static_cast<UINT>(Message::PageUpExtend), 0, 0);
}

void CScintillaCtrl::PageDown()
{
  Call(static_cast<UINT>(Message::PageDown), 0, 0);
}

void CScintillaCtrl::PageDownExtend()
{
  Call(static_cast<UINT>(Message::PageDownExtend), 0, 0);
}

void CScintillaCtrl::EditToggleOvertype()
{
  Call(static_cast<UINT>(Message::EditToggleOvertype), 0, 0);
}

void CScintillaCtrl::Cancel()
{
  Call(static_cast<UINT>(Message::Cancel), 0, 0);
}

void CScintillaCtrl::DeleteBack()
{
  Call(static_cast<UINT>(Message::DeleteBack), 0, 0);
}

void CScintillaCtrl::Tab()
{
  Call(static_cast<UINT>(Message::Tab), 0, 0);
}

void CScintillaCtrl::LineIndent()
{
  Call(static_cast<UINT>(Scintilla::Message::LineIndent), 0, 0);
}

void CScintillaCtrl::BackTab()
{
  Call(static_cast<UINT>(Message::BackTab), 0, 0);
}

void CScintillaCtrl::LineDedent()
{
  Call(static_cast<UINT>(Scintilla::Message::LineDedent), 0, 0);
}

void CScintillaCtrl::NewLine()
{
  Call(static_cast<UINT>(Message::NewLine), 0, 0);
}

void CScintillaCtrl::FormFeed()
{
  Call(static_cast<UINT>(Message::FormFeed), 0, 0);
}

void CScintillaCtrl::VCHome()
{
  Call(static_cast<UINT>(Message::VCHome), 0, 0);
}

void CScintillaCtrl::VCHomeExtend()
{
  Call(static_cast<UINT>(Message::VCHomeExtend), 0, 0);
}

void CScintillaCtrl::ZoomIn()
{
  Call(static_cast<UINT>(Message::ZoomIn), 0, 0);
}

void CScintillaCtrl::ZoomOut()
{
  Call(static_cast<UINT>(Message::ZoomOut), 0, 0);
}

void CScintillaCtrl::DelWordLeft()
{
  Call(static_cast<UINT>(Message::DelWordLeft), 0, 0);
}

void CScintillaCtrl::DelWordRight()
{
  Call(static_cast<UINT>(Message::DelWordRight), 0, 0);
}

void CScintillaCtrl::DelWordRightEnd()
{
  Call(static_cast<UINT>(Message::DelWordRightEnd), 0, 0);
}

void CScintillaCtrl::LineCut()
{
  Call(static_cast<UINT>(Message::LineCut), 0, 0);
}

void CScintillaCtrl::LineDelete()
{
  Call(static_cast<UINT>(Message::LineDelete), 0, 0);
}

void CScintillaCtrl::LineTranspose()
{
  Call(static_cast<UINT>(Message::LineTranspose), 0, 0);
}

void CScintillaCtrl::LineReverse()
{
  Call(static_cast<UINT>(Message::LineReverse), 0, 0);
}

void CScintillaCtrl::LineDuplicate()
{
  Call(static_cast<UINT>(Message::LineDuplicate), 0, 0);
}

void CScintillaCtrl::LowerCase()
{
  Call(static_cast<UINT>(Message::LowerCase), 0, 0);
}

void CScintillaCtrl::UpperCase()
{
  Call(static_cast<UINT>(Message::UpperCase), 0, 0);
}

void CScintillaCtrl::LineScrollDown()
{
  Call(static_cast<UINT>(Message::LineScrollDown), 0, 0);
}

void CScintillaCtrl::LineScrollUp()
{
  Call(static_cast<UINT>(Message::LineScrollUp), 0, 0);
}

void CScintillaCtrl::DeleteBackNotLine()
{
  Call(static_cast<UINT>(Message::DeleteBackNotLine), 0, 0);
}

void CScintillaCtrl::HomeDisplay()
{
  Call(static_cast<UINT>(Message::HomeDisplay), 0, 0);
}

void CScintillaCtrl::HomeDisplayExtend()
{
  Call(static_cast<UINT>(Message::HomeDisplayExtend), 0, 0);
}

void CScintillaCtrl::LineEndDisplay()
{
  Call(static_cast<UINT>(Message::LineEndDisplay), 0, 0);
}

void CScintillaCtrl::LineEndDisplayExtend()
{
  Call(static_cast<UINT>(Message::LineEndDisplayExtend), 0, 0);
}

void CScintillaCtrl::HomeWrap()
{
  Call(static_cast<UINT>(Message::HomeWrap), 0, 0);
}

void CScintillaCtrl::HomeWrapExtend()
{
  Call(static_cast<UINT>(Message::HomeWrapExtend), 0, 0);
}

void CScintillaCtrl::LineEndWrap()
{
  Call(static_cast<UINT>(Message::LineEndWrap), 0, 0);
}

void CScintillaCtrl::LineEndWrapExtend()
{
  Call(static_cast<UINT>(Message::LineEndWrapExtend), 0, 0);
}

void CScintillaCtrl::VCHomeWrap()
{
  Call(static_cast<UINT>(Message::VCHomeWrap), 0, 0);
}

void CScintillaCtrl::VCHomeWrapExtend()
{
  Call(static_cast<UINT>(Message::VCHomeWrapExtend), 0, 0);
}

void CScintillaCtrl::LineCopy()
{
  Call(static_cast<UINT>(Message::LineCopy), 0, 0);
}

void CScintillaCtrl::MoveCaretInsideView()
{
  Call(static_cast<UINT>(Message::MoveCaretInsideView), 0, 0);
}

Position CScintillaCtrl::LineLength(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::LineLength), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::BraceHighlight(_In_ Position posA, _In_ Position posB)
{
  Call(static_cast<UINT>(Message::BraceHighlight), static_cast<WPARAM>(posA), static_cast<LPARAM>(posB));
}

void CScintillaCtrl::BraceHighlightIndicator(_In_ BOOL useSetting, _In_ int indicator)
{
  Call(static_cast<UINT>(Message::BraceHighlightIndicator), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(indicator));
}

void CScintillaCtrl::BraceBadLight(_In_ Position pos)
{
  Call(static_cast<UINT>(Message::BraceBadLight), static_cast<WPARAM>(pos), 0);
}

void CScintillaCtrl::BraceBadLightIndicator(_In_ BOOL useSetting, _In_ int indicator)
{
  Call(static_cast<UINT>(Message::BraceBadLightIndicator), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(indicator));
}

Position CScintillaCtrl::BraceMatch(_In_ Position pos, _In_ int maxReStyle)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::BraceMatch), static_cast<WPARAM>(pos), maxReStyle));
}

Position CScintillaCtrl::BraceMatchNext(_In_ Position pos, _In_ Position startPos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::BraceMatchNext), static_cast<WPARAM>(pos), static_cast<LPARAM>(startPos)));
}

BOOL CScintillaCtrl::GetViewEOL()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetViewEOL), 0, 0));
}

void CScintillaCtrl::SetViewEOL(_In_ BOOL visible)
{
  Call(static_cast<UINT>(Message::SetViewEOL), static_cast<WPARAM>(visible), 0);
}

IDocumentEditable* CScintillaCtrl::GetDocPointer()
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<IDocumentEditable*>(Call(static_cast<UINT>(Message::GetDocPointer), 0, 0));
}

void CScintillaCtrl::SetDocPointer(_In_opt_ IDocumentEditable* doc)
{
  Call(static_cast<UINT>(Message::SetDocPointer), 0, reinterpret_cast<LPARAM>(doc));
}

void CScintillaCtrl::SetModEventMask(_In_ ModificationFlags eventMask)
{
  Call(static_cast<UINT>(Message::SetModEventMask), static_cast<WPARAM>(eventMask), 0);
}

Position CScintillaCtrl::GetEdgeColumn()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetEdgeColumn), 0, 0));
}

void CScintillaCtrl::SetEdgeColumn(_In_ Position column)
{
  Call(static_cast<UINT>(Message::SetEdgeColumn), static_cast<WPARAM>(column), 0);
}

EdgeVisualStyle CScintillaCtrl::GetEdgeMode()
{
  return static_cast<EdgeVisualStyle>(Call(static_cast<UINT>(Message::GetEdgeMode), 0, 0));
}

void CScintillaCtrl::SetEdgeMode(_In_ EdgeVisualStyle edgeMode)
{
  Call(static_cast<UINT>(Message::SetEdgeMode), static_cast<WPARAM>(edgeMode), 0);
}

COLORREF CScintillaCtrl::GetEdgeColour()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetEdgeColour), 0, 0));
}

void CScintillaCtrl::SetEdgeColour(_In_ COLORREF edgeColour)
{
  Call(static_cast<UINT>(Message::SetEdgeColour), static_cast<WPARAM>(edgeColour), 0);
}

void CScintillaCtrl::MultiEdgeAddLine(_In_ Position column, _In_ COLORREF edgeColour)
{
  Call(static_cast<UINT>(Message::MultiEdgeAddLine), static_cast<WPARAM>(column), static_cast<LPARAM>(edgeColour));
}

void CScintillaCtrl::MultiEdgeClearAll()
{
  Call(static_cast<UINT>(Message::MultiEdgeClearAll), 0, 0);
}

Position CScintillaCtrl::GetMultiEdgeColumn(_In_ int which)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetMultiEdgeColumn), static_cast<WPARAM>(which), 0));
}

void CScintillaCtrl::SearchAnchor()
{
  Call(static_cast<UINT>(Message::SearchAnchor), 0, 0);
}

Position CScintillaCtrl::SearchNext(_In_ FindOption searchFlags, _In_z_ const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::SearchNext), static_cast<WPARAM>(searchFlags), reinterpret_cast<LPARAM>(text)));
}

Position CScintillaCtrl::SearchPrev(_In_ FindOption searchFlags, _In_z_ const char* text)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::SearchPrev), static_cast<WPARAM>(searchFlags), reinterpret_cast<LPARAM>(text)));
}

Line CScintillaCtrl::LinesOnScreen()
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::LinesOnScreen), 0, 0));
}

void CScintillaCtrl::UsePopUp(_In_ PopUp popUpMode)
{
  Call(static_cast<UINT>(Message::UsePopUp), static_cast<WPARAM>(popUpMode), 0);
}

BOOL CScintillaCtrl::SelectionIsRectangle()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::SelectionIsRectangle), 0, 0));
}

void CScintillaCtrl::SetZoom(_In_ int zoomInPoints)
{
  Call(static_cast<UINT>(Message::SetZoom), static_cast<WPARAM>(zoomInPoints), 0);
}

int CScintillaCtrl::GetZoom()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetZoom), 0, 0));
}

IDocumentEditable* CScintillaCtrl::CreateDocument(_In_ Position bytes, _In_ DocumentOption documentOptions)
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<IDocumentEditable*>(Call(static_cast<UINT>(Message::CreateDocument), static_cast<WPARAM>(bytes), static_cast<LPARAM>(documentOptions)));
}

void CScintillaCtrl::AddRefDocument(_In_ IDocumentEditable* doc)
{
  Call(static_cast<UINT>(Message::AddRefDocument), 0, reinterpret_cast<LPARAM>(doc));
}

void CScintillaCtrl::ReleaseDocument(_In_ IDocumentEditable* doc)
{
  Call(static_cast<UINT>(Message::ReleaseDocument), 0, reinterpret_cast<LPARAM>(doc));
}

DocumentOption CScintillaCtrl::GetDocumentOptions()
{
  return static_cast<DocumentOption>(Call(static_cast<UINT>(Message::GetDocumentOptions), 0, 0));
}

ModificationFlags CScintillaCtrl::GetModEventMask()
{
  return static_cast<ModificationFlags>(Call(static_cast<UINT>(Message::GetModEventMask), 0, 0));
}

void CScintillaCtrl::SetCommandEvents(_In_ BOOL commandEvents)
{
  Call(static_cast<UINT>(Message::SetCommandEvents), static_cast<WPARAM>(commandEvents), 0);
}

BOOL CScintillaCtrl::GetCommandEvents()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetCommandEvents), 0, 0));
}

void CScintillaCtrl::SCISetFocus(_In_ BOOL focus)
{
  Call(static_cast<UINT>(Message::SetFocus), static_cast<WPARAM>(focus), 0);
}

BOOL CScintillaCtrl::GetFocus()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetFocus), 0, 0));
}

void CScintillaCtrl::SetStatus(_In_ Status status)
{
  Call(static_cast<UINT>(Message::SetStatus), static_cast<WPARAM>(status), 0);
}

Status CScintillaCtrl::GetStatus()
{
  return static_cast<Status>(Call(static_cast<UINT>(Message::GetStatus), 0, 0));
}

void CScintillaCtrl::SetMouseDownCaptures(_In_ BOOL captures)
{
  Call(static_cast<UINT>(Message::SetMouseDownCaptures), static_cast<WPARAM>(captures), 0);
}

BOOL CScintillaCtrl::GetMouseDownCaptures()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMouseDownCaptures), 0, 0));
}

void CScintillaCtrl::SetMouseWheelCaptures(_In_ BOOL captures)
{
  Call(static_cast<UINT>(Message::SetMouseWheelCaptures), static_cast<WPARAM>(captures), 0);
}

BOOL CScintillaCtrl::GetMouseWheelCaptures()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMouseWheelCaptures), 0, 0));
}

void CScintillaCtrl::SetCursor(_In_ CursorShape cursorType)
{
  Call(static_cast<UINT>(Message::SetCursor), static_cast<WPARAM>(cursorType), 0);
}

CursorShape CScintillaCtrl::GetCursor()
{
  return static_cast<CursorShape>(Call(static_cast<UINT>(Message::GetCursor), 0, 0));
}

void CScintillaCtrl::SetControlCharSymbol(_In_ int symbol)
{
  Call(static_cast<UINT>(Message::SetControlCharSymbol), static_cast<WPARAM>(symbol), 0);
}

int CScintillaCtrl::GetControlCharSymbol()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetControlCharSymbol), 0, 0));
}

void CScintillaCtrl::WordPartLeft()
{
  Call(static_cast<UINT>(Message::WordPartLeft), 0, 0);
}

void CScintillaCtrl::WordPartLeftExtend()
{
  Call(static_cast<UINT>(Message::WordPartLeftExtend), 0, 0);
}

void CScintillaCtrl::WordPartRight()
{
  Call(static_cast<UINT>(Message::WordPartRight), 0, 0);
}

void CScintillaCtrl::WordPartRightExtend()
{
  Call(static_cast<UINT>(Message::WordPartRightExtend), 0, 0);
}

void CScintillaCtrl::SetVisiblePolicy(_In_ VisiblePolicy visiblePolicy, _In_ int visibleSlop)
{
  Call(static_cast<UINT>(Message::SetVisiblePolicy), static_cast<WPARAM>(visiblePolicy), static_cast<LPARAM>(visibleSlop));
}

void CScintillaCtrl::DelLineLeft()
{
  Call(static_cast<UINT>(Message::DelLineLeft), 0, 0);
}

void CScintillaCtrl::DelLineRight()
{
  Call(static_cast<UINT>(Message::DelLineRight), 0, 0);
}

void CScintillaCtrl::SetXOffset(_In_ int xOffset)
{
  Call(static_cast<UINT>(Message::SetXOffset), static_cast<WPARAM>(xOffset), 0);
}

int CScintillaCtrl::GetXOffset()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetXOffset), 0, 0));
}

void CScintillaCtrl::ChooseCaretX()
{
  Call(static_cast<UINT>(Message::ChooseCaretX), 0, 0);
}

void CScintillaCtrl::GrabFocus()
{
  Call(static_cast<UINT>(Message::GrabFocus), 0, 0);
}

void CScintillaCtrl::SetXCaretPolicy(_In_ CaretPolicy caretPolicy, _In_ int caretSlop)
{
  Call(static_cast<UINT>(Message::SetXCaretPolicy), static_cast<WPARAM>(caretPolicy), static_cast<LPARAM>(caretSlop));
}

void CScintillaCtrl::SetYCaretPolicy(_In_ CaretPolicy caretPolicy, _In_ int caretSlop)
{
  Call(static_cast<UINT>(Message::SetYCaretPolicy), static_cast<WPARAM>(caretPolicy), static_cast<LPARAM>(caretSlop));
}

void CScintillaCtrl::SetPrintWrapMode(_In_ Wrap wrapMode)
{
  Call(static_cast<UINT>(Message::SetPrintWrapMode), static_cast<WPARAM>(wrapMode), 0);
}

Wrap CScintillaCtrl::GetPrintWrapMode()
{
  return static_cast<Wrap>(Call(static_cast<UINT>(Message::GetPrintWrapMode), 0, 0));
}

void CScintillaCtrl::SetHotspotActiveFore(_In_ BOOL useSetting, _In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetHotspotActiveFore), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(fore));
}

COLORREF CScintillaCtrl::GetHotspotActiveFore()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetHotspotActiveFore), 0, 0));
}

void CScintillaCtrl::SetHotspotActiveBack(_In_ BOOL useSetting, _In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetHotspotActiveBack), static_cast<WPARAM>(useSetting), static_cast<LPARAM>(back));
}

COLORREF CScintillaCtrl::GetHotspotActiveBack()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetHotspotActiveBack), 0, 0));
}

void CScintillaCtrl::SetHotspotActiveUnderline(_In_ BOOL underline)
{
  Call(static_cast<UINT>(Message::SetHotspotActiveUnderline), static_cast<WPARAM>(underline), 0);
}

BOOL CScintillaCtrl::GetHotspotActiveUnderline()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetHotspotActiveUnderline), 0, 0));
}

void CScintillaCtrl::SetHotspotSingleLine(_In_ BOOL singleLine)
{
  Call(static_cast<UINT>(Message::SetHotspotSingleLine), static_cast<WPARAM>(singleLine), 0);
}

BOOL CScintillaCtrl::GetHotspotSingleLine()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetHotspotSingleLine), 0, 0));
}

void CScintillaCtrl::ParaDown()
{
  Call(static_cast<UINT>(Message::ParaDown), 0, 0);
}

void CScintillaCtrl::ParaDownExtend()
{
  Call(static_cast<UINT>(Message::ParaDownExtend), 0, 0);
}

void CScintillaCtrl::ParaUp()
{
  Call(static_cast<UINT>(Message::ParaUp), 0, 0);
}

void CScintillaCtrl::ParaUpExtend()
{
  Call(static_cast<UINT>(Message::ParaUpExtend), 0, 0);
}

Position CScintillaCtrl::PositionBefore(_In_ Position pos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionBefore), static_cast<WPARAM>(pos), 0));
}

Position CScintillaCtrl::PositionAfter(_In_ Position pos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionAfter), static_cast<WPARAM>(pos), 0));
}

Position CScintillaCtrl::PositionRelative(_In_ Position pos, _In_ Position relative)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionRelative), static_cast<WPARAM>(pos), static_cast<LPARAM>(relative)));
}

Position CScintillaCtrl::PositionRelativeCodeUnits(_In_ Position pos, _In_ Position relative)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::PositionRelativeCodeUnits), static_cast<WPARAM>(pos), static_cast<LPARAM>(relative)));
}

void CScintillaCtrl::CopyRange(_In_ Position start, _In_ Position end)
{
  Call(static_cast<UINT>(Message::CopyRange), static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

void CScintillaCtrl::CopyText(_In_ Position length, _In_reads_bytes_(length) const char* text)
{
  Call(static_cast<UINT>(Message::CopyText), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::SetSelectionMode(_In_ SelectionMode selectionMode)
{
  Call(static_cast<UINT>(Message::SetSelectionMode), static_cast<WPARAM>(selectionMode), 0);
}

void CScintillaCtrl::ChangeSelectionMode(_In_ SelectionMode selectionMode)
{
  Call(static_cast<UINT>(Message::ChangeSelectionMode), static_cast<WPARAM>(selectionMode), 0);
}

SelectionMode CScintillaCtrl::GetSelectionMode()
{
  return static_cast<SelectionMode>(Call(static_cast<UINT>(Message::GetSelectionMode), 0, 0));
}

void CScintillaCtrl::SetMoveExtendsSelection(_In_ BOOL moveExtendsSelection)
{
  Call(static_cast<UINT>(Message::SetMoveExtendsSelection), static_cast<WPARAM>(moveExtendsSelection), 0);
}

BOOL CScintillaCtrl::GetMoveExtendsSelection()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMoveExtendsSelection), 0, 0));
}

Position CScintillaCtrl::GetLineSelStartPosition(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLineSelStartPosition), static_cast<WPARAM>(line), 0));
}

Position CScintillaCtrl::GetLineSelEndPosition(_In_ Line line)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetLineSelEndPosition), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::LineDownRectExtend()
{
  Call(static_cast<UINT>(Message::LineDownRectExtend), 0, 0);
}

void CScintillaCtrl::LineUpRectExtend()
{
  Call(static_cast<UINT>(Message::LineUpRectExtend), 0, 0);
}

void CScintillaCtrl::CharLeftRectExtend()
{
  Call(static_cast<UINT>(Message::CharLeftRectExtend), 0, 0);
}

void CScintillaCtrl::CharRightRectExtend()
{
  Call(static_cast<UINT>(Message::CharRightRectExtend), 0, 0);
}

void CScintillaCtrl::HomeRectExtend()
{
  Call(static_cast<UINT>(Message::HomeRectExtend), 0, 0);
}

void CScintillaCtrl::VCHomeRectExtend()
{
  Call(static_cast<UINT>(Message::VCHomeRectExtend), 0, 0);
}

void CScintillaCtrl::LineEndRectExtend()
{
  Call(static_cast<UINT>(Message::LineEndRectExtend), 0, 0);
}

void CScintillaCtrl::PageUpRectExtend()
{
  Call(static_cast<UINT>(Message::PageUpRectExtend), 0, 0);
}

void CScintillaCtrl::PageDownRectExtend()
{
  Call(static_cast<UINT>(Message::PageDownRectExtend), 0, 0);
}

void CScintillaCtrl::StutteredPageUp()
{
  Call(static_cast<UINT>(Message::StutteredPageUp), 0, 0);
}

void CScintillaCtrl::StutteredPageUpExtend()
{
  Call(static_cast<UINT>(Message::StutteredPageUpExtend), 0, 0);
}

void CScintillaCtrl::StutteredPageDown()
{
  Call(static_cast<UINT>(Message::StutteredPageDown), 0, 0);
}

void CScintillaCtrl::StutteredPageDownExtend()
{
  Call(static_cast<UINT>(Message::StutteredPageDownExtend), 0, 0);
}

void CScintillaCtrl::WordLeftEnd()
{
  Call(static_cast<UINT>(Message::WordLeftEnd), 0, 0);
}

void CScintillaCtrl::WordLeftEndExtend()
{
  Call(static_cast<UINT>(Message::WordLeftEndExtend), 0, 0);
}

void CScintillaCtrl::WordRightEnd()
{
  Call(static_cast<UINT>(Message::WordRightEnd), 0, 0);
}

void CScintillaCtrl::WordRightEndExtend()
{
  Call(static_cast<UINT>(Message::WordRightEndExtend), 0, 0);
}

void CScintillaCtrl::SetWhitespaceChars(_In_z_ const char* characters)
{
  Call(static_cast<UINT>(Message::SetWhitespaceChars), 0, reinterpret_cast<LPARAM>(characters));
}

int CScintillaCtrl::GetWhitespaceChars(_Inout_opt_z_ char* characters)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetWhitespaceChars), 0, reinterpret_cast<LPARAM>(characters)));
}

void CScintillaCtrl::SetPunctuationChars(_In_z_ const char* characters)
{
  Call(static_cast<UINT>(Message::SetPunctuationChars), 0, reinterpret_cast<LPARAM>(characters));
}

int CScintillaCtrl::GetPunctuationChars(_Inout_opt_z_ char* characters)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPunctuationChars), 0, reinterpret_cast<LPARAM>(characters)));
}

void CScintillaCtrl::SetCharsDefault()
{
  Call(static_cast<UINT>(Message::SetCharsDefault), 0, 0);
}

int CScintillaCtrl::AutoCGetCurrent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetCurrent), 0, 0));
}

int CScintillaCtrl::AutoCGetCurrentText(_Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AutoCGetCurrentText), 0, reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::AutoCSetCaseInsensitiveBehaviour(_In_ CaseInsensitiveBehaviour behaviour)
{
  Call(static_cast<UINT>(Message::AutoCSetCaseInsensitiveBehaviour), static_cast<WPARAM>(behaviour), 0);
}

CaseInsensitiveBehaviour CScintillaCtrl::AutoCGetCaseInsensitiveBehaviour()
{
  return static_cast<CaseInsensitiveBehaviour>(Call(static_cast<UINT>(Message::AutoCGetCaseInsensitiveBehaviour), 0, 0));
}

void CScintillaCtrl::AutoCSetMulti(_In_ MultiAutoComplete multi)
{
  Call(static_cast<UINT>(Message::AutoCSetMulti), static_cast<WPARAM>(multi), 0);
}

MultiAutoComplete CScintillaCtrl::AutoCGetMulti()
{
  return static_cast<MultiAutoComplete>(Call(static_cast<UINT>(Message::AutoCGetMulti), 0, 0));
}

void CScintillaCtrl::AutoCSetOrder(_In_ Ordering order)
{
  Call(static_cast<UINT>(Message::AutoCSetOrder), static_cast<WPARAM>(order), 0);
}

Ordering CScintillaCtrl::AutoCGetOrder()
{
  return static_cast<Ordering>(Call(static_cast<UINT>(Message::AutoCGetOrder), 0, 0));
}

void CScintillaCtrl::Allocate(_In_ Position bytes)
{
  Call(static_cast<UINT>(Message::Allocate), static_cast<WPARAM>(bytes), 0);
}

Position CScintillaCtrl::TargetAsUTF8(_Inout_ char* s)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::TargetAsUTF8), 0, reinterpret_cast<LPARAM>(s)));
}

void CScintillaCtrl::SetLengthForEncode(_In_ Position bytes)
{
  Call(static_cast<UINT>(Message::SetLengthForEncode), static_cast<WPARAM>(bytes), 0);
}

Position CScintillaCtrl::EncodedFromUTF8(_In_ const char* utf8, _Inout_ char* encoded)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::EncodedFromUTF8), reinterpret_cast<WPARAM>(utf8), reinterpret_cast<LPARAM>(encoded)));
}

Position CScintillaCtrl::FindColumn(_In_ Line line, _In_ Position column)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::FindColumn), static_cast<WPARAM>(line), static_cast<LPARAM>(column)));
}

CaretSticky CScintillaCtrl::GetCaretSticky()
{
  return static_cast<CaretSticky>(Call(static_cast<UINT>(Message::GetCaretSticky), 0, 0));
}

void CScintillaCtrl::SetCaretSticky(_In_ CaretSticky useCaretStickyBehaviour)
{
  Call(static_cast<UINT>(Message::SetCaretSticky), static_cast<WPARAM>(useCaretStickyBehaviour), 0);
}

void CScintillaCtrl::ToggleCaretSticky()
{
  Call(static_cast<UINT>(Message::ToggleCaretSticky), 0, 0);
}

void CScintillaCtrl::SetPasteConvertEndings(_In_ BOOL convert)
{
  Call(static_cast<UINT>(Message::SetPasteConvertEndings), static_cast<WPARAM>(convert), 0);
}

BOOL CScintillaCtrl::GetPasteConvertEndings()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetPasteConvertEndings), 0, 0));
}

void CScintillaCtrl::ReplaceRectangular(_In_ Position length, _In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::ReplaceRectangular), static_cast<WPARAM>(length), reinterpret_cast<LPARAM>(text));
}

void CScintillaCtrl::SelectionDuplicate()
{
  Call(static_cast<UINT>(Message::SelectionDuplicate), 0, 0);
}

void CScintillaCtrl::SetCaretLineBackAlpha(_In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::SetCaretLineBackAlpha), static_cast<WPARAM>(alpha), 0);
}

Alpha CScintillaCtrl::GetCaretLineBackAlpha()
{
  return static_cast<Alpha>(Call(static_cast<UINT>(Message::GetCaretLineBackAlpha), 0, 0));
}

void CScintillaCtrl::SetCaretStyle(_In_ CaretStyle caretStyle)
{
  Call(static_cast<UINT>(Message::SetCaretStyle), static_cast<WPARAM>(caretStyle), 0);
}

CaretStyle CScintillaCtrl::GetCaretStyle()
{
  return static_cast<CaretStyle>(Call(static_cast<UINT>(Message::GetCaretStyle), 0, 0));
}

void CScintillaCtrl::SetIndicatorCurrent(_In_ int indicator)
{
  Call(static_cast<UINT>(Message::SetIndicatorCurrent), static_cast<WPARAM>(indicator), 0);
}

int CScintillaCtrl::GetIndicatorCurrent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetIndicatorCurrent), 0, 0));
}

void CScintillaCtrl::SetIndicatorValue(_In_ int value)
{
  Call(static_cast<UINT>(Message::SetIndicatorValue), static_cast<WPARAM>(value), 0);
}

int CScintillaCtrl::GetIndicatorValue()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetIndicatorValue), 0, 0));
}

void CScintillaCtrl::IndicatorFillRange(_In_ Position start, _In_ Position lengthFill)
{
  Call(static_cast<UINT>(Message::IndicatorFillRange), static_cast<WPARAM>(start), static_cast<LPARAM>(lengthFill));
}

void CScintillaCtrl::IndicatorClearRange(_In_ Position start, _In_ Position lengthClear)
{
  Call(static_cast<UINT>(Message::IndicatorClearRange), static_cast<WPARAM>(start), static_cast<LPARAM>(lengthClear));
}

int CScintillaCtrl::IndicatorAllOnFor(_In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::IndicatorAllOnFor), static_cast<WPARAM>(pos), 0));
}

int CScintillaCtrl::IndicatorValueAt(_In_ int indicator, _In_ Position pos)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::IndicatorValueAt), static_cast<WPARAM>(indicator), static_cast<LPARAM>(pos)));
}

Position CScintillaCtrl::IndicatorStart(_In_ int indicator, _In_ Position pos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::IndicatorStart), static_cast<WPARAM>(indicator), static_cast<LPARAM>(pos)));
}

Position CScintillaCtrl::IndicatorEnd(_In_ int indicator, _In_ Position pos)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::IndicatorEnd), static_cast<WPARAM>(indicator), static_cast<LPARAM>(pos)));
}

void CScintillaCtrl::SetPositionCache(_In_ int size)
{
  Call(static_cast<UINT>(Message::SetPositionCache), static_cast<WPARAM>(size), 0);
}

int CScintillaCtrl::GetPositionCache()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPositionCache), 0, 0));
}

void CScintillaCtrl::SetLayoutThreads(_In_ int threads)
{
  Call(static_cast<UINT>(Message::SetLayoutThreads), static_cast<WPARAM>(threads), 0);
}

int CScintillaCtrl::GetLayoutThreads()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetLayoutThreads), 0, 0));
}

void CScintillaCtrl::CopyAllowLine()
{
  Call(static_cast<UINT>(Message::CopyAllowLine), 0, 0);
}

void CScintillaCtrl::CutAllowLine()
{
  Call(static_cast<UINT>(Message::CutAllowLine), 0, 0);
}

void CScintillaCtrl::SetCopySeparator(_In_z_ const char* separator)
{
  Call(static_cast<UINT>(Scintilla::Message::SetCopySeparator), 0, reinterpret_cast<LPARAM>(separator));
}

int CScintillaCtrl::GetCopySeparator(_Inout_opt_z_ char* separator)
{
  return static_cast<int>(Call(static_cast<UINT>(Scintilla::Message::GetCopySeparator), 0, reinterpret_cast<LPARAM>(separator)));
}

const char* CScintillaCtrl::GetCharacterPointer()
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<const char*>(Call(static_cast<UINT>(Message::GetCharacterPointer), 0, 0));
}

void* CScintillaCtrl::GetRangePointer(_In_ Position start, _In_ Position lengthRange)
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<void*>(Call(static_cast<UINT>(Message::GetRangePointer), static_cast<WPARAM>(start), static_cast<LPARAM>(lengthRange)));
}

Position CScintillaCtrl::GetGapPosition()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetGapPosition), 0, 0));
}

void CScintillaCtrl::IndicSetAlpha(_In_ int indicator, _In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::IndicSetAlpha), static_cast<WPARAM>(indicator), static_cast<LPARAM>(alpha));
}

Alpha CScintillaCtrl::IndicGetAlpha(_In_ int indicator)
{
  return static_cast<Alpha>(Call(static_cast<UINT>(Message::IndicGetAlpha), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::IndicSetOutlineAlpha(_In_ int indicator, _In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::IndicSetOutlineAlpha), static_cast<WPARAM>(indicator), static_cast<LPARAM>(alpha));
}

Alpha CScintillaCtrl::IndicGetOutlineAlpha(_In_ int indicator)
{
  return static_cast<Alpha>(Call(static_cast<UINT>(Message::IndicGetOutlineAlpha), static_cast<WPARAM>(indicator), 0));
}

void CScintillaCtrl::SetExtraAscent(_In_ int extraAscent)
{
  Call(static_cast<UINT>(Message::SetExtraAscent), static_cast<WPARAM>(extraAscent), 0);
}

int CScintillaCtrl::GetExtraAscent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetExtraAscent), 0, 0));
}

void CScintillaCtrl::SetExtraDescent(_In_ int extraDescent)
{
  Call(static_cast<UINT>(Message::SetExtraDescent), static_cast<WPARAM>(extraDescent), 0);
}

int CScintillaCtrl::GetExtraDescent()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetExtraDescent), 0, 0));
}

int CScintillaCtrl::MarkerSymbolDefined(_In_ int markerNumber)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarkerSymbolDefined), static_cast<WPARAM>(markerNumber), 0));
}

void CScintillaCtrl::MarginSetText(_In_ Line line, _In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::MarginSetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text));
}

int CScintillaCtrl::MarginGetText(_In_ Line line, _Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarginGetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::MarginSetStyle(_In_ Line line, _In_ int style)
{
  Call(static_cast<UINT>(Message::MarginSetStyle), static_cast<WPARAM>(line), static_cast<LPARAM>(style));
}

int CScintillaCtrl::MarginGetStyle(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarginGetStyle), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::MarginSetStyles(_In_ Line line, _In_z_ const char* styles)
{
  Call(static_cast<UINT>(Message::MarginSetStyles), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(styles));
}

int CScintillaCtrl::MarginGetStyles(_In_ Line line, _Inout_opt_z_ char* styles)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarginGetStyles), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(styles)));
}

void CScintillaCtrl::MarginTextClearAll()
{
  Call(static_cast<UINT>(Message::MarginTextClearAll), 0, 0);
}

void CScintillaCtrl::MarginSetStyleOffset(_In_ int style)
{
  Call(static_cast<UINT>(Message::MarginSetStyleOffset), static_cast<WPARAM>(style), 0);
}

int CScintillaCtrl::MarginGetStyleOffset()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::MarginGetStyleOffset), 0, 0));
}

void CScintillaCtrl::SetMarginOptions(_In_ MarginOption marginOptions)
{
  Call(static_cast<UINT>(Message::SetMarginOptions), static_cast<WPARAM>(marginOptions), 0);
}

MarginOption CScintillaCtrl::GetMarginOptions()
{
  return static_cast<MarginOption>(Call(static_cast<UINT>(Message::GetMarginOptions), 0, 0));
}

void CScintillaCtrl::AnnotationSetText(_In_ Line line, _In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::AnnotationSetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text));
}

int CScintillaCtrl::AnnotationGetText(_In_ Line line, _Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AnnotationGetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::AnnotationSetStyle(_In_ Line line, _In_ int style)
{
  Call(static_cast<UINT>(Message::AnnotationSetStyle), static_cast<WPARAM>(line), static_cast<LPARAM>(style));
}

int CScintillaCtrl::AnnotationGetStyle(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AnnotationGetStyle), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::AnnotationSetStyles(_In_ Line line, _In_z_ const char* styles)
{
  Call(static_cast<UINT>(Message::AnnotationSetStyles), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(styles));
}

int CScintillaCtrl::AnnotationGetStyles(_In_ Line line, _Inout_opt_z_ char* styles)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AnnotationGetStyles), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(styles)));
}

int CScintillaCtrl::AnnotationGetLines(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AnnotationGetLines), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::AnnotationClearAll()
{
  Call(static_cast<UINT>(Message::AnnotationClearAll), 0, 0);
}

void CScintillaCtrl::AnnotationSetVisible(_In_ AnnotationVisible visible)
{
  Call(static_cast<UINT>(Message::AnnotationSetVisible), static_cast<WPARAM>(visible), 0);
}

AnnotationVisible CScintillaCtrl::AnnotationGetVisible()
{
  return static_cast<AnnotationVisible>(Call(static_cast<UINT>(Message::AnnotationGetVisible), 0, 0));
}

void CScintillaCtrl::AnnotationSetStyleOffset(_In_ int style)
{
  Call(static_cast<UINT>(Message::AnnotationSetStyleOffset), static_cast<WPARAM>(style), 0);
}

int CScintillaCtrl::AnnotationGetStyleOffset()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AnnotationGetStyleOffset), 0, 0));
}

void CScintillaCtrl::ReleaseAllExtendedStyles()
{
  Call(static_cast<UINT>(Message::ReleaseAllExtendedStyles), 0, 0);
}

int CScintillaCtrl::AllocateExtendedStyles(_In_ int numberStyles)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AllocateExtendedStyles), static_cast<WPARAM>(numberStyles), 0));
}

void CScintillaCtrl::AddUndoAction(_In_ int token, _In_ UndoFlags flags)
{
  Call(static_cast<UINT>(Message::AddUndoAction), static_cast<WPARAM>(token), static_cast<LPARAM>(flags));
}

Position CScintillaCtrl::CharPositionFromPoint(_In_ int x, _In_ int y)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::CharPositionFromPoint), static_cast<WPARAM>(x), static_cast<LPARAM>(y)));
}

Position CScintillaCtrl::CharPositionFromPointClose(_In_ int x, _In_ int y)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::CharPositionFromPointClose), static_cast<WPARAM>(x), static_cast<LPARAM>(y)));
}

void CScintillaCtrl::SetMouseSelectionRectangularSwitch(_In_ BOOL mouseSelectionRectangularSwitch)
{
  Call(static_cast<UINT>(Message::SetMouseSelectionRectangularSwitch), static_cast<WPARAM>(mouseSelectionRectangularSwitch), 0);
}

BOOL CScintillaCtrl::GetMouseSelectionRectangularSwitch()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMouseSelectionRectangularSwitch), 0, 0));
}

void CScintillaCtrl::SetMultipleSelection(_In_ BOOL multipleSelection)
{
  Call(static_cast<UINT>(Message::SetMultipleSelection), static_cast<WPARAM>(multipleSelection), 0);
}

BOOL CScintillaCtrl::GetMultipleSelection()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetMultipleSelection), 0, 0));
}

void CScintillaCtrl::SetAdditionalSelectionTyping(_In_ BOOL additionalSelectionTyping)
{
  Call(static_cast<UINT>(Message::SetAdditionalSelectionTyping), static_cast<WPARAM>(additionalSelectionTyping), 0);
}

BOOL CScintillaCtrl::GetAdditionalSelectionTyping()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetAdditionalSelectionTyping), 0, 0));
}

void CScintillaCtrl::SetAdditionalCaretsBlink(_In_ BOOL additionalCaretsBlink)
{
  Call(static_cast<UINT>(Message::SetAdditionalCaretsBlink), static_cast<WPARAM>(additionalCaretsBlink), 0);
}

BOOL CScintillaCtrl::GetAdditionalCaretsBlink()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetAdditionalCaretsBlink), 0, 0));
}

void CScintillaCtrl::SetAdditionalCaretsVisible(_In_ BOOL additionalCaretsVisible)
{
  Call(static_cast<UINT>(Message::SetAdditionalCaretsVisible), static_cast<WPARAM>(additionalCaretsVisible), 0);
}

BOOL CScintillaCtrl::GetAdditionalCaretsVisible()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetAdditionalCaretsVisible), 0, 0));
}

int CScintillaCtrl::GetSelections()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetSelections), 0, 0));
}

BOOL CScintillaCtrl::GetSelectionEmpty()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetSelectionEmpty), 0, 0));
}

void CScintillaCtrl::ClearSelections()
{
  Call(static_cast<UINT>(Message::ClearSelections), 0, 0);
}

void CScintillaCtrl::SetSelection(_In_ Position caret, _In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetSelection), static_cast<WPARAM>(caret), static_cast<LPARAM>(anchor));
}

void CScintillaCtrl::AddSelection(_In_ Position caret, _In_ Position anchor)
{
  Call(static_cast<UINT>(Message::AddSelection), static_cast<WPARAM>(caret), static_cast<LPARAM>(anchor));
}

int CScintillaCtrl::SelectionFromPoint(_In_ int x, _In_ int y)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::SelectionFromPoint), static_cast<WPARAM>(x), static_cast<LPARAM>(y)));
}

void CScintillaCtrl::DropSelectionN(_In_ int selection)
{
  Call(static_cast<UINT>(Message::DropSelectionN), static_cast<WPARAM>(selection), 0);
}

void CScintillaCtrl::SetMainSelection(_In_ int selection)
{
  Call(static_cast<UINT>(Message::SetMainSelection), static_cast<WPARAM>(selection), 0);
}

int CScintillaCtrl::GetMainSelection()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetMainSelection), 0, 0));
}

void CScintillaCtrl::SetSelectionNCaret(_In_ int selection, _In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetSelectionNCaret), static_cast<WPARAM>(selection), static_cast<LPARAM>(caret));
}

Position CScintillaCtrl::GetSelectionNCaret(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNCaret), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetSelectionNAnchor(_In_ int selection, _In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetSelectionNAnchor), static_cast<WPARAM>(selection), static_cast<LPARAM>(anchor));
}

Position CScintillaCtrl::GetSelectionNAnchor(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNAnchor), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetSelectionNCaretVirtualSpace(_In_ int selection, _In_ Position space)
{
  Call(static_cast<UINT>(Message::SetSelectionNCaretVirtualSpace), static_cast<WPARAM>(selection), static_cast<LPARAM>(space));
}

Position CScintillaCtrl::GetSelectionNCaretVirtualSpace(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNCaretVirtualSpace), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetSelectionNAnchorVirtualSpace(_In_ int selection, _In_ Position space)
{
  Call(static_cast<UINT>(Message::SetSelectionNAnchorVirtualSpace), static_cast<WPARAM>(selection), static_cast<LPARAM>(space));
}

Position CScintillaCtrl::GetSelectionNAnchorVirtualSpace(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNAnchorVirtualSpace), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetSelectionNStart(_In_ int selection, _In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetSelectionNStart), static_cast<WPARAM>(selection), static_cast<LPARAM>(anchor));
}

Position CScintillaCtrl::GetSelectionNStart(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNStart), static_cast<WPARAM>(selection), 0));
}

Position CScintillaCtrl::GetSelectionNStartVirtualSpace(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNStartVirtualSpace), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetSelectionNEnd(_In_ int selection, _In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetSelectionNEnd), static_cast<WPARAM>(selection), static_cast<LPARAM>(caret));
}

Position CScintillaCtrl::GetSelectionNEndVirtualSpace(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNEndVirtualSpace), static_cast<WPARAM>(selection), 0));
}

Position CScintillaCtrl::GetSelectionNEnd(_In_ int selection)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetSelectionNEnd), static_cast<WPARAM>(selection), 0));
}

void CScintillaCtrl::SetRectangularSelectionCaret(_In_ Position caret)
{
  Call(static_cast<UINT>(Message::SetRectangularSelectionCaret), static_cast<WPARAM>(caret), 0);
}

Position CScintillaCtrl::GetRectangularSelectionCaret()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetRectangularSelectionCaret), 0, 0));
}

void CScintillaCtrl::SetRectangularSelectionAnchor(_In_ Position anchor)
{
  Call(static_cast<UINT>(Message::SetRectangularSelectionAnchor), static_cast<WPARAM>(anchor), 0);
}

Position CScintillaCtrl::GetRectangularSelectionAnchor()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetRectangularSelectionAnchor), 0, 0));
}

void CScintillaCtrl::SetRectangularSelectionCaretVirtualSpace(_In_ Position space)
{
  Call(static_cast<UINT>(Message::SetRectangularSelectionCaretVirtualSpace), static_cast<WPARAM>(space), 0);
}

Position CScintillaCtrl::GetRectangularSelectionCaretVirtualSpace()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetRectangularSelectionCaretVirtualSpace), 0, 0));
}

void CScintillaCtrl::SetRectangularSelectionAnchorVirtualSpace(_In_ Position space)
{
  Call(static_cast<UINT>(Message::SetRectangularSelectionAnchorVirtualSpace), static_cast<WPARAM>(space), 0);
}

Position CScintillaCtrl::GetRectangularSelectionAnchorVirtualSpace()
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::GetRectangularSelectionAnchorVirtualSpace), 0, 0));
}

void CScintillaCtrl::SetVirtualSpaceOptions(_In_ VirtualSpace virtualSpaceOptions)
{
  Call(static_cast<UINT>(Message::SetVirtualSpaceOptions), static_cast<WPARAM>(virtualSpaceOptions), 0);
}

VirtualSpace CScintillaCtrl::GetVirtualSpaceOptions()
{
  return static_cast<VirtualSpace>(Call(static_cast<UINT>(Message::GetVirtualSpaceOptions), 0, 0));
}

void CScintillaCtrl::SetRectangularSelectionModifier(_In_ int modifier)
{
  Call(static_cast<UINT>(Message::SetRectangularSelectionModifier), static_cast<WPARAM>(modifier), 0);
}

int CScintillaCtrl::GetRectangularSelectionModifier()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetRectangularSelectionModifier), 0, 0));
}

void CScintillaCtrl::SetAdditionalSelFore(_In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetAdditionalSelFore), static_cast<WPARAM>(fore), 0);
}

void CScintillaCtrl::SetAdditionalSelBack(_In_ COLORREF back)
{
  Call(static_cast<UINT>(Message::SetAdditionalSelBack), static_cast<WPARAM>(back), 0);
}

void CScintillaCtrl::SetAdditionalSelAlpha(_In_ Alpha alpha)
{
  Call(static_cast<UINT>(Message::SetAdditionalSelAlpha), static_cast<WPARAM>(alpha), 0);
}

Alpha CScintillaCtrl::GetAdditionalSelAlpha()
{
  return static_cast<Alpha>(Call(static_cast<UINT>(Message::GetAdditionalSelAlpha), 0, 0));
}

void CScintillaCtrl::SetAdditionalCaretFore(_In_ COLORREF fore)
{
  Call(static_cast<UINT>(Message::SetAdditionalCaretFore), static_cast<WPARAM>(fore), 0);
}

COLORREF CScintillaCtrl::GetAdditionalCaretFore()
{
  return static_cast<COLORREF>(Call(static_cast<UINT>(Message::GetAdditionalCaretFore), 0, 0));
}

void CScintillaCtrl::RotateSelection()
{
  Call(static_cast<UINT>(Message::RotateSelection), 0, 0);
}

void CScintillaCtrl::SwapMainAnchorCaret()
{
  Call(static_cast<UINT>(Message::SwapMainAnchorCaret), 0, 0);
}

void CScintillaCtrl::MultipleSelectAddNext()
{
  Call(static_cast<UINT>(Message::MultipleSelectAddNext), 0, 0);
}

void CScintillaCtrl::MultipleSelectAddEach()
{
  Call(static_cast<UINT>(Message::MultipleSelectAddEach), 0, 0);
}

int CScintillaCtrl::ChangeLexerState(_In_ Position start, _In_ Position end)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::ChangeLexerState), static_cast<WPARAM>(start), static_cast<LPARAM>(end)));
}

Line CScintillaCtrl::ContractedFoldNext(_In_ Line lineStart)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::ContractedFoldNext), static_cast<WPARAM>(lineStart), 0));
}

void CScintillaCtrl::VerticalCentreCaret()
{
  Call(static_cast<UINT>(Message::VerticalCentreCaret), 0, 0);
}

void CScintillaCtrl::MoveSelectedLinesUp()
{
  Call(static_cast<UINT>(Message::MoveSelectedLinesUp), 0, 0);
}

void CScintillaCtrl::MoveSelectedLinesDown()
{
  Call(static_cast<UINT>(Message::MoveSelectedLinesDown), 0, 0);
}

void CScintillaCtrl::SetIdentifier(_In_ int identifier)
{
  Call(static_cast<UINT>(Message::SetIdentifier), static_cast<WPARAM>(identifier), 0);
}

int CScintillaCtrl::GetIdentifier()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetIdentifier), 0, 0));
}

void CScintillaCtrl::RGBAImageSetWidth(_In_ int width)
{
  Call(static_cast<UINT>(Message::RGBAImageSetWidth), static_cast<WPARAM>(width), 0);
}

void CScintillaCtrl::RGBAImageSetHeight(_In_ int height)
{
  Call(static_cast<UINT>(Message::RGBAImageSetHeight), static_cast<WPARAM>(height), 0);
}

void CScintillaCtrl::RGBAImageSetScale(_In_ int scalePercent)
{
  Call(static_cast<UINT>(Message::RGBAImageSetScale), static_cast<WPARAM>(scalePercent), 0);
}

void CScintillaCtrl::MarkerDefineRGBAImage(_In_ int markerNumber, _In_ const char* pixels)
{
  Call(static_cast<UINT>(Message::MarkerDefineRGBAImage), static_cast<WPARAM>(markerNumber), reinterpret_cast<LPARAM>(pixels));
}

void CScintillaCtrl::RegisterRGBAImage(_In_ int type, _In_ const char* pixels)
{
  Call(static_cast<UINT>(Message::RegisterRGBAImage), static_cast<WPARAM>(type), reinterpret_cast<LPARAM>(pixels));
}

void CScintillaCtrl::ScrollToStart()
{
  Call(static_cast<UINT>(Message::ScrollToStart), 0, 0);
}

void CScintillaCtrl::ScrollToEnd()
{
  Call(static_cast<UINT>(Message::ScrollToEnd), 0, 0);
}

void CScintillaCtrl::SetTechnology(_In_ Technology technology)
{
  Call(static_cast<UINT>(Message::SetTechnology), static_cast<WPARAM>(technology), 0);
}

Technology CScintillaCtrl::GetTechnology()
{
  return static_cast<Technology>(Call(static_cast<UINT>(Message::GetTechnology), 0, 0));
}

void* CScintillaCtrl::CreateLoader(_In_ Position bytes, _In_ DocumentOption documentOptions)
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<void*>(Call(static_cast<UINT>(Message::CreateLoader), static_cast<WPARAM>(bytes), static_cast<LPARAM>(documentOptions)));
}

void CScintillaCtrl::FindIndicatorShow(_In_ Position start, _In_ Position end)
{
  Call(static_cast<UINT>(Message::FindIndicatorShow), static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

void CScintillaCtrl::FindIndicatorFlash(_In_ Position start, _In_ Position end)
{
  Call(static_cast<UINT>(Message::FindIndicatorFlash), static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

void CScintillaCtrl::FindIndicatorHide()
{
  Call(static_cast<UINT>(Message::FindIndicatorHide), 0, 0);
}

void CScintillaCtrl::VCHomeDisplay()
{
  Call(static_cast<UINT>(Message::VCHomeDisplay), 0, 0);
}

void CScintillaCtrl::VCHomeDisplayExtend()
{
  Call(static_cast<UINT>(Message::VCHomeDisplayExtend), 0, 0);
}

BOOL CScintillaCtrl::GetCaretLineVisibleAlways()
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::GetCaretLineVisibleAlways), 0, 0));
}

void CScintillaCtrl::SetCaretLineVisibleAlways(_In_ BOOL bAlwaysVisible)
{
  Call(static_cast<UINT>(Message::SetCaretLineVisibleAlways), static_cast<WPARAM>(bAlwaysVisible), 0);
}

void CScintillaCtrl::SetLineEndTypesAllowed(_In_ LineEndType lineEndBitSet)
{
  Call(static_cast<UINT>(Message::SetLineEndTypesAllowed), static_cast<WPARAM>(lineEndBitSet), 0);
}

LineEndType CScintillaCtrl::GetLineEndTypesAllowed()
{
  return static_cast<LineEndType>(Call(static_cast<UINT>(Message::GetLineEndTypesAllowed), 0, 0));
}

LineEndType CScintillaCtrl::GetLineEndTypesActive()
{
  return static_cast<LineEndType>(Call(static_cast<UINT>(Message::GetLineEndTypesActive), 0, 0));
}

void CScintillaCtrl::SetRepresentation(_In_z_ const char* encodedCharacter, _In_z_ const char* representation)
{
  Call(static_cast<UINT>(Message::SetRepresentation), reinterpret_cast<WPARAM>(encodedCharacter), reinterpret_cast<LPARAM>(representation));
}

int CScintillaCtrl::GetRepresentation(_In_z_ const char* encodedCharacter, _Inout_z_ char* representation)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetRepresentation), reinterpret_cast<WPARAM>(encodedCharacter), reinterpret_cast<LPARAM>(representation)));
}

void CScintillaCtrl::ClearRepresentation(_In_z_ const char* encodedCharacter)
{
  Call(static_cast<UINT>(Message::ClearRepresentation), reinterpret_cast<WPARAM>(encodedCharacter), 0);
}

void CScintillaCtrl::ClearAllRepresentations()
{
  Call(static_cast<UINT>(Message::ClearAllRepresentations), 0, 0);
}

void CScintillaCtrl::SetRepresentationAppearance(_In_z_ const char* encodedCharacter, _In_ RepresentationAppearance appearance)
{
  Call(static_cast<UINT>(Message::SetRepresentationAppearance), reinterpret_cast<WPARAM>(encodedCharacter), static_cast<LPARAM>(appearance));
}

RepresentationAppearance CScintillaCtrl::GetRepresentationAppearance(_In_z_ const char* encodedCharacter)
{
  return static_cast<RepresentationAppearance>(Call(static_cast<UINT>(Message::GetRepresentationAppearance), reinterpret_cast<WPARAM>(encodedCharacter), 0));
}

void CScintillaCtrl::SetRepresentationColour(_In_z_ const char* encodedCharacter, _In_ int colour)
{
  Call(static_cast<UINT>(Message::SetRepresentationColour), reinterpret_cast<WPARAM>(encodedCharacter), static_cast<LPARAM>(colour));
}

int CScintillaCtrl::GetRepresentationColour(_In_z_ const char* encodedCharacter)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetRepresentationColour), reinterpret_cast<WPARAM>(encodedCharacter), 0));
}

void CScintillaCtrl::EOLAnnotationSetText(_In_ Line line, _In_z_ const char* text)
{
  Call(static_cast<UINT>(Message::EOLAnnotationSetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text));
}

int CScintillaCtrl::EOLAnnotationGetText(_In_ Line line, _Inout_opt_z_ char* text)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::EOLAnnotationGetText), static_cast<WPARAM>(line), reinterpret_cast<LPARAM>(text)));
}

void CScintillaCtrl::EOLAnnotationSetStyle(_In_ Line line, _In_ int style)
{
  Call(static_cast<UINT>(Message::EOLAnnotationSetStyle), static_cast<WPARAM>(line), static_cast<LPARAM>(style));
}

int CScintillaCtrl::EOLAnnotationGetStyle(_In_ Line line)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::EOLAnnotationGetStyle), static_cast<WPARAM>(line), 0));
}

void CScintillaCtrl::EOLAnnotationClearAll()
{
  Call(static_cast<UINT>(Message::EOLAnnotationClearAll), 0, 0);
}

void CScintillaCtrl::EOLAnnotationSetVisible(_In_ EOLAnnotationVisible visible)
{
  Call(static_cast<UINT>(Message::EOLAnnotationSetVisible), static_cast<WPARAM>(visible), 0);
}

EOLAnnotationVisible CScintillaCtrl::EOLAnnotationGetVisible()
{
  return static_cast<EOLAnnotationVisible>(Call(static_cast<UINT>(Message::EOLAnnotationGetVisible), 0, 0));
}

void CScintillaCtrl::EOLAnnotationSetStyleOffset(_In_ int style)
{
  Call(static_cast<UINT>(Message::EOLAnnotationSetStyleOffset), static_cast<WPARAM>(style), 0);
}

int CScintillaCtrl::EOLAnnotationGetStyleOffset()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::EOLAnnotationGetStyleOffset), 0, 0));
}

BOOL CScintillaCtrl::SupportsFeature(_In_ Supports feature)
{
  return static_cast<BOOL>(Call(static_cast<UINT>(Message::SupportsFeature), static_cast<WPARAM>(feature), 0));
}

LineCharacterIndexType CScintillaCtrl::GetLineCharacterIndex()
{
  return static_cast<LineCharacterIndexType>(Call(static_cast<UINT>(Message::GetLineCharacterIndex), 0, 0));
}

void CScintillaCtrl::AllocateLineCharacterIndex(_In_ LineCharacterIndexType lineCharacterIndex)
{
  Call(static_cast<UINT>(Message::AllocateLineCharacterIndex), static_cast<WPARAM>(lineCharacterIndex), 0);
}

void CScintillaCtrl::ReleaseLineCharacterIndex(_In_ LineCharacterIndexType lineCharacterIndex)
{
  Call(static_cast<UINT>(Message::ReleaseLineCharacterIndex), static_cast<WPARAM>(lineCharacterIndex), 0);
}

Line CScintillaCtrl::LineFromIndexPosition(_In_ Position pos, _In_ LineCharacterIndexType lineCharacterIndex)
{
  return static_cast<Line>(Call(static_cast<UINT>(Message::LineFromIndexPosition), static_cast<WPARAM>(pos), static_cast<LPARAM>(lineCharacterIndex)));
}

Position CScintillaCtrl::IndexPositionFromLine(_In_ Line line, _In_ LineCharacterIndexType lineCharacterIndex)
{
  return static_cast<Position>(Call(static_cast<UINT>(Message::IndexPositionFromLine), static_cast<WPARAM>(line), static_cast<LPARAM>(lineCharacterIndex)));
}

void CScintillaCtrl::StartRecord()
{
  Call(static_cast<UINT>(Message::StartRecord), 0, 0);
}

void CScintillaCtrl::StopRecord()
{
  Call(static_cast<UINT>(Message::StopRecord), 0, 0);
}

int CScintillaCtrl::GetLexer()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetLexer), 0, 0));
}

void CScintillaCtrl::Colourise(_In_ Position start, _In_ Position end)
{
  Call(static_cast<UINT>(Message::Colourise), static_cast<WPARAM>(start), static_cast<LPARAM>(end));
}

void CScintillaCtrl::SetSCIProperty(_In_z_ const char* key, _In_z_ const char* value)
{
  Call(static_cast<UINT>(Message::SetProperty), reinterpret_cast<WPARAM>(key), reinterpret_cast<LPARAM>(value));
}

void CScintillaCtrl::SetKeyWords(_In_ int keyWordSet, _In_z_ const char* keyWords)
{
  Call(static_cast<UINT>(Message::SetKeyWords), static_cast<WPARAM>(keyWordSet), reinterpret_cast<LPARAM>(keyWords));
}

int CScintillaCtrl::GetSCIProperty(_In_z_ const char* key, _Inout_opt_z_ char* value)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetProperty), reinterpret_cast<WPARAM>(key), reinterpret_cast<LPARAM>(value)));
}

int CScintillaCtrl::GetPropertyExpanded(_In_z_ const char* key, _Inout_opt_z_ char* value)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPropertyExpanded), reinterpret_cast<WPARAM>(key), reinterpret_cast<LPARAM>(value)));
}

int CScintillaCtrl::GetPropertyInt(_In_z_ const char* key, _In_ int defaultValue)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPropertyInt), reinterpret_cast<WPARAM>(key), defaultValue));
}

int CScintillaCtrl::GetLexerLanguage(_Inout_opt_z_ char* language)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetLexerLanguage), 0, reinterpret_cast<LPARAM>(language)));
}

void* CScintillaCtrl::PrivateLexerCall(_In_ int operation, _In_opt_ void* pointer)
{
#pragma warning(suppress: 26487)
  return reinterpret_cast<void*>(Call(static_cast<UINT>(Message::PrivateLexerCall), static_cast<WPARAM>(operation), reinterpret_cast<LPARAM>(pointer)));
}

int CScintillaCtrl::PropertyNames(_Inout_opt_z_ char* names)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::PropertyNames), 0, reinterpret_cast<LPARAM>(names)));
}

TypeProperty CScintillaCtrl::PropertyType(_In_z_ const char* name)
{
  return static_cast<TypeProperty>(Call(static_cast<UINT>(Message::PropertyType), reinterpret_cast<WPARAM>(name), 0));
}

int CScintillaCtrl::DescribeProperty(_In_z_ const char* name, _Inout_opt_z_ char* description)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::DescribeProperty), reinterpret_cast<WPARAM>(name), reinterpret_cast<LPARAM>(description)));
}

int CScintillaCtrl::DescribeKeyWordSets(_Inout_opt_z_ char* descriptions)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::DescribeKeyWordSets), 0, reinterpret_cast<LPARAM>(descriptions)));
}

LineEndType CScintillaCtrl::GetLineEndTypesSupported()
{
  return static_cast<LineEndType>(Call(static_cast<UINT>(Message::GetLineEndTypesSupported), 0, 0));
}

int CScintillaCtrl::AllocateSubStyles(_In_ int styleBase, _In_ int numberStyles)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::AllocateSubStyles), static_cast<WPARAM>(styleBase), static_cast<LPARAM>(numberStyles)));
}

int CScintillaCtrl::GetSubStylesStart(_In_ int styleBase)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetSubStylesStart), static_cast<WPARAM>(styleBase), 0));
}

int CScintillaCtrl::GetSubStylesLength(_In_ int styleBase)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetSubStylesLength), static_cast<WPARAM>(styleBase), 0));
}

int CScintillaCtrl::GetStyleFromSubStyle(_In_ int subStyle)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetStyleFromSubStyle), static_cast<WPARAM>(subStyle), 0));
}

int CScintillaCtrl::GetPrimaryStyleFromStyle(_In_ int style)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetPrimaryStyleFromStyle), static_cast<WPARAM>(style), 0));
}

void CScintillaCtrl::FreeSubStyles()
{
  Call(static_cast<UINT>(Message::FreeSubStyles), 0, 0);
}

void CScintillaCtrl::SetIdentifiers(_In_ int style, _In_z_ const char* identifiers)
{
  Call(static_cast<UINT>(Message::SetIdentifiers), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(identifiers));
}

int CScintillaCtrl::DistanceToSecondaryStyles()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::DistanceToSecondaryStyles), 0, 0));
}

int CScintillaCtrl::GetSubStyleBases(_Inout_opt_z_ char* styles)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetSubStyleBases), 0, reinterpret_cast<LPARAM>(styles)));
}

int CScintillaCtrl::GetNamedStyles()
{
  return static_cast<int>(Call(static_cast<UINT>(Message::GetNamedStyles), 0, 0));
}

int CScintillaCtrl::NameOfStyle(_In_ int style, _Inout_opt_z_ char* name)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::NameOfStyle), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(name)));
}

int CScintillaCtrl::TagsOfStyle(_In_ int style, _Inout_opt_z_ char* tags)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::TagsOfStyle), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(tags)));
}

int CScintillaCtrl::DescriptionOfStyle(_In_ int style, _Inout_opt_z_ char* description)
{
  return static_cast<int>(Call(static_cast<UINT>(Message::DescriptionOfStyle), static_cast<WPARAM>(style), reinterpret_cast<LPARAM>(description)));
}

void CScintillaCtrl::SetILexer(_In_ void* ilexer)
{
  Call(static_cast<UINT>(Message::SetILexer), 0, reinterpret_cast<LPARAM>(ilexer));
}

Bidirectional CScintillaCtrl::GetBidirectional()
{
  return static_cast<Bidirectional>(Call(static_cast<UINT>(Message::GetBidirectional), 0, 0));
}

void CScintillaCtrl::SetBidirectional(_In_ Bidirectional bidirectional)
{
  Call(static_cast<UINT>(Message::SetBidirectional), static_cast<WPARAM>(bidirectional), 0);
}
#pragma warning(pop)
