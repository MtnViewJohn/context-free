// test.cpp
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

#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>



#define SPIN 0
    // set to 1 if you want to see spinning characters during tests
    // only works if your output device supports backspace

namespace Test
{
	testlocation::testlocation(const char* f, long l, int)
		: file(f), line(l), from(0)
		{ }
	testlocation::testlocation(const char* f, long l, const testlocation& t)
		: file(f), line(l), from(&t)
		{ }
	
	testlocation::testlocation(const testlocation& o)
		: file(o.file), line(o.line), from(o.from)
		{ }

	testlocation&
	testlocation::operator=(const testlocation& o)
		{ file = o.file; line = o.line; from = o.from; return *this; }

	void
	testlocation::put(std::ostream& out) const
	{
		if (line >= 0) {
			out << "[" << file << ":" << line << "]";
		}
		else if (file) {
			out << "[" << file << ":-]";
		}
		else {
			out << "[-:-]";
		}
		
		if (from) {
			out << "\n    from ";
			from->put(out);
		}
	}

	testlocation::operator std::string() const
	{
		std::ostringstream out;
		put(out);
		return out.str();
	}

	class testfailure : public std::exception {
	public:
		testfailure(const testlocation& l, const std::string& m, bool fatal = true);
		testfailure(const std::string& m, bool fatal = true);
		~testfailure() throw();
		
		const char* what() const throw();

		operator std::string() const;
		void put(std::ostream&) const;

		bool isFatal() const                { return fatal; }
		
		void set_test_info(const std::string& group, const std::string& name);
		
		class list : public std::vector<testfailure*> {
		public:
			void dump(std::ostream& out);
		};

	private:
		std::string	message;
		std::string group;
		std::string name;
		std::string location;
		bool		fatal;
	};

	testfailure::testfailure(const testlocation& l, const std::string& m, bool f)
		: message(m), location(l), fatal(f)
		{ }
		
	testfailure::testfailure(const std::string& m, bool f)
		: message(m), fatal(f)
		{ }

	testfailure::~testfailure() throw()
		{ }
		
	const char*
	testfailure::what() const throw()
		{ return message.c_str(); }

	void
	testfailure::put(std::ostream& out) const
	{
		out << (fatal ? "***" : "---")
			<< " " << group
			<< ", " << name
			<< " " << location
			<< std::endl
			<< "    " << message
			<< std::endl;
	}

#if 0
	testfailure::operator std::string() const
	{
		std::ostringstream out;
		put(out);
		return out.str();
	}
#endif

	void
	testfailure::set_test_info(const std::string& g, const std::string& n)
	{
		group = g;
		name = n;
	}

	void
	testfailure::list::dump(std::ostream& out)
	{
		if (empty())
			return;
		
		out << std::endl;
		for (const_iterator i = begin(); i != end(); ++i)
			(*i)->put(out);
		out << std::endl;
		clear();
	}


	typedef std::vector<test*> TestList;

	struct TestGroup {
		std::string name;
		TestList    list;
		
		TestGroup(const char* n) : name(n) { }
	};

	typedef std::map<std::string, TestGroup*> TestMap;

	TestMap&
	registry()
	{
		/* This trick is to ensure that this global is constructed before
		   it is used.
		   See C++ FAQ Lite, sections 10.11 through 10.13
		*/
		
		static TestMap* r = new TestMap;
		return *r;
	}

	test::test(const char* group, const char* n, const char* built)
		: name(n)
	{
		std::string key;
		struct tm timeInfo;
		
		if (built  &&  strptime(built, "%b %d %Y %H:%M:%S", &timeInfo)) {
			char buf[20];
			strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &timeInfo);
			key = buf;
		}
		else {
			key = "00000000000000";
		}
		
		key += group;

		TestMap& r = registry();
		TestMap::iterator i = r.find(key);
		if (i == r.end()) {
			r[key] = new TestGroup(group);
		}

