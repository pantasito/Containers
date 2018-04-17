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

	void Set_matrix(istream& is)
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				is >> body[i * n + j];	
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

	Matrix operator + (const Matrix& rhs) {
		if (m == rhs.m && n == rhs.n) {
			return this->add(rhs);
		}		
	}

	void operator += (const Matrix& rhs) {
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				body[i] += rhs.body[i];
			}
		}
	}

	Matrix sub(const Matrix& rhs) {
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				res.body[i] -= rhs.body[i];
			}
		}
		return res;
	}

	Matrix operator - (const Matrix& rhs) {	
		if (m == rhs.m && n == rhs.n) {
			return sub(rhs);
		}
	}

	void operator -= (const Matrix& rhs) {
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				body[i] -= rhs.body[i];
			}
		}
	}

	Matrix mul(const int rhs) {
		Matrix c(*this);
		for (int i = 0; i < m * n; ++i) {
			c.body[i] *= rhs;	
		}
		return c;
	}
	
	Matrix operator * (const int rhs) {		
		return mul(rhs);
	}

	void operator *= (const int rhs) {
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
						//res.set(i,j) = get(i,k)*rhs.get(k,j);
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
		
		/*
		for (int i = 0; i < m; i++)		
			for (int j = 0; j < n; j++)
						res.set(j,i, get(i,j));		
		*/
		int tmp;
		tmp = res.m;
		res.m = res.n;
		res.n = tmp;
		return res;
	}
	
	void print(ostream& os) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				os << setw(3) << body[n * i + j] << " ";
			}
			os << endl;
		}
		os << endl;
	}

	inline double get(int i, int j) {
		assert(i <= m && j <= n);
		return body[i * n +j];
	}

	inline void set(int i, int j, double value) {
		assert(i <= m && j <= n);
		if (i <= m && j <= n) body[i  * n +j ] = value;
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

	Matrix submatrix(int _i, int _j)
	{
		Matrix matr(m-1,n-1);
		int k = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if (i != _i && j != _j)
				{
					matr.body[k] = get(i,j);
					k++;
				}
			}
		return matr;
	}

	double get_the_determinant()
	{
		if (n == 1 && m == 1) return body[0];
	
		double det = 0;
		for (int j = 0; j < n; j++)
		{
			Matrix tmp = submatrix(0,j);

			int sign = (j % 2 == 1 ? -1: 1);		
	
			det += sign * tmp.get_the_determinant() * get(0,j);
		}
		return det;
	}

};

ostream& operator <<(ostream& ostr, Matrix& m)
{
	m.print(ostr);
	return ostr;
}

istream& operator >>(istream& in, Matrix& m)
{
	m.Set_matrix(in);
	return (in);
}


