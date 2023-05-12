#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class DebugRigidbodyTestActor : public BaseContentActor
{
public:
	DebugRigidbodyTestActor();
	~DebugRigidbodyTestActor();

	DebugRigidbodyTestActor(const DebugRigidbodyTestActor& _Other) = delete;
	DebugRigidbodyTestActor(DebugRigidbodyTestActor&& _Other) noexcept = delete;
	DebugRigidbodyTestActor& operator=(const DebugRigidbodyTestActor& _Other) = delete;
	DebugRigidbodyTestActor& operator=(DebugRigidbodyTestActor&& _Other) noexcept = delete;

	bool IsMove = true;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> TestRender = nullptr;
	Rigidbody2D RigdPtr  = Rigidbody2D();

};

