#include "PrecompileHeader.h"
#include "BattleArea.h"

#include <GameEngineCore/GameEngineLevel.h>

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
		MsgAssert_Rtti<BattleArea>(" - 중복된 스테이지를 생성하려 했습니다");
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

void BattleArea::ChangeMap(const std::string_view _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (BattleStageDatas.find(UpperName) == BattleStageDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - 해당 맵 데이터를 찾을 수 없습니다");
	}

	if (nullptr != CurStage)
	{
		CurStage->Off();
	}

	CurStage = BattleStageDatas[UpperName];
	CurStage->On();
}

void BattleArea::LoadBackground(GameEngineDirectory& _Directory, const std::string_view& _FileName)
{
	std::string UpperName = GameEngineString::ToUpper(_FileName);

	if (BattleBackgroundDatas.find(UpperName) != BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - 중복된 백그라운드를 생성하려 했습니다");
	}

	GameEngineFile LoadFile = GameEngineFile(_Directory.GetPlusFileName(_FileName).GetFullPath());
	GameEngineSerializer LoadSer;
	
	LoadSer.BufferResize(2048);
	LoadFile.LoadBin(LoadSer);
	
	std::shared_ptr<MultiBackground> NewBackground = GetLevel()->CreateActor<MultiBackground>();
	
	NewBackground->Off();
	NewBackground->GetTransform()->SetParent(GetTransform());
	NewBackground->LoadBin(LoadSer);
	
	BattleBackgroundDatas.insert(std::make_pair(UpperName, NewBackground));
}

void BattleArea::ChangeBackground(const std::string_view _Name)
{

	std::string UpperName = GameEngineString::ToUpper(_Name);

	if (BattleBackgroundDatas.find(UpperName) == BattleBackgroundDatas.end())
	{
		MsgAssert_Rtti<BattleArea>(" - 해당 백그라운드 데이터를 찾을 수 없습니다");
	}


	if (nullptr != CurBackground)
	{
		CurBackground->Off();
	}

	CurBackground = BattleBackgroundDatas[UpperName];
	CurBackground->On();
}
