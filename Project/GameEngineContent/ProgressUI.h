#pragma once
#include "BaseContentActor.h"

enum class ProgressType
{
	Box,
	Circle,
};

enum class FillType
{
	Left,
	Right,
	Up,
	Down
};

class ProgressUI : public BaseContentActor
{

public:
	ProgressUI();
	~ProgressUI();

	ProgressUI(const ProgressUI& _Other) = delete;
	ProgressUI(ProgressUI&& _Other) noexcept = delete;
	ProgressUI& operator=(const ProgressUI& _Other) = delete;
	ProgressUI& operator=(ProgressUI&& _Other) noexcept = delete;

	void InitValue(const float4& _Size, const float4& _Color);
	void InitProgressType(ProgressType _ProgressType, FillType _FillType);

	virtual void UpdateProgress(float _Progress);

	std::shared_ptr<class ContentUIRender> GetRender()
	{
		return ProgressRender;
	}

protected:
	std::shared_ptr<class ContentUIRender> ProgressRender = nullptr;
	ProgressBuffer Buffer;

	ProgressType ProgressTypeValue = ProgressType::Box;
	FillType FillTypeValue = FillType::Left;

	void Start() override;
private:
};

