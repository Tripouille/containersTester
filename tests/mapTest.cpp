#include "map.hpp"
#include <map>
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
using std::pair;
using std::make_pair;
using std::string;

class AllocatingClass
{
	public:
		AllocatingClass(void) : _array(new int[2]) {_array[0] = 0; _array[1] = 0;}
		AllocatingClass(AllocatingClass const & other) : _array(new int[2]) {(void)other; _array[0] = 0; _array[1] = 0;}
		~AllocatingClass() {delete[] _array;}
		AllocatingClass & operator=(AllocatingClass const & other) {(void)other; return (*this);}
		int* getArray(void) const {return (_array);}
	private:
		int* _array;
};
bool operator<(AllocatingClass const & a1, AllocatingClass const & a2) {return (a1.getArray()[0] < a2.getArray()[0]);}

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
bool operator<(ThrowingExceptionClass const & a1, ThrowingExceptionClass const & a2)
{return (a1.geta() < a2.geta());}
std::ostream& operator<<(std::ostream & os, ThrowingExceptionClass const & a) {os << a.geta(); return (os);}

class ThrowingExceptionClass2
{
	public:
		ThrowingExceptionClass2(void) : _a(2) {throw std::exception();}
		ThrowingExceptionClass2(int a) : _a(a) {}
		ThrowingExceptionClass2(ThrowingExceptionClass2 const& other) {_a = other._a;}
		~ThrowingExceptionClass2() {}
		ThrowingExceptionClass2 & operator=(ThrowingExceptionClass2 const & other) {(void)other; return (*this);}
		int geta(void) const {return (_a);}
	private:
		int _a;
};
bool operator<(ThrowingExceptionClass2 const & a1, ThrowingExceptionClass2 const & a2)
{return (a1.geta() < a2.geta());}
std::ostream& operator<<(std::ostream & os, ThrowingExceptionClass2 const & a) {os << a.geta(); return (os);}

struct greater
{
	bool operator()(int const & a, int const & b) const {return (a > b);}
};

template<class T>
void
print_map(T const & map, std::string const & name)
{
	typename T::const_iterator begin = map.begin();
	typename T::const_iterator end = map.end();
	std::cout << OUTPUT << name << " = [ ";
	while (begin != end)
	{
		std::cout << "(" << begin->first << " : " << begin->second << ") ";
		++begin;
	}
	std::cout << "] Size : " << map.size() << ENDL;
}

