#pragma once
#include "ContentLevel.h"

class AttackColToolLevel : public ContentLevel
{
public:
	AttackColToolLevel();
	~AttackColToolLevel();

	AttackColToolLevel(const AttackColToolLevel& _Other) = delete;
	AttackColToolLevel(AttackColToolLevel&& _Other) noexcept = delete;
	AttackColToolLevel& operator=(const AttackColToolLevel& _Other) = delete;
	AttackColToolLevel& operator=(AttackColToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class AttackCollisionToolGUI> AttackCollisionToolGUIPtr = nullptr;

	std::shared_ptr<class AttackColToolAnimActor> AnimRenderActor = nullptr;
	std::shared_ptr<class DebugCollisionRender> ColRenderActor = nullptr;
};

