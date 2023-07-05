#include "PrecompileHeader.h"
#include "BattleArea.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "CameraController.h"
#include "Tilemap.h"

BattleArea::BattleArea()
{
}

BattleArea::~BattleArea()
{
}

void BattleArea::LoadMap(GameEngineDirectory& _Directory, const std::string_view& _FileName)
{
	std::string UpperName = GameEngineString::ToUpper(_FileName);

	if (BattleBackgroundDatas.find(UpperName) != BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ߺ��� ���������� �����Ϸ� �߽��ϴ�");
	}


	GameEngineFile LoadFile = GameEngineFile(_Directory.GetPlusFileName(_FileName).GetFullPath());
	GameEngineSerializer LoadSer;

	LoadSer.BufferResize(131072);
	LoadFile.LoadBin(LoadSer);

	std::shared_ptr<BattleStage> NewStage = GetLevel()->CreateActor<BattleStage>();

	NewStage->Off();
	NewStage->GetTransform()->SetParent(GetTransform());
	NewStage->Init(LoadSer);

	BattleStageDatas.insert(std::make_pair(UpperName, NewStage));
}

void BattleArea::ChangeMap(const std::string_view _Name, const float4& _Pivot /*= float4::Zero*/)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (BattleStageDatas.find(UpperName) == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش� �� �����͸� ã�� �� �����ϴ�");
	}

	if (nullptr != CurStage)
	{
		CurStage->Off();
		CurStage->StageReset();
	}

	CurStage = BattleStageDatas[UpperName];
	CurStage->GetTransform()->SetLocalPosition(_Pivot);
	CurStage->StagePlay();
	CurStage->On();
}

void BattleArea::LoadBackground(GameEngineDirectory& _Directory, const std::string_view& _FileName)
{
	std::string UpperName = GameEngineString::ToUpper(_FileName);

	if (BattleBackgroundDatas.find(UpperName) != BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ߺ��� ��׶��带 �����Ϸ� �߽��ϴ�");
	}

	GameEngineFile LoadFile = GameEngineFile(_Directory.GetPlusFileName(_FileName).GetFullPath());
	GameEngineSerializer LoadSer;
	
	LoadSer.BufferResize(4096);
	LoadFile.LoadBin(LoadSer);
	
	std::shared_ptr<MultiBackground> NewBackground = GetLevel()->CreateActor<MultiBackground>();
	
	NewBackground->Off();
	NewBackground->GetTransform()->SetParent(GetTransform());
	NewBackground->LoadBin(LoadSer);
	
	BattleBackgroundDatas.insert(std::make_pair(UpperName, NewBackground));
}

void BattleArea::ChangeBackground(const std::string_view _Name, const float4& _Pivot /*= float4::Zero*/)
{

	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (BattleBackgroundDatas.find(UpperName) == BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش� ��׶��� �����͸� ã�� �� �����ϴ�");
	}


	if (nullptr != CurBackground)
	{
		CurBackground->Off();
	}

	CurBackground = BattleBackgroundDatas[UpperName];
	CurBackground->GetTransform()->SetLocalPosition(_Pivot);
	CurBackground->On();
}

void BattleArea::SetCameraLock(CameraController& _CameraCtrl)
{
	if (nullptr == CurStage)
	{
		MsgAssert_Rtti<BattleArea>(" - �� �����͸� �������� �ʰ� ī�޶� Lock�� �����Ϸ� �߽��ϴ�");
		return;
	}

	TilemapMetaData TileMeta = CurStage->GetTilemapMetaData();

	_CameraCtrl.SetMinHeight(TileMeta.Bottom);
	_CameraCtrl.SetMaxHeight(TileMeta.Top);
	_CameraCtrl.SetMinWidth(TileMeta.Left);
	_CameraCtrl.SetMaxWidth(TileMeta.Right);
}

void BattleArea::SetParentToBackground(const std::string_view& _BackgroundName, size_t _Index, GameEngineTransform* _Actor)
{
	std::string UpperName = GameEngineString::ToUpper(_BackgroundName);
	std::map<std::string, std::shared_ptr<MultiBackground>>::iterator FindIter = BattleBackgroundDatas.find(UpperName);

	if (FindIter == BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش��̸��� ��׶��尡 �������� �ʽ��ϴ� : " + UpperName);
		return;
	}

	FindIter->second->SetParentToBackground(_Index, _Actor);
}

void BattleArea::SetFiretDoorType(const std::string_view& _StageName, DoorType _Type)
{
	std::string UpperName = GameEngineString::ToUpper(_StageName);
	std::map<std::string, std::shared_ptr<BattleStage>>::iterator FindIter = BattleStageDatas.find(UpperName);

	if (FindIter == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش��̸��� ���������� �������� �ʽ��ϴ� : " + UpperName);
		return;
	}

	FindIter->second->SetFiretDoorType(_Type);
}

void BattleArea::SetSecondDoorType(const std::string_view& _StageName, DoorType _Type)
{
	std::string UpperName = GameEngineString::ToUpper(_StageName);
	std::map<std::string, std::shared_ptr<BattleStage>>::iterator FindIter = BattleStageDatas.find(UpperName);

	if (FindIter == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش��̸��� ���������� �������� �ʽ��ϴ� : " + UpperName);
		return;
	}

	FindIter->second->SetSecondDoorType(_Type);
}

void BattleArea::StageRewardOn(const std::string_view& _StageName)
{
	std::string UpperName = GameEngineString::ToUpper(_StageName);
	std::map<std::string, std::shared_ptr<BattleStage>>::iterator FindIter = BattleStageDatas.find(UpperName);

	if (FindIter == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش��̸��� ���������� �������� �ʽ��ϴ� : " + UpperName);
		return;
	}

	FindIter->second->StageRewardOn();
}

void BattleArea::StageRewardOff(const std::string_view& _StageName)
{
	std::string UpperName = GameEngineString::ToUpper(_StageName);
	std::map<std::string, std::shared_ptr<BattleStage>>::iterator FindIter = BattleStageDatas.find(UpperName);

	if (FindIter == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - �ش��̸��� ���������� �������� �ʽ��ϴ� : " + UpperName);
		return;
	}

	FindIter->second->StageRewardOff();
}

void BattleArea::ClearStage()
{
	if (nullptr != CurStage)
	{
		CurStage->StageReset();
	}
}
