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

	void LoadMap(const std::string_view& _Path);
	void ChangeMap(const std::string_view _Name);

	void LoadBackground(const std::string_view _Path);
	void ChangeBackground(const std::string_view _Name);

protected:
	
private:
	std::map<std::string, std::shared_ptr<BattleStage>> BattleStageDatas;
	std::map<std::string, std::shared_ptr<MultiBackground>> BattleBackgroundDatas;
};