template <template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > > class map>
void
test_map(void)
{
	FILE << TITLE << std::endl << "=> STARTING map tests" << ENDL;

	FILE << SUBTITLE << "Constructors" << ENDL;
	FILE << CATEGORY << "===> Default constructor" << ENDL;
	FILE << "map<int, string> mapA;" << ENDL; map<int, string> mapA;
	print_map(mapA, "mapA");
	FILE << std::boolalpha << "mapA.empty() = " << OUTPUT << mapA.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Range constructor" << ENDL;
	FILE << "pair<int, string> pairArray[] = {make_pair(1, \"A\"), make_pair(2, \"B\"), make_pair(3, \"C\")};" << ENDL;
	pair<int, string> pairArray[] = {make_pair(1, "A"), make_pair(2, "B"), make_pair(3, "C")};
	FILE << "map<int, string> mapB(pairArray, pairArray + 3);" << ENDL;
	map<int, string> mapB(pairArray, pairArray + 3);
	print_map(mapB, "mapB");
	FILE << std::boolalpha << "mapB.empty() = " << OUTPUT << mapB.empty() << ENDL;
	FILE << "map<int, string> mapC(pairArray, pairArray);" << ENDL;
	map<int, string> mapC(pairArray, pairArray);
	print_map(mapC, "mapC");
	FILE << std::boolalpha << "mapC.empty() = " << OUTPUT << mapC.empty() << ENDL;
	FILE << "pair<int, string> pairArray2[] = {make_pair(10, \"\"), make_pair(7, \"\"), make_pair(7, \"\"), make_pair(9, \"\"), make_pair(8, \"\"), make_pair(20, \"\"), make_pair(30, \"\"), make_pair(21, \"\"), make_pair(22, \"\"), make_pair(23, \"\"), make_pair(33, \"\"), make_pair(32, \"\"), make_pair(31, \"\")};" << ENDL;
	pair<int, string> pairArray2[] = {make_pair(10, ""), make_pair(7, ""), make_pair(7, ""), make_pair(9, ""), make_pair(8, ""), make_pair(20, ""), make_pair(30, ""), make_pair(21, ""), make_pair(22, ""), make_pair(23, ""), make_pair(33, ""), make_pair(32, ""), make_pair(31, "")};
	FILE << "map<int, string> mapD(pairArray2, pairArray2 + 13);" << ENDL;
	map<int, string> mapD(pairArray2, pairArray2 + 13);
	print_map(mapD, "mapD");
	FILE << std::boolalpha << "mapD.empty() = " << OUTPUT << mapD.empty() << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> Copy constructor" << ENDL;
	print_map(mapD, "mapD");
	FILE << "map<int, string> mapE(mapD);" << ENDL; map<int, string> mapE(mapD);
	print_map(mapD, "mapD");
	print_map(mapE, "mapE");
	FILE << ENDL;

	FILE << CATEGORY << "===> Destructor" << ENDL;
	AllocatingClass allocatedInstance;
	FILE << "pair<AllocatingClass, AllocatingClass> pairArray3[] = {...};" << ENDL;
	pair<AllocatingClass, AllocatingClass> pairArray3[] = {make_pair(allocatedInstance, allocatedInstance), make_pair(allocatedInstance, allocatedInstance), make_pair(allocatedInstance, allocatedInstance)};
	FILE << "map<AllocatingClass, AllocatingClass> allocatingMap(pairArray3, pairArray3 + 3);" << ENDL;
	map<AllocatingClass, AllocatingClass> allocatingMap(pairArray3, pairArray3 + 3);
	FILE << ENDL;

	FILE << SUBTITLE << "Operator" << ENDL;
	FILE << CATEGORY << "===> Operator=" << ENDL;
	print_map(mapB, "mapB");
	print_map(mapC, "mapC");
	FILE << "mapB = mapC;" << ENDL; mapB = mapC;
	print_map(mapB, "mapB");
	FILE << "mapB.insert(make_pair(0, ""));" << ENDL; mapB.insert(make_pair(0, ""));
	print_map(mapB, "mapB");
	print_map(mapC, "mapC");
	FILE << "mapB = mapC;" << ENDL; mapB = mapC;
	print_map(mapB, "mapB");
	FILE << "mapB = mapD;" << ENDL; mapB = mapD;
	print_map(mapB, "mapB");
	print_map(mapD, "mapD");
	FILE << ENDL;

	FILE << SUBTITLE << "Iterators" << ENDL;
	FILE << CATEGORY << "===> Iterators" << ENDL;
	print_map(mapC, "mapC");
	FILE << "mapC.begin() == mapC.end() : " << OUTPUT << std::boolalpha << (mapC.begin() == mapC.end()) << ENDL;
	FILE << SUBCATEGORY << "(Adding some values)" << ENDL;
	mapC[1] = "A"; mapC[2] = "B"; mapC[3] = "C";
	print_map(mapC, "mapC");
	FILE << "map<int, string>::iterator it = mapC.begin();" << ENDL; typename map<int, string>::iterator it = mapC.begin();
	FILE << "map<int, string>::iterator ite = mapC.end();" << ENDL; typename map<int, string>::iterator ite = mapC.end();
	FILE << "while (it != ite) {...; it++;}" << ENDL;
	while (it != ite)
	{
		FILE << "it->first : " << OUTPUT << it->first << RESET_ALL << ", it->second : " << OUTPUT << it->second << ENDL;
		it++;
	}
	FILE << "it--;" << ENDL; it--;
	#ifdef CONST_TEST
	FILE << "it->first = 42;" << ENDL; it->first = 42;
	#endif
	FILE << "it->second = \"CC\";" << ENDL; it->second = "CC";
	print_map(mapC, "mapC");
	FILE << ENDL;

	FILE << CATEGORY << "===> Const iterators" << ENDL;
	print_map(mapC, "mapC");
	FILE << "map<int, string>::const_iterator it = mapC.begin();" << ENDL; typename map<int, string>::const_iterator c_it = mapC.begin();
	FILE << "map<int, string>::const_iterator ite = mapC.end();" << ENDL; typename map<int, string>::const_iterator c_ite = mapC.end();
	FILE << "while (c_it != c_ite) {...; c_it++;}" << ENDL;
	while (c_it != c_ite)
	{
		FILE << "c_it->first : " << OUTPUT << c_it->first << RESET_ALL << ", c_it->second : " << OUTPUT << c_it->second << ENDL;
		c_it++;
	}
	#ifdef CONST_TEST
	FILE << "c_it--;" << ENDL; c_it--;
	FILE << "c_it->second = \"CC\";" << ENDL; c_it->second = "CC";
	#endif
	FILE << ENDL;

	FILE << CATEGORY << "===> Reverse iterators" << ENDL;
	print_map(mapC, "mapC");
	FILE << "map<int, string>::reverse_iterator r_it = mapC.rbegin();" << ENDL; typename map<int, string>::reverse_iterator r_it = mapC.rbegin();
	FILE << "map<int, string>::reverse_iterator r_ite = mapC.rend();" << ENDL; typename map<int, string>::reverse_iterator r_ite = mapC.rend();
	FILE << "while (r_it != r_ite) {...; r_it++;}" << ENDL;
	while (r_it != r_ite)
	{
		FILE << "r_it->first : " << OUTPUT << r_it->first << RESET_ALL << ", r_it->second : " << OUTPUT << r_it->second << ENDL;
		r_it++;
	}
	FILE << "r_it--;" << ENDL; r_it--;
	FILE << "r_it->second = \"AA\";" << ENDL; r_it->second = "AA";
	print_map(mapC, "mapC");
	FILE << ENDL;

	FILE << CATEGORY << "===> Const reverse iterators" << ENDL;
	print_map(mapC, "mapC");
	FILE << "map<int, string>::const_reverse_iterator rc_it = mapC.rbegin();" << ENDL; typename map<int, string>::const_reverse_iterator rc_it = mapC.rbegin();
	FILE << "map<int, string>::const_reverse_iterator rc_ite = mapC.rend();" << ENDL; typename map<int, string>::const_reverse_iterator rc_ite = mapC.rend();
	FILE << "while (rc_it != rc_ite) {...; rc_it++;}" << ENDL;
	while (rc_it != rc_ite)
	{
		FILE << "rc_it->first : " << OUTPUT << rc_it->first << RESET_ALL << ", rc_it->second : " << OUTPUT << rc_it->second << ENDL;
		rc_it++;
	}
	#ifdef CONST_TEST
	FILE << "rc_it--;" << ENDL; rc_it--;
	FILE << "rc_it->second = \"AA\";" << ENDL; rc_it->second = "AA";
	#endif
	FILE << ENDL;

	FILE << SUBTITLE << "Capacity" << ENDL;
	FILE << CATEGORY << "===> max_size()" << ENDL;
	FILE << "mapA.max_size() : " << OUTPUT << mapA.max_size() << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Element access" << ENDL;
	FILE << CATEGORY << "===> operator[]" << ENDL;
	FILE << "mapA[10] = \"A\";" << ENDL; mapA[10] = "A";
	FILE << "mapA[7] = \"B\";" << ENDL; mapA[7] = "B";
	FILE << "mapA[7] = \"C\";" << ENDL; mapA[7] = "C";
	FILE << "mapA[9] = \"D\";" << ENDL; mapA[9] = "D";
	FILE << "mapA[8] = \"E\";" << ENDL; mapA[8] = "E";
	FILE << "mapA[20] = \"F\";" << ENDL; mapA[20] = "F";
	FILE << "mapA[30] = \"G\";" << ENDL; mapA[30] = "G";
	FILE << "mapA[21] = \"H\";" << ENDL; mapA[21] = "H";
	FILE << "mapA[22] = \"I\";" << ENDL; mapA[22] = "I";
	FILE << "mapA[23] = \"J\";" << ENDL; mapA[23] = "J";
	FILE << "mapA[33] = \"K\";" << ENDL; mapA[33] = "K";
	FILE << "mapA[32] = \"L\";" << ENDL; mapA[32] = "L";
	FILE << "mapA[31] = \"M\";" << ENDL; mapA[31] = "M";
	FILE << "mapA[0] : " << OUTPUT << mapA[0] << ENDL;
	FILE << "mapA[23] : " << OUTPUT << mapA[23] << ENDL;
	FILE << "mapA[23] = \"JJ\";" << ENDL; mapA[23] = "JJ";
	print_map(mapA, "mapA");
	#ifdef CONST_TEST
	FILE << "map<int, string> const const_map(pairArray2, pairArray2 + 13);" << ENDL; map<int, string> const const_map(pairArray2, pairArray2 + 13);
	FILE << "const_map[23] : " << OUTPUT << const_map[23] << ENDL;
	#endif
	FILE << ENDL;

	FILE << SUBTITLE << "Modifiers" << ENDL;
	FILE << CATEGORY << "===> insert" << ENDL;
	FILE << SUBCATEGORY << "=====> single element (1)" << ENDL;
	print_map(mapA, "mapA");
	FILE << "pair<map<int, string>::iterator, bool> res;" << ENDL;
	pair<typename map<int, string>::iterator, bool> res;
	FILE << "res = mapA.insert(make_pair(-1, \"Z\"));" << ENDL; res = mapA.insert(make_pair(-1, "Z"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	FILE << "res = mapA.insert(make_pair(15, \"Y\"));" << ENDL; res = mapA.insert(make_pair(15, "Y"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	FILE << "res = mapA.insert(make_pair(7, \"CC\"));" << ENDL; res = mapA.insert(make_pair(7, "CC"));
	FILE << "(res.first)->first : " << OUTPUT << (res.first)->first << ENDL;
	FILE << "(res.first)->second : " << OUTPUT << (res.first)->second << ENDL;
	FILE << "res.second : " << OUTPUT << std::boolalpha << res.second << ENDL;
	print_map(mapA, "mapA");
	FILE << SUBCATEGORY << "=====> with hint (2)" << ENDL;
	FILE << "map<int, string>::iterator res2;" << ENDL; typename map<int, string>::iterator res2;
	FILE << "map<int, string>::iterator hint = mapA.begin();" << ENDL;
	typename map<int, string>::iterator hint = mapA.begin();
	FILE << "res2 = mapA.insert(hint, make_pair(-3, \"X\"));" << ENDL; res2 = mapA.insert(hint, make_pair(-3, "X"));
	FILE << "res2->first : " << OUTPUT << res2->first << ENDL;
	FILE << "res2->second : " << OUTPUT << res2->second << ENDL;
	FILE << "res2 = mapA.insert(hint, make_pair(11, \"W\"));" << ENDL; res2 = mapA.insert(hint, make_pair(11, "W"));
	FILE << "res2->first : " << OUTPUT << res2->first << ENDL;
	FILE << "res2->second : " << OUTPUT << res2->second << ENDL;
	FILE << "res2 = mapA.insert(hint, make_pair(11, \"V\"));" << ENDL; res2 = mapA.insert(hint, make_pair(11, "V"));
	FILE << "res2->first : " << OUTPUT << res2->first << ENDL;
	FILE << "res2->second : " << OUTPUT << res2->second << ENDL;
	print_map(mapA, "mapA");
	FILE << SUBCATEGORY << "=====> range (3)" << ENDL;
	FILE << "mapA.insert(pairArray, pairArray);" << ENDL; mapA.insert(pairArray, pairArray);
	print_map(mapA, "mapA");
	FILE << "mapA.insert(pairArray, pairArray + 1);" << ENDL; mapA.insert(pairArray, pairArray + 1);
	print_map(mapA, "mapA");
	FILE << "mapA.insert(pairArray, pairArray + 3);" << ENDL; mapA.insert(pairArray, pairArray + 3);
	print_map(mapA, "mapA");
	FILE << "mapA.insert(pairArray2, pairArray2 + 13);" << ENDL; mapA.insert(pairArray2, pairArray2 + 13);
	print_map(mapA, "mapA");
	FILE << ENDL;

	FILE << CATEGORY << "===> erase" << ENDL;
	FILE << SUBCATEGORY << "=====> from position (1)" << ENDL;
	print_map(mapA, "mapA");
	FILE << "mapA.erase(mapA.begin());" << ENDL; mapA.erase(mapA.begin());
	print_map(mapA, "mapA");
	FILE << "mapA.erase(mapA.begin());" << ENDL; mapA.erase(mapA.begin());
	print_map(mapA, "mapA");
	FILE << "mapA.erase(--mapA.end());" << ENDL; mapA.erase(--mapA.end());
	print_map(mapA, "mapA");
	FILE << "mapA.erase(++mapA.begin());" << ENDL; mapA.erase(++mapA.begin());
	print_map(mapA, "mapA");
	FILE << SUBCATEGORY << "(Moving iterator it) " << RESET_ALL;
	it = mapA.begin(); for (int i = 0; i < 6; ++i) ++it;
	FILE << "it->first : " << OUTPUT << it->first << ENDL;
	FILE << "mapA.erase(it);" << ENDL; mapA.erase(it);
	print_map(mapA, "mapA");
	FILE << "map<int, string> mapK; mapK[10] = \"A\"; mapK[5] = \"B\"; mapK[20] = \"C\"; mapK[4] = \"D\"; mapK[6] = \"E\"; mapK[18] = \"F\"; mapK[25] = \"G\";" << ENDL;
	map<int, string> mapK; mapK[10] = "A"; mapK[5] = "B"; mapK[20] = "C"; mapK[4] = "D"; mapK[6] = "E"; mapK[18] = "F"; mapK[25] = "G";
	print_map(mapK, "mapK");
	FILE << "mapK.erase(++mapK.begin());" << ENDL; mapK.erase(++mapK.begin());
	print_map(mapK, "mapK");
	FILE << "mapK.erase(--mapK.end());" << ENDL; mapK.erase(--mapK.end());
	print_map(mapK, "mapK");
	FILE << SUBCATEGORY << "=====> from key (2)" << ENDL;
	FILE << "mapA.erase(0) : " << OUTPUT << mapA.erase(0) << ENDL;
	print_map(mapA, "mapA");
	FILE << "mapA.erase(7) : " << OUTPUT << mapA.erase(7) << ENDL; 
	print_map(mapA, "mapA");
	FILE << "mapA.erase(8) : " << OUTPUT << mapA.erase(8) << ENDL; 
	print_map(mapA, "mapA");
	FILE << "mapA.erase(31) : " << OUTPUT << mapA.erase(31) << ENDL; 
	print_map(mapA, "mapA");
	FILE << "mapA.erase(32) : " << OUTPUT << mapA.erase(32) << ENDL; 
	print_map(mapA, "mapA");
	FILE << "mapK.clear(); mapK[10] = \"A\"; mapK[5] = \"B\"; mapK[20] = \"C\"; mapK[4] = \"D\"; mapK[6] = \"E\"; mapK[18] = \"F\"; mapK[25] = \"G\";" << ENDL;
	mapK.clear(); mapK[10] = "A"; mapK[5] = "B"; mapK[20] = "C"; mapK[4] = "D"; mapK[6] = "E"; mapK[18] = "F"; mapK[25] = "G";
	print_map(mapK, "mapK");
	FILE << "mapK.erase(++mapK.begin());" << ENDL; mapK.erase(++mapK.begin());
	print_map(mapK, "mapK");
	FILE << "mapK.erase(--mapK.end());" << ENDL; mapK.erase(--mapK.end());
	print_map(mapK, "mapK");
	FILE << SUBCATEGORY << "=====> range (3)" << ENDL;
	FILE << "mapA.erase(mapA.begin(), mapA.end());" << ENDL; mapA.erase(mapA.begin(), mapA.end());
	print_map(mapA, "mapA");
	print_map(mapD, "mapD");
	FILE << "mapD.erase(++mapD.begin(), --mapD.end());" << ENDL; mapD.erase(++mapD.begin(), --mapD.end());
	print_map(mapD, "mapD");
	FILE << ENDL;

	FILE << CATEGORY << "===> swap" << ENDL;
	print_map(mapA, "mapA");
	print_map(mapD, "mapD");
	FILE << "mapA.swap(mapD);" << ENDL; mapA.swap(mapD);
	print_map(mapA, "mapA");
	print_map(mapD, "mapD");
	print_map(mapB, "mapB");
	FILE << "mapA.swap(mapB);" << ENDL; mapA.swap(mapB);
	print_map(mapA, "mapA");
	print_map(mapB, "mapB");
	FILE << ENDL;

	FILE << CATEGORY << "===> clear" << ENDL;
	print_map(mapB, "mapB");
	FILE << "mapB.clear();" << ENDL; mapB.clear();
	print_map(mapB, "mapB");
	FILE << "mapB.clear();" << ENDL; mapB.clear();
	print_map(mapB, "mapB");
	FILE << ENDL;

	FILE << SUBTITLE << "Observers" << ENDL;
	FILE << CATEGORY << "===> key_comp" << ENDL;
	FILE << "map<int, string>::key_compare mycomp = mapA.key_comp();" << ENDL;
	typename map<int, string>::key_compare mycomp = mapA.key_comp();
	FILE << "mycomp(0, 1) : " << OUTPUT << std::boolalpha << mycomp(0, 1) << ENDL;
	FILE << "mycomp(1, 1) : " << OUTPUT << std::boolalpha << mycomp(1, 1) << ENDL;
	FILE << "mycomp(2, 1) : " << OUTPUT << std::boolalpha << mycomp(2, 1) << ENDL;
	FILE << "map<int, string, greater> mapH;" << ENDL; map<int, string, greater> mapH;
	FILE << "map<int, string, greater>::key_compare mycomp2 = mapH.key_comp();" << ENDL;
	typename map<int, string, greater>::key_compare mycomp2 = mapH.key_comp();
	FILE << "mycomp2(0, 1) : " << OUTPUT << std::boolalpha << mycomp2(0, 1) << ENDL;
	FILE << "mycomp2(1, 1) : " << OUTPUT << std::boolalpha << mycomp2(1, 1) << ENDL;
	FILE << "mycomp2(2, 1) : " << OUTPUT << std::boolalpha << mycomp2(2, 1) << ENDL;
	FILE << CATEGORY << "===> value_comp" << ENDL;
	FILE << "mapA.value_comp()(make_pair(0, \"\"), make_pair(1, \"\")) : " << OUTPUT << std::boolalpha << mapA.value_comp()(make_pair(0, ""), make_pair(1, "")) << ENDL;
	FILE << "mapA.value_comp()(make_pair(0, \"\"), make_pair(0, \"\")) : " << OUTPUT << std::boolalpha << mapA.value_comp()(make_pair(0, ""), make_pair(0, "")) << ENDL;
	FILE << "mapA.value_comp()(make_pair(1, \"\"), make_pair(0, \"\")) : " << OUTPUT << std::boolalpha << mapA.value_comp()(make_pair(1, ""), make_pair(0, "")) << ENDL;
	FILE << "mapH.value_comp()(make_pair(0, \"\"), make_pair(1, \"\")) : " << OUTPUT << std::boolalpha << mapH.value_comp()(make_pair(0, ""), make_pair(1, "")) << ENDL;
	FILE << "mapH.value_comp()(make_pair(0, \"\"), make_pair(0, \"\")) : " << OUTPUT << std::boolalpha << mapH.value_comp()(make_pair(0, ""), make_pair(0, "")) << ENDL;
	FILE << "mapH.value_comp()(make_pair(1, \"\"), make_pair(0, \"\")) : " << OUTPUT << std::boolalpha << mapH.value_comp()(make_pair(1, ""), make_pair(0, "")) << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Operations" << ENDL;
	FILE << CATEGORY << "===> find" << ENDL; //tester avec const
	print_map(mapA, "mapA");
	FILE << "mapA.find(7)->first : " << OUTPUT << mapA.find(7)->first << ENDL;
	FILE << "mapA.find(10)->first : " << OUTPUT << mapA.find(10)->first << ENDL;
	FILE << "mapA.find(33)->first : " << OUTPUT << mapA.find(33)->first << ENDL;
	FILE << "mapA.find(34) == mapA.end() : " << OUTPUT << std::boolalpha << (mapA.find(34) == mapA.end()) << ENDL;
	FILE << "mapA.find(33)->second : " << OUTPUT << mapA.find(33)->second << ENDL;
	FILE << "mapA.find(33)->second = \"Bonjour\";" << ENDL; mapA.find(33)->second = "Bonjour";
	FILE << "mapA.find(33)->second : " << OUTPUT << mapA.find(33)->second << ENDL;
	print_map(mapB, "mapB");
	FILE << "mapB.find(7) == mapB.end() : " << OUTPUT << std::boolalpha << (mapB.find(7) == mapB.end()) << ENDL;
	FILE << "map<int, string> const mapJ = mapA;" << ENDL; map<int, string> const mapJ = mapA;
	FILE << "mapJ.find(7)->first : " << OUTPUT << mapJ.find(7)->first << ENDL;
	FILE << "mapJ.find(34) == mapJ.end() : " << OUTPUT << std::boolalpha << (mapJ.find(34) == mapJ.end()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> count" << ENDL;
	print_map(mapA, "mapA");
	FILE << "mapA.count(7) : " << OUTPUT << mapA.count(7) << ENDL;
	FILE << "mapA.count(33) : " << OUTPUT << mapA.count(33) << ENDL;
	FILE << "mapA.count(0) : " << OUTPUT << mapA.count(0) << ENDL;
	print_map(mapB, "mapB");
	FILE << "mapB.count(7) : " << OUTPUT << mapB.count(7) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> lower_bound" << ENDL;
	print_map(mapA, "mapA");
	FILE << "mapA.lower_bound(8)->first : " << OUTPUT << mapA.lower_bound(8)->first << ENDL;
	FILE << "mapA.lower_bound(11)->first : " << OUTPUT << mapA.lower_bound(11)->first << ENDL;
	FILE << "mapA.lower_bound(34) == mapA.end() : " << OUTPUT << std::boolalpha << (mapA.lower_bound(34) == mapA.end()) << ENDL;
	FILE << "mapA.lower_bound(33)->second : " << OUTPUT << mapA.lower_bound(33)->second << ENDL;
	FILE << "mapA.lower_bound(33)->second = \"Salut\";" << ENDL; mapA.lower_bound(33)->second = "Salut";
	FILE << "mapA.lower_bound(33)->second : " << OUTPUT << mapA.lower_bound(33)->second << ENDL;
	FILE << "mapJ.lower_bound(8)->first : " << OUTPUT << mapJ.lower_bound(8)->first << ENDL;
	FILE << "mapJ.lower_bound(34) == mapJ.end() : " << OUTPUT << std::boolalpha << (mapJ.lower_bound(34) == mapJ.end()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> upper_bound" << ENDL;
	print_map(mapA, "mapA");
	FILE << "mapA.upper_bound(8)->first : " << OUTPUT << mapA.upper_bound(8)->first << ENDL;
	FILE << "mapA.upper_bound(11)->first : " << OUTPUT << mapA.upper_bound(11)->first << ENDL;
	FILE << "mapA.upper_bound(23)->first : " << OUTPUT << mapA.upper_bound(23)->first << ENDL;
	FILE << "mapA.upper_bound(33) == mapA.end() : " << OUTPUT << std::boolalpha << (mapA.upper_bound(33) == mapA.end()) << ENDL;
	FILE << "mapA.upper_bound(34) == mapA.end() : " << OUTPUT << std::boolalpha << (mapA.upper_bound(34) == mapA.end()) << ENDL;
	FILE << "mapA.upper_bound(11)->second : " << OUTPUT << mapA.upper_bound(11)->second << ENDL;
	FILE << "mapA.upper_bound(11)->second = \"Salut\";" << ENDL; mapA.upper_bound(11)->second = "Salut";
	FILE << "mapA.upper_bound(11)->second : " << OUTPUT << mapA.upper_bound(11)->second << ENDL;
	FILE << "mapJ.upper_bound(8)->first : " << OUTPUT << mapJ.upper_bound(8)->first << ENDL;
	FILE << "mapJ.upper_bound(33) == mapJ.end() : " << OUTPUT << std::boolalpha << (mapJ.upper_bound(33) == mapJ.end()) << ENDL;
	FILE << ENDL;

	FILE << CATEGORY << "===> equal_range" << ENDL;
	print_map(mapA, "mapA");
	std::pair<typename map<int, string>::iterator, typename map<int, string>::iterator> res3;
	FILE << "res3 = mapA.equal_range(20);" << ENDL; res3 = mapA.equal_range(20);
	FILE << "res3.first : " << OUTPUT << res3.first->first << " " << res3.first->second << ENDL;
	FILE << "res3.second : " << OUTPUT << res3.second->first << " " << res3.second->second << ENDL;
	FILE << "res3 = mapA.equal_range(11);" << ENDL; res3 = mapA.equal_range(11);
	FILE << "res3.first : " << OUTPUT << res3.first->first << " " << res3.first->second << ENDL;
	FILE << "res3.second : " << OUTPUT << res3.second->first << " " << res3.second->second << ENDL;
	FILE << "res3 = mapA.equal_range(33);" << ENDL; res3 = mapA.equal_range(33);
	FILE << "res3.first : " << OUTPUT << res3.first->first << " " << res3.first->second << ENDL;
	FILE << "res3.second == mapA.end() : " << OUTPUT << std::boolalpha << (res3.second == mapA.end()) << ENDL;
	FILE << "res3 = mapA.equal_range(34);" << ENDL; res3 = mapA.equal_range(34);
	FILE << "res3.first == mapA.end() : " << OUTPUT << std::boolalpha << (res3.first == mapA.end()) << ENDL;
	FILE << "res3.second == mapA.end() : " << OUTPUT << std::boolalpha << (res3.second == mapA.end()) << ENDL;
	std::pair<typename map<int, string>::const_iterator, typename map<int, string>::const_iterator> res4;
	FILE << "res4 = mapJ.equal_range(20);" << ENDL; res4 = mapJ.equal_range(20);
	FILE << "res4.first : " << OUTPUT << res4.first->first << " " << res4.first->second << ENDL;
	FILE << "res4.second : " << OUTPUT << res4.second->first << " " << res4.second->second << ENDL;
	FILE << "res4 = mapJ.equal_range(11);" << ENDL; res4 = mapJ.equal_range(11);
	FILE << "res4.first : " << OUTPUT << res4.first->first << " " << res4.first->second << ENDL;
	FILE << "res4.second : " << OUTPUT << res4.second->first << " " << res4.second->second << ENDL;
	FILE << "res4 = mapJ.equal_range(33);" << ENDL; res4 = mapJ.equal_range(33);
	FILE << "res4.first : " << OUTPUT << res4.first->first << " " << res4.first->second << ENDL;
	FILE << "res4.second == mapJ.end() : " << OUTPUT << std::boolalpha << (res4.second == mapJ.end()) << ENDL;
	FILE << "res4 = mapJ.equal_range(34);" << ENDL; res4 = mapJ.equal_range(34);
	FILE << "res4.first == mapJ.end() : " << OUTPUT << std::boolalpha << (res4.first == mapJ.end()) << ENDL;
	FILE << "res4.second == mapJ.end() : " << OUTPUT << std::boolalpha << (res4.second == mapJ.end()) << ENDL;
	FILE << ENDL;

	FILE << SUBTITLE << "Allocator" << ENDL;
	FILE << CATEGORY << "===> get_allocator" << ENDL;
	FILE << "map<int, string> mymap; pair<int const, string> * p;" << ENDL; map<int, string> mymap; pair<int const, string> * p;
	FILE << "p = mymap.get_allocator().allocate(5);" << ENDL; p = mymap.get_allocator().allocate(5);
	FILE << "mymap.get_allocator().deallocate(p,5);" << ENDL; mymap.get_allocator().deallocate(p,5);
	FILE << ENDL;

	FILE << SUBTITLE << "Exceptions" << ENDL;
	FILE << CATEGORY << "===> Exception-safety test with ThrowingExceptionClass, "
						"a class which throws an exception in copy constructor" << ENDL;
	FILE << "ThrowingExceptionClass throwingInstance;" << ENDL; ThrowingExceptionClass throwingInstance;
	FILE << "map<int, ThrowingExceptionClass> mapF;" << ENDL; map<int, ThrowingExceptionClass> mapF;
	FILE << "try {mapF.insert(make_pair(0, throwingInstance);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {mapF.insert(make_pair(0, throwingInstance));}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapF, "mapF");
	FILE << ENDL;

	FILE << CATEGORY << "===> Exception-safety test with ThrowingExceptionClass2, "
						"a class which throws an exception in default constructor" << ENDL;
	FILE << "map<int, ThrowingExceptionClass2> mapG;" << ENDL; map<int, ThrowingExceptionClass2> mapG;
	FILE << "ThrowingExceptionClass2 throwingInstance2(3);" << ENDL; ThrowingExceptionClass2 throwingInstance2(3);
	FILE << "try {mapG.insert(make_pair(0, throwingInstance2);}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {mapG.insert(make_pair(0, throwingInstance2));}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapG, "mapG");
	FILE << "try {cout << \"mapG[23] : \" << mapG[23];}" << ENDL;
	FILE << "catch(...) {std::cout << \"catched exception\" << std::endl;}" << ENDL;
	try {FILE << "mapG[23] : " << OUTPUT << mapG[23] << ENDL;}
	catch(...) {FILE << OUTPUT << "catched exception" << ENDL;}
	print_map(mapG, "mapG");
	FILE << ENDL;

	FILE << TITLE << "=> ENDING map tests" << ENDL << ENDL;
}

int
main(void)
{
    test_map<ft::map>();
}
