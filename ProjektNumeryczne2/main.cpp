#include "Equation.h"
#include <fstream>
#define N 958

int main()
{
	Equation E(N);

	//zad b
	/*E.initA();
	std::cout << "Zad b - Jacobi: " << E.JacobiMethod() << "\n";

	E.initA();
	std::cout << "Zad b - Gauss: " << E.GaussSeidelMethod() << "\n";*/

	//zad c
	/*E.initC();
	std::cout << "Zad c - Jacobi: " << E.JacobiMethod() << "\n";

	E.initC();
	std::cout << "Zad c - Gauss: " << E.GaussSeidelMethod() << "\n";*/

	//zad d
	E.initC();
	std::cout << "Zad d - LU: " << E.LUMethod() << "\n";

	//zad e
	/*int n[] = {100,500,1000,2000,3000};

	for (int i = 0; i < 14; i++)
	{
		Equation E(n[i]);

		E.initA();
		std::cout << "Zad e - Jacobi: " << E.JacobiMethod() << "\n";

		E.initA();
		std::cout << "Zad e - Gauss: " << E.GaussSeidelMethod() << "\n";

		E.initA();
		std::cout << "Zad e - LU: " << E.LUMethod() << "\n";
	}*/
}