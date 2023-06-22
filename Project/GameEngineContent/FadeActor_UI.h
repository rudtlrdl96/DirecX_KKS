#pragma once
#include "FadeActor.h"

class FadeActor_UI : public FadeActor
{
public:
	FadeActor_UI();
	~FadeActor_UI();

	FadeActor_UI(const FadeActor_UI& _Other) = delete;
	FadeActor_UI(FadeActor_UI&& _Other) noexcept = delete;
	FadeActor_UI& operator=(const FadeActor_UI& _Other) = delete;
	FadeActor_UI& operator=(FadeActor_UI&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};

