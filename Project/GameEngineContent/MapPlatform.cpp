#include "PrecompileHeader.h"
#include "MapPlatform.h"

#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MapPlatformDebugRender.h"


MapPlatform::MapPlatform()
{
}

MapPlatform::~MapPlatform()
{
}

void MapPlatform::Init(const Platform_DESC& _Desc)
{
	Desc = _Desc;

	GetTransform()->SetLocalPosition(_Desc.Pos);

}

void MapPlatform::PlatformDebugOn()
{
	if (true == IsDebug())
	{
		return;
	}

	std::shared_ptr<MapPlatformDebugRender> DebugRender = GetLevel()->CreateActor<MapPlatformDebugRender>();
	DebugRender->SetTargetPlatform(this);
	DebugRender->GetTransform()->SetParent(GetTransform());
	DebugRender->GetTransform()->SetLocalPosition(float4::Zero);

	DebugOn();
}

void MapPlatform::PlatformDebugOff()
{
	DebugOff();
}

void MapPlatform::ShowGUI()
{
	const char* AreaComboText[2] = { "Normal" ,"Half" };
	int CurrentPlatformTypeIndex = static_cast<int>(Desc.Type);

	ImGui::Combo("PlatformType", &CurrentPlatformTypeIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));

	PlatformType InputType = static_cast<PlatformType>(CurrentPlatformTypeIndex);

	if (InputType != Desc.Type)
	{
		Desc.Type = InputType;
	}

	ImGui::Spacing();

	float Pos[4] = { Desc.Pos.x, Desc.Pos.y, Desc.Pos.z, Desc.Pos.w };
	ImGui::DragFloat4("Postion", Pos);

	if (Desc.Pos.x != Pos[0] ||
		Desc.Pos.y != Pos[1] ||
		Desc.Pos.z != Pos[2] ||
		Desc.Pos.w != Pos[3])
	{
		Desc.Pos.x = Pos[0];
		Desc.Pos.y = Pos[1];
		Desc.Pos.z = Pos[2];
		Desc.Pos.w = Pos[3];

		GetTransform()->SetLocalPosition(Desc.Pos);
	}

	ImGui::Spacing();

	float Rot[4] = { Desc.Rot.x, Desc.Rot.y, Desc.Rot.z, Desc.Rot.w };
	ImGui::DragFloat4("Rotation", Rot);

	if (Desc.Rot.x != Rot[0] ||
		Desc.Rot.y != Rot[1] ||
		Desc.Rot.z != Rot[2] ||
		Desc.Rot.w != Rot[3])
	{
		Desc.Rot.x = Rot[0];
		Desc.Rot.y = Rot[1];
		Desc.Rot.z = Rot[2];
		Desc.Rot.w = Rot[3];
	}

	ImGui::Spacing();

	float Scale[4] = { Desc.Scale.x, Desc.Scale.y, Desc.Scale.z, Desc.Scale.w };
	ImGui::DragFloat4("Scale", Scale);

	if (Desc.Scale.x != Scale[0] ||
		Desc.Scale.y != Scale[1] ||
		Desc.Scale.z != Scale[2] ||
		Desc.Scale.w != Scale[3])
	{
		Desc.Scale.x = Scale[0];
		Desc.Scale.y = Scale[1];
		Desc.Scale.z = Scale[2];
		Desc.Scale.w = Scale[3];
	}
}

void MapPlatform::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(Desc.Type));
	_SaveSerializer.Write(&Desc.Pos, sizeof(float4));
	_SaveSerializer.Write(&Desc.Rot, sizeof(float4));
	_SaveSerializer.Write(&Desc.Scale, sizeof(float4));
}

MapPlatform::Platform_DESC MapPlatform::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	Platform_DESC LoadDesc = Platform_DESC();

	int LoadType = 0;
	_LoadSerializer.Read(LoadType);
	LoadDesc.Type = static_cast<PlatformType>(LoadType);

	_LoadSerializer.Read(&LoadDesc.Pos, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Rot, sizeof(float4));
	_LoadSerializer.Read(&LoadDesc.Scale, sizeof(float4));

	return LoadDesc;
}