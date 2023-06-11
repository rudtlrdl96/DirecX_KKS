#include "PrecompileHeader.h"
#include "BehaviorObject.h"
#include <GameEngineCore/imgui.h>

BehaviorObject::BehaviorObject()
{
}

BehaviorObject::~BehaviorObject()
{
}

void BehaviorObject::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&Data.Index, sizeof(UINT));
	_SaveSerializer.Write(&Data.Position, sizeof(float4));
	_SaveSerializer.Write(&Data.Rotation, sizeof(float4));
}

BehaviorObjectMetaData BehaviorObject::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	BehaviorObjectMetaData LoadData;

	_LoadSerializer.Read(&LoadData.Index, sizeof(UINT));

	LoadData = ContentDatabase<BehaviorObjectMetaData, LevelArea>::GetData(LoadData.Index);

	_LoadSerializer.Read(&LoadData.Position, sizeof(float4));
	_LoadSerializer.Read(&LoadData.Rotation, sizeof(float4));

	return LoadData;
}

void BehaviorObject::ShowGUI()
{
	{
		float4 Center = Data.Position;
		float InputPos[4] = { Center.x, Center.y, Center.z, Center.w };

		ImGui::DragFloat4("Behavior Object Pos", InputPos);

		if (Center.x != InputPos[0] ||
			Center.y != InputPos[1] ||
			Center.z != InputPos[2] ||
			Center.w != InputPos[3])
		{
			Data.Position.x = InputPos[0];
			Data.Position.y = InputPos[1];
			Data.Position.z = InputPos[2];
			Data.Position.w = InputPos[3];

			GetTransform()->SetLocalPosition(Data.Position);
		}
	}

	{
		float4 Rotation = Data.Rotation;
		float InputRot[4] = { Rotation.x, Rotation.y, Rotation.z, Rotation.w };

		ImGui::DragFloat4("Behavior Object Rot", InputRot);

		if (Rotation.x != InputRot[0] ||
			Rotation.y != InputRot[1] ||
			Rotation.z != InputRot[2] ||
			Rotation.w != InputRot[3])
		{
			Data.Rotation.x = InputRot[0];
			Data.Rotation.y = InputRot[1];
			Data.Rotation.z = InputRot[2];
			Data.Rotation.w = InputRot[3];

			GetTransform()->SetLocalRotation(Data.Rotation);
		}
	}
}

void BehaviorObject::Start()
{
	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
}
