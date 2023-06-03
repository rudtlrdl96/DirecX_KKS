#pragma once
#include "BaseContentActor.h"
#include "TileMetaData.h"

class ObjectMetaData
{
public:
	std::string Name = "";
	size_t Index = 0;
	LevelArea Grade = LevelArea::None;

	float4 Pos = float4::Zero;
	float4 Rot = float4::Zero;
	float4 Scale = float4::One;

	float4 Size = float4(100, 100, 0, 0);
	float4 Color = float4::Zero;
	float4 LightColor = float4::One;
};

class MapObject : public BaseContentActor
{	
public:
	MapObject();
	~MapObject();

	MapObject(const MapObject& _Other) = delete;
	MapObject(MapObject&& _Other) noexcept = delete;
	MapObject& operator=(const MapObject& _Other) = delete;
	MapObject& operator=(MapObject&& _Other) noexcept = delete;

	void Init(const ObjectMetaData& _MetaData);

	const ObjectMetaData& GetMetaData();

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static ObjectMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;

	std::string GetTexName() const;
	float4 GetTexWorldScale() const;

	GameEngineTransform* GetRenderTrans()
	{
		return ImageRender->GetTransform();
	}

protected:
	void Start() override;

private:
	ObjectMetaData MetaData = ObjectMetaData();

	std::shared_ptr<ContentSpriteRenderer> ImageRender = nullptr;
	ObjectColorBuffer Buffer;

};