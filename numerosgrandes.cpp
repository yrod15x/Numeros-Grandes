#include "numerosgrandes.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

void NumerosGrandes::leer()
{
    //Si el numero es negativo se pone el signo en primer digito. Se tiene en cuenta para las operaciones
    bool suiche = false;
    std::string strNumero;
    _digitos.clear();

    while(!suiche)
    {
        std::cout << "Ingrese el numero" << " >> ";
        getline(std::cin, strNumero);

        for(int i = 0; i < strNumero.size(); i++)
        {
            if(i == 0 and strNumero[i] == '-')
            {
                continue;
            }
            if(strNumero[i] == ' ')
            {
                std::cout << "El dato de entrada tiene un espacio." << std::endl;
                break;
            }
            if(int(strNumero[i]) < 48 or int(strNumero[i] > 57))
            {
                std::cout << "El dato de entrada tiene un carcater que no es un digito." << std::endl;
                break;
            }
            if(i == strNumero.size() - 1)
            {
                suiche = true;
            }
        }
    }
    bool negativo = false;
    for(int i = 0; i < strNumero.size(); i++)
    {
        if(i == 0 and strNumero[i] == '-')
        {
            negativo = true;
            continue;
        }
        if(negativo)
        {
            _digitos.push_back(-1 * (strNumero[i] - 48));
            negativo = false;
        }
        else
        {
             _digitos.push_back(strNumero[i] - 48);
        }
    }
}

NumerosGrandes::NumerosGrandes()
{
    _digitos.push_back(0);
}

//Constructor con string
NumerosGrandes::NumerosGrandes(std::string numero)
{
    bool suiche = false;
    while(!suiche)
    {
        for(int i = 0; i < numero.size(); i++)
        {
            if(i == 0 and numero[i] == '-')
            {
                continue;
            }
            if(i == 0 and numero[i] == '0')
            {
                std::cout << "El numero no puede comenzar con 0!" << std::endl;
                break;
            }
            if(int(numero[i]) < 48 or int(numero[i] > 57))
            {
                std::cout << "El dato de entrada tiene un carcater que no es un digito." << std::endl;
                break;
            }
            if(i == numero.size() - 1)
            {
                suiche = true;
            }
        }
        if(!suiche)
        {
            std::cout << "Vuelva a ingresar el numero >>";
            getline(std::cin, numero);
        }
    }
    bool negativo = false;
    for(int i = 0; i < numero.size(); i++)
    {
        if(i == 0 and numero[i] == '-')
        {
            negativo = true;
            continue;
        }
        if(negativo)
        {
            _digitos.push_back(-1 * (numero[i] - 48));
            negativo = false;
        }
        else
        {
             _digitos.push_back(numero[i] - 48);
        }
    }
}

NumerosGrandes::NumerosGrandes(std::vector<int> numero)
{
    //Constructor que copia vector de enteros introducidos
    _digitos = numero;
}

NumerosGrandes::~NumerosGrandes()
{
    //dtor
}

NumerosGrandes::NumerosGrandes(const NumerosGrandes& other)
{
    //copy ctor
    _digitos = other._digitos;
}

void NumerosGrandes::imprimir(std::ostream& os) const
{
    for(int i:_digitos)
    {
        os << i ;
    }
}

//Construyo esta funcion para usar cout << directamente con la instancia de la clase. Hace uso del metodo imprimir() de la clase
std::ostream& operator<<(std::ostream& os, const NumerosGrandes& numero)
{
    numero.imprimir(os);
    return os;
}

std::istream& operator>>(std::istream& in, NumerosGrandes& numero)
{
    numero.leer();
    return in;
}

void NumerosGrandes::_insertarDigitos(int numDigitos, std::vector<int> &numero)
{
    for(int i = 0; i < numDigitos; i++)
    {
        numero.insert(numero.begin(), 0);
    }
}

//Funcion interna que pone ceros delante de vector si este es menor a otro. Todo para poder hacer las operaciones mas faciles
void NumerosGrandes::_igualarTamanos(std::vector<int> &num1, std::vector<int> &num2)
{
    //Toca revisar si el numero es negativo - si lo es contar size() - 1
    if(num1.size() > num2.size())
    {
        _insertarDigitos(num1.size() - num2.size(), num2);
    }
    else if(num1.size() < num2.size())
    {
        _insertarDigitos(num2.size() - num1.size(), num1);
    }
}

std::vector<int> NumerosGrandes::_suma(std::vector<int> num1, std::vector<int> num2)
{
    int suma = 0, llevando = 0;
    bool mayorNegativo = false;

    //Determinar si poner el signo negativo al final del numero mayor (si uno de ellos es negativo)
    if((num1.size() > num2.size() and num1[0] < 0) or (num1.size() < num2.size() and num2[0] < 0))
    {
        mayorNegativo = true;
    }
    else if(num1.size() == num2.size() and (num1[0] < 0 and num2[0] < 0))
    {
       mayorNegativo = true;
    }

    _igualarTamanos(num1, num2);
    std::vector<int> vecResult(num1.size(), 0);

    for(int i = num1.size() - 1; i >= 0; i--)
    {
        if(num1[i] < 0)
        {
            num1[i] *= -1;
        }
        if(num2[i] < 0)
        {
            num2[i] *= -1;
        }
        suma += num1[i] + num2[i];
        if(suma > 10)
        {
            suma %= 10;
            llevando = 1;
        }
        else
        {
            llevando = 0;
        }
        //std::cout << num1[i] << " - " << num2[i] << " = " <<  suma << std::endl;
        vecResult[i] = suma;
        suma = llevando;
    }

    if(mayorNegativo)
    {
        vecResult[0] *= -1;
    }

    return vecResult;
}

