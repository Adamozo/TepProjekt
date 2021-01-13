#pragma once
#include "iostream" 


static const int DEFAULT_SIZE = 5;

using namespace std;

static const string DEFALUT_MyVectorDotProductError = "MyVectorDotProductError";
static const string DEFALUT_GetElementWrongIndeksError = "GetElementWrongIndeksError";
static const string DEFALUT_LackOfVectorError = "LackOfVectorError";

template <typename T>class MyVector
{
private:
	T* vec;
	bool isVertical;
	int size;

public:

	MyVector();
	MyVector(int size, bool vertical = true);
	MyVector(const MyVector& pcOther);
	MyVector(MyVector&& pcOther);
	~MyVector();
	bool setValueAt(int indeks, const T& value);
	T operator*(const MyVector& pcOther);
	MyVector operator*(const T& value);
	T dotProduct(const MyVector& pcOther);
	MyVector& operator=(MyVector&& pcOther);
	void print();
	int getSize();
	bool getIsVertical();
	T getElement(int indeks);
};

