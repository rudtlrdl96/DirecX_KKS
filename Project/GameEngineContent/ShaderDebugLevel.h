#pragma once
#include "BaseDebugLevel.h"

class ShaderDebugLevel : public BaseDebugLevel
{
public:
	ShaderDebugLevel();
	~ShaderDebugLevel();

	ShaderDebugLevel(const ShaderDebugLevel& _Other) = delete;
	ShaderDebugLevel(ShaderDebugLevel&& _Other) noexcept = delete;
	ShaderDebugLevel& operator=(const ShaderDebugLevel& _Other) = delete;
	ShaderDebugLevel& operator=(ShaderDebugLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

