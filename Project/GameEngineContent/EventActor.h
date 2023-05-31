#pragma once
#include "BaseContentActor.h"

class EventActor : public BaseContentActor
{
public:
	EventActor();
	~EventActor();

	EventActor(const EventActor& _Other) = delete;
	EventActor(EventActor&& _Other) noexcept = delete;
	EventActor& operator=(const EventActor& _Other) = delete;
	EventActor& operator=(EventActor&& _Other) noexcept = delete;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _SaveSerializer);

	void ShowGUI() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineCollision> EventCol = nullptr;


	bool ActiveEnterEvent = false;
	std::string EnterEventName = "";

	bool ActiveUpdateEvent = false;
	std::string UpdateEventName = "";

	bool ActiveExitEvent = false;
	std::string ExitEventName = "";

	bool IsEventEnter = false;

};

