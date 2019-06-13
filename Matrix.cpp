#include "Matrix.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution dis(-10, 10);

Matrix::Matrix(unsigned row, unsigned col) : rows(row), columns(col)
{
	int m_row, m_col;

	// Allocate memormy for the matrix
	m = new int*[row];
	for (m_row = 0; m_row < row; ++m_row)
	{
		m[m_row] = new int[col];
		for (m_col = 0; m_col < col; ++m_col)
		{
			m[m_row][m_col] = 0;
		}
	}
}

Matrix::~Matrix() = default;

Matrix Matrix::createRandomMatrix(unsigned r, unsigned c)
{
	int m_row;
	Matrix matrix(r, c);

	for (m_row = 0; m_row < r; ++m_row)
		matrix.m[m_row] = matrix.createRandomRow(c);
	return (matrix);
}

int* Matrix::createRandomRow(unsigned c)
{
	int *row;
	int i;
	
	row = new int[c];
	for (i = 0; i < c; ++i)
		row[i] = dis(gen);
	return (row);
}

void Matrix::print()
{
	int r, c;

	for (r = 0; r < rows; ++r)
	{
		for (c = 0; c < columns; ++c)
			std::cout << m[r][c] << '\t';
		std::cout << '\n';
	}
}

int Matrix::operator()(int r, int c)
{
	return m[r][c];
}

Matrix Matrix::operator*(Matrix rhs)
{
	Matrix r(rows, rhs.columns);

	if (columns == rhs.rows)
	{
		for (size_t i = 0; i < rows; ++i)
		{
			for (size_t j = 0; j < rhs.columns; ++j)
			{
				for (size_t k = 0; k < columns; ++k)
				{
					r.m[i][j] += m[i][k] * rhs.m[k][j];
				}
			}
		}
	}
	else
	{
		std::cout << "The number of columns of the lhs Matrix is not equal to";
		std::cout << " the number of row in the rhs Matrix\n";
	}
	return r;
}
