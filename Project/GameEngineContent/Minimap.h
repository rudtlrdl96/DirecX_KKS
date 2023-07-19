#pragma once
#include "BaseContentActor.h"

class Minimap : public BaseContentActor
{
private:
	enum class MinimapState
	{
		None,
		On,
		Off
	};
public:
	Minimap();
	~Minimap();

	Minimap(const Minimap& _Other) = delete;
	Minimap(Minimap&& _Other) noexcept = delete;
	Minimap& operator=(const Minimap& _Other) = delete;
	Minimap& operator=(Minimap&& _Other) noexcept = delete;

	void MinimapOn();
	void MinimapOff(bool _Force = false);

	void MonsterCountUpdate(size_t _Count);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentSpriteUIRenderer_Clear> MinimapImageRender = nullptr;
	std::shared_ptr<class ContentUIRender> MinimapFrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MonsterCountRender = nullptr;
	std::shared_ptr<class GameEngineCamera> MinimapCamera = nullptr;

	std::shared_ptr<ContentUIFontRenderer> MonsterCountFont = nullptr;

	ColorBuffer Buffer;

	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;

	float Progress = 0.0f;

	MinimapState State = MinimapState::None;

	std::shared_ptr<GameEngineRenderTarget> MinimapTarget = nullptr;
};