std::vector<int> NumerosGrandes::_resta(std::vector<int> num1, std::vector<int> num2)
{
    int resta = 0;
    bool negativo = false;
    bool mayor = false;

    if(num1[0] < 0 or num2[0] < 0)
    {
        negativo = true;
    }

    if(num1.size() == num2.size())
    {
        if(negativo)
        {
            //si ambos son negativos seria una suma (negativa)
            if(num1[0] < 0 and num2[0] < 0)
            {
                std::vector<int> vecResult(num1.size(), 0);
                _igualarTamanos(num1, num2);
                vecResult = _suma(num1, num2);
                return vecResult;
            }
            else
            {
                //Si uno es negativo el positivo sera el mayor
                if(num1[0] < 0 and num2[0] > 0)
                {
                    mayor = true;
                }

            }
        }
    }

    //determinar numero mayor para al hacer suma de numeros negativos este quede arriba
    if(num1.size() < num2.size())
    {
        mayor = true;
    }

    _igualarTamanos(num1, num2);
    std::vector<int> vecResult(num1.size(), 0);

    if(mayor)
    {
        num1.swap(num2);
    }

    for(int i = num1.size() - 1; i >= 0; i--)
    {
        if(num1[i] < 0)
        {
            num1[i] *= -1;
        }
        if(num2[i] < 0)
        {
            num2[i] *= -1;
        }

        if(num1[i] < num2[i])
        {
            if(i > 0)
            {
                num1[i - 1] -= 1;
                num1[i] += 10;
            }
        }
        resta = num1[i] - num2[i];
        std::cout << num1[i] << " - " << num2[i] << " = " <<  resta << std::endl;
        vecResult[i] = resta;
        resta = 0;
    }

    return vecResult;
}

std::vector<int> NumerosGrandes::_producto(std::vector<int> num1, std::vector<int> num2)
{
    std::vector<int> producto;
    int mult, llevando = 0;

    if(num1.size() < num2.size())
    {
        num1.swap(num2);
    }

    for(int i = num1.size() -1; i >= 0; i--)
    {
        for(int j = num2.size() -1; j >= 0; j--)
        {
            mult = num1[i] * num2[j];
            //Primer numero a multiplicar
            if(i == num1.size() - 1)
            {

                if(mult >= 10)
                {
                    producto.push_back(mult % 10);
                    llevando = static_cast<int>(mult / 10);
                }
                else
                {
                    producto.push_back(mult);
                }
            }
            //Numeros que no sean el primer digito
            if(i > 0 and i < num1.size() - 1)
            {
                if(mult >= 10)
                {
                    producto.push_back(mult % 10 + llevando);
                    llevando = static_cast<int>(mult / 10);
                }
                else
                {
                    producto.push_back(mult % 10 + llevando);
                }

            }
            if(i == 0)
            {
                if(mult + llevando >= 10)
                {
                    mult += llevando;
                    producto.push_back(mult % 10);
                    producto.push_back(static_cast<int>(mult / 10));
                }
                else
                {
                    producto.push_back(mult + llevando);
                }

            }
        }
    }

    //Se debe invertir el vector porque sus digitos vienen volteados debido a pushback
    std::reverse(producto.begin(), producto.end());
    return producto;
}

//Esto es como hacer objeto1.operador+(objeto2)
NumerosGrandes NumerosGrandes::operator+(const NumerosGrandes& otroNum)
{
    NumerosGrandes num2(otroNum);
    std::vector<int> numerador1 = _digitos;
    std::vector<int> numerador2 = num2.getDigitos();

    bool negativo = false;

    if(numerador1[0] < 0 or numerador2[0] < 0)
    {
        negativo = true;
    }

    //suma postiva
    if(!negativo)
    {
        NumerosGrandes resultado(_suma(numerador1, numerador2));
        return resultado;
    }
    else
    {
        NumerosGrandes resultado(_resta(numerador1, numerador2));
        return resultado;
    }
}

//Hacer el operador resta
//Esto es como hacer objeto1.operador+(objeto2)
NumerosGrandes NumerosGrandes::operator-(const NumerosGrandes& otroNum)
{
    NumerosGrandes num2(otroNum);
    std::vector<int> numerador1 = _digitos;
    std::vector<int> numerador2 = num2.getDigitos();

    bool negativo = false;

    if(numerador1[0] < 0 or numerador2[0] < 0)
    {
        negativo = true;
    }

    //resta positiva
    if(!negativo)
    {
        NumerosGrandes resultado(_resta(numerador1, numerador2));
        return resultado;
    }
    else
    {
        NumerosGrandes resultado(_suma(numerador1, numerador2));
        return resultado;
    }
}

NumerosGrandes NumerosGrandes::operator*(const NumerosGrandes& otroNum)
{
    NumerosGrandes num2(otroNum);
    std::vector<int> numerador1 = _digitos;
    std::vector<int> numerador2 = num2.getDigitos();
    std::vector<int> resultado, suma;
    suma.push_back(0);
    std::vector<int> temp;
    int contador = numerador2.size() - 1;

    //Si se multiplica por una cifra
    if(numerador2.size() == 1 or numerador1.size() == 1)
    {
        resultado = _producto(numerador1, numerador2);
    }
    else
    {

        for(int i = 0; i < numerador2.size(); i++)
        {
            temp.push_back(numerador2[contador]);
            resultado =  _producto(numerador1, temp);
            contador--;
            for(int k = 0; k < i; k++)
            {
                resultado.push_back(0);
            }

            std::vector<int>::iterator it;
            for(it = resultado.begin(); it < resultado.end(); it++)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;

            temp.clear();

            suma = _suma(suma, resultado);

        }
    }


    NumerosGrandes producto(suma);
    return producto;

}
