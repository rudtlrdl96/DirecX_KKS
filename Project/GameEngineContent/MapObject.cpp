#include "PrecompileHeader.h"
#include "MapObject.h"
#include <GameEngineCore/imgui.h>

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

void MapObject::Init(const ObjectMetaData& _MetaData)
{
	MetaData = _MetaData;

	if ("" == MetaData.Name)
	{
		MsgAssert_Rtti<MapObject>(" - 텍스쳐 이름을 지정하지 않았습니다");
	}

	if (MetaData.Size == float4::Zero)
	{
		MsgAssert_Rtti<MapObject>(" - 랜더 사이즈를 지정하지 않았습니다");
	}

	if (true == MetaData.IsMinimapRender && nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		ImageRender->PushCameraRender((int)CameraOrder::MiniMap);
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
	Buffer.LightColor = MetaData.LightColor;

	ImageRender->On();
}

const ObjectMetaData& MapObject::GetMetaData()
{
	MetaData.Pos = GetTransform()->GetLocalPosition();
	MetaData.Rot = GetTransform()->GetLocalRotation();
	MetaData.Scale = GetTransform()->GetLocalScale();
	MetaData.Color = Buffer.Color;
	MetaData.LightColor = Buffer.LightColor;

	return MetaData;
}

void MapObject::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	GetMetaData();

	_SaveSerializer.Write(MetaData.Name);
	_SaveSerializer.Write(&MetaData.Index, sizeof(size_t));
	_SaveSerializer.Write(&MetaData.Grade, sizeof(LevelArea));
	_SaveSerializer.Write(&MetaData.IsMinimapRender, sizeof(bool));
	_SaveSerializer.Write(&MetaData.Pos, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Rot, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Scale, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Size, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Color, sizeof(float4));
	_SaveSerializer.Write(&MetaData.LightColor, sizeof(float4));

}

ObjectMetaData MapObject::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	ObjectMetaData LoadMetaData = ObjectMetaData();

	_LoadSerializer.Read(LoadMetaData.Name);
	_LoadSerializer.Read(&LoadMetaData.Index, sizeof(size_t));
	_LoadSerializer.Read(&LoadMetaData.Grade, sizeof(LevelArea));
	_LoadSerializer.Read(&LoadMetaData.IsMinimapRender, sizeof(bool));
	_LoadSerializer.Read(&LoadMetaData.Pos, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Rot, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Scale, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Size, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Color, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.LightColor, sizeof(float4));
	
	return LoadMetaData;
}

void MapObject::ShowGUI()
{
	ImGui::Spacing();

	ImGui::Checkbox("IsMinimapRender", &MetaData.IsMinimapRender);

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

	float LightColor[4] = { Buffer.LightColor.x, Buffer.LightColor.y, Buffer.LightColor.z, Buffer.LightColor.w };
	ImGui::ColorEdit4("MyLightColor##1", LightColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_AlphaBar);

	if (Buffer.LightColor.x != LightColor[0] ||
		Buffer.LightColor.y != LightColor[1] ||
		Buffer.LightColor.z != LightColor[2] ||
		Buffer.LightColor.w != LightColor[3])
	{
		Buffer.LightColor.x = LightColor[0];
		Buffer.LightColor.y = LightColor[1];
		Buffer.LightColor.z = LightColor[2];
		Buffer.LightColor.w = LightColor[3];
	}
}

std::string MapObject::GetTexName() const
{
	if (nullptr == ImageRender)
	{
		MsgAssert_Rtti<MapObject>(" - 랜더를 생성하지않고 텍스쳐 이름을 받아오려 했습니다");
		return "";
	}

	return ImageRender->GetTexName();
}

float4 MapObject::GetTexWorldScale() const
{
	if (nullptr == ImageRender)
	{
		MsgAssert_Rtti<MapObject>(" - 랜더를 생성하지않고 텍스쳐 이름을 받아오려 했습니다");
		return float4::Zero;
	}

	return ImageRender->GetTransform()->GetWorldScale();
}

void MapObject::Start()
{
	ImageRender = CreateComponent<ContentSpriteRenderer>();
	ImageRender->PipeSetting("2DTexture_Object");
	ImageRender->GetShaderResHelper().SetConstantBufferLink("ObjectColorBuffer", Buffer);
	ImageRender->CameraCullingOn();
	ImageRender->Off();
}