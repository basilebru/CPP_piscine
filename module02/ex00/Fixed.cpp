#include "Fixed.hpp"
#include <iostream>

const int Fixed::num_fract_bit = 8;

Fixed::Fixed(void): value(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &copy)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = copy;
    // this->value = copy.getRawBits(); (revient au meme)
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

int     Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->value;
}

void    Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->value = raw;
}

Fixed&  Fixed::operator=(const Fixed &copy)
{
    std::cout << "Assignement operator called" << std::endl;
    this->value = copy.getRawBits();
    return(*this);
}

