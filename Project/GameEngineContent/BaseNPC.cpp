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
	_SaveSerializer.Write(&Data.Index, sizeof(UINT));
	_SaveSerializer.Write(&Data.CenterPos, sizeof(float4));
}

NPCMetaData BaseNPC::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	NPCMetaData LoadData;

	UINT LoadIndex = 0;
	_LoadSerializer.Read(&LoadIndex, sizeof(UINT));
	LoadData = ContentDatabase<NPCMetaData, LevelArea>::GetData(LoadIndex);

	_LoadSerializer.Read(&LoadData.CenterPos, sizeof(float4));

	return LoadData;
}

void BaseNPC::Start()
{
	MainRender = CreateComponent<ContentSpriteRenderer>();
	MainRender->PipeSetting("2DTexture_ColorLight");
	MainRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MainRender->SetScaleToTexture("Empty.png");
	MainRender->SetScaleRatio(2.0f);

	SpriteLoad();
}

void BaseNPC::Update(float _DeltaTime)
{
	if (CurFrame != MainRender->GetCurrentFrame())
	{
		CurFrame = static_cast<UINT>(MainRender->GetCurrentFrame());
		AnimTimeCheck = 0.0f;
	}

	AnimTimeCheck += _DeltaTime;

	if (AnimFramePause[CurAnimation][CurFrame] > AnimTimeCheck)
	{
		MainRender->SetAnimPauseOn();
	}
	else
	{
		MainRender->SetAnimPauseOff();
	}
}

void BaseNPC::PlayAnimation(const std::string_view& _AnimationName, bool _IsForce, size_t _Frame)
{
	AnimTimeCheck = 0.0f;
	CurFrame = static_cast<UINT>(-1);
	CurAnimation = _AnimationName;
	MainRender->ChangeAnimation(CurAnimation, _IsForce, _Frame);
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
	
	ImGui::Text(GameEngineString::AnsiToUTF8("Name : " + std::string(Data.Name)).data());

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

		GetTransform()->SetLocalPosition(Data.CenterPos);
	}
}