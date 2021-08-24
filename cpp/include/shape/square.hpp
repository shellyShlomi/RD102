#ifndef ILRD_RD102_SQUARE_HPP
#define ILRD_RD102_SQUARE_HPP

#include "shape.hpp"

namespace ilrd
{

class Square: public Shape
{
public:
	explicit Square();
	virtual ~Square();

	void Draw() const;

}; // Square

} //ilrd

#endif /* ILRD_RD102_SQUARE_HPP */