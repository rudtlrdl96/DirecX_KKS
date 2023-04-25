#include "PrecompileHeader.h"
#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Init(const BG_DESC& _Desc)
{
	Desc = _Desc;

	if (nullptr == BackImage)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	Desc.Center;
	Desc.Ratio;
	BackImage->SetTexture(Desc.TextureName);
	BackImage->GetTransform()->SetLocalScale(Desc.Size);

	GetTransform()->SetLocalPosition(Desc.Center);
}

void Background::Start()
{
	BackImage = CreateComponent<GameEngineSpriteRenderer>();	
	BackImage->Off();
}

void Background::Update(float _DeltaTime)
{
	if (nullptr == BackImage)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	if(nullptr == Target)
	{
		return;
	}

	if (true == Target->IsDeath())
	{
		Target = nullptr;
		return;
	}

	float4 RenderPos = Desc.Center;
	float4 TargetDir = Target->GetWorldPosition() - Desc.Center;

	RenderPos += TargetDir * Desc.Ratio;

	BackImage->GetTransform()->SetWorldPosition(RenderPos);
}
