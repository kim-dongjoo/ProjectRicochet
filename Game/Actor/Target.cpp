#include "Target.h"

Target::Target(const Vector2F& position) : Actor('T', Color:: Blue, position)
{
	SetRenderSortingOrder(1);
}
