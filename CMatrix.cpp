#include "CMatrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Exception.cpp"

using namespace std;

template<typename T>
CMatrix<T>::CMatrix()
{
	matrix = new(nothrow) T*[DEFAULT_NUMBER_OF_ROWS];

	if (matrix != nullptr)
	{
		numberOfRows = DEFAULT_NUMBER_OF_ROWS;
		numberOfColumns = DEFAULT_NUMBER_OF_COLUMNS;

		for (int i = 0; i < numberOfRows; i++)
		{
			matrix[i] = new(nothrow) T[numberOfColumns];
			if (matrix[i] == nullptr)
			{
				i = numberOfRows + 1;
				matrix = nullptr;
				numberOfColumns = 0; // aby nie powodowa³o b³êdu gdzieœ przy rozbudowie programu
				numberOfRows = 0;    //
				
			}
		}

	}
}

template<typename T>
CMatrix<T>::CMatrix(int numberOfColumns, int numberOfRows, bool useRand)
{
	if (numberOfRows > 0 && numberOfColumns > 0) {
	
		matrix = new(nothrow) T*[numberOfRows];

		if (matrix != nullptr)
		{
			this->numberOfColumns = numberOfColumns;
			this->numberOfRows = numberOfRows;


			for (int i = 0; i < numberOfRows; i++)
			{
				matrix[i] = new(nothrow) T[numberOfColumns];
				if (matrix[i] == nullptr)
				{
					i = numberOfRows + 1;
					matrix = nullptr;
					numberOfColumns = 0; // aby nie powodowa³o b³êdu gdzieœ przy rozbudowie programu
					numberOfRows = 0;    //

					useRand = false;
				}
			}

			if (useRand) {
				for (int i = 0; i < numberOfRows; i++) {
					for (int j = 0; j < numberOfColumns; j++)
						matrix[i][j] = rand() % 100 + 1;
				}
			}
		}

	}

	else
	{
		matrix = nullptr;
		this->numberOfColumns = 0;
		this->numberOfRows = 0;
	}
		
}

template<typename T>
CMatrix<T>::~CMatrix()
{
	if (this->matrix != nullptr) 
	{
		for (int i = 0; i < numberOfRows; i++)
			delete[] matrix[i];

		delete[] matrix;
	}
	cout << "DELETE" << endl;
}

template<typename T>
CMatrix<T>::CMatrix(const CMatrix& pcOther)
{
	numberOfColumns = pcOther.numberOfColumns;
	numberOfRows = pcOther.numberOfRows;
	
	if (pcOther.matrix != nullptr)
	{
		matrix = new T * [numberOfRows];

		for (int i = 0; i < numberOfRows; i++)
			matrix[i] = new T[numberOfColumns];

		for (int i = 0; i < numberOfRows; i++)
		{
			for (int j = 0; j < numberOfColumns; j++)
			{
				matrix[i][j] = pcOther.matrix[i][j];
			}
		}
	}

	else
		matrix = nullptr;
	
	cout << "COPY"<<endl;
}

template<typename T>
CMatrix<T>::CMatrix(CMatrix&& pcOther)
{
	numberOfColumns = pcOther.numberOfColumns;
	numberOfRows = pcOther.numberOfRows;
	matrix = pcOther.matrix;


	pcOther.matrix = nullptr;
	pcOther.numberOfColumns = 0;
	pcOther.numberOfColumns = 0;

	cout << "MOVE"<<endl;
}

