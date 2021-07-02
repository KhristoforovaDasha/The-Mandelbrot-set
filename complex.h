#pragma once
#include <cmath>
#include <iostream>
class complex {
public:
    complex (double real, double imagine);
    complex ();
    complex operator + (complex& first);
    complex operator * (complex& first);
    complex& operator = (complex first);
    void Swap(complex& rhs);
    double len();
private:
    double real_;
    double imagine_;
};

