#include "Ground.h"

Ground::Ground(const Vector2F& position) : Actor('.', Color::White, position)
{
	SetRenderSortingOrder(0);
}