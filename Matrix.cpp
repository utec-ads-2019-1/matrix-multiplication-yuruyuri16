#include "Matrix.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution dis(-10, 10);

Matrix::Matrix(unsigned row, unsigned col) : rows(row), columns(col)
{
	size_t m_row, m_col;

	// Allocate memory for the matrix
	m = new int*[row];
	for (m_row = 0; m_row < row; ++m_row)
	{
		m[m_row] = new int[col];
		for (m_col = 0; m_col < col; ++m_col)
			m[m_row][m_col] = 0;
	}
}

Matrix::~Matrix() = default;

/* Not working
Matrix::~Matrix()
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] m[i];
	}
	delete[] m;
}
*/

Matrix Matrix::createRandomMatrix(unsigned r, unsigned c)
{
	size_t m_row;
	Matrix matrix(r, c);

	for (m_row = 0; m_row < r; ++m_row)
		matrix.m[m_row] = matrix.createRandomRow(c);
	return (matrix);
}

int* Matrix::createRandomRow(unsigned c)
{
	int *row;
	size_t i;
	
	row = new int[c];
	for (i = 0; i < c; ++i)
		row[i] = dis(gen);
	return (row);
}

void Matrix::print()
{
	size_t r, c;

	for (r = 0; r < rows; ++r)
	{
		for (c = 0; c < columns; ++c)
			std::cout << m[r][c] << '\t';
		std::cout << '\n';
	}
}

int Matrix::operator()(unsigned r, unsigned c)
{
	return m[r][c];
}

void Matrix::fillrows(Matrix b, Matrix &res, unsigned row_i, unsigned row_f)
{
	size_t i, j, k;

	for (i = row_i; i < row_f; ++i)
		for (j = 0; j < b.columns; ++j)
			for (k = 0; k < columns; ++k)
				res.m[i][j] += m[i][k] * b.m[k][j];
}


Matrix Matrix::operator*(Matrix rhs)
{
	std::thread *t;
	int *arr;
	size_t i;

	Matrix r(rows, rhs.columns);

	if (columns == rhs.rows)
	{
		if (r.rows < NUM_THREADS)
		{
			std::cout << "Using " << r.rows << (r.rows == 1 ? " thread.\n" : " threads.\n");
			t = new std::thread[r.rows];
			for (int i = 0; i < r.rows; ++i)
				t[i] = std::thread(&Matrix::fillrows, this, rhs, std::ref(r), i, i + 1);
			for (int i = 0; i < r.rows; ++i)
				t[i].join();

		}
		else if (r.rows >= NUM_THREADS)
		{
			std::cout << "Using " << NUM_THREADS << " threads.\n";
			arr = new int[NUM_THREADS];
			t = new std::thread[NUM_THREADS];
			int n1 = r.rows % NUM_THREADS;
			int n2 = r.rows / NUM_THREADS;
			for (i = 0; i < NUM_THREADS; ++i)
			{
				arr[i] = n2;
				if (n1-- > 0)
					arr[i] += 1;
			}
			int cont = 0;
			for (i = 0; i < NUM_THREADS; ++i)
			{
				t[i] = std::thread(&Matrix::fillrows, this, rhs, std::ref(r), cont, cont + arr[i]);
				cont += arr[i];
			}

			for (i = 0; i < NUM_THREADS; ++i)
				t[i].join();
			delete[] arr;
		}
	}
	else
	{
		std::cout << "The number of columns of the lhs Matrix is not equal to";
		std::cout << " the number of row in the rhs Matrix\n";
	}
	return r;
}
