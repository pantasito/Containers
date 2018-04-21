#include <iostream>
#include <assert.h>
#include "Matrix.h"

using namespace std;

	void test_matrix()
	{
		cout << "Start test matrix" << endl;
		Matrix a(3, 3, 1, 4);
		//a.print();
		Matrix b(3, 3, 0, 10);
		//b.print();
		//Matrix c("a.txt");
		//c.print();
		Matrix d = a.add(b);
		//d.print();
		Matrix e = a.mul(2);
		//e.print();
		Matrix f(3, 3);
		//f.print();
		//a.print();
		//a.set(3, 3, 10);
		//a.print();
		//float g = a.get_the_determinant();
		//cout << g;
		cout << a << endl << b << endl;
		a *= b;
		cout << a << endl;


		Matrix m1(4, 4, 0, 9);
		Matrix sub_m1_1 = m1.submatrix(2, 2);
		Matrix sub_m1_2 = m1.submatrix(3, 0);

		cout << "Matrix m1:" << endl << m1 << endl;
		cout << "Submatrix m1 (2,2):" << endl << sub_m1_1 << endl;
		cout << "Submatrix m1 (3,0):" << endl << sub_m1_2 << endl;


		Matrix m2(3, 3, 0, 9);
		cout << "Determinant of matrix: " << endl << m2 << " is : " << m2.get_the_determinant() << endl << endl;

		Matrix i(4, 4, 0, 10);
		Matrix j = i.get_the_inverse_matrix();
		Matrix k = i * j;

		cout << "Matrix A: " << endl << i << endl << "Inverse matrix of A: " << endl << j << endl << "A*A^(-1): "<< endl << k << endl;
		
		Matrix c(b);
		Matrix m(8, 8, 0, 10);
		divided_into_4_parts_Matrix(a, b, c, d, m);
		cout << "Matrix M: " << endl << i << endl << "Matrix M:" << endl << m << endl << "Blocks of matrix M: " << endl
			 << "Matrix A:"<< endl << a << endl << "Matrix B:" << endl << b << endl 
			 << "Matrix C:"<< endl << c << endl << "Matrix D:" << endl << d << endl;
	}

	int main() {
	
	test_matrix();
	
	system("pause");
}