		r[key]->list.push_back(this);
	}

	bool anyPasses;

	void
	pass(const testlocation& loc)
	{
		anyPasses = true;
		
		if (SPIN) {
			static int          seqIndex = 0;
			static const char   seqChars[] = { '-', '\\', '|', '/' };
			static const int    seqLength = sizeof(seqChars) / sizeof(seqChars[0]);
			
			std::cout << '\010'   // backspace
				 << seqChars[seqIndex];
			seqIndex = (seqIndex + 1) % seqLength;
		}
	}

	void
	fail(const testlocation& loc, const std::string& message)
		{ throw new testfailure(loc, message); }

	namespace {
		bool
		longstr(const std::string& s) {
			return s.size() > 20 || s.find('\n') != std::string::npos;
		}
	};

	void
	failsame(const testlocation& loc,
					 const char* expectExpr, const std::string& expected,
					 const char* actualExpr, const std::string& actual)
	{
		bool longmsg = longstr(expected) || longstr(actual);
		
		bool noconv = expected.empty() && actual.empty();
			// if both value strings are empty, then there was no conversion
			// to string available, just show the expectedExpr
			
		std::ostringstream message;
		message << actualExpr
				<< " had wrong value";
		if (noconv) {
			message << "; expected "
					<< expectExpr;
		}
		else {
			message << (longmsg ? "\nexpected:\n" : "; expected ")
					<< expected
					<< (longmsg ? "\nactual:\n" : "; actual ")
					<< actual
					<< (longmsg ? "\n" : "");
		}
		
		fail(loc, message.str());
	}

	void
	fail_contains(const testlocation& loc,
		const std::string& needle, const std::string& haystack)
	{
		if (longstr(haystack) || longstr(needle))
			fail(loc,
				"needle:\n" + needle +
				"\nnot found in haystack:\n" + haystack +
				"\n");
		else
			fail(loc, needle + " not found in " + haystack);
	}

	std::string
	tostring(bool b)
		{ return b ? "true" : "false"; }

	std::string
	tostring(const std::string& s)
		{ return s; }

	std::string
	tostring(int i)
		{ std::ostringstream o; o << i; return o.str(); }

	void
	skip(const testlocation& loc)
		{ throw new testfailure(loc, "test skipped", false); }


	void check_contains(const testlocation& loc,
		const char* needleExpr, const std::string& needle,
		const char* haystackExpr, const std::string& haystack)
	{
		if (haystack.find(needle) == std::string::npos)
			fail_contains(loc, needle, haystack);
		else
			pass(loc);
	}
	
	void check(const testlocation& loc,
					const char* expr, bool actual)
		{ if (!actual) fail(loc, expr); else pass(loc); }

	bool
	runAll(bool reportPerGroup, bool stopOnFailingGroup)
	{
		testfailure::list failures;
		int testCount = 0;
		int passCount = 0;
		int failCount = 0;
		int skipCount = 0;

		std::cout <<
			  "Running all unit tests:\n"
			  "--------------------------------------------------\n";

		TestMap& r = registry();
		for (TestMap::const_iterator i = r.begin(); i != r.end(); ++i) {
			TestGroup& group = *i->second;

			std::cout << std::setw(12) << group.name;

			TestList& l = group.list;
			for (TestList::const_iterator j = l.begin(); j != l.end(); ++j) {
				test& t = **j;

				testfailure* failure = 0;
				anyPasses = false;

				if (SPIN) std::cout << ' ';


				try {
					t.run();
				}
				catch (testfailure* f) {
					failure = f;
				}
				catch (std::exception* e) {
					failure = new testfailure(e->what());
					delete e;
				}
				catch (const std::string& s) {
					failure = new testfailure(s);
				}
				catch (...) {
					failure = new testfailure("threw an uncaught exception");
				}

				if (!failure && anyPasses == 0) {
					failure = new testfailure("test skipped", false);
				}


				if (SPIN) std::cout << '\010';

				if (failure) {
					failure->set_test_info(group.name, t.name);
					failures.push_back(failure);
					if (failure->isFatal()) {
						std::cout << '*';
						failCount += 1;
					}
					else {
						std::cout << '-';
						skipCount += 1;
					}
				}
				else if (anyPasses) {
					std::cout << '.';
					passCount += 1;
				}

				testCount += 1;
			}
			std::cout << std::endl;

			if (reportPerGroup)
				failures.dump(std::cout);
			if (stopOnFailingGroup && failCount > 0)
				break;
		}

		std::cout << "--------------------------------------------------\n"
				<< testCount << " tests: "
				<< passCount << " passed, "
				<< failCount << " failed, "
				<< skipCount << " skipped\n";

		failures.dump(std::cout);

		return failCount == 0;
	}
}
