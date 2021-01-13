#include <iostream>
#include <iostream>
#include "CMatrix.cpp"

using namespace std;

void test1()
{
	cout << "test 1" << endl;
	CMatrix<int> a;
	a.printMatrix();
	cout << "test 1 end" << endl;
}

void test2()
{
	cout << "test 2" << endl;
	CMatrix<int> a(5,5,true);
	a.printMatrix();
	cout << "test 2 end" << endl;

}

void test3()
{
	cout << "test 3" << endl;
	CMatrix<int> a(500000000, 500000000);
	a.printMatrix();
	cout << "test 3 end" << endl;
}

void test4()
{
	cout << "test 4" << endl;
	CMatrix<int> a(3,3,true);
	a.printMatrix();

	CMatrix<int> b = a;
	cout << endl;
	b.printMatrix();

	cout << "test 4 end" << endl;
}

void test5()
{
	cout << "test 5" << endl;
	CMatrix<int> a(3, 3, true);
	a.printMatrix();

	CMatrix<int> b = move(a);
	cout << endl;
	b.printMatrix();

	cout << "test 5 end" << endl;
}

void test6()
{
	cout << "test 6" << endl;
	MyVector<int> a;
	a.print();

	cout << "test 6 end" << endl;
}

void test7()
{
	cout << "test 7" << endl;
	MyVector<int> a(4,false);
	a.print();

	cout << "test 7 end" << endl;
}

void test8()
{
	cout << "test 8" << endl;
	MyVector<int> a(1000000000000);
	a.print();

	cout << "test 8 end" << endl;
}

void test9()
{
	cout << "test 9" << endl;
	MyVector<int> a(3);
	a.print();

	cout << endl;

	MyVector<int> b = a;
	b.print();

	cout << "test 9 end" << endl;
}

void test10()
{
	cout << "test 10" << endl;
	MyVector<int> a(3);
	a.print();

	cout << endl;

	bool result = a.setValueAt(0,254);
	
	if (result)
		a.print();

	else
		cout << "not set" << endl;


	cout << "test 10 end" << endl;
}

void test11()
{
	cout << "test 11" << endl;
	MyVector<int> a(3);
	a.print();

	cout << endl;

	bool result = a.setValueAt(254, 254);

	if (result)
		a.print();

	else
		cout << "not set" << endl;


	cout << "test 11 end" << endl;
}

void test12()
{
	try
	{
		CMatrix<int> a(3, 3, true);

		a.printMatrix();

		cout << a.getElement(0, 10) << endl;
	}

	catch (Exception m)
	{
		cout << endl << m.what() << endl;
	}
	catch (MyVecException m)
	{
		cout << endl << m.what() << endl;
	}
}

void test13()
{
	try
	{
		MyVector<int> a(5);

		a.print();

		cout << endl;

		MyVector<int> b = a * (-1);

		cout << endl;

		b.print();
	}

	catch (MyVecException m)
	{
		cout << endl << m.what() << endl;
	}

}



int main() {

	test12();

	return 0;
}
