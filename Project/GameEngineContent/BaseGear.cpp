#include "PrecompileHeader.h"
#include "BaseGear.h"
#include "Player.h"

BaseGear::BaseGear()
{
}

BaseGear::~BaseGear()
{

}

void BaseGear::DropGear(const float4& _WorldPos)
{
	State = GearState::Drop;

	DropRigid.SetVelocity(float4(0, 850));
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

void BaseGear::CallUseEvent()
{
	if (0.2f <= PressTime)
	{
		return;
	}

	if (State == GearState::Fixed || State == GearState::Wave)
	{
		GameEngineSound::Play("Object_GainItem.wav");
		UseGear();
		IsUse = true;
	}
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
		
	GearBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
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
	if (nullptr != ColPlayer && true == ColPlayer->IsDeath())
	{
		ColPlayer = nullptr;
	}

	if (false == IsFocus())
	{
		PressTime = 0.0f;

		if (true == IsEnterCheck && nullptr != ColExitCallback)
		{
			ColExitCallback();
		}

		if (true == DestroySound.IsValid())
		{
			DestroySound.Stop();
			DestroySound.Clear();
		}

		IsEnterCheck = false;
	}
	
	if (true == IsFocus() && (State == GearState::Fixed || State == GearState::Wave))
	{
		std::shared_ptr<GameEngineCollision> Col = GearBodyCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != Col)
		{
			ColPlayer = Col->GetActor()->DynamicThis<Player>();

			if (nullptr == ColPlayer)
			{
				MsgAssert_Rtti<BaseGear>(" - Player 클래스만 Player ColOrder를 가질 수 있습니다.");
			}

			if (false == IsEnterCheck)
			{
				if (nullptr != ColEnterCallback)
				{
					ColEnterCallback();
				}

				IsEnterCheck = true;
			}

			if (nullptr != ColUpdateCallback)
			{
				ColUpdateCallback();
			}

			if (GameEngineInput::IsPress("UseKey"))
			{
				if (0.2f <= PressTime && false == DestroySound.IsValid())
				{
					DestroySound = GameEngineSound::Play("Object_DestroyItem_loop.wav");
					DestroySound.SetLoop();
				}

				PressTime += _DeltaTime;

				if (1.0f <= PressTime)
				{
					Death(); 
					DestroySound.Stop();
				}
			}
			else
			{
				PressTime = 0.0f;

				if (true == DestroySound.IsValid())
				{
					bool IsPlay = false;
					DestroySound.isPlaying(&IsPlay);

					if (true == IsPlay)
					{
						DestroySound.Stop();
						DestroySound.Clear();
					}
				}
			}
		}		
	}

	if (true == IsColWave)
	{
		if (false == IsFocus())
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
		else if (false == IsFocus())
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


	if (true == IsLegendaryGear)
	{
		if (nullptr == LegendaryFrontLoopEffect && (State == GearState::Wave || State == GearState::Fixed))
		{
			if (nullptr == LegendaryFrontStartEffect)
			{
				LegendaryFrontStartEffect = EffectManager::PlayEffect({
					.EffectName = "LegendaryGear_Front_Start",
					.Position = GetEffectPos() + float4(-5, 270),
					.Triger = EffectDeathTrigger::None,
					});

				LegendaryFrontStartEffect->GetTransform()->SetParent(GetTransform());

				float4 Pos = LegendaryFrontStartEffect->GetTransform()->GetWorldPosition();
				Pos.z = Render->GetTransform()->GetWorldPosition().z - 0.1f;
				LegendaryFrontStartEffect->GetTransform()->SetWorldPosition(Pos);
			}
			else if (true == LegendaryFrontStartEffect->IsAnimationEnd())
			{
				LegendaryFrontStartEffect->Death();
				LegendaryFrontStartEffect = nullptr;

				LegendaryFrontLoopEffect = EffectManager::PlayEffect({
					.EffectName = "LegendaryGear_Front_Loop",
					.Position = GetEffectPos() + float4(5, 220),
					.Triger = EffectDeathTrigger::None,
					});

				LegendaryFrontLoopEffect->GetTransform()->SetParent(GetTransform());

				float4 Pos = LegendaryFrontLoopEffect->GetTransform()->GetWorldPosition();
				Pos.z = Render->GetTransform()->GetWorldPosition().z - 0.1f;
				LegendaryFrontLoopEffect->GetTransform()->SetWorldPosition(Pos);
			}

			if (nullptr == LegendaryBehindLoopEffect)
			{
				if (nullptr == LegendaryBehindStartEffect)
				{
					LegendaryBehindStartEffect = EffectManager::PlayEffect({
						.EffectName = "LegendaryGear_Behind_Start",
						.Position = GetEffectPos() + float4(0, 220),
						.Triger = EffectDeathTrigger::None,
						});

					LegendaryBehindStartEffect->GetTransform()->SetParent(GetTransform());

					float4 Pos = LegendaryBehindStartEffect->GetTransform()->GetWorldPosition();
					Pos.z = Render->GetTransform()->GetWorldPosition().z + 0.1f;
					LegendaryBehindStartEffect->GetTransform()->SetWorldPosition(Pos);
				}
				else if (true == LegendaryBehindStartEffect->IsAnimationEnd())
				{
					LegendaryBehindStartEffect->Death();
					LegendaryBehindStartEffect = nullptr;

					LegendaryBehindLoopEffect = EffectManager::PlayEffect({
						.EffectName = "LegendaryGear_Behind_Loop",
						.Position = GetEffectPos() + float4(0, 220),
						.Triger = EffectDeathTrigger::None,
						});

					LegendaryBehindLoopEffect->GetTransform()->SetParent(GetTransform());

					float4 Pos = LegendaryBehindLoopEffect->GetTransform()->GetWorldPosition();
					Pos.z = Render->GetTransform()->GetWorldPosition().z + 0.1f;
					LegendaryBehindLoopEffect->GetTransform()->SetWorldPosition(Pos);
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
}

void BaseGear::Destroy()
{
	if (false == IsUse)
	{
		SoundDoubleCheck::Play("Object_DestroyItem_Completed.wav");
	}

	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());

	if (false == IsEffectOff)
	{
		PlayDestroyEffect();
	}

	if (true == DestroySound.IsValid())
	{
		DestroySound.Stop();
		DestroySound.Clear();
	}
}

void BaseGear::UseGear()
{
}

void BaseGear::SetWaveState(std::shared_ptr<GameEngineCollision> _PlatformCol)
{
	DropRigid.SetVelocity(float4::Zero);

	GameEngineSound::Play("DropGear.wav");

	State = GearState::Wave;

	GameEngineTransform* ColTrans = _PlatformCol->GetTransform();

	float4 GreaPos = GetTransform()->GetWorldPosition();
	float PlatformUp = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy() + 40;

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
