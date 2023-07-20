#pragma once
#include "BaseContentActor.h"

class MouseCursor : public BaseContentActor
{
public:
	MouseCursor();
	~MouseCursor();

	MouseCursor(const MouseCursor& _Other) = delete;
	MouseCursor(MouseCursor&& _Other) noexcept = delete;
	MouseCursor& operator=(const MouseCursor& _Other) = delete;
	MouseCursor& operator=(MouseCursor&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

private:
	std::shared_ptr<class ContentFadeRender> CursorRender = nullptr;
	ColorBuffer Buffer;

	float HideTime = 0.0f;

	float4 PrevPos = float4::Zero;
};

