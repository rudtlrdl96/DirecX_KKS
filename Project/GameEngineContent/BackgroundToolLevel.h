#pragma once
#include "ContentLevel.h"

class BackgroundToolLevel : public ContentLevel
{
public:
	BackgroundToolLevel();
	~BackgroundToolLevel();

	BackgroundToolLevel(const BackgroundToolLevel& _Other) = delete;
	BackgroundToolLevel(BackgroundToolLevel&& _Other) noexcept = delete;
	BackgroundToolLevel& operator=(const BackgroundToolLevel& _Other) = delete;
	BackgroundToolLevel& operator=(BackgroundToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

