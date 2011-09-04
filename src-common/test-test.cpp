// test-test.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2003 Mark Lentczner - markl@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#include "test.h"

#include <string>

using namespace std;

namespace {
	string
	message(exception* f)
	{
		return f->what();
	}
}

TEST(test, check) {
    CHECK(true);
    CHECK_MSG(true, "true wasn't true");
    CHECK_SAME(7, 3 + 4);

    string a("abc");
    string b("a");
    b += "b";
    b += "c";
    CHECK_SAME(a, b);

    int* i = new int[42];
    CHECK_VALID(i);
    delete[] i;
}


TEST(test, failure) {
    bool fail;

    fail = false;
    try {
        PASS();
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(!fail);
    
    fail = false;
    try {
        FAIL("failure");
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);
    
    fail = false;
    try {
        CHECK(false);
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);

    fail = false;
    try {
        CHECK_MSG(false, "false wasn't true");
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);

    fail = false;
    try {
        CHECK_SAME(42, 3 + 4);
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);

    fail = false;
    try {
        string a("alpha");
        string b("beta");
        CHECK_SAME(a, b);
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);

    fail = false;
    try {
        int* i = 0;
        CHECK_VALID(i);
    }
    catch (exception* f) {
        delete f;
        fail = true;
    }
    CHECK(fail);
    
    bool skip = false;
    try {
        SKIP();
    }
    catch (exception* f) {
        delete f;
        skip = true;
    }
    CHECK(skip);
}


TEST(test, reporting)
{
    try {
        CHECK_MSG(false, "false wasn't true");
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("false wasn't true", message(f));
        delete f;
    }
    
    try {
        typedef int thing[2];
            // this has no conversion to string
        
        thing x = { 1, 2 };
        thing y = { 3, 4 };
        CHECK_SAME(x, y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("y had wrong value; expected x", message(f));
        delete f;
    }
    
    try {
        bool x = true;
        bool y = false;
        CHECK_SAME(x, y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("y had wrong value; expected true; actual false",
            message(f));
        delete f;
    }
    
    try {
        int x = 4;
        int y = 5;
        CHECK_SAME(x, y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("y had wrong value; expected 4; actual 5", message(f));
        delete f;
    }
    
    try {
        string x("abc");
        string y("def");
        CHECK_SAME(x, y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("y had wrong value; expected abc; actual def",
            message(f));
        delete f;
    }
    
    try {
        string x("abc\nuvw");
        string y("def\nxyz");
        CHECK_SAME(x, y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME(
            "y had wrong value\nexpected:\nabc\nuvw\nactual:\ndef\nxyz\n",
            message(f));
        delete f;
    }

    try {
        string y("def");
        CHECK_SAME("abc", y);
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("y had wrong value; expected abc; actual def",
            message(f));
        delete f;
    }
    
    try {
        SKIP();
    }
    catch (exception* f) {
        CHECK_CONTAINS("test skipped", message(f));
    }
}

TEST(test, check_contains)
{
    CHECK_CONTAINS("abc", "now i've sung my abc's");
    
    try {
        CHECK_CONTAINS("abc", "row row row");
        FAIL("should have failed");
    }
    catch (exception* f) {
        CHECK_SAME("abc not found in row row row",
            message(f));
        delete f;
    }
}

TEST(test, calledfrom)
{
    Test::testlocation a("alpha", 18);
    CHECK_SAME("[alpha:18]", (string)a);
    
    {
        WHERE(a);
        Test::testlocation b("beta", 22, _called_from);
        CHECK_SAME("[beta:22]\n    from [alpha:18]", (string)b);
    }

    Test::testlocation c("gamma", 34);
    CHECK_SAME("[gamma:34]", (string)c);
    
    {
        WHERE(c);
        Test::testlocation d("delta", 42, _called_from);
        {
            WHERE(d);
            Test::testlocation e("epsilon", 55, _called_from);
            
            CHECK_SAME("[epsilon:55]\n    from [delta:42]\n    from [gamma:34]",
                (string)e);
        }
        
        Test::testlocation f("phi", 62, _called_from);
        CHECK_SAME("[phi:62]\n    from [gamma:34]",
            (string)f);
    }
}

#if 0
static TestGroupList tests(SL_SORTED | SL_DUPLICATES);
struct Test_airplanes_takeoff : test {
    Test_airplanes_takeoff()
        : test(tests, "airplanes", "takeoff", "Apr 6 2005 18:43:31") { }
    void run();
} test_airplanes_takeoff;
void Test_airplanes_takeoff::run()
{
    CHECK_SAME("thrust", "thrust");
}

TEST(test, runAll)
{
    pt::outmemory out;
    out.open();

    pt::runAll(out, tests, false, false);

    pt::string output = out.get_strdata();
    CHECK_SAME("Running all unit tests:\n"
"--------------------------------------------------\n"
"   airplanes: .\n"
"--------------------------------------------------\n"
"1 tests: 1 passed, 0 failed, 0 skipped\n"
        , output);
}
#endif
