#pragma once
#include "BaseContentActor.h"

class Background : public BaseContentActor
{
public:
	class BG_DESC
	{
	public:
		std::string TextureName = "";
		float4 Center = float4::Zero;
		float Ratio = 0.0f;
		float4 Size = float4::Zero;
		float4 Color = float4::Zero;
		bool Animation = false;
		float AnimationSpeed = 0.0f;
	};
public:
	Background();
	~Background();

	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;
	
	void Init(const BG_DESC& _Desc);
	void UpdateTargetPos(float _DeltaTime, const float4& _TargetPos);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	static BG_DESC LoadBin(GameEngineSerializer& _SaveSerializer);

protected:
	void Start() override;

private:
	BG_DESC Desc = BG_DESC();

	std::shared_ptr<GameEngineSpriteRenderer> BackImage = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> AnimationImage = nullptr;

	float AnimationProgress = 0.0f;
	float4 AnimationMoveDir = float4::Zero;

};