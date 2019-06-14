#include <iostream>

#include "Matrix.hpp"


int	main(int charc, char **argv)
{
	Matrix a = Matrix::createRandomMatrix(1, 20);
	Matrix b = Matrix::createRandomMatrix(20, 1);
	Matrix c = a * b;
	std::cout << "a:\n";
	a.print();
	std::cout << "\nb:\n";
	b.print();
	std::cout << "\nc:\n";
	c.print();
	return (0);
}
