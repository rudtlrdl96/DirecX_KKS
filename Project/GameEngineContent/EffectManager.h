#pragma once
#include "EffectActor.h"

class EffectParameter
{
public:
	const std::string_view& EffectName = "";
	float4 Position = float4::Zero;
	float AddSetZ = 0.0f;
	float Scale = 1.0f;

	EffectDeathTrigger Triger = EffectDeathTrigger::AnimEnd;
	float Time = 0.0f;
	float WaitTime = 0.0f;

	bool FlipX = false;
	bool IsUI = false;

	float4 Color = float4::Zero;

};

class EffectManager
{
public:
	static bool IsCreate(const std::string_view& _EffectName);
	static void CreateMetaData(const std::string_view& _EffectName, const EffectMetaData& _MetaData);
	static std::shared_ptr<EffectActor> PlayEffect(const EffectParameter& _Parameter);

	static void SetLevel(std::shared_ptr<class GameEngineLevel> _Level)
	{
		CurLevel = _Level;
	}

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