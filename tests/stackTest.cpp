#include "stack.hpp"
#include <stack>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "vector.hpp"
#include "Color.hpp"
#define TITLE FG_CYAN << BOLD
#define SUBTITLE FG_RED << BOLD
#define CATEGORY FG_DGRAY << BOLD
#define SUBCATEGORY FG_DGRAY
#define OUTPUT FG_GREEN << UNDERLINED
#define FILE std::cout << RESET_ALL
using std::deque;

template <template <class T, class Container = deque<T> > class stack>
void
test_stack(void)
{
	FILE << TITLE << std::endl << "=> STARTING stack tests" << ENDL;
	FILE << TITLE << std::endl << "=> deque" << ENDL;

	FILE << "stack<int> stackA;" << ENDL; stack<int> stackA;
	FILE << "stackA.empty() : " << std::boolalpha << OUTPUT << stackA.empty() << ENDL;
	FILE << "stackA.size() : " << OUTPUT << stackA.size() << ENDL;

	FILE << "stackA.push(0);" << ENDL; stackA.push(0);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.empty() : " << std::boolalpha << OUTPUT << stackA.empty() << ENDL;
	FILE << "stackA.size() : " << OUTPUT << stackA.size() << ENDL;

	FILE << "stackA.push(1);" << ENDL; stackA.push(1);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.push(2);" << ENDL; stackA.push(2);
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;
	FILE << "stackA.pop();" << ENDL; stackA.pop();
	FILE << "stackA.top() : " << OUTPUT << stackA.top() << ENDL;

	FILE << "stack<int> stackB(stackA);" << ENDL; stack<int> stackB(stackA);
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;
	FILE << "stackB.empty() : " << std::boolalpha << OUTPUT << stackB.empty() << ENDL;
	FILE << "stackB.size() : " << OUTPUT << stackB.size() << ENDL;
	FILE << "stackA.push(42);" << ENDL; stackA.push(42);
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;
	FILE << "stackB = stackA;" << ENDL; stackB = stackA;
	FILE << "stackB.top() : " << OUTPUT << stackB.top() << ENDL;

	FILE << ENDL;
	FILE << "stack<int> const stackConst(stackA);" << ENDL; stack<int> const stackConst(stackA);
	FILE << "stackConst.top() : " << OUTPUT << stackConst.top() << ENDL;
	FILE << "stackConst.empty() : " << std::boolalpha << OUTPUT << stackConst.empty() << ENDL;
	FILE << "stackConst.size() : " << OUTPUT << stackConst.size() << ENDL;

	FILE << ENDL;
	FILE << "stack<int> stackEmpty;" << ENDL; stack<int> stackEmpty;
	FILE << "stackConst == stackA : " << std::boolalpha << OUTPUT << (stackConst == stackA) << ENDL;
	FILE << "stackConst == stackEmpty : " << std::boolalpha << OUTPUT << (stackConst == stackEmpty) << ENDL;
	FILE << "stackConst != stackA : " << std::boolalpha << OUTPUT << (stackConst != stackA) << ENDL;
	FILE << "stackConst != stackEmpty : " << std::boolalpha << OUTPUT << (stackConst != stackEmpty) << ENDL;
	FILE << "stackConst < stackA : " << std::boolalpha << OUTPUT << (stackConst < stackA) << ENDL;
	FILE << "stackEmpty < stackConst: " << std::boolalpha << OUTPUT << (stackEmpty < stackConst) << ENDL;
	FILE << "stackConst <= stackA : " << std::boolalpha << OUTPUT << (stackConst <= stackA) << ENDL;
	FILE << "stackEmpty <= stackConst: " << std::boolalpha << OUTPUT << (stackEmpty <= stackConst) << ENDL;
	FILE << "stackConst > stackA : " << std::boolalpha << OUTPUT << (stackConst > stackA) << ENDL;
	FILE << "stackEmpty > stackConst: " << std::boolalpha << OUTPUT << (stackEmpty > stackConst) << ENDL;
	FILE << "stackConst >= stackA : " << std::boolalpha << OUTPUT << (stackConst >= stackA) << ENDL;
	FILE << "stackEmpty >= stackConst: " << std::boolalpha << OUTPUT << (stackEmpty >= stackConst) << ENDL;


	FILE << TITLE << std::endl << "=> vector" << ENDL;

	FILE << "stack<int, ft::vector<int> > vectorstackA;" << ENDL; stack<int, ft::vector<int> > vectorstackA;
	FILE << "vectorstackA.empty() : " << std::boolalpha << OUTPUT << vectorstackA.empty() << ENDL;
	FILE << "vectorstackA.size() : " << OUTPUT << vectorstackA.size() << ENDL;

	FILE << "vectorstackA.push(0);" << ENDL; vectorstackA.push(0);
	FILE << "vectorstackA.top() : " << OUTPUT << vectorstackA.top() << ENDL;
	FILE << "vectorstackA.empty() : " << std::boolalpha << OUTPUT << vectorstackA.empty() << ENDL;
	FILE << "vectorstackA.size() : " << OUTPUT << vectorstackA.size() << ENDL;

	FILE << "vectorstackA.push(1);" << ENDL; vectorstackA.push(1);
	FILE << "vectorstackA.top() : " << OUTPUT << vectorstackA.top() << ENDL;
	FILE << "vectorstackA.push(2);" << ENDL; vectorstackA.push(2);
	FILE << "vectorstackA.top() : " << OUTPUT << vectorstackA.top() << ENDL;
	FILE << "vectorstackA.pop();" << ENDL; vectorstackA.pop();
	FILE << "vectorstackA.top() : " << OUTPUT << vectorstackA.top() << ENDL;

	FILE << "stack<int, ft::vector<int> > vectorstackB(vectorstackA);" << ENDL; stack<int, ft::vector<int> > vectorstackB(vectorstackA);
	FILE << "vectorstackB.top() : " << OUTPUT << vectorstackB.top() << ENDL;
	FILE << "vectorstackB.empty() : " << std::boolalpha << OUTPUT << vectorstackB.empty() << ENDL;
	FILE << "vectorstackB.size() : " << OUTPUT << vectorstackB.size() << ENDL;
	FILE << "vectorstackA.push(42);" << ENDL; vectorstackA.push(42);
	FILE << "vectorstackB.top() : " << OUTPUT << vectorstackB.top() << ENDL;
	FILE << "vectorstackB = vectorstackA;" << ENDL; vectorstackB = vectorstackA;
	FILE << "vectorstackB.top() : " << OUTPUT << vectorstackB.top() << ENDL;

	FILE << ENDL;
	FILE << "stack<int, ft::vector<int> > const vectorstackConst(vectorstackA);" << ENDL; stack<int, ft::vector<int> > const vectorstackConst(vectorstackA);
	FILE << "vectorstackConst.top() : " << OUTPUT << vectorstackConst.top() << ENDL;
	FILE << "vectorstackConst.empty() : " << std::boolalpha << OUTPUT << vectorstackConst.empty() << ENDL;
	FILE << "vectorstackConst.size() : " << OUTPUT << vectorstackConst.size() << ENDL;

	FILE << ENDL;
	FILE << "stack<int, ft::vector<int> > vectorstackEmpty;" << ENDL; stack<int, ft::vector<int> > vectorstackEmpty;
	FILE << "vectorstackConst == vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst == vectorstackA) << ENDL;
	FILE << "vectorstackConst == vectorstackEmpty : " << std::boolalpha << OUTPUT << (vectorstackConst == vectorstackEmpty) << ENDL;
	FILE << "vectorstackConst != vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst != vectorstackA) << ENDL;
	FILE << "vectorstackConst != vectorstackEmpty : " << std::boolalpha << OUTPUT << (vectorstackConst != vectorstackEmpty) << ENDL;
	FILE << "vectorstackConst < vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst < vectorstackA) << ENDL;
	FILE << "vectorstackEmpty < vectorstackConst: " << std::boolalpha << OUTPUT << (vectorstackEmpty < vectorstackConst) << ENDL;
	FILE << "vectorstackConst <= vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst <= vectorstackA) << ENDL;
	FILE << "vectorstackEmpty <= vectorstackConst: " << std::boolalpha << OUTPUT << (vectorstackEmpty <= vectorstackConst) << ENDL;
	FILE << "vectorstackConst > vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst > vectorstackA) << ENDL;
	FILE << "vectorstackEmpty > vectorstackConst: " << std::boolalpha << OUTPUT << (vectorstackEmpty > vectorstackConst) << ENDL;
	FILE << "vectorstackConst >= vectorstackA : " << std::boolalpha << OUTPUT << (vectorstackConst >= vectorstackA) << ENDL;
	FILE << "vectorstackEmpty >= vectorstackConst: " << std::boolalpha << OUTPUT << (vectorstackEmpty >= vectorstackConst) << ENDL;

	FILE << TITLE << "=> ENDING stack tests" << ENDL << ENDL;
}

int
main(void)
{
    test_stack<std::stack>();
}
