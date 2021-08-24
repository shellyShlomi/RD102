// Developer: Shelly Shlomi
// Status: Done
// Reviewer: Yakov
// Group: RD102
// date: 24.8.21
// description: Implementation of Shape library 

#include <iostream> // cout
#include <list>		// list

#include "line.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"

namespace ilrd
{

/**************************** Shapes interface impl ****************************/

void PrintShapes(const std::list<Shape*> &shape_list)
{
	for (std::list<Shape *>::const_iterator it = shape_list.begin();
												it != shape_list.end(); ++it)
	{
		(*it)->Draw();
	}
	std::cout << std::endl;
	return;
}

Shape::~Shape()
{
	//empty
}

void Shape::Move(size_t offset)
{
	for (size_t i = 0; i < offset; ++i)
	{
		std::cout << " ";
	}
	Draw();
	return;
}

/********************************* Circle impl *********************************/

Circle::Circle()
{
	//empty
}

Circle::~Circle()
{
	//empty
}

void Circle::Draw() const
{
	std::cout << "Circle ";
	return;
}

/******************************* Rectangle impl *******************************/


Rectangle::Rectangle()
{
	//empty
}

Rectangle::~Rectangle()
{
	//empty
}
void Rectangle::Draw() const
{
	std::cout << "Rectangle " ;
	return;
}


/********************************** Line impl **********************************/

Line::Line()
{
	//empty
}

Line::~Line()
{
	//empty
}
void Line::Draw() const
{
	std::cout << "Line ";
	return;
}


/********************************* Square impl *********************************/

Square::Square()
{
	//empty
}

Square::~Square()
{
	//empty
}
void Square::Draw() const
{
	std::cout << "Square ";
	return;
}

}