#pragma once
#include "BattleLevel.h"

class CastleLevel : public BattleLevel
{
public:
	CastleLevel();
	~CastleLevel();

	CastleLevel(const CastleLevel& _Other) = delete;
	CastleLevel(CastleLevel&& _Other) noexcept = delete;
	CastleLevel& operator=(const CastleLevel& _Other) = delete;
	CastleLevel& operator=(CastleLevel&& _Other) noexcept = delete;

	static void AddResetCallback(std::function<void()> _Callback)
	{
		ResetCallback.push_back(_Callback);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void AreaClear() override;

private:
	static std::vector<std::function<void()>> ResetCallback;

};

