#pragma once
#include "BaseContentActor.h"

class BG_DESC
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
	
	void Init(const BG_DESC& _Desc);
	void UpdateTargetPos(float _DeltaTime, const float4& _TargetPos);
	void ResizeTextureScale(float _Scale);

	void CreateLeftRender();
	void CreateRightRedner();

	void ReleaseLeftRender();
	void ReleaseRightRender();

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static BG_DESC LoadBin(GameEngineSerializer& _SaveSerializer);

	inline BG_DESC& GetDescRef()
	{
		return Desc;
	}

	inline TextureMoveBuffer& GetShaderBuffer()
	{
		return Buffer;
	}

protected:
	void Start() override;

private:
	BG_DESC Desc = BG_DESC();

	std::shared_ptr<GameEngineSpriteRenderer> BackRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> LeftRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RightRender = nullptr;

	TextureMoveBuffer Buffer;
};