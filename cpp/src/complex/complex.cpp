/*  Developer: Shelly Shlomi;									*
 *  Status:approved;											*
 *  Date Of Creation:11.08.21;									*
 *  Date Of Approval:11.08.21;									*
 *  Approved By:                                                * 
 *          phas 1: approved by maor;                           * 
 *          phas 2: approved by nir;                            *
 *  Description: complex numbers;					                */


#include <iostream> /*  ostream  */

#include "complex.hpp"

const size_t NULL_TERMINETOR = 1;


namespace ilrd
{

Complex::Complex(double real_, double imag_) :
    m_real(real_), m_imag(imag_)
{}
}
