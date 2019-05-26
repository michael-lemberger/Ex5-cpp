#include <sstream>
#include <iostream>
#include <sstream>
#include "badkan.hpp"
#include "range.hpp"
#include "chain.hpp"
#include "zip.hpp"
#include "product.hpp"
#include "powerset.hpp"
using namespace std;
using namespace itertools;

template<typename Iterable>
string iterable_to_string(const Iterable& iterable) {
	ostringstream ostr;
	for (decltype(*iterable.begin()) i : iterable){
		ostr << i << ",";
	}
	return ostr.str();
}

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		ostringstream stream;
		
		testcase.setname("range-test");
		for (int i: range(5,9))
			stream << i;
		testcase.CHECK_OUTPUT(stream.str(),"5678");
		stream.str("");
		for (double i: range(5.2,9.2))
			stream << i << " ";
		testcase.CHECK_EQUAL(stream.str(),string("5.2 6.2 7.2 8.2 "));
		stream.str("");
		for (char i: range('a','d'))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"a b c ");
		stream.str("");
		for (char i: range(':','?'))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),": ; < = > ");
		stream.str("");
		for (char i: range(':',':'))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"");
		stream.str("");
		for (char i: range(6,6))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"");
		stream.str("");

	
	
		testcase.setname("chin-test");
		for (auto i: chain(range(1,4),range(5,9)))
			stream << i;
		testcase.CHECK_OUTPUT(stream.str(),"1235678");
		stream.str("");
		for (auto i: chain(range('a','d'),string("hello"))) 
			stream <<i;
		testcase.CHECK_OUTPUT(stream.str(),"abchello");	
		stream.str("");
		for (auto i: chain(range(':','?'),string("hello")))
			stream <<i;
		testcase.CHECK_OUTPUT(stream.str(),":;<=>hello");
		stream.str("");
		for (auto i: chain(range(1,4),range(5,5)))
			stream << i;
		testcase.CHECK_OUTPUT(stream.str(),"123");
		stream.str("");
		for (auto i: chain(range(4,4),range(5,9)))
			stream << i;
		testcase.CHECK_OUTPUT(stream.str(),"5678");
		stream.str("");
		
		
		
		testcase.setname("zip-test");
		for (auto i: zip(range(1,6),string("hello")))
			stream << i << " ";			
		testcase.CHECK_OUTPUT(stream.str(),"1,h 2,e 3,l 4,l 5,o ");
		stream.str("");
		for (auto i: zip(chain(range(':','?'),string("hello")),range(0,10)))
			stream << i << " ";	
		testcase.CHECK_OUTPUT(stream.str(),":,0 ;,1 <,2 =,3 >,4 h,5 e,6 l,7 l,8 o,9 ");
		stream.str("");
		for (auto i: zip(range(-9,-5),range(5,9)))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"-9,5 -8,6 -7,7 -6,8 ");
		stream.str("");
		for (auto i: zip(range(-9,-5),range(5.5,9.5)))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"-9,5.5 -8,6.5 -7,7.5 -6,8.5 ");
		stream.str("");
				for (auto i: zip(zip(range(1,6),string("hello")),zip(range(-9,-4),range(5,10))))
			stream << i << " ";	
		testcase.CHECK_OUTPUT(stream.str(),"1,h,-9,5 2,e,-8,6 3,l,-7,7 4,l,-6,8 5,o,-5,9 ");
		stream.str("");



		testcase.setname("product-test");
		for (auto i: product(range(1,4),string("helo")))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"1,h 1,e 1,l 1,o 2,h 2,e 2,l 2,o 3,h 3,e 3,l 3,o ");
		stream.str("");
		for (auto i: product(range('a','c'),chain(range(1,4),range(0,2))))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"a,1 a,2 a,3 a,0 a,1 b,1 b,2 b,3 b,0 b,1 ");
		stream.str("");
		for (auto i: product(range(':','<'),zip(string("hlool"),string("elwrd"))))
			stream << i << " "; 
		testcase.CHECK_OUTPUT(stream.str(),":,h,e :,l,l :,o,w :,o,r :,l,d ;,h,e ;,l,l ;,o,w ;,o,r ;,l,d ");
		stream.str("");
		for (auto i: product(product(string("helo"),range(1,2)),product(string("helo"),range(3,4))))
			stream << i << " ";
		testcase.CHECK_OUTPUT(stream.str(),"h,1,h,3 h,1,e,3 h,1,l,3 h,1,o,3 e,1,h,3 e,1,e,3 e,1,l,3 e,1,o,3 l,1,h,3 l,1,e,3 l,1,l,3 l,1,o,3 o,1,h,3 o,1,e,3 o,1,l,3 o,1,o,3 ");
		stream.str("");		

		
		testcase.setname("powerset-test");
		for (auto i: powerset(string("abc")))
			stream << i << " "; 
		testcase.CHECK_OUTPUT(iterable_to_string(powerset(string("abc"))),"{},{a},{b},{a,b},{c},{a,c},{b,c},{a,b,c},");
		stream.str("");
		for (auto i: powerset(chain(range(1,3),range('S','U'))))
			stream << i << " "; 
		testcase.CHECK_OUTPUT(stream.str(),"{},{1},{2},{1,2},{S},{1,S},{2,S},{T},{1,T},{2,T},{S,T},{1,2,S},{1,2,T},{1,S,T},{2,S,T},{1,2,S,T}");
		stream.str("");

		
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	if(grade>95)
	cout<< "Your grade is: "<<grade<<" great! :-)"<<endl;
	else
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

