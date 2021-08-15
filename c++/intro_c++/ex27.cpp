
#include <iostream>

class X
{
public:
    explicit X();
    explicit X(int a_);
    explicit X(int a_, int b_);

    // X &operator=(const int x){Print();m_a +=x;return *this;};

    operator int() const;
    void Print() const;

private:
    int m_a;
};


X::X() : m_a(0)
{
    std::cout << "default c tor " << m_a << std::endl;
}
X::X(int a_) : m_a(a_)
{
    std::cout << "convertion c tor 1 arg " << m_a << std::endl;
}
X::X(int a_, int b_) : m_a(a_ + b_)
{
    std::cout << "convertion c tor 2 args " << m_a << std::endl;
}

X::operator int() const
{
    std::cout << "cast operator for type X to int " << m_a << std::endl;

    return (m_a);
}

void X::Print() const
{
    std::cout << "X::Print() " << m_a << std::endl;
}

void Fifi(const X &x_)
{
    std::cout << "Fifi() " << x_ << std::endl;
    x_.Print();
}

int main()
{
    X x1(7);
    std::cout << std::endl;

    Fifi(x1); // (1)
    std::cout << std::endl;

    Fifi(X(8)); // (2)
    std::cout << std::endl;
    // (X(8) = 9).Print();
    // Fifi(9); // (3)
    std::cout << std::endl;
    // Fifi(5, 5); // (4)
    return x1 * 3; //(5)
}