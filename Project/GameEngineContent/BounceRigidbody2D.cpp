#include "PrecompileHeader.h"
#include "BounceRigidbody2D.h"

BounceRigidbody2D::BounceRigidbody2D()
{
}

BounceRigidbody2D::~BounceRigidbody2D()
{
}

void BounceRigidbody2D::BounceSetting(GameEngineTransform* _Trans, std::weak_ptr<GameEngineCollision> _Col)
{
	if (nullptr == _Trans)
	{
		MsgAssert_Rtti<BounceRigidbody2D>("nullptr Transform을 설정하려 했습니다 ");
		return;
	}

	Transform = _Trans;
	CheckCol = _Col;

	if (nullptr == CheckCol.lock())
	{
		MsgAssert_Rtti<BounceRigidbody2D>("nullptr GameEngineCollision을 설정하려 했습니다 ");
		return;
	}
}

void BounceRigidbody2D::UpdateForce(float _DeltaTime)
{
	Rigidbody2D::UpdateForce(_DeltaTime);

	std::shared_ptr<GameEngineCollision> ColPtr = CheckCol.lock();

	if (nullptr == ColPtr || false == ColPtr->IsUpdate())
	{
		return;
	}

	GameEngineTransform* ColTrans = ColPtr->GetTransform();

	float4 CenterPos = Transform->GetWorldPosition();

	ColTrans->SetWorldRotation(float4::Zero);

	if (0.0f < Velocity.y)
	{
		// Up Check
		ColTrans->SetWorldScale(float4(ColWitdh * 0.1f, ColHeight * 0.1f, 1.0f));
		ColTrans->SetWorldPosition(CenterPos + float4(0, ColHeight * 0.5f, 0.0f));

		if (nullptr != ContentFunc::PlatformColCheck(ColPtr))
		{
			float4 ReverseYVelocity = Velocity;
			ReverseYVelocity.y = -Velocity.y;

			Velocity = ReverseYVelocity * BounceReduced;
		}
	}
	else
	{
		// Down Check
		ColTrans->SetWorldScale(float4(ColWitdh * 0.1f, ColHeight * 0.1f, 1.0f));
		ColTrans->SetWorldPosition(CenterPos - float4(0, ColHeight * 0.5f, 0.0f));

		if (nullptr != ContentFunc::PlatformColCheck(ColPtr, true))
		{
			float4 ReverseYVelocity = Velocity;
			ReverseYVelocity.y = -Velocity.y;

			Velocity = ReverseYVelocity * BounceReduced;
		}
	}

	if (0.0f > Velocity.x)
	{
		// Left Check
		ColTrans->SetWorldScale(float4(ColWitdh * 0.1f, ColHeight * 0.1f, 1.0f));
		ColTrans->SetWorldPosition(CenterPos - float4(ColWitdh * 0.5f, 0.0f, 0.0f));

		if (nullptr != ContentFunc::PlatformColCheck(ColPtr))
		{
			float4 ReverseYVelocity = Velocity;
			ReverseYVelocity.x = -Velocity.x;

			Velocity = ReverseYVelocity * BounceReduced;
		}
	}
	else
	{
		// Right Check
		ColTrans->SetWorldScale(float4(ColWitdh * 0.1f, ColHeight * 0.1f, 1.0f));
		ColTrans->SetWorldPosition(CenterPos + float4(ColWitdh * 0.5f, 0.0f, 0.0f));

		if (nullptr != ContentFunc::PlatformColCheck(ColPtr))
		{
			float4 ReverseYVelocity = Velocity;
			ReverseYVelocity.x = -Velocity.x;

			Velocity = ReverseYVelocity  * BounceReduced;
		}
	}
}
