#pragma once
#include "BehaviorObject.h"

class Pigeon : public BehaviorObject
{
public:
	Pigeon();
	~Pigeon();

	Pigeon(const Pigeon& _Other) = delete;
	Pigeon(Pigeon&& _Other) noexcept = delete;
	Pigeon& operator=(const Pigeon& _Other) = delete;
	Pigeon& operator=(Pigeon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void ResetBehavior() override;
	void PlayBehavior() override;
private:


};

