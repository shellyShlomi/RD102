#ifndef ILRD_RD102_SHAPES_HPP
#define ILRD_RD102_SHAPES_HPP

#include <cstddef> // size_t
#include <list> // list

namespace ilrd
{
class Shape
{
public:

	virt
	ual ~Shape();

	virtual void Draw() const=0;
	void Move(size_t offset);
}; // Shape

void PrintShapes(const Shape **shape_list, size_t list_size); // stl list

class Line: public Shape
{
public:
	explicit Line();
	~Line();

	void Draw() const;

}; // Line

class Circle: public Shape
{
public:
	explicit Circle();
	~Circle();
	
	void Draw() const;

}; // Circle

class Rectangle: public Shape
{
public:
	explicit Rectangle();
	~Rectangle();

	void Draw() const;

}; // Rectangle

class Square: public Rectangle
{
public:
	explicit Square();
	~Square();

	void Draw() const;
}; // Square		

} //ilrd

#endif /* ILRD_RD102_SHAPES_HPP */