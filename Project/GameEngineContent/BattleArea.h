#pragma once
#include "BaseContentActor.h"
#include "BattleStage.h"
#include "MultiBackground.h"

class BattleArea : public BaseContentActor
{
public:
	BattleArea();
	~BattleArea();

	BattleArea(const BattleArea& _Other) = delete;
	BattleArea(BattleArea&& _Other) noexcept = delete;
	BattleArea& operator=(const BattleArea& _Other) = delete;
	BattleArea& operator=(BattleArea&& _Other) noexcept = delete;

	void LoadMap(GameEngineDirectory& _Directory, const std::string_view& _FileName);
	void ChangeMap(const std::string_view _Name);

	void LoadBackground(GameEngineDirectory& _Directory, const std::string_view& _FileName);
	void ChangeBackground(const std::string_view _Name);

	inline void UpdateBackground(float _DeltaTime, const float4& _CenterPos)
	{
		CurBackground->UpdateTargetPos(_DeltaTime, _CenterPos);
	}

protected:
	
private:
	std::map<std::string, std::shared_ptr<MultiBackground>> BattleBackgroundDatas;
	std::map<std::string, std::shared_ptr<BattleStage>> BattleStageDatas;

	std::shared_ptr<BattleStage> CurStage = nullptr;
	std::shared_ptr<MultiBackground> CurBackground = nullptr;
};