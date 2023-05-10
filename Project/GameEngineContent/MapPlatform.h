#pragma once
#include "BaseContentActor.h"



class MapPlatform : public BaseContentActor
{
	friend class MapPlatformDebugRender;
public:
	enum class PlatformType
	{
		Normal, // �Ϲ� �÷���
		Half,   // �Ʒ������� ���� �ö�� �� ������ �������� �Ʒ��� ���������� �÷���
	};

	class Platform_DESC
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

	void Init(const Platform_DESC& _Desc);
	void PlatformDebugOn();
	void PlatformDebugOff();

	void ShowGUI() override;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static Platform_DESC LoadBin(GameEngineSerializer& _LoadSerializer);

	const Platform_DESC& GetDesc() const
	{
		return Desc;
	}

protected:

private:
	Platform_DESC Desc = Platform_DESC();
};

