/* cfdg.l
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2014 John Horigan - john@glyphic.com
// Copyright (C) 2005 Chris Coyne - ccoyne77@gmail.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
*/


%{
    #define YY_NO_UNISTD_H
    #include "builder.h"
    #include "scanner.h"
    #include "astexpression.h"
    #include "cfdg.tab.hpp"

    /* import the parser's token type into a local typedef */
    typedef yy::CfdgParser::token token;
    typedef yy::CfdgParser::token_type token_type;    
    
%}


INTEGER     [0-9]+%?
RATIONAL    ([0-9]+\.[0-9]*%?)|(\.[0-9]+%?)
RATIONAL2   [0-9]+%?\.\.
FLOAT       ([0-9]+\.[0-9]*[eE][+-]?[0-9]+%?)|(\.[0-9]+[eE][+-]?[0-9]+%?)|[0-9]+[eE][+-]?[0-9]+%?
PATHOP      MOVETO|LINETO|ARCTO|CURVETO|MOVEREL|LINEREL|ARCREL|CURVEREL|CLOSEPOLY
FILENAME   [a-zA-Z\200-\377][a-zA-Z\200-\377_\-0-9\.]*\.cfdg
STRINGLET  [a-zA-Z\200-\377_]([a-zA-Z_0-9\200-\377])*
STRING     {STRINGLET}(::{STRINGLET})*

/* calling this externally    */
/* don't want yywrap to exist.*/

%option noyywrap
%option 8bit
%option yylineno
%option c++
%option prefix="Cfdg"
%option batch

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(utf8length(yytext, yyleng));
%}

%%

 /* code to place at the beginning of yylex() */
%{
    // reset location
    setupLoc(yylloc);
    
    if (atStartup) {
        int t = startToken;
        atStartup = false;
        return t;
    }
%}
                                                                
 /* comment line */
"#"|"//" {
                                                                
    int c;
    
    while ((c = yyinput()) != EOF) {
        if (c == '\n') break;
    }

    yylloc->lines(1); yylloc->step();
}

 /* C-style comment */
"/*" {
    int c;
    bool lastCharWasAStar = false;
 
    // stop when we get to */ or end-of-file
    while ((c = yyinput()) != EOF) {
        if (c == '\n') 
            yylloc->lines(1);
        else 
            yylloc->columns();
            
        if (c == '/' && lastCharWasAStar) 
            break;
        
        lastCharWasAStar = c == '*';
    }
    
    if (c == EOF) {
        LexerError("end-of-file in block comment");
        return token::BADEOF;
    }
    
    yylloc->step();     // move on to next token
}

 /* Quoted string */
\042[^\042\n]*[\042\n] {        /* \042 is " in ASCII */
    if (yytext[yyleng - 1] != '\042') {
        LexerError("end-of-line in quoted string");
        return token::BADEOF;
    } else {
        yylval->string = new std::string(yytext + 1, yyleng - 2); 
        return token::USER_QSTRING;
    }
}
          
"startshape"    {return token::STARTSHAPE;}
"background"    {return token::BACKGROUND;}
"include"       {return token::INCLUDE;}
"import"        {return token::IMPORT;}
"tile"          {return token::TILE;}
"rule"          {return token::RULE;}
"path"          {return token::PATH;}
"shape"         {return token::SHAPE;}
"loop"          {return token::LOOP;}
"clone"         {return token::CLONE;}
"let"           {return token::LET;}
"="             {return token::BECOMES;}
"finally"       {return token::FINALLY;}
"if"            {return token::IF;}
"else"          {return token::ELSE;}
"switch"        {return token::SWITCH;}
"case"          {return token::CASE;}
".."            {return token::RANGEOP;}
\xe2\x80\xa6    {return token::RANGEOP;}
\xc2\xb1        {return token::PLUSMINUSOP;}
"+/-"           {return token::PLUSMINUSOP;}
\xe2\x88\x9e    {return token::CF_INFINITY;}

