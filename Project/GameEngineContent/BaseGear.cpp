#include "PrecompileHeader.h"
#include "BaseGear.h"
#include "Player.h"

bool BaseGear::GearDoubleCheck = false;

BaseGear::BaseGear()
{
}

BaseGear::~BaseGear()
{
	if (true == IsBodyCol || true == IsPrevFrameCol)
	{
		GearDoubleCheck = false;
	}
}

void BaseGear::DropGear(const float4& _WorldPos)
{
	State = GearState::Drop;

	DropRigid.SetVelocity(float4(0, 950));
	GetTransform()->SetWorldPosition(_WorldPos);
}

void BaseGear::DropGear_Bezier(const float4& _Start, const float4& _End)
{
	State = GearState::Bezier;
	BezierPoint.resize(3);

	GetTransform()->SetWorldPosition(_Start);

	BezierPoint[0] = _Start;
	BezierPoint[1] = float4::Lerp(_Start, _End, 0.5f) + float4(0, 300);
	BezierPoint[2] = _End;

	BezierProgress = 0.0f;
}

void BaseGear::BlackAndWhiteEffectOn()
{
	IsBlackAndWhite = true;
}

void BaseGear::ColWaveOn()
{
	PrevState = State;
	IsColWave = true;
	WaveCenter = GetTransform()->GetWorldPosition();
}

void BaseGear::Start()
{
	Render = CreateComponent<ContentSpriteRenderer>();

	Render->PipeSetting("2DTexture_BlackAndWhite");
	Render->GetShaderResHelper().SetConstantBufferLink("BlackAndWhiteBuffer", Buffer);

	Render->GetTransform()->SetLocalScale(float4(40, 40, 1));

	GearGroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GearGroundCol->GetTransform()->SetLocalPosition(float4(0, -20, 0));
	GearGroundCol->GetTransform()->SetLocalScale(float4(40, 40, 1));
	GearGroundCol->SetColType(ColType::AABBBOX2D);
		
	GearBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GearBodyCol->GetTransform()->SetLocalScale(float4(40, 40, 1));
	GearBodyCol->SetColType(ColType::AABBBOX2D);

	GetContentLevel()->AddEvent("MoveStage", GetActorCode(), [this]()
		{
			Death();
		});

	DropRigid.SetActiveGravity(true);
	DropRigid.SetGravity(-2000);
	DropRigid.SetMaxSpeed(2000);

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}
}

