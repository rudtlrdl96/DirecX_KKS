#pragma once
#include "BaseDebugLevel.h"

class ShaderDebugLevel : public BaseDebugLevel
{
private:
	enum class TargetRotType
	{
		X,
		Y,
		Z,
	};
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
	std::shared_ptr<GameEngineCamera> MainCam = nullptr;
	std::shared_ptr<GameEngineActor> ShaderTestActor = nullptr;

	float4 RotVector = float4::Zero;

	bool IsCameraRot = false;
	bool IsTargetRot = false;

	TargetRotType TargetRotState = TargetRotType::X;

	TransformData OldTrans;
};

