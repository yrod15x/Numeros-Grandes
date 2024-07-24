#include <iostream>
#include "numerosgrandes.h"
#include <vector>

int main()
{
    std::vector<int> numeros = {1, 5, 8, 9};
    NumerosGrandes num2("1879");
    NumerosGrandes num1(numeros);


    //std::cin >> num2;
    std::cout << num1 * num2 << std::endl;
    //std::cout << num2 << std::endl;


    return 0;
}
