#include "PrecompileHeader.h"
#include "EventActor.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "GameEventManager.h"

EventActor::EventActor()
{
}

EventActor::~EventActor()
{
}

void EventActor::Start()
{
	EventCol = CreateComponent<GameEngineCollision>();
}

void EventActor::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> PlayerCol = EventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (true == IsEventEnter)
	{
		if (true == ActiveEnterEvent)
		{
			GameEventManager::CallEvent(UpdateEventName);
		}

		if (nullptr == PlayerCol)
		{
			IsEventEnter = false;
			GameEventManager::CallEvent(ExitEventName);
		}
	}

	if (false == IsEventEnter)
	{
		if (nullptr != PlayerCol)
		{
			IsEventEnter = true;
			GameEventManager::CallEvent(EnterEventName);
		}
	}
}

void EventActor::SaveBin(GameEngineSerializer& _SaveSerializer)
{
}

void EventActor::LoadBin(GameEngineSerializer& _SaveSerializer)
{
}

void EventActor::ShowGUI()
{
}