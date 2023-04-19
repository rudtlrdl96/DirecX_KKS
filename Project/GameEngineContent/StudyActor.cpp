#include "PrecompileHeader.h"
#include "StudyActor.h"
#include <GameEngineCore/GameEngineRenderer.h>

StudyActor::StudyActor()
{
}

StudyActor::~StudyActor()
{
}

void StudyActor::Start()
{
	std::shared_ptr<GameEngineRenderer> RenderPtr = CreateComponent<GameEngineRenderer>();
	RenderPtr->SetPipeLine("2DTexture");
	RenderPtr->GetTransform()->SetWorldScale(float4(300.0f, 300.0f, 300.0f, 1.0f));

	PlayerFSM.Init(this);

	PlayerFSM.AddFSM("Idle",
		nullptr,
		&StudyActor::IdleUpdate,
		nullptr);

	PlayerFSM.AddFSM("Move",
		nullptr,
		&StudyActor::MoveUpdate,
		nullptr);

	PlayerFSM.AddFSM("Attack",
		nullptr,
		&StudyActor::AttackUpdate,
		nullptr);

	PlayerFSM.ChangeState("Idle");
}

void StudyActor::Update(float _DeltaTime)
{
	PlayerFSM.Update(_DeltaTime);
}
