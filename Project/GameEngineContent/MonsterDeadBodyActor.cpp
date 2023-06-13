#include "PrecompileHeader.h"
#include "MonsterDeadBodyActor.h"
#include "BattleLevel.h"

MonsterDeadBodyActor::MonsterDeadBodyActor()
{
}

MonsterDeadBodyActor::~MonsterDeadBodyActor()
{
}

void MonsterDeadBodyActor::SetTexture(const std::string_view& _TextureName, float _Ratio /*= 1.0f*/)
{
	BodyRender->SetScaleToTexture(_TextureName);

	float4 TextureScale = BodyRender->GetTransform()->GetLocalScale();

	BodyRender->GetTransform()->SetLocalScale(TextureScale * _Ratio);
	BodyRender->On();
}

void MonsterDeadBodyActor::Destroy()
{
	ContentLevel* LevelPtr = GetContentLevel();
	LevelPtr->RemoveEvent("MoveStage", GetActorCode());
}

void MonsterDeadBodyActor::Start()
{
	BodyRender = CreateComponent<ContentSpriteRenderer>();
	BodyRender->PipeSetting("2DTexture_Color");
	BodyRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	BodyRender->Off();

	BattleLevel* BattleLevelPtr = static_cast<BattleLevel*>(GetLevel());

	if (nullptr != BattleLevelPtr)
	{
		BattleLevelPtr->AddEvent("MoveStage", GetActorCode(), [this]()
			{
				Death();
			});
	}
}
