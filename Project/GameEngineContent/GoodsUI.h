#pragma once
#include "BaseContentActor.h"

class GoodsUI : public BaseContentActor
{
public:
	GoodsUI();
	~GoodsUI();

	GoodsUI(const GoodsUI& _Other) = delete;
	GoodsUI(GoodsUI&& _Other) noexcept = delete;
	GoodsUI& operator=(const GoodsUI& _Other) = delete;
	GoodsUI& operator=(GoodsUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	std::shared_ptr<GameEngineUIRenderer> GoldGoodsRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> BoneGoodsRender = nullptr;

	std::shared_ptr<ContentUIFontRenderer> GoldCountFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> BoneCountFont = nullptr;

};

