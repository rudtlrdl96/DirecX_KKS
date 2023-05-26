#pragma once
#include "AnimationAttackMetaData.h"

class ContentFunc
{
public:
	template<typename SwapData>
	static void Swap(SwapData* _Left, SwapData* _Right)
	{
		SwapData Temp = *_Left;
		*_Left = *_Right;
		*_Right = Temp;
	}

	static float4 GetMousePos(std::shared_ptr<class GameEngineCamera> _MainCam);
	static void ImGuiHelpMarker(const std::string_view& _Text);

	static std::string GetOpenFilePath();
	static std::string GetSaveFilePath();

	static float4 ConvertFloat4(float _FloatArr[4]);

	static AnimationAttackMetaData LoadAnimAttackMetaData(const std::string_view& _Path);

	static std::shared_ptr<class GameEngineCollision> PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf = false);

	template<typename TYPE>
	static TYPE Lerp(TYPE _Start, TYPE _End, float _Progress)
	{
		if (0 > _Progress)
		{
			_Progress = 0.0f;
		}

		if (1 < _Progress)
		{
			_Progress = 1.0f;
		}
	
		// V0 + t * (V1 - V0)
		return _Start + _Progress * (_End - _Start);
	}

protected:
	
private:
	ContentFunc();
	~ContentFunc();

	ContentFunc(const ContentFunc& _Other) = delete;
	ContentFunc(ContentFunc&& _Other) noexcept = delete;
	ContentFunc& operator=(const ContentFunc& _Other) = delete;
	ContentFunc& operator=(ContentFunc&& _Other) noexcept = delete;
};

