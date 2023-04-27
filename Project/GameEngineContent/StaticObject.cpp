#include "PrecompileHeader.h"
#include "StaticObject.h"

#if _DEBUG
std::shared_ptr<StaticObject> StaticObject::FocusStaticObject = nullptr;
#endif

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

void StaticObject::Init(const SObject_DESC& _Desc)
{
	Desc = _Desc;

	if ("" == Desc.Name)
	{
		MsgAssert_Rtti<StaticObject>(" - �ؽ��� �̸��� �������� �ʾҽ��ϴ�");
	}

	if (Desc.Size == float4::Zero)
	{
		MsgAssert_Rtti<StaticObject>(" - ���� ����� �������� �ʾҽ��ϴ�");
	}

	ImageRender->SetTexture(Desc.Name);
	ImageRender->GetTransform()->SetLocalScale(Desc.Size);
	ImageRender->GetTransform()->SetLocalPosition(Desc.Pos);

	float4 ActorScale = GetTransform()->GetLocalScale();
	float4 RenderScale = ImageRender->GetTransform()->GetLocalScale();
	
	ImageRender->On();
}

void StaticObject::Start()
{
	ImageRender = CreateComponent<GameEngineSpriteRenderer>();
	ImageRender->SetPipeLine("2DTexture_ColorLight");
	ImageRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", Desc.Color);
	ImageRender->Off();
}