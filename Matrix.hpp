#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <random>

class Matrix
{
	private:
		int **m;
		unsigned rows, columns;

	public:
		Matrix(unsigned, unsigned);
		~Matrix();
		int operator()(int, int);
		Matrix operator*(Matrix);
		static Matrix createRandomMatrix(unsigned, unsigned);
		int* createRandomRow(unsigned);
		void print();
};

#endif
