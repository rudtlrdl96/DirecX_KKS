#include "PrecompileHeader.h"
#include "StageRewardObject.h"

StageRewardObject::StageRewardObject()
{
}

StageRewardObject::~StageRewardObject()
{
}

void StageRewardObject::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->GetTransform()->SetLocalScale(float4(150, 150));

	RewardCol = CreateComponent<GameEngineCollision>();
	RewardCol->GetTransform()->SetLocalScale(float4(150, 150));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}
}

void StageRewardObject::Update(float _DeltaTime)
{
	if (nullptr == RewardCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("UseKey"))
	{
		IsRewardEndValue = true;
	}
}