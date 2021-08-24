#include <iostream> // cout
#include <list>     // list

#include "shapes.hpp"

void TestShape();

int main()
{
    TestShape();
    return (0);
}

void TestShape()
{
    const size_t C_OFFSET = 20;
    std::list<ilrd::Shape *> shape_l(0);

    shape_l.push_back(new ilrd::Circle());
    shape_l.push_back(new ilrd::Line());
    shape_l.push_back(new ilrd::Circle());
    shape_l.push_back(new ilrd::Line());
    shape_l.push_back(new ilrd::Square());
    shape_l.push_back(new ilrd::Rectangle());
    shape_l.push_back(new ilrd::Square());

    std::cout << "defult offset of move" << std::endl;
    std::cout << std::endl;

    for (std::list<ilrd::Shape *>::iterator it = shape_l.begin();
         it != shape_l.end(); ++it)
    {
        (*it)->Move();
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "20 is offset of move" << std::endl;
    std::cout << std::endl;

    for (std::list<ilrd::Shape *>::iterator it = shape_l.begin();
         it != shape_l.end(); ++it)
    {
        (*it)->Move(C_OFFSET);
    }
    std::cout << std::endl;
    std::cout << std::endl;

    PrintShapes(shape_l);

    std::cout << std::endl;

    return;
}
