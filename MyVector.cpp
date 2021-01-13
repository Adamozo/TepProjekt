#include "MyVector.h"
#include "MyVecException.cpp"

using namespace std;

template <typename T>
MyVector<T>::MyVector()
{
	vec = new(nothrow) T[DEFAULT_SIZE];
	isVertical = true;
	
	if (vec != nullptr)
		size = DEFAULT_SIZE;
	else
		size = 0;
}

template<typename T>
MyVector<T>::MyVector(int length, bool vertical)
{
	if (length > 0)
	{
		vec = new(nothrow) T[length];
		isVertical = vertical;
		
		if (vec != nullptr)
			size = length;
		else
			size = 0;
	}
	else
	{
		vec = nullptr;
		size = 0;
		isVertical = vertical;
	}
}

template <typename T>
MyVector<T>::MyVector(const MyVector& pcOther)
{
	
	isVertical = pcOther.isVertical;
	
	if (pcOther.vec != nullptr)
	{
		size = pcOther.size;

		vec = new T[size];

		for (int i = 0; i < size; i++)
			vec[i] = pcOther.vec[i];
	}

	else
	{
		vec = nullptr;
		size = 0;
	}


	cout << "COPY"<<endl;
}

template <typename T>
MyVector<T>::MyVector(MyVector&& pcOther)
{
	vec = pcOther.vec;
	isVertical = pcOther.isVertical;
	size = pcOther.size;


	pcOther.vec = nullptr;
	pcOther.size = 0;

	cout << "MOVE"<<endl;
}

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] vec;
	size = 0;

	cout << "DESTR"<<endl;
}

template<typename T>
bool MyVector<T>::setValueAt(int indeks,const T& value)
{
	if(vec == nullptr || indeks < 0 || indeks >= size)
		return false;

	else
	{
		vec[indeks] = value;
		return true;
	}
}

template<typename T>
T MyVector<T>::operator*(const MyVector& pcOther)
{
	if (size == pcOther.size && vec != nullptr && pcOther.vec != nullptr)
	{
		T product = T();

		for (int i = 0; i < size; i++)
			product += vec[i] * pcOther.vec[i];

		return product;
	}

	else
		throw MyVecException(DEFALUT_MyVectorDotProductError);

	
}

template<typename T>
MyVector<T> MyVector<T>::operator*(const T& value)
{
	if (vec != nullptr)
	{
		MyVector<T> temp(size,isVertical);

		bool check;

		for (int i = 0; i < size; i++)
		{
			check = temp.setValueAt(i, vec[i] * value);

			if(!check) throw MyVecException(DEFALUT_MyVectorDotProductError);
		}

		return move(temp);
	}

	else
		throw MyVecException(DEFALUT_MyVectorDotProductError);


}

template<typename T>
T MyVector<T>::dotProduct(const MyVector& pcOther)
{
	if (size == pcOther.size && vec != nullptr && pcOther.vec != nullptr)
	{
		T product = T();

		for (int i = 0; i < size; i++)
			product += vec[i] * pcOther.vec[i];

		return product;
	}

	else
		throw MyVecException(DEFALUT_MyVectorDotProductError);
}

template<typename T>
void MyVector<T>::print()
{
	if (vec == nullptr)
		cout << endl << "vec = nullptr";

	else
	{
		for (int i = 0; i < size; i++)
			cout << vec[i] << " ";
	}

	cout << endl;
}

template<typename T>
bool MyVector<T>::getIsVertical()
{
	return isVertical;
}

template<typename T>
int MyVector<T>::getSize()
{
	return size;
}

template<typename T>
T MyVector<T>::getElement(int indeks)
{
	if (vec == nullptr)
		throw MyVecException(DEFALUT_LackOfVectorError);

	else if(indeks < 0 || indeks >= size)
		throw MyVecException(DEFALUT_GetElementWrongIndeksError);

	else
		return vec[indeks];

}
	
template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& pcOther)
{
	if (this != &pcOther)
	{
		delete[] vec;

		vec = pcOther.vec;
		size = pcOther.size;
		isVertical = pcOther.isVertical;

		pcOther.vec = nullptr;
	}

	return *this;
}