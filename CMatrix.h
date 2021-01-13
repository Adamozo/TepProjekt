#pragma once
#include <iostream>
#include <string>
#include "MyVector.cpp"

static const int DEFAULT_NUMBER_OF_COLUMNS = 5;
static const int DEFAULT_NUMBER_OF_ROWS = 5;



using namespace std;

static const string DEFALUT_DiferentSizeOfMatrixsError = "IncorrectSizeOfMatrixsError";
static const string DEFALUT_EmptyMatrixError = "EmptyMatrixError";
static const string DEFALUT_WrongRowNumberError = "WrongRowNumberError";
static const string DEFALUT_VectorValueNotSet = "VectorValueNotSet";
static const string DEFALUT_WrongColumnNumberError = "WrongColumnNumberError";

template <typename T> class CMatrix
{

private:
	T** matrix;
	int numberOfColumns;
	int numberOfRows;
	

public:
	CMatrix();
	CMatrix(int numberOfColumns, int numberOfRows, bool useRand  = false);
	~CMatrix();
	CMatrix(const CMatrix& pcOther);
	CMatrix(CMatrix&& pcOther);
	CMatrix(MyVector<T>&& pcOther);

	int getNumberOfColumns();
	int getNumberOfRows();

	bool setNumberOfColumns(int newNumberOfColumns);
	bool setNumberOfRows(int newNumberOfRows);
	bool setElement(int rowNumber, int columnNumber, T newValue);

	T getElement(int rowNumber, int columnNumber);
	CMatrix getNewMatrix(int rowNumber, int columnNumber, bool rand = false);

	void printMatrix();

	CMatrix operator+(const CMatrix& pcOther);
	CMatrix add(const CMatrix& pcOther);
	CMatrix& operator+=(const CMatrix& pcOther);
	CMatrix& addEq(const CMatrix& pcOther);

	CMatrix operator-(const CMatrix& pcOther);
	CMatrix sub(const CMatrix& pcOther);
	CMatrix& operator-=(const CMatrix& pcOther);
	CMatrix& subEq(const CMatrix& pcOther);

	CMatrix& operator=(CMatrix&& pcOther);
	CMatrix operator*(const T& multiplier);
	CMatrix multScalar(const T& multiplier);
	CMatrix operator*(const CMatrix& pcOther);
	CMatrix multMatrix(const CMatrix& pcOther);

	T dotProduct(CMatrix& cOther);
	CMatrix operator~();
	CMatrix getTranspoze();

	MyVector<T> createVectorFromMatrixRow(int rowNumber);
	MyVector<T> createVectorFromMarixColumn(int columnNumber);
	bool indentityMatrix();

	bool readFromFile(string fileName);

};
