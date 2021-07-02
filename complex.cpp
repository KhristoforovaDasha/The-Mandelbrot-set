#include "complex.h"

complex::complex(double real, double imagine)
    :real_(real), imagine_(imagine) {}
complex::complex()
    : real_(0), imagine_(0) {}
complex complex:: operator + (complex& first) {
    complex data(real_ + first.real_, imagine_ + first.imagine_);
    return data;
}
complex complex:: operator * (complex& first) {
    complex data(real_ * first.real_ - imagine_ * first.imagine_, imagine_ * first.real_ + real_ * first.imagine_);
    return data;
}
double complex::len() {
    return std::sqrt(real_ * real_ + imagine_ * imagine_);
}
complex& complex:: operator = (complex first) {
    Swap(first);
    return *this;
}
void complex:: Swap(complex & rhs) {
    std::swap(real_, rhs.real_);
    std::swap(imagine_, rhs.imagine_);
}