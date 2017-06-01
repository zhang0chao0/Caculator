#ifndef STACK_H
#define STACK_H

#include<iostream>
#include<assert.h>

#define MaxSize 100

template<class T>
class Stack
{
private:
	T *elements;                    //存放栈中元素
	int top;                        //栈顶指针
	int Max;                        //最大容纳个数
	void overflowProcess();         //溢出处理
public:
	Stack(int sz = 50);             //构造函数
	~Stack(){ delete[]elements; }   //析构函数
	void Push(const T&x);           //压栈
	bool Pop(T&x);                  //弹栈
	bool getTop(T&x)                //获得栈顶元素
	{
		if (IsEmpty()) return false;
		x = elements[top];
		return true;
	}
	bool IsEmpty()const             //是否为空
	{
		return (top == -1) ? true : false;
	}
	bool IsFull() const             //是否慢
	{
		return (top == Max - 1) ? true : false;
	}
	int getSize() const             //栈中元素
	{
		return top + 1;
	}
	void MakeEmpty(){ top = -1; }   //清空栈
	//重载<<
	//friend ostream& operator<< (ostream&os, Stack<T> &s);
};
//*******************************************构造函数
template<class T>
Stack<T>::Stack(int sz) :top(-1), Max(sz)
{
	elements = new T[Max];
	assert(elements != nullptr);
	//*********************当()参数为假，结束程序
}
//*******************************************溢出函数
template<class T>
void Stack<T>::overflowProcess()
{
	//*************************加100个
	T *newArray = new T[Max + MaxSize];
	assert(newArray != nullptr);
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	Max = Max + MaxSize;
	delete[]elements;
	elements = newArray;
}
//*******************************************压栈
template<class T>
void Stack<T>::Push(const T&x)
{
	if (IsFull() == true)
		overflowProcess();
	elements[++top] = x;
}
//********************************************弹栈
template<class T>
bool Stack<T>::Pop(T &x)
{
	if (IsEmpty() == true)
		return false;
	x = elements[top--];
	return true;
}
//******************************************重载<<
/*template<class T>
ostream& operator<< (ostream&os, Stack<T> &s)
{
	os << "top=" << s.top << endl;
	for (int i = 0; i < s.top; i++)
	{
		os << i << ":" << s.elements[i] << endl;
	}
	return os;
}*/

#endif