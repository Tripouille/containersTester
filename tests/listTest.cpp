#include "list.hpp"
#include "myAllocator.hpp"
#include <list>
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

class NoDefaultConstructorClass
{
	public:
		NoDefaultConstructorClass(int a) : _a(a) {}
		NoDefaultConstructorClass(NoDefaultConstructorClass const& other) : _a(other._a) {}
		~NoDefaultConstructorClass() {}
		NoDefaultConstructorClass & operator=(NoDefaultConstructorClass const & other) {_a = other._a; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
		NoDefaultConstructorClass(void) {}
};
std::ostream&	operator<<(std::ostream& os, NoDefaultConstructorClass const& obj) {os << obj.geta(); return (os);}

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

struct intStruct
{
	int a;
	intStruct(int n = 0) : a(n) {}
};
std::ostream&	operator<<(std::ostream& os, intStruct const& obj) {os << obj.a; return (os);}

template<class T>
void
print_list(T list, std::string const & name)
{
	typename T::iterator begin = list.begin();
	typename T::iterator end = list.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
			std::cout << *begin << " ";
			++begin;
	}
	std::cout << "] Size = " << list.size() << ENDL;
}

template <class T>
T
inc_iterator(T it, long n = 1)
{
	if (n < 0)
		while (n++ < 0)
			--it;
	else
		while (n-- > 0)
			++it;
	return (it);
}

bool single_digit(const int & value) {return (value < 10);}
struct is_odd
{
	bool operator()(const int & value) {return (value % 2 == 1);}
};
bool same_integral_part(double first, double second) {return (int(first) == int(second));}
bool comp_integral_part(double first, double second) {return (int(first) < int(second));}

