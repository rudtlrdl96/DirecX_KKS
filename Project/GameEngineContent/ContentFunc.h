#pragma once


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

protected:
	
private:
	ContentFunc();
	~ContentFunc();

	ContentFunc(const ContentFunc& _Other) = delete;
	ContentFunc(ContentFunc&& _Other) noexcept = delete;
	ContentFunc& operator=(const ContentFunc& _Other) = delete;
	ContentFunc& operator=(ContentFunc&& _Other) noexcept = delete;
};