void BaseGear::Update(float _DeltaTime)
{
	if (true == IsPrevFrameCol || true == IsBodyCol)
	{
		GearDoubleCheck = false;
	}

	IsBodyCol = false;

	if (nullptr != ColPlayer && true == ColPlayer->IsDeath())
	{
		ColPlayer = nullptr;
	}

	std::shared_ptr<GameEngineCollision> Col = GearBodyCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (false == GearDoubleCheck && nullptr != Col)
	{
		ColPlayer = Col->GetActor()->DynamicThis<Player>();
		GearDoubleCheck = true;

		if (nullptr == ColPlayer)
		{
			MsgAssert_Rtti<BaseGear>(" - Player 클래스만 Player ColOrder를 가질 수 있습니다.");
		}

		IsBodyCol = true;

		if (false == IsPrevFrameCol && nullptr != ColEnterCallback)
		{
			ColEnterCallback();
		}

		if (true == GameEngineInput::IsDown("UseKey"))
		{
			UseGear();
		}
	}
	else
	{
		if (true == IsPrevFrameCol && nullptr != ColExitCallback)
		{
			ColExitCallback();
		}
	}

	if (true == IsColWave)
	{
		if (false == IsBodyCol)
		{
			State = PrevState;
			GetTransform()->SetWorldPosition(WaveCenter);
		}
		else if (State != GearState::Wave)
		{
			State = GearState::Wave;
			ResetLiveTime();
		}
	}

	if (true == IsBlackAndWhite)
	{
		if (State != GearState::Wave && State != GearState::Fixed)
		{
			Buffer.Color.a = 1.0f;
		}
		else if (false == IsBodyCol)
		{
			Buffer.Color.a = 1.0f;

			if (nullptr == DeactiveEffect)
			{
				DeactiveEffect = EffectManager::PlayEffect({
					.EffectName = "GearDeactiveLoop",
					.Position = GetEffectPos(),
					.Triger = EffectDeathTrigger::None,
					});

				DeactiveEffect->GetTransform()->SetParent(GetTransform());

				float4 Pos = DeactiveEffect->GetTransform()->GetWorldPosition();
				Pos.z = GetTransform()->GetWorldPosition().z + 1.0f;
				DeactiveEffect->GetTransform()->SetWorldPosition(Pos);
			}

			if (nullptr != ActiveLoopEffect)
			{
				ActiveLoopEffect->Death();
				ActiveLoopEffect = nullptr;
			}

			if (nullptr != ActiveStartEffect)
			{
				ActiveStartEffect->Death();
				ActiveStartEffect = nullptr;
			}

		}
		else
		{
			Buffer.Color.a = 0.0f;

			if (nullptr != DeactiveEffect)
			{
				DeactiveEffect->Death();
				DeactiveEffect = nullptr;
			}

			if (nullptr == ActiveLoopEffect)
			{
				if (nullptr == ActiveStartEffect)
				{
					ActiveStartEffect = EffectManager::PlayEffect({
						.EffectName = "GearActiveStart",
						.Position = GetEffectPos() + float4(-2, 12),
						});

					ActiveStartEffect->GetTransform()->SetParent(GetTransform());

					float4 Pos = ActiveStartEffect->GetTransform()->GetWorldPosition();
					Pos.z = GetTransform()->GetWorldPosition().z + 1.0f;
					ActiveStartEffect->GetTransform()->SetWorldPosition(Pos);

				}
				else if (true == ActiveStartEffect->IsAnimationEnd())
				{
					ActiveLoopEffect = EffectManager::PlayEffect({
						.EffectName = "GearActiveLoop",
						.Position = GetEffectPos(),
						.Triger = EffectDeathTrigger::None,
						});

					ActiveLoopEffect->GetTransform()->SetParent(GetTransform());
				
					float4 Pos = ActiveLoopEffect->GetTransform()->GetWorldPosition();
					Pos.z = GetTransform()->GetWorldPosition().z + 1.0f;
					ActiveLoopEffect->GetTransform()->SetWorldPosition(Pos);

					ActiveStartEffect->Death();
					ActiveStartEffect = nullptr;
				}
			}
		}
	}

	switch (State)
	{
	case GearState::Fixed:
	{
		
	}
		break;
	case GearState::Wave:
	{
		GetTransform()->SetWorldPosition(WaveCenter + float4(0, -sinf(GetLiveTime() * 3.0f) * 7.0f, 0));
	}
		break;
	case GearState::Drop:
	{
		DropRigid.UpdateForce(_DeltaTime);

		float4 DropVel = DropRigid.GetVelocity();

		GetTransform()->AddWorldPosition(DropVel * _DeltaTime);

		if (-300 < DropVel.y)
		{
			return;
		}

		std::shared_ptr<GameEngineCollision> PlatformCol = GearGroundCol->Collision((int)CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlatformCol)
		{
			SetWaveState(PlatformCol);

			if (nullptr != MoveEndCallback)
			{
				MoveEndCallback();
				MoveEndCallback = nullptr;
			}
		}

		PlatformCol = GearGroundCol->Collision((int)CollisionOrder::Platform_Half, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlatformCol)
		{
			SetWaveState(PlatformCol);

			if (nullptr != MoveEndCallback)
			{
				MoveEndCallback();
				MoveEndCallback = nullptr;
			}
		}
	}
		break;

	case GearState::Bezier:
	{
		BezierProgress += _DeltaTime * 1.5f;

		if (1.0f <= BezierProgress)
		{
			BezierProgress = 1.0f;
			State = GearState::Fixed;

			if (nullptr != MoveEndCallback)
			{
				MoveEndCallback();
				MoveEndCallback = nullptr;
			}
		}

		GetTransform()->SetWorldPosition(ContentFunc::Bezier(BezierPoint, BezierProgress));
	}
		break;
	}

	IsPrevFrameCol = IsBodyCol;
}

void BaseGear::Destroy()
{
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());

	if (false == IsEffectOff)
	{
		PlayDestroyEffect();
	}
}

void BaseGear::UseGear()
{
}

void BaseGear::SetWaveState(std::shared_ptr<GameEngineCollision> _PlatformCol)
{
	State = GearState::Wave;

	GameEngineTransform* ColTrans = _PlatformCol->GetTransform();

	float4 GreaPos = GetTransform()->GetWorldPosition();
	float PlatformUp = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy() + Render->GetTransform()->GetWorldScale().hy() + 20;

	GreaPos.y = PlatformUp;

	GetTransform()->SetWorldPosition(GreaPos);

	WaveCenter = GreaPos;
	ResetLiveTime();
}

void BaseGear::PlayDestroyEffect()
{
}

float4 BaseGear::GetEffectPos()
{
	switch (State)
	{
	case GearState::Wave:
		return WaveCenter;
		break;
	}

	return GetTransform()->GetWorldPosition();
}
