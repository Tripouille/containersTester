#include "vector.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define SUBTITLE FG_RED << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE std::cout << RESET_ALL

class ThrowingExceptionClass
{
	public:
		ThrowingExceptionClass(void) : _a(2) {}
		ThrowingExceptionClass(int a) : _a(a) {}
		ThrowingExceptionClass(ThrowingExceptionClass const& other) {(void)other; throw std::exception();}
		~ThrowingExceptionClass() {}
		ThrowingExceptionClass & operator=(ThrowingExceptionClass const & other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};

class AllocatingClass
{
	public:
		AllocatingClass(void) {_array = new int[2];}
		AllocatingClass(AllocatingClass const & other) {(void)other; _array = new int[2];}
		~AllocatingClass() {delete[] _array;}
		AllocatingClass & operator=(AllocatingClass const & other) {(void)other; return (*this);}
	private:
		int* _array;
};

template<class T>
void
print_vector(T const & vector, std::string const & name)
{
	typename T::const_iterator begin = vector.begin();
	typename T::const_iterator end = vector.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin < end)
	{
		std::cout << *begin << " ";
		++begin;
	}
	std::cout << "] Size : " << vector.size()
	<< ", Capacity : " << vector.capacity() << ENDL;
}

template <template <class T, class Alloc = std::allocator<T> > class vec>
void
test_vector(void)
{
	FILE << TITLE << std::endl << "=> STARTING vector tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "vec<int> vectorA;" << ENDL; vec<int> vectorA;
	print_vector(vectorA, "vectorA");
	FILE << std::boolalpha << "vectorA.empty() : " << OUTPUT << vectorA.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "vec<int> vectorB(3, 2);" << ENDL; vec<int> vectorB(3, 2);
	print_vector(vectorB, "vectorB");
	FILE << std::boolalpha << "vectorB.empty() : " << OUTPUT << vectorB.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArrayA[] = {1, 2, 3, 4, 5};" << ENDL; int intArrayA[] = {1, 2, 3, 4, 5};
	FILE << "vec<int> vectorC(intArrayA, intArrayA + 5);" << ENDL; vec<int> vectorC(intArrayA, intArrayA + 5);
	print_vector(vectorC, "vectorC");
	FILE << std::boolalpha << "vectorC.empty() : " << OUTPUT << vectorC.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_vector(vectorC, "vectorC");
	FILE << "vector<int> vectorD(vectorC);" << ENDL; vec<int> vectorD(vectorC);
	print_vector(vectorC, "vectorC");
	print_vector(vectorD, "vectorD");
	FILE << ENDL;

	FILE << CATEGORY << "===> Destructor" << ENDL;
	FILE << "vec<AllocatingClass> allocatingVector(3);" << ENDL;
	vec<AllocatingClass> allocatingVector(3);
	FILE << ENDL;

	FILE << SUBTITLE << "Operator" << ENDL;
	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	FILE << "vectorB = vectorC;" << ENDL; vectorB = vectorC;
	print_vector(vectorB, "vectorB");
	FILE << "vectorB.push_back(6);" << ENDL; vectorB.push_back(6);
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	FILE << "vectorB = vectorC;" << ENDL; vectorB = vectorC;
	print_vector(vectorB, "vectorB");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	vectorA.clear();
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.begin() == vectorA.end() : " << OUTPUT << std::boolalpha << (vectorA.begin() == vectorA.end()) << ENDL;
	FILE << SUBCATEGORY << "(Pushing some values)" << ENDL;
	vectorA.push_back(1); vectorA.push_back(2); vectorA.push_back(3); vectorA.push_back(4);
	print_vector(vectorA, "vectorA");
	FILE << "vec<int>::iterator it = vectorA.begin();" << ENDL; typename vec<int>::iterator it = vectorA.begin();
	FILE << "vec<int>::iterator ite = vectorA.end();" << ENDL; typename vec<int>::iterator ite = vectorA.end();
	//FILE << "(*it == vectorA.front()) = " << OUTPUT << std::boolalpha << (*it == vectorA.front()) << ENDL;
	FILE << "it == vectorA.end() : " << OUTPUT << std::boolalpha << (it == vectorA.end()) << ENDL;
	FILE << "it != vectorA.end() : " << OUTPUT << std::boolalpha << (it != vectorA.end()) << ENDL;
	FILE << "it < ite : " << OUTPUT << std::boolalpha << (it < ite) << ENDL;
	FILE << "it <= ite : " << OUTPUT << std::boolalpha << (it <= ite) << ENDL;
	FILE << "it > ite : " << OUTPUT << std::boolalpha << (it > ite) << ENDL;
	FILE << "it >= ite : " << OUTPUT << std::boolalpha << (it >= ite) << ENDL;
	FILE << "it <= it : " << OUTPUT << std::boolalpha << (it <= it) << ENDL;
	FILE << "it >= it : " << OUTPUT << std::boolalpha << (it >= it) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		++it;
	}
	FILE << "it == vectorA.end() : " << OUTPUT << std::boolalpha << (it == vectorA.end()) << ENDL;
	FILE << "it != vectorA.end() : " << OUTPUT << std::boolalpha << (it != vectorA.end()) << ENDL;
	FILE << "it--;" << ENDL; it--;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "--it;" << ENDL; --it;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "it++;" << ENDL; it++;
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "--it; --it;" << ENDL; --it; --it;
	//FILE << "(*it == vectorA.back()) = " << OUTPUT << std::boolalpha << (*it == vectorA.back()) << ENDL;
	FILE << "*it = 42;" << ENDL; *it = 42;
	print_vector(vectorA, "vectorA");
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "*(it + 2) : " << OUTPUT << *(it + 2) << ENDL;
	FILE << "*(it - 1) : " << OUTPUT << *(it - 1) << ENDL;
	FILE << "*(2 + it) : " << OUTPUT << *(2 + it) << ENDL;
	FILE << "ite - it : " << OUTPUT << (ite - it) << ENDL;
	FILE << "*(it += 2) : " << OUTPUT << *(it += 2) << ENDL;
	FILE << "*(it -= 2) : " << OUTPUT << *(it -= 2) << ENDL;
	FILE << "(it += 42) = vectorA.begin();" << ENDL; (it += 42) = vectorA.begin();
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "(it -= 42) = --vectorA.end();" << ENDL; (it -= 42) = --vectorA.end();
	FILE << "*it : " << OUTPUT << *it << ENDL;
	FILE << "it[0] : " << OUTPUT << it[0] << ENDL;
	FILE << "it[0] = -1;" << ENDL; it[0] = -1;
	print_vector(vectorA, "vectorA");
	FILE << "it[-2] : " << OUTPUT << it[-2] << ENDL;
	FILE << "it[-2] = -2;" << ENDL; it[-2] = -2;
	print_vector(vectorA, "vectorA");
	FILE << "vec<int>::iterator const const_it = vectorA.begin();" << ENDL;
	typename vec<int>::iterator const const_it = vectorA.begin();
	FILE << "const_it[0] : " << OUTPUT << const_it[0] << ENDL;
	FILE << "const_it[2] : " << OUTPUT << const_it[2] << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Const Iterators" << ENDL;
	FILE << "vec<double> const constDoubleVec(1, 1);" << ENDL; vec<double> const constDoubleVec(1, 1);
	print_vector(constDoubleVec, "constDoubleVec");
	FILE << "const_iterator cit = constDoubleVec.begin();" << ENDL; typename vec<double>::const_iterator cit = constDoubleVec.begin();
	FILE << "const_iterator cite = constDoubleVec.end();" << ENDL; typename vec<double>::const_iterator cite = constDoubleVec.end();
	FILE << "cit - cite : " << OUTPUT << cit - cite << ENDL;
	FILE << "cite - cit : " << OUTPUT << cite - cit << ENDL;
	FILE << "*cit : " << OUTPUT << *cit << ENDL;
	FILE << "vec<double> doubleVec;" << ENDL; vec<double> doubleVec;
	print_vector(doubleVec, "doubleVec");
	FILE << "doubleVec.push_back(5);" << ENDL; doubleVec.push_back(5);
	FILE << "doubleVec.push_back(4);" << ENDL; doubleVec.push_back(4);
	FILE << "doubleVec.push_back(3);" << ENDL; doubleVec.push_back(3);
	print_vector(doubleVec, "doubleVec");
	FILE << "cit = doubleVec.begin();" << ENDL;cit = doubleVec.begin();
	FILE << "*cit : " << OUTPUT << *cit << ENDL;
	FILE << "*++cit : " << OUTPUT << *++cit << ENDL;
	FILE << "*--cit : " << OUTPUT << *--cit << ENDL;
	FILE << "*cit++ : " << OUTPUT << *cit++ << ENDL;
	FILE << "*cit-- : " << OUTPUT << *cit-- << ENDL;
	FILE << "*cit : " << OUTPUT << *cit << ENDL;
	FILE << "*(cit + 2) : " << OUTPUT << *(cit + 2) << ENDL;
	FILE << "*(2 + cit) : " << OUTPUT << *(2 + cit) << ENDL;
	FILE << "*++cit : " << OUTPUT << *++cit << ENDL;
	FILE << "*(cit - 1) : " << OUTPUT << *(cit - 1) << ENDL;
	FILE << "*--cit : " << OUTPUT << *--cit << ENDL;
	FILE << "*((cit += 2) = doubleVec.begin()): " << OUTPUT << *((cit += 2) = doubleVec.begin()) << ENDL;
	FILE << "*(cit += 2) : " << OUTPUT << *(cit += 2) << ENDL;
	FILE << "*((cit -= 2) = --doubleVec.end()): " << OUTPUT << *((cit -= 2) = --doubleVec.end()) << ENDL;
	FILE << "*(cit -= 2) : " << OUTPUT << *(cit -= 2) << ENDL;
	FILE << "cit[0] : " << OUTPUT << cit[0] << ENDL;
	FILE << "*++cit : " << OUTPUT << *++cit << ENDL;
	FILE << "cit[-1] : " << OUTPUT << cit[-1] << ENDL;
	FILE << "cit[0] : " << OUTPUT << cit[0] << ENDL;
	FILE << "cit[1] : " << OUTPUT << cit[1] << ENDL;
	#ifdef CONST_TEST
	cit[1] = 42;
	#endif
	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse Iterators" << ENDL;
	FILE << "vec<char>  charVec(1, 'A');" << ENDL; vec<char>  charVec(1, 'A');
	print_vector(charVec, "charVec");
	FILE << "reverse_iterator rit = charVec.rbegin();" << ENDL; typename vec<char>::reverse_iterator rit = charVec.rbegin();
	FILE << "reverse_iterator rite = charVec.rend();" << ENDL; typename vec<char>::reverse_iterator rite = charVec.rend();
	FILE << "rit - rite : " << OUTPUT << rit - rite << ENDL;
	FILE << "rite - rit : " << OUTPUT << rite - rit << ENDL;
	FILE << "(rite + (rit - rite)) == rit : " <<  std::boolalpha << OUTPUT << ((rite + (rit - rite)) == rit) << ENDL;
	FILE << "*rit : " << OUTPUT << *rit << ENDL;
	FILE << "charVec.push_back('B');" << ENDL; charVec.push_back('B');
	FILE << "charVec.push_back('C');" << ENDL; charVec.push_back('C');
	FILE << "charVec.push_back('D');" << ENDL; charVec.push_back('D');
	print_vector(charVec, "charVec");
	FILE << "rit = charVec.rbegin();" << ENDL;rit = charVec.rbegin();
	FILE << "*rit : " << OUTPUT << *rit << ENDL;
	FILE << "*++rit : " << OUTPUT << *++rit << ENDL;
	FILE << "*--rit : " << OUTPUT << *--rit << ENDL;
	FILE << "*rit++ : " << OUTPUT << *rit++ << ENDL;
	FILE << "*rit-- : " << OUTPUT << *rit-- << ENDL;
	FILE << "*rit : " << OUTPUT << *rit << ENDL;
	FILE << "*(rit + 2) : " << OUTPUT << *(rit + 2) << ENDL;
	FILE << "*(2 + rit) : " << OUTPUT << *(2 + rit) << ENDL;
	FILE << "*++rit : " << OUTPUT << *++rit << ENDL;
	FILE << "*(rit - 1) : " << OUTPUT << *(rit - 1) << ENDL;
	FILE << "*--rit : " << OUTPUT << *--rit << ENDL;
	FILE << "*((rit += 2) = charVec.rbegin()): " << OUTPUT << *((rit += 2) = charVec.rbegin()) << ENDL;
	FILE << "*(rit += 2) : " << OUTPUT << *(rit += 2) << ENDL;
	FILE << "*((rit -= 2) = --charVec.rend()): " << OUTPUT << *((rit -= 2) = --charVec.rend()) << ENDL;
	FILE << "*(rit -= 2) : " << OUTPUT << *(rit -= 2) << ENDL;
	FILE << "rit[0] : " << OUTPUT << rit[0] << ENDL;
	FILE << "*++rit : " << OUTPUT << *++rit << ENDL;
	FILE << "rit[-1] : " << OUTPUT << rit[-1] << ENDL;
	FILE << "rit[0] : " << OUTPUT << rit[0] << ENDL;
	FILE << "rit[1] : " << OUTPUT << rit[1] << ENDL;
	FILE << "rit[1] = 'Z';" << ENDL; rit[1] = 'Z';
	FILE << "rit[1] : " << OUTPUT << rit[1] << ENDL;
	print_vector(charVec, "charVec");
	FILE << ENDL;

	FILE << CATEGORY << "===> Const Reverse Iterators" << ENDL;
	FILE << "vec<char>  charVec(1, 'A');" << ENDL; vec<char>  charVec2(1, 'A');
	print_vector(charVec2, "charVec2");
	FILE << "reverse_iterator crit = charVec2.rbegin();" << ENDL; typename vec<char>::const_reverse_iterator crit = charVec2.rbegin();
	FILE << "reverse_iterator crite = charVec2.rend();" << ENDL; typename vec<char>::const_reverse_iterator crite = charVec2.rend();
	FILE << "crit - crite : " << OUTPUT << crit - crite << ENDL;
	FILE << "crite - crit : " << OUTPUT << crite - crit << ENDL;
	FILE << "(crite + (crit - crite)) == crit : " <<  std::boolalpha << OUTPUT << ((crite + (crit - crite)) == crit) << ENDL;
	FILE << "*crit : " << OUTPUT << *crit << ENDL;
	FILE << "charVec2.push_back('B');" << ENDL; charVec2.push_back('B');
	FILE << "charVec2.push_back('C');" << ENDL; charVec2.push_back('C');
	FILE << "charVec2.push_back('D');" << ENDL; charVec2.push_back('D');
	print_vector(charVec2, "charVec2");
	FILE << "crit = charVec2.rbegin();" << ENDL;crit = charVec2.rbegin();
	FILE << "*crit : " << OUTPUT << *crit << ENDL;
	FILE << "*++crit : " << OUTPUT << *++crit << ENDL;
	FILE << "*--crit : " << OUTPUT << *--crit << ENDL;
	FILE << "*crit++ : " << OUTPUT << *crit++ << ENDL;
	FILE << "*crit-- : " << OUTPUT << *crit-- << ENDL;
	FILE << "*crit : " << OUTPUT << *crit << ENDL;
	FILE << "*(crit + 2) : " << OUTPUT << *(crit + 2) << ENDL;
	FILE << "*(2 + crit) : " << OUTPUT << *(2 + crit) << ENDL;
	FILE << "*++crit : " << OUTPUT << *++crit << ENDL;
	FILE << "*(crit - 1) : " << OUTPUT << *(crit - 1) << ENDL;
	FILE << "*--crit : " << OUTPUT << *--crit << ENDL;
	FILE << "*((crit += 2) = charVec2.rbegin()): " << OUTPUT << *((crit += 2) = charVec2.rbegin()) << ENDL;
	FILE << "*(crit += 2) : " << OUTPUT << *(crit += 2) << ENDL;
	FILE << "*((crit -= 2) = --charVec2.rend()): " << OUTPUT << *((crit -= 2) = --charVec2.rend()) << ENDL;
	FILE << "*(crit -= 2) : " << OUTPUT << *(crit -= 2) << ENDL;
	FILE << "crit[0] : " << OUTPUT << crit[0] << ENDL;
	FILE << "*++crit : " << OUTPUT << *++crit << ENDL;
	FILE << "crit[-1] : " << OUTPUT << crit[-1] << ENDL;
	FILE << "crit[0] : " << OUTPUT << crit[0] << ENDL;
	FILE << "crit[1] : " << OUTPUT << crit[1] << ENDL;
	FILE << "crit[1] : " << OUTPUT << crit[1] << ENDL;
	FILE << "crit[1] : " << OUTPUT << crit[1] << ENDL;
	#ifdef CONST_TEST
	crit[1] = 42;
	#endif
	print_vector(charVec2, "charVec2");
	FILE << ENDL;

	FILE << SUBTITLE << "Capacity" << ENDL;
	FILE << CATEGORY << "===> max_size()" << ENDL;
	FILE << "vectorA.max_size() : " << OUTPUT << vectorA.max_size() << ENDL;
	FILE << CATEGORY << "===> resize()" << ENDL;
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(4);" << ENDL; vectorA.resize(4);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(3);" << ENDL; vectorA.resize(3);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(4);" << ENDL; vectorA.resize(4);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(5);" << ENDL; vectorA.resize(5);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(9, 1);" << ENDL; vectorA.resize(9, 1);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.resize(100);" << ENDL; vectorA.resize(100);
	print_vector(vectorA, "vectorA");
	//vectorA.resize(4611686018427387903); //bad_alloc exception, vector in valid state
	FILE << ENDL;
	FILE << CATEGORY << "===> reserve()" << ENDL;
	vectorA.clear();
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.reserve(0);" << ENDL; vectorA.reserve(0);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.reserve(150);" << ENDL; vectorA.reserve(150);
	print_vector(vectorA, "vectorA");
	FILE << "vectorA.reserve(400);" << ENDL; vectorA.reserve(400);
	print_vector(vectorA, "vectorA");
	FILE << ENDL;

	FILE << SUBTITLE << "Element access" << ENDL;
	FILE << CATEGORY << "===> operator[]" << ENDL;
	FILE << "vec<int> test(2, 1);" << ENDL; vec<int> test(2, 1);
	FILE << "test[0] : " << OUTPUT << test[0] << ENDL;
	FILE << "test[0] = 21;" << ENDL; test[0] = 21;
	FILE << "test[0] : " << OUTPUT << test[0] << ENDL;
	FILE << "test[1] = 7;" << ENDL; test[1] = 7;
	FILE << "test[1] : " << OUTPUT << test[1] << ENDL;
	FILE << "vec<int> const const_test(1, 42);" << ENDL; vec<int> const const_test(1, 42);
	FILE << "const_test[0] : " << OUTPUT << const_test[0] << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> at" << ENDL;
	FILE << "test.at(0) : " << OUTPUT << test.at(0) << ENDL;
	try
		{FILE << "test.at(42) : " << test.at(42) << ENDL;}
	catch (std::out_of_range const & e)
		{FILE << OUTPUT << e.what() << ENDL;}
	FILE << "const_test.at(0) : " << const_test.at(0) << ENDL;
	try
		{FILE << "const_test.at(-1) : " << const_test.at(static_cast<unsigned long>(-1)) << ENDL;}
	catch (std::out_of_range const & e)
		{FILE << OUTPUT << e.what() << ENDL;}
	FILE << ENDL;

	FILE << CATEGORY << "===> front" << ENDL;
	print_vector(charVec, "charVec");
	FILE << "vec<char> const constCharVec(charVec); " << ENDL; vec<char> const constCharVec(charVec);
	FILE << "charVec.front() = 'W';" << ENDL; charVec.front() = 'W';
	FILE << "charVec.front() : " << charVec.front() << ENDL;

	print_vector(constCharVec, "constCharVec");
	#ifdef CONST_TEST
		FILE << "constCharVec.front() = 'W';" << ENDL; constCharVec.front() = 'W';
	#endif
	FILE << "constCharVec.front() : " << constCharVec.front() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> back" << ENDL;
	print_vector(charVec, "charVec");
	FILE << "charVec.back() = 'O';" << ENDL; charVec.back() = 'O';
	FILE << "charVec.back() : " << charVec.back() << ENDL;

	print_vector(constCharVec, "constCharVec");
	#ifdef CONST_TEST
		FILE << "constCharVec.back() = 'P';" << ENDL; constCharVec.back() = 'P';
	#endif
	FILE << "constCharVec.back() : " << constCharVec.back() << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Modifiers" << ENDL;
	FILE << CATEGORY << "===> Exception-safety test with <ThrowingExceptionClass>, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "vec<ThrowingExceptionClass> vectorE;" << ENDL; vec<ThrowingExceptionClass> vectorE;
	FILE << "ThrowingExceptionClass testObject;" << ENDL; ThrowingExceptionClass testObject;
	FILE << "try {vectorE.push_back(testobject);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {vectorE.push_back(testObject);}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	FILE << "vectorE.size() = " << OUTPUT << vectorE.size() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> assign" << ENDL;
	FILE << SUBCATEGORY << "=====> fill (2)" << ENDL;
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.assign(7, 100);" << ENDL; vectorC.assign(7, 100);
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.clear(); vectorC.assign(7, 100);" << ENDL; vectorC.clear(); vectorC.assign(7, 100);
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << SUBCATEGORY << "=====> range (1)" << ENDL;
	print_vector(vectorB, "vectorB");
	FILE << "vectorC.assign(vectorB.rbegin(), vectorB.rend());" << ENDL; vectorC.assign(vectorB.rbegin(), vectorB.rend());
	print_vector(vectorC, "vectorC");
	FILE << "int myints[] = {1337, 4, 7};" << ENDL; int myints[] = {1337, 4, 7};
	FILE << "vectorC.assign(myints + 1, myints + 3);" << ENDL; vectorC.assign(myints + 1, myints + 3);
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.clear(); vectorC.assign(myints + 1, myints + 3);" << ENDL; vectorC.clear(); vectorC.assign(myints + 1, myints + 3);
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << CATEGORY << "===> push_back / pop_back" << ENDL;
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.push_back(9);" << ENDL; vectorC.push_back(9);
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.pop_back();" << ENDL; vectorC.pop_back();
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.pop_back();" << ENDL; vectorC.pop_back();
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.pop_back();" << ENDL; vectorC.pop_back();
	print_vector(vectorC, "vectorC");
	FILE << std::boolalpha << "vectorC.empty() : " << OUTPUT << vectorC.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> insert" << ENDL;
	FILE << "vec<int> vectorF;" << ENDL; vec<int> vectorF;
	print_vector(vectorF, "vectorF");
	FILE << "vectorF.insert(vectorF.end(), 1);" << ENDL; vectorF.insert(vectorF.end(), 1);
	print_vector(vectorF, "vectorF");
	print_vector(vectorC, "vectorC");
	FILE << "vectorC.insert(vectorC.end(), 1);" << ENDL; vectorC.insert(vectorC.end(), 1);
	print_vector(vectorC, "vectorC");
	print_vector(vectorD, "vectorD");
	FILE << "vectorD.insert(vectorD.end(), 6);" << ENDL; vectorD.insert(vectorD.end(), 6);
	print_vector(vectorD, "vectorD");
	FILE << "vectorD.insert(vectorD.begin(), 0);" << ENDL; vectorD.insert(vectorD.begin(), 0);
	print_vector(vectorD, "vectorD");
	FILE << "vec<int>::iterator insert_it = vectorD.begin() + 2;" << ENDL;
	typename vec<int>::iterator insert_it = vectorD.begin() + 2;
	FILE << "*insert_it : " << OUTPUT << *insert_it << ENDL;
	FILE << "vectorD.insert(vectorD.begin() + 4, 3);" << ENDL; vectorD.insert(vectorD.begin() + 4, 3);
	print_vector(vectorD, "vectorD");
	FILE << "*insert_it : " << OUTPUT << *insert_it << ENDL;
	FILE << "vectorD.insert(vectorD.begin(), 3, -1);" << ENDL; vectorD.insert(vectorD.begin(), 3, -1);
	print_vector(vectorD, "vectorD");
	FILE << "vectorD.insert(vectorD.end(), 0, 7);" << ENDL; vectorD.insert(vectorD.end(), 0, 7);
	print_vector(vectorD, "vectorD");
	FILE << "vectorD.insert(vectorD.end(), 1, 7);" << ENDL; vectorD.insert(vectorD.end(), 1, 7);
	print_vector(vectorD, "vectorD");
	FILE << ENDL;

	FILE << CATEGORY << "===> erase" << ENDL;
	FILE << SUBCATEGORY << "=====> single" << ENDL;
	FILE << "vec<int> v(vectorB)" << ENDL; vec<int> v(vectorB);
	print_vector(v, "v");
	FILE << "*v.erase(v.begin() + 1) : " << *v.erase(v.begin() + 1) << ENDL;
	print_vector(v, "v");
	FILE << "*v.erase(v.begin()) : " << *v.erase(v.begin()) << ENDL;
	print_vector(v, "v");
	FILE << "*v.erase(v.end() - 1) : " << *v.erase(v.end() - 1) << ENDL;
	print_vector(v, "v");
	FILE << SUBCATEGORY << "=====> range" << ENDL;
	FILE << "*v.erase(v.begin(), v.end()) : " << *v.erase(v.begin(), v.end()) << ENDL;
	print_vector(v, "v");
	FILE << "v = vectorB;" << ENDL; v = vectorB; print_vector(v, "v");
	FILE << "*v.erase(v.begin() + 1, v.end() - 1) : " << *v.erase(v.begin() + 1, v.end() - 1) << ENDL;
	print_vector(v, "v");
	FILE << "v = vectorB;" << ENDL; v = vectorB; print_vector(v, "v");
	FILE << "*v.erase(v.begin(), v.begin() + 2) : " << *v.erase(v.begin(), v.begin() + 2) << ENDL;
	print_vector(v, "v");
	FILE << "*v.erase(v.end() - 2, v.end()) : " << *v.erase(v.end() - 2, v.end()) << ENDL;
	print_vector(v, "v");
	FILE << ENDL;

	FILE << CATEGORY << "===> swap" << ENDL;
	print_vector(vectorA, "vectorA");
	print_vector(vectorB, "vectorB");
	FILE << "vectorA.swap(vectorB);" << ENDL; vectorA.swap(vectorB);
	print_vector(vectorA, "vectorA");
	print_vector(vectorB, "vectorB");
	print_vector(vectorC, "vectorC");
	print_vector(vectorD, "vectorD");
	FILE << "vectorC.swap(vectorD);" << ENDL; vectorC.swap(vectorD);
	print_vector(vectorC, "vectorC");
	print_vector(vectorD, "vectorD");
	FILE << ENDL;

	FILE << SUBTITLE << "Non-member function overloads" << ENDL;
	FILE << CATEGORY << "===> Relational operators" << ENDL;
	vectorA.clear(); vectorB.clear();
	print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorB.assign(2, 1); print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorA.assign(3, 1); print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorA.assign(2, 2); print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	*vectorA.begin() = 1; *(--vectorB.end()) = 3; print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorB.clear(); vectorB.push_back(-10); vectorB.push_back(-20);
	print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorA.push_back(3); vectorB.clear(); for (int i = 4; i <= 7; i++) vectorB.push_back(i);
	print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorA.push_back(4); vectorB.clear(); vectorB.push_back(42); vectorB.push_back(21); vectorB.push_back(10);
	print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	vectorA = vectorB;
	print_vector(vectorA, "vectorA"); print_vector(vectorB, "vectorB");
	FILE << "vectorA == vectorB : " << OUTPUT << std::boolalpha << (vectorA == vectorB) << ENDL;
	FILE << "vectorA != vectorB : " << OUTPUT << std::boolalpha << (vectorA != vectorB) << ENDL;
	FILE << "vectorA < vectorB : " << OUTPUT << std::boolalpha << (vectorA < vectorB) << ENDL;
	FILE << "vectorA > vectorB : " << OUTPUT << std::boolalpha << (vectorA > vectorB) << ENDL;
	FILE << "vectorA <= vectorB : " << OUTPUT << std::boolalpha << (vectorA <= vectorB) << ENDL;
	FILE << "vectorA >= vectorB : " << OUTPUT << std::boolalpha << (vectorA >= vectorB) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Swap" << ENDL;
	print_vector(vectorA, "vectorA");
	print_vector(vectorC, "vectorC");
	FILE << "swap(vectorA, vectorC);" << ENDL; swap(vectorA, vectorC);
	print_vector(vectorA, "vectorA");
	print_vector(vectorC, "vectorC");
	FILE << ENDL;

	FILE << TITLE << "=> ENDING vector tests" << ENDL << ENDL;
}

int
main(void)
{
    test_vector<ft::vector>();
}
