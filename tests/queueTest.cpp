#include "queue.hpp"
#include <queue>
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

template <template <class T, class Container = deque<T> > class queue>
void
test_queue(void)
{
	FILE << TITLE << std::endl << "=> STARTING queue tests" << ENDL;
	FILE << TITLE << std::endl << "=> deque" << ENDL;

	FILE << "queue<int> queueA;" << ENDL; queue<int> queueA;
	FILE << "queueA.empty() : " << std::boolalpha << OUTPUT << queueA.empty() << ENDL;
	FILE << "queueA.size() : " << OUTPUT << queueA.size() << ENDL;

	FILE << "queueA.push(0);" << ENDL; queueA.push(0);
	FILE << "queueA.front() : " << OUTPUT << queueA.front() << ENDL;
	FILE << "queueA.back() : " << OUTPUT << queueA.back() << ENDL;
	FILE << "queueA.empty() : " << std::boolalpha << OUTPUT << queueA.empty() << ENDL;
	FILE << "queueA.size() : " << OUTPUT << queueA.size() << ENDL;

	FILE << "queueA.push(1);" << ENDL; queueA.push(1);
	FILE << "queueA.front() : " << OUTPUT << queueA.front() << ENDL;
	FILE << "queueA.back() : " << OUTPUT << queueA.back() << ENDL;
	FILE << "queueA.push(2);" << ENDL; queueA.push(2);
	FILE << "queueA.front() : " << OUTPUT << queueA.front() << ENDL;
	FILE << "queueA.back() : " << OUTPUT << queueA.back() << ENDL;
	FILE << "queueA.pop();" << ENDL; queueA.pop();
	FILE << "queueA.front() : " << OUTPUT << queueA.front() << ENDL;
	FILE << "queueA.back() : " << OUTPUT << queueA.back() << ENDL;

	FILE << "queue<int> queueB(queueA);" << ENDL; queue<int> queueB(queueA);
	FILE << "queueB.front() : " << OUTPUT << queueB.front() << ENDL;
	FILE << "queueB.back() : " << OUTPUT << queueB.back() << ENDL;
	FILE << "queueB.empty() : " << std::boolalpha << OUTPUT << queueB.empty() << ENDL;
	FILE << "queueB.size() : " << OUTPUT << queueB.size() << ENDL;
	FILE << "queueA.push(42);" << ENDL; queueA.push(42);
	FILE << "queueB.front() : " << OUTPUT << queueB.front() << ENDL;
	FILE << "queueB.back() : " << OUTPUT << queueB.back() << ENDL;
	FILE << "queueB = queueA;" << ENDL; queueB = queueA;
	FILE << "queueB.front() : " << OUTPUT << queueB.front() << ENDL;
	FILE << "queueB.back() : " << OUTPUT << queueB.back() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> const queueConst(queueA);" << ENDL; queue<int> const queueConst(queueA);
	FILE << "queueConst.front() : " << OUTPUT << queueConst.front() << ENDL;
	FILE << "queueConst.back() : " << OUTPUT << queueConst.back() << ENDL;
	FILE << "queueConst.empty() : " << std::boolalpha << OUTPUT << queueConst.empty() << ENDL;
	FILE << "queueConst.size() : " << OUTPUT << queueConst.size() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> queueEmpty;" << ENDL; queue<int> queueEmpty;
	FILE << "queueConst == queueA : " << std::boolalpha << OUTPUT << (queueConst == queueA) << ENDL;
	FILE << "queueConst == queueEmpty : " << std::boolalpha << OUTPUT << (queueConst == queueEmpty) << ENDL;
	FILE << "queueConst != queueA : " << std::boolalpha << OUTPUT << (queueConst != queueA) << ENDL;
	FILE << "queueConst != queueEmpty : " << std::boolalpha << OUTPUT << (queueConst != queueEmpty) << ENDL;
	FILE << "queueConst < queueA : " << std::boolalpha << OUTPUT << (queueConst < queueA) << ENDL;
	FILE << "queueEmpty < queueConst: " << std::boolalpha << OUTPUT << (queueEmpty < queueConst) << ENDL;
	FILE << "queueConst <= queueA : " << std::boolalpha << OUTPUT << (queueConst <= queueA) << ENDL;
	FILE << "queueEmpty <= queueConst: " << std::boolalpha << OUTPUT << (queueEmpty <= queueConst) << ENDL;
	FILE << "queueConst > queueA : " << std::boolalpha << OUTPUT << (queueConst > queueA) << ENDL;
	FILE << "queueEmpty > queueConst: " << std::boolalpha << OUTPUT << (queueEmpty > queueConst) << ENDL;
	FILE << "queueConst >= queueA : " << std::boolalpha << OUTPUT << (queueConst >= queueA) << ENDL;
	FILE << "queueEmpty >= queueConst: " << std::boolalpha << OUTPUT << (queueEmpty >= queueConst) << ENDL;


	FILE << TITLE << std::endl << "=> vector" << ENDL;

	FILE << "queue<int> vectorqueueA;" << ENDL; queue<int> vectorqueueA;
	FILE << "vectorqueueA.empty() : " << std::boolalpha << OUTPUT << vectorqueueA.empty() << ENDL;
	FILE << "vectorqueueA.size() : " << OUTPUT << vectorqueueA.size() << ENDL;

	FILE << "vectorqueueA.push(0);" << ENDL; vectorqueueA.push(0);
	FILE << "vectorqueueA.front() : " << OUTPUT << vectorqueueA.front() << ENDL;
	FILE << "vectorqueueA.back() : " << OUTPUT << vectorqueueA.back() << ENDL;
	FILE << "vectorqueueA.empty() : " << std::boolalpha << OUTPUT << vectorqueueA.empty() << ENDL;
	FILE << "vectorqueueA.size() : " << OUTPUT << vectorqueueA.size() << ENDL;

	FILE << "vectorqueueA.push(1);" << ENDL; vectorqueueA.push(1);
	FILE << "vectorqueueA.front() : " << OUTPUT << vectorqueueA.front() << ENDL;
	FILE << "vectorqueueA.back() : " << OUTPUT << vectorqueueA.back() << ENDL;
	FILE << "vectorqueueA.push(2);" << ENDL; vectorqueueA.push(2);
	FILE << "vectorqueueA.front() : " << OUTPUT << vectorqueueA.front() << ENDL;
	FILE << "vectorqueueA.back() : " << OUTPUT << vectorqueueA.back() << ENDL;
	FILE << "vectorqueueA.pop();" << ENDL; vectorqueueA.pop();
	FILE << "vectorqueueA.front() : " << OUTPUT << vectorqueueA.front() << ENDL;
	FILE << "vectorqueueA.back() : " << OUTPUT << vectorqueueA.back() << ENDL;

	FILE << "queue<int> vectorqueueB(vectorqueueA);" << ENDL; queue<int> vectorqueueB(vectorqueueA);
	FILE << "vectorqueueB.front() : " << OUTPUT << vectorqueueB.front() << ENDL;
	FILE << "vectorqueueB.back() : " << OUTPUT << vectorqueueB.back() << ENDL;
	FILE << "vectorqueueB.empty() : " << std::boolalpha << OUTPUT << vectorqueueB.empty() << ENDL;
	FILE << "vectorqueueB.size() : " << OUTPUT << vectorqueueB.size() << ENDL;
	FILE << "vectorqueueA.push(42);" << ENDL; vectorqueueA.push(42);
	FILE << "vectorqueueB.front() : " << OUTPUT << vectorqueueB.front() << ENDL;
	FILE << "vectorqueueB.back() : " << OUTPUT << vectorqueueB.back() << ENDL;
	FILE << "vectorqueueB = vectorqueueA;" << ENDL; vectorqueueB = vectorqueueA;
	FILE << "vectorqueueB.front() : " << OUTPUT << vectorqueueB.front() << ENDL;
	FILE << "vectorqueueB.back() : " << OUTPUT << vectorqueueB.back() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> const vectorqueueConst(vectorqueueA);" << ENDL; queue<int> const vectorqueueConst(vectorqueueA);
	FILE << "vectorqueueConst.front() : " << OUTPUT << vectorqueueConst.front() << ENDL;
	FILE << "vectorqueueConst.back() : " << OUTPUT << vectorqueueConst.back() << ENDL;
	FILE << "vectorqueueConst.empty() : " << std::boolalpha << OUTPUT << vectorqueueConst.empty() << ENDL;
	FILE << "vectorqueueConst.size() : " << OUTPUT << vectorqueueConst.size() << ENDL;

	FILE << ENDL;
	FILE << "queue<int> vectorqueueEmpty;" << ENDL; queue<int> vectorqueueEmpty;
	FILE << "vectorqueueConst == vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst == vectorqueueA) << ENDL;
	FILE << "vectorqueueConst == vectorqueueEmpty : " << std::boolalpha << OUTPUT << (vectorqueueConst == vectorqueueEmpty) << ENDL;
	FILE << "vectorqueueConst != vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst != vectorqueueA) << ENDL;
	FILE << "vectorqueueConst != vectorqueueEmpty : " << std::boolalpha << OUTPUT << (vectorqueueConst != vectorqueueEmpty) << ENDL;
	FILE << "vectorqueueConst < vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst < vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty < vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty < vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst <= vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst <= vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty <= vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty <= vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst > vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst > vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty > vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty > vectorqueueConst) << ENDL;
	FILE << "vectorqueueConst >= vectorqueueA : " << std::boolalpha << OUTPUT << (vectorqueueConst >= vectorqueueA) << ENDL;
	FILE << "vectorqueueEmpty >= vectorqueueConst: " << std::boolalpha << OUTPUT << (vectorqueueEmpty >= vectorqueueConst) << ENDL;

	FILE << TITLE << "=> ENDING queue tests" << ENDL << ENDL;
}

int
main(void)
{
    test_queue<ft::queue>();
}
