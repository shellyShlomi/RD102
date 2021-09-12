#include <iostream> //cout
#include <cstring>
using namespace std;

class PublicTransport
{
public:
    PublicTransport() : m_license_plate(++s_count)
    {
        cout << "PublicTransport::Ctor()" << m_license_plate << "\n";
    }

    virtual ~PublicTransport()
    {
        --s_count;
        cout << "PublicTransport::Dtor()" << m_license_plate << "\n";
    }

    PublicTransport(const PublicTransport &other) : m_license_plate(++s_count)
    {
        (void)other;
        cout << "PublicTransport::CCtor() " << m_license_plate << "\n";
    }

    virtual void display()
    {
        cout << "PublicTransport::display(): " << m_license_plate << "\n";
    }

    static void print_count()
    {
        cout << "s_count: " << s_count << "\n";
    }

protected:
    int get_ID()
    {
        return m_license_plate;
    }

private:
    static int s_count;
    int m_license_plate;
    PublicTransport &operator=(const PublicTransport &); // disabled
};

int PublicTransport::s_count = 0;

class Minibus : public PublicTransport
{
public:
    Minibus() : m_numSeats(20)
    {
        cout << "Minibus::Ctor()\n";
    }

    Minibus(const Minibus &other) : PublicTransport(other),
                                    m_numSeats(other.m_numSeats)
    {
        cout << "Minibus::CCtor()\n";
    }

    ~Minibus()
    {
        cout << "Minibus::Dtor()\n";
    }

    void display()
    {
        cout << "Minibus::display() ID:" << get_ID();
        cout << " num seats:" << m_numSeats << "\n";
    }

    virtual void wash(int minutes)
    {
        cout << "Minibus::wash(" << minutes << ") ID:" << get_ID() << "\n";
    }

private:
    int m_numSeats;
};

class Taxi : public PublicTransport
{
public:
    Taxi()
    {
        cout << "Taxi::Ctor()\n";
    }

    Taxi(const Taxi &other) : PublicTransport(other)
    {
        cout << "Taxi::CCtor()\n";
    }

    ~Taxi()
    {
        cout << "Taxi::Dtor()\n";
    }

    void display()
    {
        cout << "Taxi::display() ID:" << get_ID() << "\n";
    }

private:
};

template <class T>
inline T max_func(const T &t1, const T &t2)
{
    return ((t1 > t2) ? t1 : t2);
}

class SpecialTaxi : public Taxi
{
public:
    SpecialTaxi()
    {
        cout << "SpecialTaxi::Ctor()\n";
    }

    SpecialTaxi(const SpecialTaxi &other) : Taxi(other)
    {
        cout << "SpecialTaxi::CCtor()\n";
    }

    ~SpecialTaxi()
    {
        cout << "SpecialTaxi::Dtor()\n";
    }

    void display()
    {
        cout << "SpecialTaxi::display() ID:" << get_ID() << "\n";
    }

private:
};

class PublicConvoy : public PublicTransport
{
public:
    PublicConvoy() : m_pt1(new Minibus()), m_pt2(new Taxi())
    {
    }

    PublicConvoy(PublicConvoy &other) : PublicTransport(other),
                                        m_pt1(new Minibus(dynamic_cast<Minibus &>(*(other.m_pt1)))),
                                        m_pt2(new Taxi(dynamic_cast<Taxi &>(*(other.m_pt2)))),
                                        m_m(other.m_m), m_t(other.m_t)
    {
    }

    ~PublicConvoy()
    {
        delete m_pt1;
        delete m_pt2;
    }

    void display()
    {
        m_pt1->display();
        m_pt2->display();
        m_m.display();
        m_t.display();
    }

private:
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
};

void print_info(PublicTransport &a)
{
    a.display();
}

void print_info()
{
    PublicTransport::print_count();
}

void print_info(Minibus &m)
{
    m.wash(3);
}

PublicTransport print_info(int i)
{
    (void)i;
    Minibus ret;
    cout << "print_info(int i)\n";
    ret.display();
    return ret;
}

void taxi_display(Taxi s)
{
    s.display();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    Minibus m;
    // std::cout << "------------------------------------------------" << std::endl;
    print_info(m);
    // std::cout << "------------------------------------------------" << std::endl;

    print_info(3).display();
    // std::cout << "------------------------------------------------" << std::endl;

    PublicTransport *array[] = {new Minibus(), new Taxi(), new Minibus()};
    // //     std::cout << "------------------------------------------------" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        array[i]->display();
    }
    // std::cout << "------------------------------------------------" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        delete array[i];
    }

    PublicTransport arr2[] = {Minibus(), Taxi(), PublicTransport()};
    // std::cout << "------------------------------------------------" << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        arr2[i].display();
    }

    print_info(arr2[0]);
    //     std::cout << "------------------------------------------------" << std::endl;

    PublicTransport::print_count();

    Minibus m2;
    //     std::cout << "------------------------------------------------" << std::endl;

    m2.print_count();
    //     std::cout << "------------------------------------------------" << std::endl;

    Minibus arr3[4];
    //     std::cout << "------------------------------------------------" << std::endl;

    Taxi *arr4 = new Taxi[4];
    //     std::cout << "------------------------------------------------" << std::endl;

    delete[] arr4;
    //     std::cout << "------------------------------------------------" << std::endl;

    std::cout << max_func(1, 2) << "\n";
    //     std::cout << "------------------------------------------------" << std::endl;

    std::cout << max_func<int>(1, 2.0f) << "\n";
    //     std::cout << "------------------------------------------------" << std::endl;

    // std::cout << "------------------------------------------------" << std::endl;
    SpecialTaxi st;
    // std::cout << "------------------------------------------------" << std::endl;

    taxi_display(st);
    // std::cout << "------------------------------------------------" << std::endl;
    // std::cout << "------------------------------------------------" << std::endl;

    PublicConvoy *ts1 = new PublicConvoy();
    // std::cout << "------------------------------------------------" << std::endl;

    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    // std::cout << "------------------------------------------------" << std::endl;

    ts1->display();
    // std::cout << "------------------------------------------------" << std::endl;

    ts2->display();

    // std::cout << "------------------------------------------------" << std::endl;

    delete ts1;
    // std::cout << "------------------------------------------------" << std::endl;

    ts2->display(); // this crashes. fix the bug!
    // std::cout << "------------------------------------------------" << std::endl;

    delete ts2;
    // std::cout << "------------------------------------------------" << std::endl;
    // std::cout << "------------------------------------------------" << std::endl;

    return 0;
}
