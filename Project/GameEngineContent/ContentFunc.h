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

	static float4 Bezier(std::vector<float4>& _Points, float _Time);

	template<typename EnumClass>
	static EnumClass RandEnum(std::vector<float>& _RandPer)
	{
		float CheckPer = 0.0f;
		float AllPer = 0.0f;

		for (size_t i = 0; i < _RandPer.size(); i++)
		{
			AllPer += _RandPer[i];
		}

		float RandPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, AllPer);

		EnumClass Result;

		for (size_t i = 0; i < _RandPer.size(); i++)
		{
			CheckPer += _RandPer[i];

			if (CheckPer >= RandPer)
			{
				Result = static_cast<EnumClass>(i);
				break;
			}
		}

		return Result;
	}

	static std::vector<int> RandomReward(std::vector<int>& _Datas, std::vector<int>& _Duplication, int _Count);

protected:
	
private:
	ContentFunc();
	~ContentFunc();

	ContentFunc(const ContentFunc& _Other) = delete;
	ContentFunc(ContentFunc&& _Other) noexcept = delete;
	ContentFunc& operator=(const ContentFunc& _Other) = delete;
	ContentFunc& operator=(ContentFunc&& _Other) noexcept = delete;
};

