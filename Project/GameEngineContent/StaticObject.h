#pragma once
#include "BaseContentActor.h"

class StaticObject : public BaseContentActor
{
public:
	StaticObject();
	~StaticObject();

	StaticObject(const StaticObject& _Other) = delete;
	StaticObject(StaticObject&& _Other) noexcept = delete;
	StaticObject& operator=(const StaticObject& _Other) = delete;
	StaticObject& operator=(StaticObject&& _Other) noexcept = delete;

protected:
	
private:
	std::shared_ptr<GameEngineSpriteRenderer> ImageRender = nullptr;
};