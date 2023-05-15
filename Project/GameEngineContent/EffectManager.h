#pragma once


class EffectManager
{
public:

protected:
	
private:
	static std::shared_ptr<class GameEngineLevel> CurLevel;

	EffectManager();
	~EffectManager();

	EffectManager(const EffectManager& _Other) = delete;
	EffectManager(EffectManager&& _Other) noexcept = delete;
	EffectManager& operator=(const EffectManager& _Other) = delete;
	EffectManager& operator=(EffectManager&& _Other) noexcept = delete;
};