"time"          {yylval->modToken = AST::ASTmodTerm::time;          return token::MODTYPE;}
"timescale"     {yylval->modToken = AST::ASTmodTerm::timescale;     return token::MODTYPE;}
"rotate"        {yylval->modToken = AST::ASTmodTerm::rot;           return token::MODTYPE;}
"r"             {yylval->modToken = AST::ASTmodTerm::rot;           return token::MODTYPE;}
"flip"          {yylval->modToken = AST::ASTmodTerm::flip;          return token::MODTYPE;}
"f"             {yylval->modToken = AST::ASTmodTerm::flip;          return token::MODTYPE;}
"hue"           {yylval->modToken = AST::ASTmodTerm::hue;           return token::MODTYPE;}
"h"             {yylval->modToken = AST::ASTmodTerm::hue;           return token::MODTYPE;}
"saturation"    {yylval->modToken = AST::ASTmodTerm::sat;           return token::MODTYPE;}
"sat"           {yylval->modToken = AST::ASTmodTerm::sat;           return token::MODTYPE;}
"brightness"    {yylval->modToken = AST::ASTmodTerm::bright;        return token::MODTYPE;}
"b"             {yylval->modToken = AST::ASTmodTerm::bright;        return token::MODTYPE;}
"alpha"         {yylval->modToken = AST::ASTmodTerm::alpha;         return token::MODTYPE;}
"a"             {yylval->modToken = AST::ASTmodTerm::alpha;         return token::MODTYPE;}
"transform"     {yylval->modToken = AST::ASTmodTerm::transform;     return token::MODTYPE;}
"trans"         {yylval->modToken = AST::ASTmodTerm::transform;     return token::MODTYPE;}
"x"             {yylval->modToken = AST::ASTmodTerm::x;             return token::MODTYPE;}
"y"             {yylval->modToken = AST::ASTmodTerm::y;             return token::MODTYPE;}
"z"             {yylval->modToken = AST::ASTmodTerm::z;             return token::MODTYPE;}
"size"          {yylval->modToken = AST::ASTmodTerm::size;          return token::MODTYPE;}
"s"             {yylval->modToken = AST::ASTmodTerm::size;          return token::MODTYPE;}
"skew"          {yylval->modToken = AST::ASTmodTerm::skew;          return token::MODTYPE;}
"|hue"          {yylval->modToken = AST::ASTmodTerm::targHue;       return token::MODTYPE;}
"|h"            {yylval->modToken = AST::ASTmodTerm::targHue;       return token::MODTYPE;}
"|saturation"   {yylval->modToken = AST::ASTmodTerm::targSat;       return token::MODTYPE;}
"|sat"          {yylval->modToken = AST::ASTmodTerm::targSat;       return token::MODTYPE;}
"|brightness"   {yylval->modToken = AST::ASTmodTerm::targBright;    return token::MODTYPE;}
"|b"            {yylval->modToken = AST::ASTmodTerm::targBright;    return token::MODTYPE;}
"|alpha"        {yylval->modToken = AST::ASTmodTerm::targAlpha;     return token::MODTYPE;}
"|a"            {yylval->modToken = AST::ASTmodTerm::targAlpha;     return token::MODTYPE;}

"param"         { return v2token(yylval, AST::ASTmodTerm::param); }
"p"             { return v2token(yylval, AST::ASTmodTerm::param); }
"width"         { return v2token(yylval, AST::ASTmodTerm::stroke); }
"x1"            { return v2token(yylval, AST::ASTmodTerm::x1); }
"y1"            { return v2token(yylval, AST::ASTmodTerm::y1); }
"x2"            { return v2token(yylval, AST::ASTmodTerm::x2); }
"y2"            { return v2token(yylval, AST::ASTmodTerm::y2); }
"rx"            { return v2token(yylval, AST::ASTmodTerm::xrad); }
"ry"            { return v2token(yylval, AST::ASTmodTerm::yrad); }

"<"             { return token::LT; }
"<="            { return token::LE; }
\xe2\x89\xa4    { return token::LE; }
">"             { return token::GT; }
">="            { return token::GE; }
\xe2\x89\xa5    { return token::GE; }
"=="            { return token::EQ; }
"<>"            { return token::NEQ; }
\xe2\x89\xa0    { return token::NEQ; }
"!"             { return token::NOT; }
"&&"            { return token::AND; }
"||"            { return token::OR; }
"^^"            { return token::XOR; }
"--"            { return '_'; }

{PATHOP}    {yylval->string = new std::string(yytext); return token::USER_PATHOP;}
{STRING}    {
    // This greedy string regex gobbles up Unicode operators. Find the first one
    // and chop the string there.
    yylval->string = new std::string(yytext);
    size_t pos = std::string::npos;
    token_type tok = token::USER_STRING;
    for (tokenMap::value_type& tokenEntry: utf8chars) {
        size_t spos = yylval->string->find(tokenEntry.second);
        if (spos != std::string::npos && (spos < pos || pos == std::string::npos)) {
            pos = spos;
            tok = tokenEntry.first;
        }
    }
    
    if (pos == 0) {
        // Unicode operator found at 1st char, Unread all but the operator and
        // return the token for the operator.
        delete yylval->string;
        yylval->string = nullptr;
        size_t len = strlen(utf8chars[tok]);
        (yylloc->end) = (yylloc->begin);
        yylloc->columns(1);
        yyless(len);
        return tok;
    }
    
    if (pos != std::string::npos) {
        // Unicode operator found after 1st char. Unread everything from operator to
        // end of string and truncate string before operator.
        yylval->string->resize(pos);
        (yylloc->end) = (yylloc->begin);
        yylloc->columns(utf8length(yytext, pos));
        yyless(pos);
        return token::USER_STRING;
    }
    int c = yyinput();
    if (c != EOF) unput(c);
    return c == '[' ? token::USER_ARRAYNAME : token::USER_STRING;
}
{RATIONAL}  {yylval->string = new std::string(yytext); return token::USER_RATIONAL;}
{FLOAT}     {yylval->string = new std::string(yytext); return token::USER_RATIONAL;}
{RATIONAL2}  {
    yylval->string = new std::string(yytext, yyleng - 2);
    yyless(yyleng - 2);
    (yylloc->end) += -2;
    return token::USER_RATIONAL;
}
{INTEGER}   {yylval->string = new std::string(yytext); return token::USER_RATIONAL;}
{FILENAME}  {yylval->string = new std::string(yytext); return token::USER_FILENAME;}

 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    yylloc->lines(1); yylloc->step();
}

 /* pass all other characters up to bison */
