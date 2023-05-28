#pragma once
#include "BaseContentActor.h"

class BackgroundMetaData
{
public:
	std::string Name = "";
	UINT Index = 0;
	LevelArea Grade = LevelArea::None;

	float4 Center = float4::Zero;

	bool IsLeftRender = false;
	bool IsRightRender = false;

	bool Animation = false;
	float AnimationSpeed = 0.0f;

	float MoveRatio = 1.0f;

	float4 TextureSize = float4::Zero;
	float TextureScale = 1.0f;

	float4 Color = float4::Zero;
	float4 LightColor = float4::One;
};

class Background : public BaseContentActor
{
public:
	Background();
	~Background();

	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;
	
	void Init(const BackgroundMetaData& _MetaData);
	void UpdateTargetPos(float _DeltaTime, const float4& _TargetPos);
	void ResizeTextureScale(float _Scale);

	void CreateLeftRender();
	void CreateRightRedner();

	void ReleaseLeftRender();
	void ReleaseRightRender();

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static BackgroundMetaData LoadBin(GameEngineSerializer& _SaveSerializer);

	inline BackgroundMetaData& GetMetaDataRef()
	{
		return MetaData;
	}

	inline TextureMoveBuffer& GetShaderBuffer()
	{
		return Buffer;
	}

protected:
	void Start() override;

private:
	BackgroundMetaData MetaData = BackgroundMetaData();

	std::shared_ptr<ContentSpriteRenderer> BackRender = nullptr;
	std::shared_ptr<ContentSpriteRenderer> LeftRender = nullptr;
	std::shared_ptr<ContentSpriteRenderer> RightRender = nullptr;

	TextureMoveBuffer Buffer;
};