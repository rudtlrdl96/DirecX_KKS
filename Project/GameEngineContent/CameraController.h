#pragma once


class CameraController
{
public:
	enum class CamCtrlType
	{
		None,
		LookAt,
		Move,
	};
public:
	CameraController();
	~CameraController();

	CameraController(const CameraController& _Other) = delete;
	CameraController(CameraController&& _Other) noexcept = delete;
	CameraController& operator=(const CameraController& _Other) = delete;
	CameraController& operator=(CameraController&& _Other) noexcept = delete;

	void Start(std::shared_ptr<class GameEngineCamera> _MainCam);
	void Update(float _DeltaTime);

	// Z°ª Àû¿ë X
	void CameraMove_ExceptionZ(const float4& _Start, const float4& _End, float _Time);
	void CameraShake(float _ShakeDis, float _ShakeSpeed, int _ShakeCount);

	inline float4 GetCameraPos() const
	{
		return CamPos;
	}

	inline void SetCamPos(const float4& _Pos)
	{
		CamPos = _Pos;
	}

	inline void SetCamRot(const float4& _Rot)
	{
		CamRot = _Rot;
	}

	inline void AddCamPos(const float4& _Pos)
	{
		CamPos += _Pos;
	}

	inline void AddCamRot(const float4& _Rot)
	{
		CamRot += _Rot;
	}

	inline void SetMinWidth(float _Value)
	{
		MinWidth = _Value;
	}

	inline void SetMinHeight(float _Value)
	{
		MinHeight = _Value;
	}

	inline void SetMaxWidth(float _Value)
	{
		MaxWidth = _Value;
	}

	inline void SetMaxHeight(float _Value)
	{
		MaxHeight = _Value;
	}

	void SetLookatTarget(std::shared_ptr<class GameEngineActor> _Target);

protected:
	
private:
	std::shared_ptr<class GameEngineCamera> MainCamera = nullptr;
	std::shared_ptr<class GameEngineActor> LookAtTarget = nullptr;

	CamCtrlType CamType = CamCtrlType::None;
	float4 CamPos = float4::Zero;
	float4 CamRot = float4::Zero;

	float4 WindowSize = float4::Zero;
	float4 WindowSizeHalf = float4::Zero;

	float MinWidth = -1000000.0f;
	float MinHeight = -1000000.0f;

	float MaxWidth = 1000000.0f;
	float MaxHeight = 1000000.0f;

	float4 MoveStartPos = float4::Zero;
	float4 MoveEndPos = float4::Zero;

	float MoveSpeed = 0.0f;
	float MoveProgress = 0.0f;

	int ShakeCount = 0;
	float ShakeSpeed = 0.0f;
	float ShakeMinDistance = 0.0f;
	float ShakeMaxDistance = 0.0f;
	float ShakeProgress = 0.0f;

	float4 StartShakePos = float4::Zero;
	float4 EndShakePos = float4::Zero;

	float4 CameraEffectPos = float4::Zero;

	float4 LastCameraPos = float4::Zero;
	Quaternion LastCameraRot = Quaternion::Zero;

	void CalShakeValue();
};