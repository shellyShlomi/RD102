#include <iostream>
/*
class B
{
public:
    B(int a_ ) : m_a(a_) { std::std::cout << "B::Ctor" << std::std::endl; }
    virtual ~B() { std::std::cout << "B::Dtor" << std::std::endl; }
    //java style is not allowed in our coding convention
    virtual void Print1() const;
     void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

void B::Print1() const
{
    std::std::cout << "B::Print1 B::m_a - " << m_a << std::std::endl;
}

void B::Print2() const
{
    std::std::cout << "B::Print2" << std::std::endl;
}

void B::Print3() const
{
    std::std::cout << "B::Print3" << std::std::endl;
}

class X : public B
{
public:
    X() : B(6), m_b(0) { std::std::cout << "X::Ctor" << std::std::endl; }

    ~X() { std::std::cout << "X::Dtor" << std::std::endl; }

    virtual void Print1() const
    {
        std::std::cout << "X::Print1 X::m_b - " << m_b << std::std::endl;
        B::Print1();
        std::std::cout << "X::Print1 end" << std::std::endl;
    }

    void Print2() const { std::std::cout << "X::Print2" << std::std::endl; }
    void Print4() const { std::std::cout << "X::Print4" << std::std::endl; }

private:
    int m_b;
};

int main()
{
    B *b1 = new B(10); //call B
    std::std::cout << std::std::endl;
    B *b2 = new X; //
    std::std::cout << std::std::endl
              << "main b1:" << std::std::endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();
    std::std::cout << std::std::endl
              << "main b2:" << std::std::endl;
    b2->Print1();
    b2->Print2();

    std::std::cout << std::std::endl;
    std::std::cout << std::std::endl;

    b2->Print3();
    std::std::cout << std::std::endl;

    std::std::cout << std::std::endl;
    X *b3 = new X;
    std::std::cout << std::std::endl
              << "main b3:" << std::std::endl;
    b3->Print1();
    b3->Print2();
    b3->Print4();

    X *xx = static_cast<X *>(b2);
    std::std::cout << std::std::endl
              << "main xx:" << std::std::endl;
    xx->Print2();
    b2->Print2();

    delete b1;
    delete b2;
    delete b3;

    return 0;
} */

class B
{
public:
    B(int a_) : m_a(a_) { std::cout << "B::Ctor" << std::endl; }
    virtual ~B() { std::cout << "B::Dtor" << std::endl; }
    //java style is not allowed in our coding convention
    virtual void Print1() const;
    virtual void Print2() const;
    virtual void Print3() const;

private:
    int m_a;
};

void B::Print1() const
{
    std::cout << "B::Print1 B::m_a - " << m_a << std::endl;
}

void B::Print2() const
{
    std::cout << "B::Print2" << std::endl;
}

void B::Print3() const
{
    std::cout << "B::Print3" << std::endl;
}

class X : public B
{
public:
    X() : B(8), m_b(0) { std::cout << "X::Ctor" << std::endl; }

    ~X() { std::cout << "X::Dtor" << std::endl; }

    virtual void Print1() const
    {
        std::cout << "X::Print1 X::m_b - " << m_b << std::endl;
        B::Print1();
        std::cout << "X::Print1 end" << std::endl;
    }

    void Print2() const { std::cout << "X::Print2" << std::endl; }

private:
    int m_b;
};

class Y : public X
{
public:
    Y() : m_b(0) { std::cout << "Y::Ctor" << std::endl; }

    ~Y() { std::cout << "Y::Dtor" << std::endl; }

    void Print1() const
    {
        std::cout << "Y::Print1 Y::m_b - " << m_b << std::endl;
        // B::Print1();
        std::cout << "Y::Print1 end" << std::endl;
    }
    // void Print2() const { std::cout << "Y::Print2" << std::endl; }


private:
    int m_b;
};

int main()
{
    B *b1 = new B(0);
    B *b2 = new X;
    X *b3 = new Y;

    // std::cout << std::endl
    //           << "main b1:" << std::endl;
    // b1->Print1();
    // b1->Print2();
    // // b1->Print3();

    // std::cout << std::endl
    //           << "main b2:" << std::endl;
    // b2->Print1();
    // b2->Print2();
    // // b2->Print3();

    // // X *xx = new X;//static_cast<X *>(b2);
    // X *x = static_cast<X *>(b2);
    // // B *x1 = static_cast<X *>(b2);
    // std::cout << std::endl
    //           << "main xx:" << std::endl;
    // // xx->Print2();
    // x->Print2();
    // // x1->Print2();
    // b2->Print2();

    b3->Print1();
    b3->Print2();
    b3->Print3();

    delete b1;
    delete b2;
    delete b3;

    return 0;
}