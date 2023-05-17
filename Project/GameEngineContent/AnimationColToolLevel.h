#pragma once
#include "ContentLevel.h"

class AnimationColToolLevel : public ContentLevel
{
public:
	AnimationColToolLevel();
	~AnimationColToolLevel();

	AnimationColToolLevel(const AnimationColToolLevel& _Other) = delete;
	AnimationColToolLevel(AnimationColToolLevel&& _Other) noexcept = delete;
	AnimationColToolLevel& operator=(const AnimationColToolLevel& _Other) = delete;
	AnimationColToolLevel& operator=(AnimationColToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class AnimationCollisionToolGUI> AnimationCollisionGUIPtr = nullptr;

	std::shared_ptr<class AttackColToolAnimActor> AnimRenderActor = nullptr;
	std::shared_ptr<class AttackColRender> ColRenderActor = nullptr;
};

