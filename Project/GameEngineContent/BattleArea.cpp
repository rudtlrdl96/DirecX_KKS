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
	}

	CurStage = BattleStageDatas[UpperName];
	CurStage->GetTransform()->SetLocalPosition(_Pivot);
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
