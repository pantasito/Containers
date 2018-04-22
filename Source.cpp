#include <iostream>
#include <assert.h>
#include "Matrix.h"

using namespace std;

	void test_matrix()
	{
		cout << "Start test Matrix class" << endl;
		Matrix a(1, 1, 1, 4);
		cout << "Matrix a:" << endl << a << endl;
		Matrix b(3, 3, 0, 10);
		cout << "Matrix b:" << endl << b << endl;
		Matrix c(1, 3, 0, 10);
		cout << "Matrix c:" << endl << c << endl;
		Matrix d(3, 1, 0, 10);
		cout << "Matrix d:" << endl << d << endl;

		Matrix m1(4, 4, 0, 9);
		Matrix sub_m1_1 = m1.submatrix(2, 2);
		Matrix sub_m1_2 = m1.submatrix(3, 0);

		cout << "Matrix m1:" << endl << m1 << endl;
		cout << "Submatrix m1 (2,2):" << endl << sub_m1_1 << endl;
		cout << "Submatrix m1 (3,0):" << endl << sub_m1_2 << endl;

		Matrix m2(3, 3, 0, 9);
		cout << "Determinant of matrix: " << endl << m2 << " is : " << m2.det() << endl << endl;

		Matrix m3(4, 4, 0, 10);
		Matrix m3_inv = m3.get_inverse();
		Matrix e = m3 * m3_inv;

		cout << "Matrix A: " << endl << m3 << endl;
		cout << "Inverse matrix of A: " << endl << m3_inv << endl;
		cout << "A*A^(-1): " << endl << e << endl;

		Matrix m4(8, 8, 0, 10);
		m4.divided_into_4_parts(a, b, c, d);
		cout << "Matrix M:" << endl << m4 << endl;
		cout << "Block Left Top" << endl << a << endl << "Block Right Top" << endl << b << endl;
		cout << "Block Left Lower" << endl << c << endl << "Block Right Lower" << endl << d << endl;
	
	}
	

	int main() {
	
	test_matrix();

	system("pause");
}
	//нужно ли метод print вынести в приватные методы?