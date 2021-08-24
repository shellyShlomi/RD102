#ifndef ILRD_RD102_SHAPE_HPP
#define ILRD_RD102_SHAPE_HPP

#include <cstddef> // size_t
#include <list> // list

namespace ilrd
{
class Shape
{
public:

	virtual ~Shape();

	virtual void Draw() const=0;
	void Move(size_t offset = 10);

}; // Shape

void PrintShapes(const std::list<Shape *> &shape_list); // stl list


} // ilrd

#endif /* ILRD_RD102_SHAPE_HPP */
