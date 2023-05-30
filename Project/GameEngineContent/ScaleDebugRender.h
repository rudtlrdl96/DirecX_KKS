#pragma once
#include "BaseContentActor.h"

class ScaleDebugRender : public BaseContentActor
{
public:
	ScaleDebugRender();
	~ScaleDebugRender();

	ScaleDebugRender(const ScaleDebugRender& _Other) = delete;
	ScaleDebugRender(ScaleDebugRender&& _Other) noexcept = delete;
	ScaleDebugRender& operator=(const ScaleDebugRender& _Other) = delete;
	ScaleDebugRender& operator=(ScaleDebugRender&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<ContentSpriteRenderer> DebugRender = nullptr;
	ColorBuffer DebugBuffer;

};

