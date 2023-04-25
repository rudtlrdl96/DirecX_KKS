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
		MsgAssert("��׶��� �̹����� �ʱ�ȭ ���� �ʰ� ����Ϸ� �߽��ϴ�");
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
		MsgAssert("��׶��� �̹����� �ʱ�ȭ ���� �ʰ� ����Ϸ� �߽��ϴ�");
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
