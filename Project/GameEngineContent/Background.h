#pragma once
#include "BaseContentActor.h"

class Background : public BaseContentActor
{
public:
	class BG_DESC
	{
	public:
		std::string TextureName;
		float4 Center;
		float Ratio;
		float4 Size;
	};
public:
	Background();
	~Background();

	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;
	
	void Init(const BG_DESC& _Desc);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	BG_DESC Desc;

	std::shared_ptr<GameEngineTransform> Target = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BackImage = nullptr;
};