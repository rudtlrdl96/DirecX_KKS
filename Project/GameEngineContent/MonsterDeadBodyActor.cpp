#include "PrecompileHeader.h"
#include "MonsterDeadBodyActor.h"

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

void MonsterDeadBodyActor::Start()
{
	BodyRender = CreateComponent<ContentSpriteRenderer>();
	BodyRender->PipeSetting("2DTexture_ColorLight");
	BodyRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	BodyRender->Off();

	GameEventManager::AddEvent("MoveStage", GetActorCode(), [this]()
		{
			Death();
		});
}
