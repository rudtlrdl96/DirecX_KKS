#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include "Collision2D.h"

class Rigidbody2D : public GameEngineComponent
{
public:
	Rigidbody2D();
	~Rigidbody2D();

	Rigidbody2D(const Rigidbody2D& _Other) = delete;
	Rigidbody2D(Rigidbody2D&& _Other) noexcept = delete;
	Rigidbody2D& operator=(const Rigidbody2D& _Other) = delete;
	Rigidbody2D& operator=(Rigidbody2D&& _Other) noexcept = delete;

	void Init(const std::vector<int>& _ColTypes);
	
protected:
	void Update(float _DeltaTime) override;

private:
};

