#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}

Level::~Level()
{
	// �޸� ����
	for (Actor* actor : actors)
	{
		//if (actor)
		//{
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}

}

void Level::SpawnActor(Actor* newActor)
{
	// TODO : �ߺ� ���� ���� ó��

	actors.push_back(newActor);

	// ���ʽ� ����.
	newActor->SetOwner(this);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	// ����
	SortActorsByRenderSortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// �˻�
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ���͸� ����
			if (actor == otherActor)
				continue;

			if (actor->GetPosition() == otherActor->GetPosition())
			{
				if (actor->renderSortingOrder < otherActor->renderSortingOrder)
				{
					searchedActor = otherActor;
					break;
				}
			}
		}
		
		if (searchedActor)
		{
			continue;
		}

		// Draw Call
		actor->Render();
	}
}

void Level::SortActorsByRenderSortingOrder()
{
	for (int idx = 0; idx < (int)actors.size(); ++idx)
	{
		for (int jdx = 0; jdx < (int)actors.size() - 1; ++jdx)
		{
			if (actors[jdx]->renderSortingOrder > actors[jdx + 1]->renderSortingOrder)
			{
				std::swap(actors[jdx], actors[jdx + 1]);
			}
		}


	}
}