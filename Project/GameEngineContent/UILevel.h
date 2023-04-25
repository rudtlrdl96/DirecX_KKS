#pragma once
#include "ContentLevel.h"

class UILevel : public ContentLevel
{
public:
	UILevel();
	~UILevel();

	UILevel(const UILevel& _Other) = delete;
	UILevel(UILevel&& _Other) noexcept = delete;
	UILevel& operator=(const UILevel& _Other) = delete;
	UILevel& operator=(UILevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:


};

