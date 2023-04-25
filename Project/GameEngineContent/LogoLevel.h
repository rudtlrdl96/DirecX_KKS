#pragma once
#include "ContentLevel.h"
#include <memory>

class LogoLevel : public ContentLevel
{
public:
	LogoLevel();
	~LogoLevel();

	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
private:
};