#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <random>
#include <thread>

#define NUM_THREADS std::thread::hardware_concurrency()

class Matrix
{
	private:
		int **m;
		unsigned rows, columns;

	public:
		Matrix(unsigned, unsigned);
		~Matrix();
		int operator()(unsigned, unsigned);
		Matrix operator*(Matrix);
		static Matrix createRandomMatrix(unsigned, unsigned);
		int* createRandomRow(unsigned);
		void print();
		void fillrows(Matrix, Matrix&, unsigned, unsigned);
};

#endif
