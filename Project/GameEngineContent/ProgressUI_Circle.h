#pragma once
#include "ProgressUI.h"

class ProgressUI_Circle : public ProgressUI
{
public:
	ProgressUI_Circle();
	~ProgressUI_Circle();

	ProgressUI_Circle(const ProgressUI_Circle& _Other) = delete;
	ProgressUI_Circle(ProgressUI_Circle&& _Other) noexcept = delete;
	ProgressUI_Circle& operator=(const ProgressUI_Circle& _Other) = delete;
	ProgressUI_Circle& operator=(ProgressUI_Circle&& _Other) noexcept = delete;

	void UpdateProgress(float _Progress) override;

	inline bool IsProgressEnd() const
	{
		return IsProgressEndValue;
	}

protected:
	void Start() override;
	
private:
	ProgressCircleBuffer Buffer;

	bool IsProgressEndValue = false;
};

