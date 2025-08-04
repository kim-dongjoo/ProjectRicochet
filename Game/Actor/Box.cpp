#include "Box.h"

Box::Box(const Vector2F& position) : Actor('B', Color::Green, position)
{
	SetRenderSortingOrder(2);
}
