#ifndef ILRD_RD102_LINE_HPP
#define ILRD_RD102_LINE_HPP

#include "shape.hpp"

namespace ilrd
{

class Line: public Shape
{
public:
	explicit Line();
	virtual ~Line();

	void Draw() const;

}; // Line

} //ilrd

#endif /* ILRD_RD102_LINE_HPP */