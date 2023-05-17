#pragma once
#include "BaseContentActor.h"
#include "AnimationAttackMetaData.h"

class AttackColRender : public BaseContentActor
{
public:
	AttackColRender();
	~AttackColRender();

	AttackColRender(const AttackColRender& _Other) = delete;
	AttackColRender(AttackColRender&& _Other) noexcept = delete;
	AttackColRender& operator=(const AttackColRender& _Other) = delete;
	AttackColRender& operator=(AttackColRender&& _Other) noexcept = delete;

	void DrawColData(const AttackColMetaData& _Data);

protected:

private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> Renders;
};

