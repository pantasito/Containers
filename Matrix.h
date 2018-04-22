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

	void set_row_num(int _m) {
		m = _m;
	}

	void set_column_num(int _n) {
	n = _n;
	}
	
	void set_size(int _m, int _n) {
		delete[] body;
		m = _m;
		n = _n;
		body = new double[m * n];
	}

public:
	Matrix(int _m, int _n) {
		m = _m;
		n = _n;
		body = new double[m * n];
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

	~Matrix() {
		delete[] body;
	}

	int get_row_num() const {
		return m;
	}

	int get_column_num() const {
		return n;
	}

	void Set_matrix(istream& is)
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				is >> body[i * n + j];	
	}

	Matrix add(const Matrix rhs) const {
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				res.body[i] += rhs.body[i];
			}
		}
		return res;	
	}

	Matrix operator + (const Matrix& rhs) const {
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

	Matrix sub(const Matrix& rhs) const {
		Matrix res(*this);
		if (m == rhs.m && n == rhs.n) {
			for (int i = 0; i < m * n; ++i) {
				res.body[i] -= rhs.body[i];
			}
		}
		return res;
	}

	Matrix operator - (const Matrix& rhs) const {
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

	Matrix mul(const int rhs) const {
		Matrix c(*this);
		for (int i = 0; i < m * n; ++i) {
			c.body[i] *= rhs;	
		}
		return c;
	}
	
	Matrix operator * (const int rhs) const {
		return mul(rhs);
	}

	void operator *= (const int rhs) {
		for (int i = 0; i < m * n; ++i) {
			body[i] *= rhs;
		}
	}


	Matrix mul(const Matrix& rhs) const {
		Matrix res(m, rhs.n);
		if (n == rhs.m) {
			for (int i = 0; i < res.m; ++i) {
				for (int j = 0; j < res.n; ++j) {
					res.body[res.n * i + j] = 0;
					for (int k = 0; k < n; ++k) {
						//res.set(i,j) = get(i,k) * rhs.get(k,j);
						res.body[res.n * i + j] += body[n * i + k] * rhs.body[k * rhs.n + j];
					}
				}
			}
		}
		return res;
	}

	Matrix operator * (const Matrix& rhs) const {
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
		delete[] body;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			body[i] = res.body[i];
		}
		delete[] res.body;
	}

	void operator = (const Matrix& rhs) {
		m = rhs.m;
		n = rhs.n;
		delete[] body;
		body = new double[m * n];
		for (int i = 0; i < m * n; ++i) {
			body[i] = rhs.body[i];
		}
	}

	bool operator == (const Matrix& a) const {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (body[i * n + j] != a.body[i * n + j]) return false;
			}
		}
		return true;
	}
	
	bool operator != (const Matrix& a) const {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (body[i * n + j] == a.body[i * n + j]) return false;
			}
		}
		return true;
	}

	Matrix transpose() const {		
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
	
	inline double get(int i, int j) const {
		assert(i <= m && j <= n);
		return body[i * n +j];
	}

	inline void set(int i, int j, double value) {
		assert(i <= m && j <= n);
		if (i <= m && j <= n) body[i  * n +j ] = value;
	}

	Matrix get_inverse() const {
		Matrix res(m, n);
		double res_det = 1.0 / det();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				//det от submatrix;
				int sign = ((i + j) % 2 == 1 ? -1 : 1);
				res.set(j, i, res_det * (sign * submatrix(i, j).det()));
			}
		}
		return res;
	}

	Matrix submatrix(int _i, int _j) const {
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

	double det() const {
		if (n == 1 && m == 1) return body[0];
		double res = 0;
		for (int j = 0; j < n; j++) {
			Matrix tmp = submatrix(0,j);
			int sign = (j % 2 == 1 ? -1: 1);		
			res += sign * tmp.det() * get(0,j);
		}
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

	//methods for fast multiplication
	void divided_into_4_parts(Matrix& a, Matrix& b, Matrix& c, Matrix& d) const{
		int new_m = m / 2;
		int new_n = n / 2;
		a.set_size(new_m, new_n);
		b.set_size(new_m, new_n);
		c.set_size(new_m, new_n);
		d.set_size(new_m, new_n);

		initialize_block(a, 0, 0);
		initialize_block(b, 0, new_n);
		initialize_block(c, new_m, 0);
		initialize_block(d, new_m, new_n);
	}

	Matrix(const Matrix& a, const Matrix& b, const Matrix& c, const Matrix& d) {
		m = a.get_row_num() * 2;
		n = a.get_column_num() * 2;
		body = new double[m * n];

		initialize_from_blocks(a, 0, 0);
		initialize_from_blocks(b, 0, n/2);
		initialize_from_blocks(c, m/2, 0);
		initialize_from_blocks(d, m/2, n/2);
	}

	void initialize_block(Matrix& a, int row_start_pos, int column_start_pos) const{
		for (int i = 0; i < a.get_row_num(); ++i) {
			for (int j = 0; j < a.get_column_num(); ++j) {
				a.set(i, j, get(row_start_pos + i, column_start_pos + j));
			}
		}
	}

	void initialize_from_blocks(const Matrix& a, int row_start_pos, int column_start_pos) {
		for (int i = 0; i < a.get_row_num(); ++i) {
			for (int j = 0; j < a.get_column_num(); ++j) {
				set(i + row_start_pos, j + column_start_pos, a.get(i, j));
			}
		}
	}

	Matrix fast_mul(const Matrix& rhs) {
		
		Matrix a11(1, 1, 1, 1);
		Matrix a12(a11), a21(a11), a22(a11);
		divided_into_4_parts(a11, a12, a21, a22);

		Matrix b11(a11), b12(a11), b21(a11), b22(a11);
		rhs.divided_into_4_parts(b11, b12, b21, b22);

		Matrix p1(a11), p2(a11), p3(a11), p4(a11), p5(a11), p6(a11), p7(a11);

		p1 = (a11 + a22) * (b11 + b22);
		p2 = (a21 + a22) * b11;
		p3 = a11 * (b12 - b22);
		p4 = a22 * (b21 - b11);
		p5 = (a11 + a12) * b22;
		p6 = (a21 - a11) * (b11 + b12);
		p7 = (a12 - a22) * (b21 + b22);

		Matrix c11(a11), c12(a11), c21(a11), c22(a11);
		c11 = p1 + p4 - p5 + p7;
		c12 = p3 + p5;
		c21 = p2 + p4;
		c22 = p1 - p2 + p3 + p6;
		Matrix res(c11, c12, c21, c22);
		return res;
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



/*
Ќаставлени€ по быстрому умножению матриц:
5) ƒелаешь метод быстрого умножени€. https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A8%D1%82%D1%80%D0%B0%D1%81%D1%81%D0%B5%D0%BD%D0%B0
в формулахъ где надо 7 P вычисл€ть, используешь свое старое умножение mul (или оператор*)
6)  ак реализовал уможиени€ такое, об€зательно! отдаль его. ќп€ть же обычного принта достаочно.
7) ѕосле этого подумай как сделать рекурсивно все это.

ѕосле 2,4,6 пункта все изменени€ вливай. “.е. € хочу видеть до 6 пункта 3 коммита.

убрать дублирующийс€ код или его не так много?
написть проверку на ошибки
перегрузить оператор [][];
написать быстрое умножение матриц
написать операцию - добавить столбец?
помен€ть местами два столбца
помен€ть местами две строки
написать класс линейные уравнени€
*/
