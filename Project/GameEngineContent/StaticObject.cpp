#include "PrecompileHeader.h"
#include "StaticObject.h"
#include <GameEngineCore/imgui.h>

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
		MsgAssert_Rtti<StaticObject>(" - 텍스쳐 이름을 지정하지 않았습니다");
	}

	if (Desc.Size == float4::Zero)
	{
		MsgAssert_Rtti<StaticObject>(" - 랜더 사이즈를 지정하지 않았습니다");
	}

	ImageRender->SetTexture(Desc.Name);
	Desc.Size.z = 1;
	ImageRender->GetTransform()->SetLocalScale(Desc.Size);
	GetTransform()->SetLocalPosition(Desc.Pos);
	GetTransform()->SetLocalRotation(Desc.Rot);
	GetTransform()->SetLocalScale(Desc.Scale);

	float4 ActorScale = GetTransform()->GetLocalScale();
	float4 RenderScale = ImageRender->GetTransform()->GetLocalScale();
	
	Buffer.Color = Desc.Color;

	ImageRender->On();
}

const SObject_DESC& StaticObject::GetDesc()
{
	Desc.Pos = GetTransform()->GetLocalPosition();
	Desc.Rot = GetTransform()->GetLocalRotation();
	Desc.Scale = GetTransform()->GetLocalScale();
	Desc.Color = Buffer.Color;

	return Desc;
}

void StaticObject::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	GetDesc();

	_SaveSerializer.Write(Desc.Name);
	_SaveSerializer.Write(&Desc.Index, sizeof(size_t));
	_SaveSerializer.Write(&Desc.Grade, sizeof(LevelArea));
	_SaveSerializer.Write(&Desc.Pos, sizeof(float4));
	_SaveSerializer.Write(&Desc.Rot, sizeof(float4));
	_SaveSerializer.Write(&Desc.Scale, sizeof(float4));
	_SaveSerializer.Write(&Desc.Size, sizeof(float4));
	_SaveSerializer.Write(&Desc.Color, sizeof(float4));

}

SObject_DESC StaticObject::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	SObject_DESC LoadDesc = SObject_DESC();

	_LoadSerializer.Read(LoadDesc.Name);
	_LoadSerializer.Read(&LoadDesc.Index, sizeof(size_t));
	_LoadSerializer.Read(&LoadDesc.Grade, sizeof(LevelArea));
	_LoadSerializer.Read(&LoadDesc.Pos, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Rot, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Scale, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Size, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Color, sizeof(float4));
	
	return LoadDesc;
}

void StaticObject::ShowGUI()
{
	ImGui::Spacing();

	float Color[4] = { Buffer.Color.x, Buffer.Color.y, Buffer.Color.z, Buffer.Color.w };
	ImGui::ColorEdit4("MyColor##1", Color, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_AlphaBar);
	
	if (Buffer.Color.x != Color[0] ||
		Buffer.Color.y != Color[1] ||
		Buffer.Color.z != Color[2] ||
		Buffer.Color.w != Color[3])
	{
		Buffer.Color.x = Color[0];
		Buffer.Color.y = Color[1];
		Buffer.Color.z = Color[2];
		Buffer.Color.w = Color[3];
	}

	//ImGui::ColorEdit4();
}

void StaticObject::Start()
{
	ImageRender = CreateComponent<GameEngineSpriteRenderer>();
	ImageRender->SetPipeLine("2DTexture_ColorLight");
	ImageRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	ImageRender->Off();
}