template<typename T>
CMatrix<T>::CMatrix(MyVector<T>&& pcOther)
{
	if (pcOther.getSize()>0)
	{
		if (pcOther.getIsVertical())
		{
		
			matrix = new(nothrow) T*[pcOther.getSize()];

			if (matrix != nullptr)
			{
				numberOfRows = pcOther.getSize();
				numberOfColumns = 1;

				for (int i = 0; i < numberOfRows; i++)
				{
					matrix[i] = new(nothrow) T[1];
					if (matrix[i] == nullptr)
					{
						i = numberOfRows + 1;
						matrix = nullptr;
						numberOfColumns = 0; // aby nie powodowa³o b³êdu gdzieœ przy rozbudowie programu
						numberOfRows = 0;    //

					}
				}

				for (int i = 0; i < numberOfRows; i++)
					matrix[i][0] = pcOther.getElement(i);

			}
		}
		else
		{
			matrix = new(nothrow) T * [1];

			if (matrix != nullptr)
			{
				numberOfRows = 1;
				numberOfColumns = pcOther.getSize();

				matrix[0] = new(nothrow) T[numberOfColumns];

				if (matrix[0] == nullptr)
				{
					matrix = nullptr;
					numberOfColumns = 0; // aby nie powodowa³o b³êdu gdzieœ przy rozbudowie programu
					numberOfRows = 0;    //

				}

				for (int i = 0; i < numberOfColumns; i++)
					matrix[0][i] = pcOther.getElement(i);

			}
		}

	}

	else
	{
		matrix = nullptr;
		numberOfColumns = 0;
		numberOfRows = 0;
	}
}

template<typename T>
int CMatrix<T>::getNumberOfColumns()
{
	return numberOfColumns;
}

template<typename T>
int CMatrix<T>::getNumberOfRows()
{
	return numberOfRows;
}

template<typename T>
bool CMatrix<T>::setNumberOfColumns(int newNumberOfColumns)
{
	if (newNumberOfColumns <= 0)
		return false;

	CMatrix<T> temp(newNumberOfColumns, numberOfRows, false);

	if (temp.matrix == nullptr)
		return false;

	if (newNumberOfColumns < this->numberOfColumns) {
		for (int i = 0; i < numberOfRows; i++)
			for (int j = 0; j < newNumberOfColumns; j++)
				temp.matrix[i][j] = matrix[i][j];
	}
	else {
		for (int i = 0; i < numberOfRows; i++)
			for (int j = 0; j < newNumberOfColumns; j++) {
				if (this->numberOfColumns > j)
					temp.matrix[i][j] = matrix[i][j];
				else
					temp.matrix[i][j] = T();
			}
	}

	if (matrix != nullptr) {
		for (int i = 0; i < this->numberOfRows; i++)
			delete[] matrix[i];

		delete[] matrix;
	}

	numberOfColumns = temp.numberOfColumns;
	this->numberOfRows = numberOfRows;
	matrix = temp.matrix;
	temp.matrix = nullptr;

	return true;
}

template <typename T>
bool CMatrix<T>::setNumberOfRows(int numberOfRows) {
	if (numberOfRows <= 0)
		return false;

	CMatrix<T> temp(numberOfColumns,numberOfRows,false);

	if (temp.matrix == nullptr)
		return false;

	if (numberOfRows < this->numberOfRows) {
		for (int i = 0; i < numberOfRows; i++)
			for (int j = 0; j < numberOfColumns; j++)
				temp.matrix[i][j] = matrix[i][j];
	}
	else {
		for (int i = 0; i < numberOfRows; i++)
			for (int j = 0; j < numberOfColumns; j++) {
				if (this->numberOfRows > i)
					temp.matrix[i][j] = matrix[i][j];
				else
					temp.matrix[i][j] = T();
			}
	}

	if (matrix != nullptr) {
		for (int i = 0; i < this->numberOfRows; i++)
			delete[] matrix[i];

		delete[] matrix;
	}

	numberOfColumns = temp.numberOfColumns;
	this->numberOfRows = numberOfRows;
	matrix = temp.matrix;
	temp.matrix = nullptr;

	return true;
}

template<typename T>
bool CMatrix<T>::setElement(int rowNumber, int columnNumber, T newValue)
{

	if (rowNumber >= numberOfRows || columnNumber >= numberOfColumns || rowNumber < 0 || columnNumber < 0)
		return false;

	matrix[rowNumber][columnNumber] = newValue;

	return true;
}

