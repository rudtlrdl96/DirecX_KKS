#pragma once
#include "EffectActor.h"

class EffectManager
{
public:
	static bool IsCreate(const std::string_view& _EffectName);
	static void CreateMetaData(const std::string_view& _EffectName, const EffectMetaData& _MetaData);
	static std::shared_ptr<EffectActor> PlayEffect(const std::string_view& _EffectName, EffectDeathTrigger _Triger = EffectDeathTrigger::AnimEnd, float _Time = 0.0f);

protected:
	
private:
	static std::map<std::string, EffectMetaData> EffectMetaDatas;
	static std::shared_ptr<class GameEngineLevel> CurLevel;

	EffectManager() {}
	~EffectManager() {}

	EffectManager(const EffectManager& _Other) = delete;
	EffectManager(EffectManager&& _Other) noexcept = delete;
	EffectManager& operator=(const EffectManager& _Other) = delete;
	EffectManager& operator=(EffectManager&& _Other) noexcept = delete;
};