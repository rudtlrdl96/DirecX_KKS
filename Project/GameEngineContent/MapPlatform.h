#pragma once
#include "BaseContentActor.h"



class MapPlatform : public BaseContentActor
{
	friend class MapPlatformDebugRender;
public:
	enum class PlatformType
	{
		Normal, // 일반 플랫폼
		Half,   // 아래에서는 위로 올라올 수 있지만 위에서는 아래로 못내려가는 플랫폼
	};

	class PlatformMetaData
	{
	public:
		PlatformType Type = PlatformType::Normal;
		float4 Pos = float4::Zero;
		float4 Rot = float4::Zero;
		float4 Scale = float4::One;
	};
public:
	MapPlatform();
	~MapPlatform();

	MapPlatform(const MapPlatform& _Other) = delete;
	MapPlatform(MapPlatform&& _Other) noexcept = delete;
	MapPlatform& operator=(const MapPlatform& _Other) = delete;
	MapPlatform& operator=(MapPlatform&& _Other) noexcept = delete;

	void Init(const PlatformMetaData& _MetaData);
	void PlatformDebugOn();
	void PlatformDebugOff();

	void ShowGUI() override;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static PlatformMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

	const PlatformMetaData& GetMetaData() const
	{
		return MetaData;
	}

protected:

private:
	PlatformMetaData MetaData = PlatformMetaData();
	std::shared_ptr<class GameEngineCollision> PlatformCol = nullptr;
};

