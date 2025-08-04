#include "Goal.h"

Goal::Goal(const Vector2F& position) : Actor('T', Color::Blue, position)
{
	SetRenderSortingOrder(1);
}