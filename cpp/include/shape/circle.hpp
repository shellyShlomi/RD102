#ifndef ILRD_RD102_CIRCLE_HPP
#define ILRD_RD102_CIRCLE_HPP

#include "shape.hpp"

namespace ilrd
{

class Circle: public Shape
{
public:
	explicit Circle();
	virtual ~Circle();

	void Draw() const;

}; // Circle

} //ilrd

#endif /* ILRD_RD102_CIRCLE_HPP */