template<typename T>
T CMatrix<T>::getElement(int rowNumber, int columnNumber)
{
	if (rowNumber >= numberOfRows || columnNumber >= numberOfColumns || rowNumber < 0 || columnNumber < 0)
		throw Exception(DEFALUT_GetElementWrongIndeksError);

	return matrix[rowNumber][columnNumber];

}

template<typename T>
CMatrix<T> CMatrix<T>::getNewMatrix(int rowNumber, int columnNumber, bool rand)
{
	CMatrix<T> temp(rowNumber, columnNumber, rand);

	return move(temp);
}

template<typename T>
void CMatrix<T>::printMatrix()
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				cout << matrix[i][j] << " ";

			cout << endl;
		}
	}

	else
		cout << endl << "matrix = nullptr" << endl;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfRows, pcOther.numberOfColumns,false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = matrix[i][j] + pcOther.matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::add(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfRows, pcOther.numberOfColumns, false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = matrix[i][j] + pcOther.matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator+=(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				matrix[i][j] = matrix[i][j] + pcOther.matrix[i][j];
		}


		return *this;
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T>& CMatrix<T>::addEq(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);



		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				matrix[i][j] = matrix[i][j] + pcOther.matrix[i][j];
		}

		return *this;
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfRows, pcOther.numberOfColumns, false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = matrix[i][j] - pcOther.matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::sub(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfRows, pcOther.numberOfColumns, false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = matrix[i][j] - pcOther.matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				matrix[i][j] = matrix[i][j] - pcOther.matrix[i][j];
		}

		return *this;
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T>& CMatrix<T>::subEq(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr) {
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				matrix[i][j] = matrix[i][j] - pcOther.matrix[i][j];
		}

		return *this;
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator=(CMatrix&& pcOther)
{
	if (this == &pcOther) return *this;

	else if (matrix != nullptr)
	{
		for (int i = 0; i < numberOfRows; i++)
			delete[] matrix[i];

		delete[] matrix;
	}

	numberOfColumns = pcOther.numberOfColumns;
	numberOfRows = pcOther.numberOfRows;
	matrix = pcOther.matrix;
	pcOther.matrix = nullptr;

	return *this;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const T& multiplier)
{
	if(matrix != nullptr)
	{
		CMatrix<T> tempMatrix(numberOfRows, numberOfColumns, false);

		for(int i = 0; i < numberOfRows; i++)
		{
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = multiplier * matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::multScalar(const T& multiplier)
{
	if (matrix != nullptr)
	{
		CMatrix<T> tempMatrix(numberOfRows, numberOfColumns, false);

		for (int i = 0; i < numberOfRows; i++)
		{
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[i][j] = multiplier * matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr)
	{
		if (numberOfColumns != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfColumns,numberOfRows);

		for (int i = 0; i < numberOfRows; i++)
		{
			for (int j = 0; j < pcOther.numberOfColumns; j++)
			{
				T sum = T();

				for (int k = 0; k < pcOther.numberOfRows; k++)
					sum += matrix[i][k] * pcOther.matrix[k][j];

				tempMatrix.matrix[i][j] = sum;
			}
		}
		

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::multMatrix(const CMatrix& pcOther)
{
	if (matrix != nullptr && pcOther.matrix != nullptr)
	{
		if (numberOfColumns != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		CMatrix<T> tempMatrix(pcOther.numberOfColumns, numberOfRows);

		for (int i = 0; i < numberOfRows; i++)
		{
			for (int j = 0; j < pcOther.numberOfColumns; j++)
			{
				T sum = T();

				for (int k = 0; k < pcOther.numberOfRows; k++)
					sum += matrix[i][k] * pcOther.matrix[k][j];

				tempMatrix.matrix[i][j] = sum;
			}
		}


		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);

}

/*
template<typename T>
T CMatrix<T>::dotProduct(CMatrix& pcOther)
{
	T scalar = T();

	if (matrix != nullptr && pcOther.matrix != nullptr)
	{
		if (numberOfColumns != pcOther.numberOfColumns || numberOfRows != pcOther.numberOfRows)
			throw Exception(DEFALUT_DiferentSizeOfMatrixsError);

		else if (numberOfColumns == 1)
		{
			for (int i = 0; i < numberOfRows; i++)
				scalar += matrix[i][0] * pcOther.matrix[i][0];

			return scalar;
		}

		else if (numberOfRows == 1)
		{
			for (int i = 0; i < numberOfColumns; i++)
				scalar += matrix[0][i]*pcOther.matrix[0][i];

			return scalar;
		}

		else
			throw invalid_argument("invalid input");
	}

	throw invalid_argument("invalid input");
}

*/

template<typename T>
CMatrix<T> CMatrix<T>::operator~() 
{
	if (matrix != nullptr) {
		CMatrix<T> tempMatrix(numberOfColumns, numberOfRows,false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[j][i] = this->matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
CMatrix<T> CMatrix<T>::getTranspoze()
{
	if (matrix != nullptr) {
		CMatrix<T> tempMatrix(numberOfColumns, numberOfRows, false);

		for (int i = 0; i < numberOfRows; i++) {
			for (int j = 0; j < numberOfColumns; j++)
				tempMatrix.matrix[j][i] = this->matrix[i][j];
		}

		return move(tempMatrix);
	}

	throw Exception(DEFALUT_EmptyMatrixError);
}

template<typename T>
MyVector<T> CMatrix<T>::createVectorFromMatrixRow(int rowNumber)
{
	if(matrix == nullptr)
		throw Exception(DEFALUT_EmptyMatrixError);

	else if (rowNumber<0 || rowNumber >= numberOfRows)
		throw Exception(DEFALUT_WrongRowNumberError);

	else
	{
		MyVector<T> temp(numberOfColumns, false);

		bool check = false;

		for (int i = 0; i < numberOfColumns; i++)
		{
			check = temp.setValueAt(i, matrix[rowNumber][i]);

			if (check == false) throw Exception(DEFALUT_VectorValueNotSet);
		}

		return move(temp);
	}

	
}

template<typename T>
MyVector<T> CMatrix<T>::createVectorFromMarixColumn(int columnNumber)
{
	if (matrix == nullptr)
		throw Exception(DEFALUT_EmptyMatrixError);

	else if(columnNumber < 0 || columnNumber >= numberOfColumns)
		throw Exception(DEFALUT_WrongColumnNumberError);

	else
	{
		MyVector<T> temp(numberOfRows);

		bool check;

		for (int i = 0; i < numberOfRows; i++)
		{
			check = temp.setValueAt(i, matrix[i][columnNumber]);

			if (check == false) throw Exception(DEFALUT_VectorValueNotSet);
		}

		return move(temp);
	}

}

template<typename T>
bool CMatrix<T>::indentityMatrix()
{

	if (matrix == nullptr || numberOfColumns != numberOfRows)
		return false;

	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}

	return true;
}

template <typename T>
bool CMatrix<T>::readFromFile(string fileName) {

	string line;
	fstream file;
	string singleWord;

	int wordCounter = 0;
	int lineCounter = 0;
	vector<string> wordsFromFile;

	file.open(fileName);
	if (file.good()) {
		while (!file.eof()) {
			lineCounter++;
			getline(file, line);
			stringstream ss(line);
			while (getline(ss, singleWord, ' ')) {
				wordCounter++;
				wordsFromFile.push_back(singleWord);
			}
		}
		file.close();
	}
	else 
		return false;

	if (wordCounter % lineCounter != 0)
		return false;

	CMatrix temp(wordCounter / lineCounter,lineCounter);

	for (int i = 0; i < lineCounter; i++)
		for (int j = 0; j < wordCounter / lineCounter; j++)
			temp.matrix[i][j] = (T)stod(wordsFromFile.at(i * (wordCounter / lineCounter) + j));

	numberOfColumns = temp.numberOfColumns;
	numberOfRows = temp.numberOfRows;
	matrix = temp.matrix;

	temp.matrix = nullptr;

	return true;
}