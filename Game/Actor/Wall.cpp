#include "Wall.h"

Wall::Wall(const Vector2F& position) : Actor('#', Color::White, position)
{
	SetRenderSortingOrder(0);
}
