#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

/*
убрать дублирующийся код или его не так много?
написть проверку на ошибки
перегрузить оператор [][];
написать детерминант
написать обратную матрицу
написать быстрое умножение матриц
написать операцию - добавить столбец?
поменять местами два столбца
поменять местами две строки
написать класс линейные уравнения
*/

class Matrix{
	int m;			// row
	int n;			// column
	double * body;

public:
	Matrix(int _m, int _n) {
		m = _m;
		n = _n;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			body[i] = 0;
		}
	}

	Matrix(int _m, int _n, int min, int max) {
		m = _m;
		n = _n;
		body = new double[m * n];
		srand( time(0) );	
		for (int i = 0; i < m * n; ++i) {
			body[i] = rand() % (max + 1 - min) + min;
		}
	}
	
	Matrix(const char* file_name) {
		ifstream in("a.txt");
		in >> m;
		in >> n;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			in >> body[i];
		}
 	}
		
	Matrix(const Matrix& a) {
		m = a.m;
		n = a.n;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			body[i] = a.body[i];
		}
	}

	void Set_matrix()
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				cin >> body[i * n + j];	
	}

	Matrix add(const Matrix rhs){
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				res.body[i] += rhs.body[i];
			}
		}
		return res;	
	}

	Matrix operator + (const Matrix rhs) {
		if (m == rhs.m && n == rhs.n) {
			Matrix res(*this);
			res.add(rhs);
			return res;
		}
	}

	void operator += (const Matrix rhs) {
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				body[i] += rhs.body[i];
			}
		}
	}

	Matrix sub(const Matrix rhs) {
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				res.body[i] -= rhs.body[i];
			}
		}
		return res;
	}

	Matrix operator - (const Matrix rhs) {
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			res.sub(rhs);
		}
		return res;
	}

	void operator -= (const Matrix rhs) {
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				body[i] -= rhs.body[i];
			}
		}
	}

	Matrix mul(const int& rhs) {
		Matrix c(*this);
		for (int i = 0; i < m * n; ++i) {
			c.body[i] *= rhs;	
		}
		return c;
	}
	
	Matrix operator * (const int& rhs) {
		Matrix c(*this);
		return c.mul(rhs);
	}

	void operator *= (const int& rhs) {
			for (int i = 0; i < m * n; ++i) {
				body[i] *= rhs;
			}
		}


	Matrix mul(const Matrix& rhs) {
		Matrix res(m, rhs.n);
		if (n == rhs.m) {
			for (int i = 0; i < res.m; ++i) {
				for (int j = 0; j < res.n; ++j) {
					for (int k = 0; k < n; ++k) {
						res.body[res.n * i + j] += body[n * i + k] * rhs.body[k * rhs.n + j];
					}
				}
			}
		}
		return res;
	}

	Matrix operator * (const Matrix& rhs) {
		Matrix res(m, rhs.n);
		if (n == rhs.m) {
			res = mul(rhs);
		}
		return res;
	}
	
	void operator *= (const Matrix& rhs) {
		Matrix res(m, rhs.n);
		if (n == rhs.m) {
			res = mul(rhs);
		}
		m = res.m;
		n = res.n;
		delete body;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			body[i] = res.body[i];
		}
		delete res.body;
	}

	bool operator == (const Matrix& a) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (body[i * n + j] != a.body[i * n + j]) return false;
			}
		}
		return true;
	}
	
	bool operator != (const Matrix& a) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (body[i * n + j] == a.body[i * n + j]) return false;
			}
		}
		return true;
	}

	Matrix transpose_the_matrix() {		
		Matrix res(*this);

		int j = 0;
		for (int i = 0; i < m * n; ++i) {
			res.body[i] = body[j];
			j += n;
			if (j >= m * n) j = j % (m * n) + 1;
		}
		int tmp;
		tmp = res.m;
		res.m = res.n;
		res.n = tmp;
		return res;
	}
	
	void print() {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << setw(3) << body[n * i + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	double get(int i, int j) {
		if (i <= m && j <= n) return body[(i-1) * n + (j-1)];
	}

	void set(int i, int j, double value) {
		if (i <= m && j <= n) body[(i - 1) * n + (j - 1)] = value;
	}

	/*
	Matrix minor() {
		Matrix B(m - 1, n - 1);
		cout << B.m << " " << B.n << endl;
		for (int i = 0; i < B.m; ++i) {
			for (int j = 0; j < B.n; ++j) {
				B.body[i * B.n + j] = body[(i + 1) * n + (j + 1)];
				cout << "New elem No = " << i * B.n + j << " Old elem No " << (i + 1) * n + (j + 1) << endl;
			}
		}
		return B;
	}
	*/

/*
	double get_the_determinant() {
		Matrix A(*this);
		if (A.m == A.n) {
			double res = 0;
			for (int i = 0; i < m; ++i) {
				if (m == 1) return body[0];
				else {
					Matrix B(m - 1, n - 1);
					for (int j = 0; j < B.m; ++j) {
						for (int k = 0; k < B.n; ++k) {
							B.body[B.n * j + k] = A.body[(A.n + 1) * j + (k + 1)];
						}
					}

					
					res += body[i] * get_the_determinant();
				}
			}
			return res;
		}
		cout << "cant help" << endl;
		return -1.0;
	}
	*/
	/*
	Matrix get_the_inverse_matrix(const Matrix& A) {}
	*/
};


ostream& operator <<(ostream& ostr, Matrix& m)
{
	m.print();
	return (ostr);
}

istream& operator >>(istream& in, Matrix& m)
{
	m.Set_matrix();
	return (in);
}

int main() {
	Matrix a(3,3,1,4);
	//a.print();
	Matrix b(3,3,0,10);
	//b.print();
	Matrix c("a.txt");
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
	cout << a << b;
	a *= b;
	cout << a;

	system("pause");
}