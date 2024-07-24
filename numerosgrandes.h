#ifndef NUMEROSGRANDES_H
#define NUMEROSGRANDES_H
#include <vector>
#include <iostream>


class NumerosGrandes
{
    public:
        NumerosGrandes();
        NumerosGrandes(std::vector<int> numero);
        NumerosGrandes(std::string numero);
        ~NumerosGrandes();
        NumerosGrandes(const NumerosGrandes& other);
        std::vector<int> getDigitos(){return _digitos;};
        void imprimir(std::ostream& os) const;
        void leer();
        //Sobrecarga el operador + para poder hacer la funcion de sumas dos numeros grandes
        NumerosGrandes operator+(const NumerosGrandes& otroNum);
        NumerosGrandes operator-(const NumerosGrandes& otroNum);
        NumerosGrandes operator*(const NumerosGrandes& otroNum);
    private:
        std::vector<int> _digitos;
        void _igualarTamanos(std::vector<int> &num1, std::vector<int> &num2);
        void _insertarDigitos(int numDigitos, std::vector<int> &numero);
        std::vector<int> _suma(std::vector<int> num1, std::vector<int> num2);
        std::vector<int> _resta(std::vector<int> num1, std::vector<int> num2);
        std::vector<int> _producto(std::vector<int> num1, std::vector<int> num2);

};

//Estas funciones de operadores de entrada y salida deben estar por fuera de la clase
std::ostream& operator<<(std::ostream& os, const NumerosGrandes& numero);
std::istream& operator>>(std::istream& in, NumerosGrandes& numero);

#endif // NUMEROSGRANDES_H
