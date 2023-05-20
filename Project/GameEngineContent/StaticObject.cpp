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

void StaticObject::Init(const SObjectMetaData& _MetaData)
{
	MetaData = _MetaData;

	if ("" == MetaData.Name)
	{
		MsgAssert_Rtti<StaticObject>(" - 텍스쳐 이름을 지정하지 않았습니다");
	}

	if (MetaData.Size == float4::Zero)
	{
		MsgAssert_Rtti<StaticObject>(" - 랜더 사이즈를 지정하지 않았습니다");
	}

	ImageRender->SetTexture(MetaData.Name);
	MetaData.Size.z = 1;
	ImageRender->GetTransform()->SetLocalScale(MetaData.Size);
	GetTransform()->SetLocalPosition(MetaData.Pos);
	GetTransform()->SetLocalRotation(MetaData.Rot);
	GetTransform()->SetLocalScale(MetaData.Scale);

	float4 ActorScale = GetTransform()->GetLocalScale();
	float4 RenderScale = ImageRender->GetTransform()->GetLocalScale();
	
	Buffer.Color = MetaData.Color;

	ImageRender->On();
}

const SObjectMetaData& StaticObject::GetMetaData()
{
	MetaData.Pos = GetTransform()->GetLocalPosition();
	MetaData.Rot = GetTransform()->GetLocalRotation();
	MetaData.Scale = GetTransform()->GetLocalScale();
	MetaData.Color = Buffer.Color;

	return MetaData;
}

void StaticObject::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	GetMetaData();

	_SaveSerializer.Write(MetaData.Name);
	_SaveSerializer.Write(&MetaData.Index, sizeof(size_t));
	_SaveSerializer.Write(&MetaData.Grade, sizeof(LevelArea));
	_SaveSerializer.Write(&MetaData.Pos, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Rot, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Scale, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Size, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Color, sizeof(float4));

}

SObjectMetaData StaticObject::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	SObjectMetaData LoadMetaData = SObjectMetaData();

	_LoadSerializer.Read(LoadMetaData.Name);
	_LoadSerializer.Read(&LoadMetaData.Index, sizeof(size_t));
	_LoadSerializer.Read(&LoadMetaData.Grade, sizeof(LevelArea));
	_LoadSerializer.Read(&LoadMetaData.Pos, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Rot, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Scale, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Size, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Color, sizeof(float4));
	
	return LoadMetaData;
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
}

std::string StaticObject::GetTexName() const
{
	if (nullptr == ImageRender)
	{
		MsgAssert_Rtti<StaticObject>(" - 랜더를 생성하지않고 텍스쳐 이름을 받아오려 했습니다");
		return "";
	}

	return ImageRender->GetTexName();
}

float4 StaticObject::GetTexWorldScale() const
{
	if (nullptr == ImageRender)
	{
		MsgAssert_Rtti<StaticObject>(" - 랜더를 생성하지않고 텍스쳐 이름을 받아오려 했습니다");
		return float4::Zero;
	}

	return ImageRender->GetTransform()->GetWorldScale();
}

void StaticObject::Start()
{
	ImageRender = CreateComponent<ContentSpriteRenderer>();
	ImageRender->PipeSetting("2DTexture_ColorLight");
	ImageRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	ImageRender->Off();
}