#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "AnimationAttackMetaData.h"

class AnimationCollisionToolGUI : public GameEngineCoreWindow
{
public:
	AnimationCollisionToolGUI();
	~AnimationCollisionToolGUI();

	AnimationCollisionToolGUI(const AnimationCollisionToolGUI& _Other) = delete;
	AnimationCollisionToolGUI(AnimationCollisionToolGUI&& _Other) noexcept = delete;
	AnimationCollisionToolGUI& operator=(const AnimationCollisionToolGUI& _Other) = delete;
	AnimationCollisionToolGUI& operator=(AnimationCollisionToolGUI&& _Other) noexcept = delete;
	
	void SetRenderer(std::shared_ptr<class GameEngineSpriteRenderer> _Render);
	void SetCol(std::shared_ptr<class AttackColRender> _Render);

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SpriteRender = nullptr;
	std::shared_ptr<class AttackColRender> ColRender = nullptr;

	std::string SpriteAnimationName = "";

	AnimationAttackMetaData ColMetaDatas = AnimationAttackMetaData();

	float RenderScale = 1.0f;

	UINT ShowFrame = 0;
	UINT StartFrame = 0;
	UINT EndFrame = 0;

	void Save();
	void Load();
};