#pragma once
#include "ContentLevel.h"

class PhysicsDebugLevel : public ContentLevel
{
public:
	PhysicsDebugLevel();
	~PhysicsDebugLevel();

	PhysicsDebugLevel(const PhysicsDebugLevel& _Other) = delete;
	PhysicsDebugLevel(PhysicsDebugLevel&& _Other) noexcept = delete;
	PhysicsDebugLevel& operator=(const PhysicsDebugLevel& _Other) = delete;
	PhysicsDebugLevel& operator=(PhysicsDebugLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

