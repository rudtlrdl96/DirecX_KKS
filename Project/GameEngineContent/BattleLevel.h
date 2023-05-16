#pragma once
#include "ContentLevel.h"
#include "BattleArea.h"

class BattleLevel : public ContentLevel
{
public:
	BattleLevel();
	~BattleLevel();

	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) noexcept = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetPosDebugActor(const float4& _Pos);

	std::shared_ptr<class BoneSkull> DebugActor = nullptr;
	std::shared_ptr<class BattleArea> BattleAreaPtr = nullptr;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:


};

