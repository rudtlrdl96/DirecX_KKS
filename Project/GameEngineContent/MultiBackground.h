#pragma once
#include "BaseContentActor.h"
#include "Background.h"

class MultiBackground : public BaseContentActor
{
	
public:
	MultiBackground();
	~MultiBackground();

	MultiBackground(const MultiBackground& _Other) = delete;
	MultiBackground(MultiBackground&& _Other) noexcept = delete;
	MultiBackground& operator=(const MultiBackground& _Other) = delete;
	MultiBackground& operator=(MultiBackground&& _Other) noexcept = delete;

	void CreateBackground(BackgroundMetaData& _MetaData);
	void UpdateTargetPos(float _DeltaTime, const float4& _TargetPos);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _SaveSerializer);

	void ShowGUI() override;
	void ClearBackground();

	void SetParentToBackground(size_t _Index, GameEngineTransform* _Actor);
protected:
	
private:
	std::vector<std::shared_ptr<Background>> BackgroundBuffer;

	int CurrentBackgroundIndex = -1;
};

