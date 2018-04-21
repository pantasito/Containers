#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

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

	int get_matrix_row_num() {
		return m;
	}

	void set_matrix_row_num(int _m) {
		m = _m;
	}

	int get_matrix_column_num() {
		return n;
	}

	void set_matrix_column_num(int _n) {
		n = _n;
	}

	void set_matrix_size(int _m, int _n) {
		delete body;
		m = _m;
		n = _n;
		body = new double[m * n];
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
			return add(rhs);
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
						//res.set(i,j) = get(i,k) * rhs.get(k,j);
						res.body[res.n * i + j] += body[n * i + k] * rhs.body[k * rhs.n + j];
					}
				}
			}
		}
		return res;
	}

	Matrix operator * (const Matrix& rhs) {
		if (n == rhs.m) {
			return mul(rhs);
		}
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
		const double zero = 2e-14;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				os << setw(3);
				if (fabs(body[n * i + j]) < zero) os << 0 << " ";
				else os << body[n * i + j] << " ";
			}
			os << endl;
		}
	}

	inline double get(int i, int j) {
		assert(i <= m && j <= n);
		return body[i * n +j];
	}

	inline void set(int i, int j, double value) {
		assert(i <= m && j <= n);
		if (i <= m && j <= n) body[i  * n +j ] = value;
	}

	Matrix get_the_inverse_matrix() {
		Matrix res(m, n);
		double res_det = 1.0 / get_the_determinant();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				//det от submatrix;
				int sign = ((i + j) % 2 == 1 ? -1 : 1);
				res.set(j, i, res_det * (sign * submatrix(i, j).get_the_determinant()));
			}
		}
		return res;
	}

	Matrix submatrix(int _i, int _j) {
		Matrix matr(m-1,n-1);
		int k = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				if (i != _i && j != _j) {
					matr.body[k] = get(i,j);
					k++;
				}
			}
		return matr;
	}

	double get_the_determinant() {
		if (n == 1 && m == 1) return body[0];
		double det = 0;
		for (int j = 0; j < n; j++) {
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

void initialize_the_matrix(Matrix& a, Matrix& e, int row_start_pos, int column_start_pos) {
	for (int i = 0; i < a.get_matrix_row_num(); ++i) {
		for (int j = 0; j < a.get_matrix_column_num(); ++j) {
			a.set(i, j, e.get(row_start_pos + i, column_start_pos + j));
		}
	}
}

void divided_into_4_parts_Matrix(Matrix& a, Matrix& b, Matrix& c, Matrix& d, Matrix& e) {
	int m = e.get_matrix_row_num() / 2;
	int n = e.get_matrix_column_num() / 2;
	a.set_matrix_size(m, n);
	b.set_matrix_size(m, n);
	c.set_matrix_size(m, n);
	d.set_matrix_size(m, n);
	
	initialize_the_matrix(a, e, 0, 0);
	initialize_the_matrix(b, e, 0, n);
	initialize_the_matrix(c, e, m, 0);
	initialize_the_matrix(d, e, m, n);
}

/*
Наставления по быстрому умножению матриц:
1) Напиши функцию, которая из матрицы возвращает 4 матрицы (каким образом она будет это делать решать тебе)
2) Обязательно! Оталадь ее, в данном случае обычного принта сначала исходной матрицы, а потом 4 блоков будет достаточно.
Т.е. принтуешь, глазками смотришь и проверяешь что блоки правильные.
Если совпало, можно считать что более менее отладил.
На данный момент не парься над тем что будет если вызвать эту функцию для матрицы нечетного размера.
3) После этого  сделай функцию (метод), который из 4х сделает одну матрицу (можешь даже такой конструктор сделать).
4) Обязательно отладь его!!
5) Делаешь метод быстрого умножения. https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A8%D1%82%D1%80%D0%B0%D1%81%D1%81%D0%B5%D0%BD%D0%B0
в формулахъ где надо 7 P вычислять, используешь свое старое умножение mul (или оператор*)
6) Как реализовал уможиения такое, обязательно! отдаль его. Опять же обычного принта достаочно.
7) После этого подумай как сделать рекурсивно все это.

После 2,4,6 пункта все изменения вливай. Т.е. я хочу видеть до 6 пункта 3 коммита.

Алгоритм Штрассена — Википедия
Алгоритм Штрассена предназначен для быстрого умножения матриц.
Он был разработан Фолькером Штрассеном в 1969 году и является обобщением метода умножения Карацубы н...
ru.wikipedia.org

убрать дублирующийся код или его не так много?
написть проверку на ошибки
перегрузить оператор [][];
написать быстрое умножение матриц
написать операцию - добавить столбец?
поменять местами два столбца
поменять местами две строки
написать класс линейные уравнения
*/