. {
    return static_cast<int>(*yytext);
}

<<EOF>> {
    if (!YY_CURRENT_BUFFER)
        yyterminate();
    if (!mLocationStack.empty()) {
        *yylloc = mLocationStack.top();
        mLocationStack.pop();
    }
    yylloc->step();
    return token::GOODEOF;
}

%% /*** Additional Code ***/

namespace yy {

Scanner::Scanner(std::istream* in, std::ostream* out)
    : yyFlexLexer(in, out), nextLocAction(normalAction), 
      startToken(token::CFDG2), maybeVersion(0), atStartup(true)
{
    utf8chars[token::RANGEOP] = "\xe2\x80\xa6";
    utf8chars[token::PLUSMINUSOP] = "\xc2\xb1";
    utf8chars[token::LE] = "\xe2\x89\xa4";
    utf8chars[token::GE] = "\xe2\x89\xa5";
    utf8chars[token::NEQ] = "\xe2\x89\xa0";
    utf8chars[token::CF_INFINITY] = "\xe2\x88\x9e";
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

void Scanner::LexerError(const char* msg) 
{
    driver->error(lineno(), msg);
}
    
void Scanner::setupLoc(CfdgParser::location_type* yylloc)
{
    switch (nextLocAction) {
        case normalAction:
        case popLoc:
            yylloc->step();
            break;
        case pushLoc:
            mLocationStack.push(*yylloc);
            *yylloc = CfdgParser::location_type();
            break;
    }
    nextLocAction = normalAction;
    yylloc->begin.filename = yylloc->end.filename = driver->m_currentPath;
}

// Compute the number of Unicode characters in a block of UTF-8 encoded bytes
unsigned int Scanner::utf8length(const char* txt, size_t len)
{
    unsigned int length = 0;
    for (size_t i = 0; i < len; ++i, ++length) {
        unsigned char c = static_cast<unsigned char>(txt[i]);
        if (c == '\0')
            LexerError("Invalid UTF-8 encoding: ASCII null character");
        if ((c & 0x80) == 0) continue;
        size_t j = 0;
        for (; c & 0x80; ++j)
            c <<= 1;
        
        if (j == 1) {
            LexerError("Invalid UTF-8 encoding: unexpected continuation byte");
            continue;
        }
        
        if (j > 4)      // 4 bytes max per RFC 3629
            LexerError("Invalid UTF-8 encoding: code point out of range");
        
        if (j && i + j > len) {
            LexerError("Invalid UTF-8 encoding: sequence extends past end of buffer");
            return length;
        }
        
        // Compute the Unicode code point
        unsigned long code = (c & 0x7f) >> j;
        size_t k = 1;
        for (; k < j; ++k) {
            if ((txt[i + k] & 0xc0) != 0x80) {
                LexerError("Invalid UTF-8 encoding: expecting a continuation byte");
                break;
            }
            code = (code << 6) | (txt[i + k] & 0x3f);
        }
        if (k < j) {
            // malformed code is actually k bytes long, not j bytes long
            i += k - 1;
            continue;
        }
        
        // Check for illegal code points
        if (code >= 0xd800 && code <= 0xdfff)
            LexerError("Invalid UTF-8 encoding: UTF-16 surrogate halves");
        if (code == 0xfffe || code == 0xffff)
            LexerError("Invalid UTF-8 encoding: illegal code point");
        if (code == 0)
            LexerError("Invalid UTF-8 encoding: encoded null character");
        if (code > 0x10ffff)
            LexerError("Invalid UTF-8 encoding: codepoint above U+10FFFF");
        
        // Check for encodings that are more bytes than they need to be
        switch (j) {
            case 2:
                if (code > 0x7f) break;
            case 3:
                if (code > 0x7ff) break;
            case 4:
                if (code > 0xffff) break;
                LexerError("Invalid UTF-8 encoding: overlong sequence");
            default:
                break;
        }
        if (j)
            i += j - 1;
    }
    return length;
}

CfdgParser::token_type Scanner::v2token(CfdgParser::semantic_type* yylval,
                                        AST::ASTmodTerm::modTypeEnum mod)
{
    if (startToken == token::CFDG2) {
        yylval->modToken = mod;
        return mod == AST::ASTmodTerm::param ? token::PARAM : token::MODTYPE;
    } else {
        yylval->string = new std::string(yytext);
        return token::USER_STRING;
    }
}

}   // namespace yy

/* This implementation of CfdgFlexLexer::yylex() is required to fill the
 * vtable of the class CfdgFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int yyFlexLexer::yylex()
{
    std::cerr << "in yyFlexLexer::yylex() !" << std::endl;
    return 0;
}

