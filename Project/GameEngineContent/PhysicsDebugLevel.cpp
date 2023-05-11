#include "PrecompileHeader.h"
#include "PhysicsDebugLevel.h"
#include "DebugRigidbodyTestActor.h"

PhysicsDebugLevel::PhysicsDebugLevel()
{
}

PhysicsDebugLevel::~PhysicsDebugLevel()
{
}

void PhysicsDebugLevel::Start()
{
	ContentLevel::Start();

	CreateActor<DebugRigidbodyTestActor>();
}

void PhysicsDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}
