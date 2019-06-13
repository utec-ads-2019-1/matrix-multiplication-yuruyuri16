#include <iostream>
#include <thread>

#include "Matrix.hpp"

int	main(int charc, char **argv)
{
	std::cout << std::thread::hardware_concurrency() << '\n';
	Matrix a = Matrix::createRandomMatrix(5, 2);
	Matrix b = Matrix::createRandomMatrix(2, 5);
	Matrix c = a * b;
	std::cout << "a:\n";
	a.print();
	std::cout << "\nb:\n";
	b.print();
	std::cout << "\nc:\n";
	c.print();
	return (0);
}
