
#include <cstdio>

class X
{
public:
    explicit X(int a_);
    void Foo();
    int GetPrivet() const;

private:
    int m_a;
};

X::X(int a_)
    : m_a(a_)
{
}

int X::GetPrivet() const
{
    return (m_a);
}

void X::Foo()
{
    printf("%d\n", m_a);
}

void Foo(const X &x_)
{
    printf("%d\n", x_.GetPrivet());
}

int main()
{
    X x1(1);

    x1.Foo();
    printf("%d\n", x1.GetPrivet());
    Foo(x1);

    return 0;
}
