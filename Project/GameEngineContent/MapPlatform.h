#pragma once
#include "BaseContentActor.h"



class MapPlatform : public BaseContentActor
{
	friend class MapPlatformDebugRender;
	friend class ObjectManager;
public:
	enum class PlatformType
	{
		Normal, // �Ϲ� �÷���
		Half,   // �Ʒ������� ���� �ö�� �� ������ �������� �Ʒ��� ���������� �÷���
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

	inline void EmphasizeOn()
	{
		IsEmphasize = true;
	}

	inline void EmphasizeOff()
	{
		IsEmphasize = false;
	}
	

protected:

private:
	PlatformMetaData MetaData = PlatformMetaData();
	std::shared_ptr<class GameEngineCollision> PlatformCol = nullptr;

	bool IsEmphasize = false;
};

