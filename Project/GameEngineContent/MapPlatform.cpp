#include "PrecompileHeader.h"
#include "MapPlatform.h"

#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "CollisionDebugRender.h"


MapPlatform::MapPlatform()
{
}

MapPlatform::~MapPlatform()
{
}

void MapPlatform::Init(const PlatformMetaData& _MetaData)
{
	MetaData = _MetaData;

	GetTransform()->SetLocalPosition(MetaData.Pos);

	switch (MetaData.Type)
	{
	case PlatformType::Normal:
	{
		if (nullptr == PlatformCol)
		{
			PlatformCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
			PlatformCol->SetColType(ColType::AABBBOX2D);
		}
		else
		{
			PlatformCol->SetOrder((int)CollisionOrder::Platform_Normal);
		}
	}
		break;
	case PlatformType::Half:
	{
		if (nullptr == PlatformCol)
		{
			PlatformCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
			PlatformCol->SetColType(ColType::AABBBOX2D);
		}
		else
		{
			PlatformCol->SetOrder((int)CollisionOrder::Platform_Half);
		}
	}
		break;
	default:
		MsgAssert_Rtti<MapPlatform>(" - 잘못된 플랫폼 타입입니다.");
		break;
	}

	PlatformCol->GetTransform()->SetLocalScale(MetaData.Scale);
}

void MapPlatform::PlatformDebugOn()
{
	if (true == IsDebug())
	{
		return;
	}

	std::shared_ptr<CollisionDebugRender> DebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
	
	DebugRender->SetColorCallback(std::bind([this]()
		{
			if (nullptr == this)
			{
				return CollisionDebugRender::DebugColor::Green;
			}

			if (true == IsEmphasize)
			{
				return CollisionDebugRender::DebugColor::Magenta;
			}

			if (MetaData.Type == PlatformType::Normal)
			{
				return CollisionDebugRender::DebugColor::Green;
			}

			if (MetaData.Type == PlatformType::Half)
			{
				return CollisionDebugRender::DebugColor::Red;
			}

			return CollisionDebugRender::DebugColor::Red;
		}));
	
	DebugRender->SetTargetCollision(PlatformCol);
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
	const char* AreaComboText[2] = { "Normal" ,"Half"};
	int CurrentPlatformTypeIndex = static_cast<int>(MetaData.Type);

	ImGui::Combo("PlatformType", &CurrentPlatformTypeIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));

	PlatformType InputType = static_cast<PlatformType>(CurrentPlatformTypeIndex);

	if (InputType != MetaData.Type)
	{
		MetaData.Type = InputType;
	}

	ImGui::Spacing();

	float Pos[4] = { MetaData.Pos.x, MetaData.Pos.y, MetaData.Pos.z, MetaData.Pos.w };
	ImGui::DragFloat4("Position", Pos);

	if (MetaData.Pos.x != Pos[0] ||
		MetaData.Pos.y != Pos[1] ||
		MetaData.Pos.z != Pos[2] ||
		MetaData.Pos.w != Pos[3])
	{
		MetaData.Pos.x = Pos[0];
		MetaData.Pos.y = Pos[1];
		MetaData.Pos.z = Pos[2];
		MetaData.Pos.w = Pos[3];

		GetTransform()->SetLocalPosition(MetaData.Pos);
	}

	ImGui::Spacing();

	float Rot[4] = { MetaData.Rot.x, MetaData.Rot.y, MetaData.Rot.z, MetaData.Rot.w };
	ImGui::DragFloat4("Rotation", Rot);

	if (MetaData.Rot.x != Rot[0] ||
		MetaData.Rot.y != Rot[1] ||
		MetaData.Rot.z != Rot[2] ||
		MetaData.Rot.w != Rot[3])
	{
		MetaData.Rot.x = Rot[0];
		MetaData.Rot.y = Rot[1];
		MetaData.Rot.z = Rot[2];
		MetaData.Rot.w = Rot[3];
	}

	ImGui::Spacing();

	float Scale[4] = { MetaData.Scale.x, MetaData.Scale.y, MetaData.Scale.z, MetaData.Scale.w };
	ImGui::DragFloat4("Scale", Scale);

	if (MetaData.Scale.x != Scale[0] ||
		MetaData.Scale.y != Scale[1] ||
		MetaData.Scale.z != Scale[2] ||
		MetaData.Scale.w != Scale[3])
	{
		MetaData.Scale.x = Scale[0];
		MetaData.Scale.y = Scale[1];
		MetaData.Scale.z = Scale[2];
		MetaData.Scale.w = Scale[3];

		PlatformCol->GetTransform()->SetLocalScale(MetaData.Scale);
	}

}

void MapPlatform::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(MetaData.Type));
	_SaveSerializer.Write(&MetaData.Pos, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Rot, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Scale, sizeof(float4));
}

MapPlatform::PlatformMetaData MapPlatform::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	PlatformMetaData LoadMetaData = PlatformMetaData();

	int LoadType = 0;
	_LoadSerializer.Read(LoadType);
	LoadMetaData.Type = static_cast<PlatformType>(LoadType);

	_LoadSerializer.Read(&LoadMetaData.Pos, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Rot, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Scale, sizeof(float4));

	return LoadMetaData;
}