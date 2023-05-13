#pragma once
#include "BaseContentActor.h"

class AttackColToolAnimActor : public BaseContentActor
{
public:
	AttackColToolAnimActor();
	~AttackColToolAnimActor();

	AttackColToolAnimActor(const AttackColToolAnimActor& _Other) = delete;
	AttackColToolAnimActor(AttackColToolAnimActor&& _Other) noexcept = delete;
	AttackColToolAnimActor& operator=(const AttackColToolAnimActor& _Other) = delete;
	AttackColToolAnimActor& operator=(AttackColToolAnimActor&& _Other) noexcept = delete;

	inline std::shared_ptr<GameEngineSpriteRenderer> GetSpriteRender()
	{
		return Render;
	}

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr; 

};

