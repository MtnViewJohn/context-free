// test.h
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

// A small test framework

#ifndef INCLUDED_TEST_H
#define INCLUDED_TEST_H

#include <iosfwd>
#include <string>

namespace Test {
	class testlocation {
	public:
		testlocation(const char* f, long l, int = 0);
		testlocation(const char* f, long l, const testlocation& t);		
		testlocation(const testlocation& o);
		
		operator std::string() const;
		void put(std::ostream&) const;

	private:
		testlocation& operator=(const testlocation& o);

		const char*         file;
		int                 line;
		const testlocation* from;
	};


	class test {
	public:
		test(const char* group, const char* name,
			const char* built = __DATE__ " " __TIME__);
		virtual void run() = 0;
		std::string name;
	protected:
		static const int _called_from = 0;
	};
	


	void pass(const testlocation& loc);
	
	void fail(const testlocation& loc,
				const std::string& message);

	void failsame(const testlocation& loc,
				const char* expectExpr, const char* actualExpr);
	
	void skip(const testlocation& loc);
	
	
	void failsame(const testlocation& loc,
				 const char* expectExpr, const std::string& expected,
				 const char* actualExpr, const std::string& actual);

	void fail_contains(const testlocation& loc, 
				const std::string& needle, 
				const std::string& haystack);

	template <typename T>
	std::string tostring(T)						{ return ""; }
	std::string tostring(const std::string& s);
	std::string tostring(int i);
	std::string tostring(bool b);
	
	template <typename TE, typename TA>
	void check_same(const testlocation& loc,
				 const char* expectExpr, TE expected,
				 const char* actualExpr, TA actual)
	{        
		if (actual != (TA)expected)
			failsame(loc,
				expectExpr, tostring((TA)expected),
				actualExpr, tostring(actual));
		else
			pass(loc);
	}

	void check_contains(const testlocation& loc,
		const char* needleExpr, const std::string& needle,
		const char* haystackExpr, const std::string& haystack);
			
	void check(const testlocation& loc,
					const char* expr, bool actual);
	
	
	bool runAll(
		bool reportPerGroup = false,
		bool stopOnFailingGroup = false);
		// returns true if passes all tests
}


#define TEST(group, name) \
    struct Test_##group##_##name : public ::Test::test { \
        Test_##group##_##name() : ::Test::test(#group, #name) { } \
        void run(); \
    } test_##group##_##name; \
    void Test_##group##_##name::run()


#define HERE    ::Test::testlocation(__FILE__, __LINE__, _called_from)
#define WHERE   const ::Test::testlocation& _called_from
#define THERE   _called_from


#define PASS() \
    ::Test::pass(HERE)
    
#define FAIL(message) \
    ::Test::fail(HERE, message)

#define SKIP() \
    ::Test::skip(HERE)
    
#define CHECK(cond) \
    ::Test::check(HERE, #cond, cond)

#define CHECK_MSG(cond, message) \
    ::Test::check(HERE, message, cond)

#define CHECK_SAME(v, e) \
    ::Test::check_same(HERE, #v, v, #e, e)

#define CHECK_CONTAINS(needle, haystack) \
    ::Test::check_contains(HERE, #needle, needle, #haystack, haystack)

#define CHECK_VALID(ptr) \
    CHECK((ptr) != 0)


#endif // INCLUDED_TEST_H
