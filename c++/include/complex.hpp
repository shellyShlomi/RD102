#ifndef ILRD_RD102_COMPLEX_HPP
#define ILRD_RD102_COMPLEX_HPP

#include <iosfwd>
#include <cstdlib>

namespace ilrd
{
	class Complex
	{
	public:
		Complex(double real_ = 0.0, double imag_ = 0.0); // non-explicit on purpose

		inline Complex &operator+=(const Complex &rhs_);
		inline Complex &operator*=(const Complex &rhs_);
		inline Complex &operator-=(const Complex &rhs_);
		inline Complex &operator/=(const Complex &rhs_);

		inline double GetReal() const;
		inline double GetImagenary() const;
		inline void SetReal(double real_);
		inline void SetImagenary(double imag_);

	private:
		double m_real;
		double m_imag;
	}; // complex

	inline double Complex::GetReal() const
	{
		return (m_real);
	}

	inline double Complex::GetImagenary() const
	{
		return (m_imag);
	}
	inline void Complex::SetReal(double real_)
	{
		m_real = real_;

		return;
	}
	inline void Complex::SetImagenary(double imag_)
	{
		m_imag = imag_;

		return;
	}

	inline const Complex operator+(const Complex &lhs_, const Complex &rhs_)
	{
		return (Complex(lhs_.GetReal() + rhs_.GetReal(),
						lhs_.GetImagenary() + rhs_.GetImagenary()));
	}
	inline const Complex operator-(const Complex &lhs_, const Complex &rhs_)
	{
		return (Complex(lhs_.GetReal() - rhs_.GetReal(),
						lhs_.GetImagenary() - rhs_.GetImagenary()));
	}

	inline const Complex operator*(const Complex &lhs_, const Complex &rhs_)
	{
		double a = lhs_.GetReal();
		double b = lhs_.GetImagenary();
		double c = rhs_.GetReal();
		double d = rhs_.GetImagenary();

		double new_real = (a * c) - (b * d);
		double new_imag = (b * c) + (a * d);

		return (Complex(new_real, new_imag));
	}

	inline const Complex operator/(const Complex &lhs_, const Complex &rhs_)
	{
		double a = lhs_.GetReal();
		double b = lhs_.GetImagenary();
		double c = rhs_.GetReal();
		double d = rhs_.GetImagenary();

		double real = (a * c + b * d) / (c * c + d * d);
		double imag = (b * c - a * d) / (c * c + d * d);

		return (Complex(real, imag));
	}

	inline bool operator==(const Complex &lhs_, const Complex &rhs_)
	{
		return ((lhs_.GetReal() == rhs_.GetReal()) &
				(lhs_.GetImagenary() == rhs_.GetImagenary()));
	}
	inline bool operator!=(const Complex &lhs_, const Complex &rhs_)
	{
		return (!(lhs_ == rhs_));
	}

	inline std::istream &operator>>(std::istream &in, Complex &rhs_)
	{
		char num[100] = {'\0'};

		in.getline(num, 100, ',');
		rhs_.SetReal(atof(num));
		in.getline(num, 100, '\n');

		rhs_.SetImagenary(atof(num));
		return (in);
	}

	inline std::ostream &operator<<(std::ostream &os, const Complex &complex)
	{
		return (os << "(" << complex.GetReal() << ", " << complex.GetImagenary() << "i)");
	}

	inline Complex &Complex::operator+=(const Complex &rhs_)
	{
		*this = *this + rhs_;
		return (*this);
	}
	inline Complex &Complex::operator*=(const Complex &rhs_)
	{
		*this = *this * rhs_;
		return (*this);
	}
	inline Complex &Complex::operator-=(const Complex &rhs_)
	{
		*this = *this - rhs_;
		return (*this);
	}

	inline Complex &Complex::operator/=(const Complex &rhs_)
	{
		*this = *this / rhs_;
		return (*this);
	}

} //ilrd

#endif /* ILRD_RD102_COMPLEX_HPP */
