#include "PrecompileHeader.h"
#include "BaseNPC.h"
#include <GameEngineCore/imgui.h>

BaseNPC::BaseNPC()
{
}

BaseNPC::~BaseNPC()
{
}

void BaseNPC::SaveBin(GameEngineSerializer& _SaveSerializer)
{
}

NPCMetaData BaseNPC::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	NPCMetaData LoadData;

	return LoadData;
}

void BaseNPC::Start()
{
	MainRender = CreateComponent<ContentSpriteRenderer>();
	MainRender->PipeSetting("2DTexture_ColorBuffer");
	MainRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);

	SpriteLoad();
}

void BaseNPC::ShowGUI()
{
	//UINT Index = 0;
	//LevelArea Grade = LevelArea::None;
	//std::string Name = "";
	//float4 CenterPos = float4::Zero;

	ImGui::Text(std::string("NPC Index : " + std::to_string(Data.Index)).data() );

	const type_info& RttiInfo = typeid(Data.Grade);
	ImGui::Text(std::string("Level Area : " + std::string(RttiInfo.name())).data());
	
	ImGui::Text(std::string("Name : " + std::string(Data.Name)).data());

	float4 Pos = Data.CenterPos;

	float InputCenter[4] = { Pos.x, Pos.y, Pos.z, Pos.w };
	ImGui::DragFloat4("Center", InputCenter);

	if (InputCenter[0] != Pos.x ||
		InputCenter[1] != Pos.y ||
		InputCenter[2] != Pos.z ||
		InputCenter[3] != Pos.w)
	{
		Data.CenterPos.x = InputCenter[0];
		Data.CenterPos.y = InputCenter[1];
		Data.CenterPos.z = InputCenter[2];
		Data.CenterPos.w = InputCenter[3];
	}
}