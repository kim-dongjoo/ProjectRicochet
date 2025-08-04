#include "Goal.h"

Goal::Goal(const Vector2F& position) : Actor('G', Color::Blue, position)
{
	SetRenderSortingOrder(1);
}