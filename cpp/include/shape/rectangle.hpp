#ifndef ILRD_RD102_RECTANGLE_HPP
#define ILRD_RD102_RECTANGLE_HPP

#include "shape.hpp"

namespace ilrd
{

class Rectangle: public Shape
{
public:
	explicit Rectangle();
	virtual ~Rectangle();

	void Draw() const;

}; // Rectangle

} //ilrd

#endif /* ILRD_RD102_RECTANGLE_HPP */