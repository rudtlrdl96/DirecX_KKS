#pragma once
#include "Rigidbody2D.h"
#include <GameEngineCore/GameEngineCollision.h>

class BounceRigidbody2D : public Rigidbody2D
{
public:
	BounceRigidbody2D();
	~BounceRigidbody2D();

	BounceRigidbody2D(const BounceRigidbody2D& _Other) = delete;
	BounceRigidbody2D(BounceRigidbody2D&& _Other) noexcept = delete;
	BounceRigidbody2D& operator=(const BounceRigidbody2D& _Other) = delete;
	BounceRigidbody2D& operator=(BounceRigidbody2D&& _Other) noexcept = delete;

	void BounceSetting(GameEngineTransform* _Trans, std::weak_ptr<GameEngineCollision> _Col);

	inline void SetColWitdh(float _Witdh)
	{
		ColWitdh = _Witdh;
	}

	inline void SetColHeight(float _Height)
	{
		ColHeight = _Height;
	}

	void UpdateForce(float _DeltaTime) override;
protected:
	
private:
	GameEngineTransform* Transform = nullptr;
	std::weak_ptr<GameEngineCollision> CheckCol;

	float ColWitdh = 1.0f;
	float ColHeight = 1.0f;

	float BounceReduced = 0.5f;

};