//template <template <class T, class Alloc = std::allocator<T> > class containerT>
template <template <class T, class Alloc = myAllocator<T> > class containerT>
void
test_list(void)
{
	FILE << TITLE << std::endl << "=> STARTING list tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "list<int> listA;" << ENDL; containerT<int> listA;
	print_list(listA, "listA");
	FILE << "listA.max_size() = " << OUTPUT << listA.max_size() << ENDL;
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Fill constructor" << ENDL;
	FILE << "list<int> listB(4, -1);" << ENDL; containerT<int> listB(4, -1);
	print_list(listB, "listB");
	FILE << std::boolalpha << "listB.empty() = " << OUTPUT << listB.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "int intArray[] = {1, 2, 3, 4, 5};" << ENDL; int intArray[] = {1, 2, 3, 4, 5};
	containerT<int> listC(intArray, intArray + 5);
	print_list(listC, "listC");
	FILE << std::boolalpha << "listC.empty() = " << OUTPUT << listC.empty() << ENDL;
	FILE << "listC.front() = " << OUTPUT << listC.front() << ENDL;
	FILE << "listC.back() = " << OUTPUT << listC.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Destructor" << ENDL;
	FILE << "list<AllocatingClass> allocatingList(3);" << ENDL;
	containerT<AllocatingClass> allocatingList(3);
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_list(listC, "listC");
	FILE << "list<int> listD(listC);" << ENDL; containerT<int> listD(listC);
	print_list(listC, "listC");
	print_list(listD, "listD");
	FILE << ENDL;

	FILE << SUBTITLE << "Operator" << ENDL;
	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_list(listB, "listB");
	print_list(listC, "listC");
	FILE << "listB = listC;" << ENDL; listB = listC;
	print_list(listB, "listB");
	FILE << "listB.push_front(0);" << ENDL; listB.push_front(0);
	print_list(listB, "listB");
	print_list(listC, "listC");
	FILE << ENDL;

	FILE << SUBTITLE << "Basic modifiers" << ENDL;
	FILE << CATEGORY << "===> Basic tests with <int>" << ENDL;
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listA.push_front(2);" << ENDL; listA.push_front(2);
	print_list(listA, "listA");
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.push_front(1);" << ENDL; listA.push_front(1);
	print_list(listA, "listA");
	FILE << std::boolalpha << "listA.empty() = " << OUTPUT << listA.empty() << ENDL;
	FILE << "listA.push_back(3);" << ENDL; listA.push_back(3);
	print_list(listA, "listA");
	FILE << "listA.push_back(4);" << ENDL; listA.push_back(4);
	FILE << "listA.push_back(5);" << ENDL; listA.push_back(5);
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "=====> Popping" << ENDL;
	FILE << "listA.pop_front();" << ENDL; listA.pop_front();
	print_list(listA, "listA");
	FILE << "listA.pop_back();" << ENDL; listA.pop_back();
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listA.front() = " << OUTPUT << listA.front() << ENDL;
	FILE << "listA.back() = " << OUTPUT << listA.back() << ENDL;
	FILE << "listA.back() = 9;" << ENDL; listA.back() = 9;
	print_list(listA, "listA");
	FILE << "listA.front() = -9;" << ENDL; listA.front() = -9;
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <int> const list" << ENDL;
	FILE << "list<int> const listE(3, -2);" << ENDL; containerT<int> const listE(3, -2);
	print_list(listE, "listE");
	FILE << std::boolalpha << "listE.empty() = " << OUTPUT << listE.empty() << ENDL;
	FILE << "listE.front() = " << OUTPUT << listE.front() << ENDL;
	FILE << "listE.back() = " << OUTPUT << listE.back() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Basic tests with <NoDefaultConstructorClass>" << ENDL;
	FILE << SUBCATEGORY << "=====> Empty list" << ENDL;
	FILE << "list<NoDefaultConstructorClass> listF;" << ENDL; containerT<NoDefaultConstructorClass> listF;
	print_list(listF, "listF");
	FILE << "listF.max_size() = " << OUTPUT << listF.max_size() << ENDL;
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << SUBCATEGORY << "=====> Pushing" << ENDL;
	FILE << "listF.push_front(NoDefaultConstructorClass(2));" << ENDL; listF.push_front(NoDefaultConstructorClass(2));
	print_list(listF, "listF");
	FILE << "listF.push_front(NoDefaultConstructorClass(1));" << ENDL; listF.push_front(NoDefaultConstructorClass(1));
	print_list(listF, "listF");
	FILE << std::boolalpha << "listF.empty() = " << OUTPUT << listF.empty() << ENDL;
	FILE << "listF.push_back(NoDefaultConstructorClass(3));" << ENDL; listF.push_back(NoDefaultConstructorClass(3));
	print_list(listF, "listF");
	FILE << "listF.push_back(NoDefaultConstructorClass(4));" << ENDL; listF.push_back(NoDefaultConstructorClass(4));
	print_list(listF, "listF");
	FILE << SUBCATEGORY << "=====> Front and back" << ENDL;
	FILE << "listF.front() = NoDefaultConstructorClass(-9);" << ENDL; listF.front() = NoDefaultConstructorClass(-9);
	FILE << "listF.back() = NoDefaultConstructorClass(9);" << ENDL; listF.back() = NoDefaultConstructorClass(9);
	print_list(listF, "listF");
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with <ThrowingExceptionClass>, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "list<ThrowingExceptionClass> listG;" << ENDL; containerT<ThrowingExceptionClass> listG;
	FILE << "ThrowingExceptionClass testObject;" << ENDL; ThrowingExceptionClass testObject;
	FILE << "try {listG.push_back(testobject);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {listG.push_back(testObject);}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	FILE << "listG.size() = " << OUTPUT << listG.size() << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	listA.clear();
	print_list(listA, "listA");
	FILE << "listA.begin() == listA.end() : " << OUTPUT << std::boolalpha << (listA.begin() == listA.end()) << ENDL;
	FILE << SUBCATEGORY << "(Pushing some values)" << ENDL;
	listA.push_back(1); listA.push_back(2); listA.push_back(3);
	print_list(listA, "listA");
	FILE << "list<int>::iterator it = listA.begin();" << ENDL; typename containerT<int>::iterator it = listA.begin();
	FILE << "list<int>::iterator ite = listA.end();" << ENDL; typename containerT<int>::iterator ite = listA.end();
	FILE << "(*it == listA.front()) = " << OUTPUT << std::boolalpha << (*it == listA.front()) << ENDL;
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "*it = " << OUTPUT << *it << ENDL;
		it++;
	}
	FILE << "it--;" << ENDL; it--;
	FILE << "(*it == listA.back()) = " << OUTPUT << std::boolalpha << (*it == listA.back()) << ENDL;
	FILE << "*it = 42;" << ENDL; *it = 42;
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Const iterators" << ENDL;
	FILE << "list<int>::const_iterator c_it = listA.begin();" << ENDL; typename containerT<int>::const_iterator c_it = listA.begin();
	FILE << "list<int>::const_iterator c_ite = listA.end();" << ENDL; typename containerT<int>::const_iterator c_ite = listA.end();
	FILE << "(*c_it == listA.front()) = " << OUTPUT << std::boolalpha << (*c_it == listA.front()) << ENDL;
	FILE << "while (c_it != c_ite) {...; c_it++;}" << ENDL;
	while (c_it != c_ite)
	{
		FILE << "*c_it = " << OUTPUT << *c_it << ENDL;
		c_it++;
	}
	FILE << "c_it--;" << ENDL; c_it--;
	FILE << "(*c_it == listA.back()) = " << OUTPUT << std::boolalpha << (*c_it == listA.back()) << ENDL;
	#ifdef CONST_TEST
	*c_it = 42;
	#endif
	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse iterators" << ENDL;
	FILE << "list<int>::reverse_iterator r_it = listA.rbegin();" << ENDL; typename containerT<int>::reverse_iterator r_it = listA.rbegin();
	FILE << "list<int>::reverse_iterator r_ite = listA.rend();" << ENDL; typename containerT<int>::reverse_iterator r_ite = listA.rend();
	FILE << "while (r_it != r_ite) {...; r_it++;}" << ENDL;
	while (r_it != r_ite)
	{
		FILE << "*r_it = " << OUTPUT << *r_it << ENDL;
		r_it++;
	}
	FILE << "r_it--;" << ENDL; r_it--;
	FILE << "(*r_it == listA.front()) = " << OUTPUT << std::boolalpha << (*r_it == listA.front()) << ENDL;
	FILE << "*r_it = -42;" << ENDL; *r_it = -42;;
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Const reverse iterators" << ENDL;
	FILE << "list<int>::const_reverse_iterator cr_it = listA.rbegin();" << ENDL; typename containerT<int>::const_reverse_iterator cr_it = listA.rbegin();
	FILE << "list<int>::const_reverse_iterator cr_ite = listA.rend();" << ENDL; typename containerT<int>::const_reverse_iterator cr_ite = listA.rend();
	FILE << "while (cr_it != cr_ite) {...; cr_it++;}" << ENDL;
	while (cr_it != cr_ite)
	{
		FILE << "*cr_it = " << OUTPUT << *cr_it << ENDL;
		cr_it++;
	}
	FILE << "cr_it--;" << ENDL; cr_it--;
	FILE << "(*cr_it == listA.front()) = " << OUTPUT << std::boolalpha << (*cr_it == listA.front()) << ENDL;
	#ifdef CONST_TEST
	*cr_it = 42;
	#endif
	FILE << ENDL;

	FILE << CATEGORY << "===> Operator-> on iterators" << ENDL;
	FILE << "list<intStruct> listH;" << ENDL; containerT<intStruct> listH;
	FILE << "listH.push_back(intStruct(1));" << ENDL; listH.push_back(intStruct(1));
	FILE << "listH.push_back(intStruct(2));" << ENDL; listH.push_back(intStruct(2));
	print_list(listH, "listH");
	FILE << "list<intStruct>::iterator structIt = listH.begin();" << ENDL;
	typename containerT<intStruct>::iterator structIt = listH.begin();
	FILE << "structIt++;" << ENDL; structIt++;
	FILE << "structIt->a = " << OUTPUT << structIt->a << ENDL;
	FILE << "list<intStruct>::const_iterator c_structIt = listH.begin();" << ENDL;
	typename containerT<intStruct>::const_iterator c_structIt = listH.begin();
	FILE << "c_structIt++;" << ENDL; c_structIt++;
	FILE << "c_structIt->a = " << OUTPUT << c_structIt->a << ENDL;
	FILE << "list<intStruct>::reverse_iterator r_structIt = listH.rbegin();" << ENDL;
	typename containerT<intStruct>::reverse_iterator r_structIt = listH.rbegin();
	FILE << "r_structIt++;" << ENDL; r_structIt++;
	FILE << "r_structIt->a = " << OUTPUT << r_structIt->a << ENDL;
	FILE << "list<intStruct>::const_reverse_iterator cr_structIt = listH.rbegin();" << ENDL;
	typename containerT<intStruct>::const_reverse_iterator cr_structIt = listH.rbegin();
	FILE << "cr_structIt++;" << ENDL; cr_structIt++;
	FILE << "cr_structIt->a = " << OUTPUT << cr_structIt->a << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Modifiers" << ENDL;
	FILE << CATEGORY << "===> Assign" << ENDL;
	FILE << SUBCATEGORY << "=====> fill (2)" << ENDL;
	print_list(listA, "listA");
	FILE << "listA.assign(7, 100);" << ENDL; listA.assign(7, 100);
	print_list(listA, "listA");
	FILE << "listA.clear(); listA.assign(7, 100);" << ENDL; listA.clear(); listA.assign(7, 100);
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "=====> range (1)" << ENDL;
	print_list(listB, "listB");
	FILE << "listA.assign(listB.rbegin(), listB.rend());" << ENDL; listA.assign(listB.rbegin(), listB.rend());
	print_list(listA, "listA");
	FILE << "int myints[] = {1337, 4, 7};" << ENDL; int myints[] = {1337, 4, 7};
	FILE << "listA.assign(myints + 1, myints + 3);" << ENDL; listA.assign(myints + 1, myints + 3);
	print_list(listA, "listA");
	FILE << "listA.clear(); listA.assign(myints + 1, myints + 3);" << ENDL; listA.clear(); listA.assign(myints + 1, myints + 3);
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Insert" << ENDL;
	FILE << SUBCATEGORY << "=====> insert single element (1)" << ENDL;
	listA.clear(); print_list(listA, "listA");
	FILE << "it = listA.begin();" << SUBCATEGORY << " (points to begin() = end())" << ENDL; it = listA.begin();
	FILE << "it = listA.insert(it, 1);" << ENDL; it = listA.insert(it, 1);
	FILE << "*it = " << OUTPUT << *it << ENDL;
	print_list(listA, "listA");
	print_list(listC, "listC");
	FILE << "it = listC.begin(); ++it;" << SUBCATEGORY << " (points to 2)" << ENDL; it = listC.begin(); ++it;
	FILE << "it = listC.insert(it, 10);" << ENDL; it = listC.insert(it, 10);
	FILE << "*it = " << OUTPUT << *it << ENDL;
	print_list(listC, "listC");
	FILE << "it = listC.begin();" << SUBCATEGORY << " (points now to number 1)" << ENDL; it = listC.begin();
	FILE << "it = listC.insert(it, 0);" << ENDL; it = listC.insert(it, 0);
	FILE << "*it = " << OUTPUT << *it << ENDL;
	print_list(listC, "listC");
	FILE << "it = --listC.end();" << SUBCATEGORY << " (points now to number 5)" << ENDL; it = --listC.end();
	FILE << "it = listC.insert(it, 20);" << ENDL; it = listC.insert(it, 20);
	FILE << "*it = " << OUTPUT << *it << ENDL;
	print_list(listC, "listC");
	FILE << "it = listC.end();" << SUBCATEGORY << " (points now to end(), after 5)" << ENDL; it = listC.end();
	FILE << "it = listC.insert(it, 6);" << ENDL; it = listC.insert(it, 6);
	FILE << "*it = " << OUTPUT << *it << ENDL;
	print_list(listC, "listC");
	FILE << SUBCATEGORY << "=====> insert fill (2)" << ENDL;
	FILE << SUBCATEGORY << "(it still points on end() of listC)" << ENDL;
	FILE << "listC.insert(it, 3, 7);" << ENDL; listC.insert(it, 3, 7);
	print_list(listC, "listC");
	FILE << "it = listC.begin();" << SUBCATEGORY << " (points now to number 0)" << ENDL; it = listC.begin();
	FILE << "listC.insert(it, 2, -1);" << ENDL; listC.insert(it, 2, -1);
	print_list(listC, "listC");
	FILE << "listC.clear(); it = listC.begin();" << ENDL; listC.clear(); print_list(listC, "listC"); it = listC.begin();
	FILE << "listC.insert(it, 4, 0);" << ENDL; listC.insert(it, 4, 0); print_list(listC, "listC");
	FILE << SUBCATEGORY << "=====> insert range (3)" << ENDL;
	FILE << "listC.clear(); it = listC.begin();" << ENDL; listC.clear(); it = listC.begin(); print_list(listC, "listC"); 
	FILE << "int myints[] = {1337, 4, 7};" << ENDL;
	FILE << "listC.insert(it, myints + 1, myints + 3);" << ENDL; listC.insert(it, myints + 1, myints + 3); print_list(listC, "listC");
	FILE << "listC.insert(it, myints, myints + 3);" << ENDL; listC.insert(it, myints, myints + 3); print_list(listC, "listC");
	FILE << ENDL;

	FILE << CATEGORY << "===> Erase" << ENDL;
	FILE << SUBCATEGORY << "=====> erase(iterator position)" << ENDL;
	print_list(listC, "listC");
	FILE << "it = listC.begin(); it = listC.erase(it);" << ENDL; it = listC.begin(); it = listC.erase(it);
	print_list(listC, "listC");
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << "it = --listC.end(); it = listC.erase(it);" << ENDL; it = --listC.end(); it = listC.erase(it);
	print_list(listC, "listC");
	FILE << "it = ++listC.begin(); listC.erase(it);" << ENDL; it = ++listC.begin(); it = listC.erase(it);
	print_list(listC, "listC");
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << SUBCATEGORY << "=====> erase(iterator first, iterator last)" << ENDL;
	print_list(listB, "listB");
	FILE << "it = listB.begin(); ite = listB.end();" << ENDL; it = listB.begin(); ite = listB.end();
	FILE << "it = listB.erase(it, ite);" << ENDL; it = listB.erase(it, ite);
	print_list(listB, "listB");
	FILE << SUBCATEGORY << "(pushing some values)" << ENDL;
	listB.push_back(0); listB.push_back(1); listB.push_back(2); listB.push_back(3); listB.push_back(4); listB.push_back(5); 
	print_list(listB, "listB");
	FILE << "it = ++listB.begin(); ite = inc_iterator(listB.end(), -2);" << ENDL; it = ++listB.begin(); ite = inc_iterator(listB.end(), -2);
	FILE << "it = listB.erase(it, ite);" << ENDL; it = listB.erase(it, ite);
	print_list(listB, "listB");
	FILE << "*it = " << OUTPUT << *it << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Swap" << ENDL;
	print_list(listA, "listA");
	listB.pop_back(); listB.push_back(1); listB.push_back(2); listB.push_back(3); listB.push_back(4); listB.push_back(5); 
	print_list(listB, "listB");
	FILE << "listA.swap(listB);" << ENDL; listA.swap(listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listA.swap(listB);" << ENDL; listA.swap(listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listA.clear(); listA.swap(listB);" << ENDL; listA.clear(); listA.swap(listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listA.swap(listB);" << ENDL; listA.swap(listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << SUBCATEGORY << "(modifying lists)" << ENDL;
	listA.push_back(1); listB.erase(listB.begin(), --listB.end());
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listA.swap(listB);" << ENDL; listA.swap(listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << ENDL;

	FILE << CATEGORY << "===> Resize" << ENDL;
	listA.clear(); print_list(listA, "listA");
	FILE << "listA.resize(0, -1);" << ENDL; listA.resize(0, -1);
	print_list(listA, "listA");
	FILE << "listA.resize(1, -1);" << ENDL; listA.resize(1, -1);
	print_list(listA, "listA");
	FILE << "listA.resize(0, -1);" << ENDL; listA.resize(0, -1);
	print_list(listA, "listA");
	FILE << "listA.resize(6, -1); listA.push_front(42);" << ENDL; listA.resize(6, -1); listA.push_front(42);
	print_list(listA, "listA");
	FILE << "listA.resize(4, -1);" << ENDL; listA.resize(4, -1);
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << SUBTITLE << "Operations" << ENDL;
	FILE << CATEGORY << "===> Splice" << ENDL;
	FILE << SUBCATEGORY << "=====> splice entire list (1)" << ENDL;
	FILE << "list<int> listempty;" << ENDL; containerT<int> listempty; print_list(listempty, "listempty");
	FILE << "list<int> listdest(1, 1);" << ENDL; containerT<int> listdest(1, 1); print_list(listdest, "listdest");
	FILE << "list<int> listdest3(3, 3);" << ENDL; containerT<int> listdest3(3, 3); print_list(listdest3, "listdest3");
	FILE << "listdest.splice(listdest.begin(), listempty);" << ENDL; listdest.splice(listdest.begin(), listempty);
	print_list(listdest, "listdest");
	FILE << "listempty.splice(listempty.begin(), listdest);" << ENDL; listempty.splice(listempty.begin(), listdest);
	print_list(listempty, "listempty");
	print_list(listdest, "listdest");
	FILE << "listempty.splice(listempty.end(), listdest3);" << ENDL; listempty.splice(listempty.end(), listdest3);
	print_list(listempty, "listempty");
	print_list(listdest3, "listdest3");
	FILE << "list<int> listdest2(2, 2);" << ENDL; containerT<int> listdest2(2, 2); print_list(listdest2, "listdest2");
	FILE << "listempty.splice(++listempty.begin(), listdest2);" << ENDL; listempty.splice(++listempty.begin(), listdest2);
	print_list(listempty, "listempty");
	print_list(listdest2, "listdest2");
	FILE << "listempty.push_front(0);" << ENDL; listempty.push_front(0);  print_list(listempty, "listempty");
	FILE << "listempty.push_back(4);" << ENDL; listempty.push_back(4);  print_list(listempty, "listempty");
	FILE << "listdest2.push_front(0);" << ENDL; listdest2.push_front(0);  print_list(listdest2, "listdest2");
	FILE << "listdest2.push_back(1);" << ENDL; listdest2.push_back(1);  print_list(listdest2, "listdest2");

	FILE << SUBCATEGORY << "=====> splice single element (2)" << ENDL;
	FILE << "list<int> listdest4;" << ENDL; containerT<int> listdest4; print_list(listdest4, "listdest4");
	FILE << "listdest4.splice(listdest4.begin(), listempty, listempty.begin());" << ENDL; listdest4.splice(listdest4.begin(), listempty, listempty.begin());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listempty, --listempty.end());" << ENDL; listdest4.splice(listdest4.end(), listempty, --listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(++listdest4.begin(), listempty, listempty.begin());" << ENDL; listdest4.splice(++listdest4.begin(), listempty, listempty.begin());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listempty.push_front(5);" << ENDL; listempty.push_front(5); print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listempty, listempty.begin());" << ENDL; listdest4.splice(listdest4.end(), listempty, listempty.begin());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listempty.push_back(-1);" << ENDL; listempty.push_back(-1); print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.begin(), listempty, --listempty.end());" << ENDL; listdest4.splice(listdest4.begin(), listempty, --listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.push_back(42);" << ENDL; listdest4.push_back(42); print_list(listdest4, "listdest4");
	FILE << "listdest4.push_front(21);" << ENDL; listdest4.push_front(21); print_list(listdest4, "listdest4");
	FILE << "listdest4.pop_back();" << ENDL; listdest4.pop_back(); print_list(listdest4, "listdest4");
	FILE << "listdest4.pop_front();" << ENDL; listdest4.pop_front(); print_list(listdest4, "listdest4");

	FILE << CATEGORY << "=====> splice element range (3)" << ENDL;
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(inc_iterator(listdest4.begin(), 3), listempty, listempty.begin(), inc_iterator(listempty.begin(), 3))" << ENDL;
	listdest4.splice(inc_iterator(listdest4.begin(), 3), listempty, listempty.begin(), inc_iterator(listempty.begin(), 3));
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listempty.front() = -2" << ENDL; listempty.front() = -2; print_list(listempty, "listempty");
	FILE << "listempty.back() = 6" << ENDL; listempty.back() = 6; print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.begin(), listempty, listempty.begin(), --listempty.end())" << ENDL;
	listdest4.splice(listdest4.begin(), listempty, listempty.begin(), --listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listempty, listempty.begin(), --listempty.end())" << ENDL;
	listdest4.splice(listdest4.end(), listempty, listempty.begin(), --listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listempty, listempty.begin(), listempty.end())" << ENDL;
	listdest4.splice(listdest4.end(), listempty, listempty.begin(), listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listempty, listempty.begin(), listempty.end())" << ENDL;
	listdest4.splice(listdest4.end(), listempty, listempty.begin(), listempty.end());
	print_list(listdest4, "listdest4");
	print_list(listempty, "listempty");
	FILE << "listempty.push_back(42)" << ENDL; listempty.push_back(42); print_list(listempty, "listempty");
	FILE << "listempty.push_front(21)" << ENDL; listempty.push_front(21); print_list(listempty, "listempty");
	FILE << "listdest4.splice(listdest4.end(), listdest4, listdest4.begin(), listdest4.end());" << ENDL;
	listdest4.splice(listdest4.end(), listdest4, listdest4.begin(), listdest4.end());
	print_list(listdest4, "listdest4");
	FILE << "listdest4.splice(listdest4.end(), listdest4, listdest4.begin());" << ENDL;
	listdest4.splice(listdest4.end(), listdest4, listdest4.begin());
	print_list(listdest4, "listdest4");
	FILE << ENDL;

	FILE << CATEGORY << "===> Remove" << ENDL;
	listA.clear();
	print_list(listA, "listA");
	FILE << "listA.remove(2);" << ENDL; listA.remove(2);
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "(modifyling list)" << ENDL;
	int array[] = {1, 2, 3, 3, 2, 3, 4, 2, 5, 5}; listA.assign(array, array + 10);
	print_list(listA, "listA");
	FILE << "listA.remove(2);" << ENDL; listA.remove(2);
	print_list(listA, "listA");
	FILE << "listA.remove(3);" << ENDL; listA.remove(3);
	print_list(listA, "listA");
	FILE << "listA.remove(6);" << ENDL; listA.remove(6);
	print_list(listA, "listA");
	FILE << "listA.remove(1);" << ENDL; listA.remove(1);
	print_list(listA, "listA");
	FILE << "listA.remove(5);" << ENDL; listA.remove(5);
	print_list(listA, "listA");
	FILE << "listA.remove(4);" << ENDL; listA.remove(4);
	print_list(listA, "listA");
	FILE << "listA.push_back(1); listA.push_front(0);" << ENDL; listA.push_back(1); listA.push_front(0);
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Remove_if" << ENDL;
	FILE << SUBCATEGORY << "bool single_digit (const int & value) {return (value < 10);}" << ENDL;
	listA.clear();
	print_list(listA, "listA");
	FILE << "listA.remove_if(single_digit);" << ENDL; listA.remove_if(single_digit);
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "(modifyling list)" << ENDL;
	int array2[] = {15, 36, 7, 17, 20, 39, 4, 1}; listA.assign(array2, array2 + 8);
	print_list(listA, "listA");
	FILE << "listA.remove_if(single_digit);" << ENDL; listA.remove_if(single_digit);
	print_list(listA, "listA");
	FILE << "listA.remove_if(single_digit);" << ENDL; listA.remove_if(single_digit);
	print_list(listA, "listA");
	FILE << SUBCATEGORY << "struct is_odd {bool operator() (const int & value) {return (value % 2 == 1);}};" << ENDL;
	FILE << "listA.remove_if(is_odd());" << ENDL; listA.remove_if(is_odd());
	print_list(listA, "listA");
	FILE << ENDL;

	FILE << CATEGORY << "===> Unique" << ENDL;
	FILE << SUBCATEGORY << "=====> unique()" << ENDL;
	listA.clear();
	print_list(listA, "listA");
	FILE << "listA.unique(); listA.push_front(0); listA.push_back(1);" << ENDL; listA.unique(); listA.push_front(0); listA.push_back(1);
	print_list(listA, "listA");
	double mydoubles[] = {3.14, 3.14, 4.5, 12.1, 12.1, 12.1, 12.7, 13.1, 13.2, 13.3, 72.2, 72.72, 73.6};
	containerT<double> listJ(mydoubles, mydoubles + 13);
	print_list(listJ, "listJ");
	FILE << "listJ.unique();" << ENDL; listJ.unique();
	print_list(listJ, "listJ");
	FILE << "listJ.unique();" << ENDL; listJ.unique();
	print_list(listJ, "listJ");
	FILE << SUBCATEGORY << "=====> unique(binary_pred)" << ENDL;
	FILE << SUBCATEGORY << "bool same_integral_part(double first, double second) {return (int(first) == int(second));}" << ENDL;
	FILE << "listJ.unique(same_integral_part);" << ENDL; listJ.unique(same_integral_part);
	print_list(listJ, "listJ");
	FILE << "listJ.unique(same_integral_part);" << ENDL; listJ.unique(same_integral_part);
	print_list(listJ, "listJ");
	FILE << ENDL;

	FILE << CATEGORY << "===> Merge" << ENDL;
	FILE << SUBCATEGORY << "=====> merge(list & x)" << ENDL;
	print_list(listJ, "listJ");
	double mydoubles2[] = {1.2, 2.3, 4.1, 72.3, 73.7, 73.8};
	containerT<double> listK(mydoubles2, mydoubles2 + 6);
	print_list(listK, "listK");
	FILE << "listJ.merge(listK);" << ENDL; listJ.merge(listK);
	print_list(listJ, "listJ");
	print_list(listK, "listK");
	FILE << "listJ.merge(listK);" << ENDL; listJ.merge(listK);
	print_list(listJ, "listJ");
	print_list(listK, "listK");
	FILE << SUBCATEGORY << "=====> merge(list & x, Compare comp)" << ENDL;
	FILE << "listK.push_back(4.3);" << ENDL; listK.push_back(4.3); print_list(listK, "listK");
	FILE << "listJ.merge(listK, comp_integral_part);" << ENDL; listJ.merge(listK, comp_integral_part);
	print_list(listJ, "listJ");
	print_list(listK, "listK");
	FILE << "listJ.merge(listK, comp_integral_part);" << ENDL; listJ.merge(listK, comp_integral_part);
	print_list(listJ, "listJ");
	print_list(listK, "listK");
	FILE << ENDL;

	FILE << CATEGORY << "===> Sort" << ENDL;
	print_list(listD, "listD");
	FILE << "listD.sort();" << ENDL; listD.sort(); print_list(listD, "listD");
	FILE << "listD.clear();" << ENDL; listD.clear(); print_list(listD, "listD");
	FILE << "listD.sort();" << ENDL; listD.sort(); print_list(listD, "listD");
	FILE << SUBCATEGORY << "(modifyling list)" << ENDL;
	int array3[] = {1}; listD.assign(array3, array3 + sizeof(array3) / sizeof(*array3));
	print_list(listD, "listD");
	FILE << "listD.sort();" << ENDL; listD.sort(); print_list(listD, "listD");
	FILE << SUBCATEGORY << "(modifyling list)" << ENDL;
	int array4[] = {6, 5, 4, 3, 2, 2, 1}; listD.assign(array4, array4 + sizeof(array4) / sizeof(*array4));
	print_list(listD, "listD");
	FILE << "listD.sort();" << ENDL; listD.sort(); print_list(listD, "listD");
	FILE << SUBCATEGORY << "(modifyling list)" << ENDL;
	int array5[] = {-2, 8, 4, 9, 0, 0, 2, 8, 3, 1, 10, 10000, 5000, -4321}; listD.assign(array5, array5 + sizeof(array5) / sizeof(*array5));
	print_list(listD, "listD");
	FILE << "iterator listD_last = --listD.end()" << ENDL; typename containerT<int>::iterator listD_last = --listD.end();
	FILE << "*listD_last = " << *listD_last << ENDL;
	FILE << "listD.sort();" << ENDL; listD.sort(); print_list(listD, "listD");
	FILE << "*listD_last = " << *listD_last << ENDL;
	FILE << "listD_last = --listD.end()" << ENDL; listD_last = --listD.end();
	FILE << "*listD_last = " << *listD_last << ENDL;
	FILE << "listD.sort(std::greater<int>());" << ENDL; listD.sort(std::greater<int>()); print_list(listD, "listD");
	FILE << "*listD_last = " << *listD_last << ENDL;
	listD.clear();

	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse" << ENDL;
	print_list(listA, "listA");
	FILE << "listA.reverse();" << ENDL; listA.reverse();
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listB.reverse();" << ENDL; listB.reverse();
	print_list(listB, "listB");
	FILE << "listB.push_back(-1);" << ENDL; listB.push_back(-1);
	print_list(listB, "listB");
	FILE << "listB.push_front(6);" << ENDL; listB.push_front(6);
	print_list(listB, "listB");
	FILE << "listB.reverse();" << ENDL; listB.reverse();
	print_list(listB, "listB");
	FILE << "listB.reverse();" << ENDL; listB.reverse();
	print_list(listB, "listB");
	FILE << ENDL;

	FILE << SUBTITLE << "Observers" << ENDL;
	FILE << CATEGORY << "===> Get_allocator" << ENDL;
	FILE << "list<int> mylist; int * p;" << ENDL; containerT<int> mylist; int * p;
	FILE << "p = mylist.get_allocator().allocate(5);" << ENDL; p = mylist.get_allocator().allocate(5);
	FILE << "for (int i = 0; i < 5; ++i) p[i] = i;" << ENDL; for (int i = 0; i < 5; ++i) p[i] = i;
	FILE << "for (int i = 0; i < 5; ++i) std::cout << ' ' << p[i];" << ENDL;
	for (int i = 0; i < 5; ++i) FILE << OUTPUT << p[i] << ' '; FILE << ENDL;
	FILE << "mylist.get_allocator().deallocate(p,5);" << ENDL; mylist.get_allocator().deallocate(p,5);
	FILE << ENDL;

	FILE << SUBTITLE << "Non-member function overloads" << ENDL;
	FILE << CATEGORY << "===> Relational operators" << ENDL;
	listA.clear(); listB.clear();
	print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listB.assign(2, 1); print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listA.assign(3, 1); print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listA.assign(2, 2); print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	*listA.begin() = 1; *(--listB.end()) = 3; print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listB.clear(); listB.push_back(-10); listB.push_back(-20);
	print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listA.push_back(3); listB.clear(); for (int i = 4; i <= 7; i++) listB.push_back(i);
	print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listA.push_back(4); listB.clear(); listB.push_back(42); listB.push_back(21); listB.push_back(10);
	print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	listA = listB;
	print_list(listA, "listA"); print_list(listB, "listB");
	FILE << "listA == listB : " << OUTPUT << std::boolalpha << (listA == listB) << ENDL;
	FILE << "listA != listB : " << OUTPUT << std::boolalpha << (listA != listB) << ENDL;
	FILE << "listA < listB : " << OUTPUT << std::boolalpha << (listA < listB) << ENDL;
	FILE << "listA > listB : " << OUTPUT << std::boolalpha << (listA > listB) << ENDL;
	FILE << "listA <= listB : " << OUTPUT << std::boolalpha << (listA <= listB) << ENDL;
	FILE << "listA >= listB : " << OUTPUT << std::boolalpha << (listA >= listB) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Swap" << ENDL;
	print_list(listA, "listA");
	listB.assign(myints, myints + 3);
	print_list(listB, "listB");
	FILE << "swap(listA, listB);" << ENDL; swap(listA, listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "swap(listA, listB);" << ENDL; swap(listA, listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "listA.clear(); swap(listA, listB);" << ENDL; listA.clear(); swap(listA, listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "swap(listA, listB);" << ENDL; swap(listA, listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << SUBCATEGORY << "(modifying lists)" << ENDL;
	listA.push_back(1); listB.erase(listB.begin(), --listB.end());
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << "swap(listA, listB);" << ENDL; swap(listA, listB);
	print_list(listA, "listA");
	print_list(listB, "listB");
	FILE << ENDL;

	FILE << TITLE << "=> ENDING list tests" << ENDL << ENDL;
}

int
main(void)
{
    test_list<ft::list>();
}
