#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class AnimationCollisionToolGUI : public GameEngineCoreWindow
{
public:
	AnimationCollisionToolGUI();
	~AnimationCollisionToolGUI();

	AnimationCollisionToolGUI(const AnimationCollisionToolGUI& _Other) = delete;
	AnimationCollisionToolGUI(AnimationCollisionToolGUI&& _Other) noexcept = delete;
	AnimationCollisionToolGUI& operator=(const AnimationCollisionToolGUI& _Other) = delete;
	AnimationCollisionToolGUI& operator=(AnimationCollisionToolGUI&& _Other) noexcept = delete;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;

	void SetRenderer(std::shared_ptr<class GameEngineSpriteRenderer> _Render);
	void SetCol(std::shared_ptr<class DebugCollisionRender> _Render);

protected:
	
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SpriteRender = nullptr;
	std::shared_ptr<class DebugCollisionRender> ColRender = nullptr;

	std::string SpriteAnimationName = "";

	const char* ColTypeComboText[2] = { "Box", "Sphere"};
	int ColComboIndex = 0;

	float RenderScale = 1.0f;

	UINT LoadWitdhCount = 1;
	UINT LoadHeightCount = 1;

	UINT ShowIndex = 0;
	UINT StartIndex = 0;
	UINT EndIndex = 0;

	float4 ColCenterPos = float4::Zero;
	float4 ColSize = float4::Zero;
};