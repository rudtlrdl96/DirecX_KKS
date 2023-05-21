#pragma once
#include <GameEngineCore/GameEngineCollision.h>

class ColEnterCheck
{
public:
	ColEnterCheck();
	~ColEnterCheck();

	ColEnterCheck(const ColEnterCheck& _Other) = delete;
	ColEnterCheck(ColEnterCheck&& _Other) noexcept = delete;
	ColEnterCheck& operator=(const ColEnterCheck& _Other) = delete;
	ColEnterCheck& operator=(ColEnterCheck&& _Other) noexcept = delete;

	inline void FrameReset()
	{
		AllCols.clear();
	}

	inline void SetEnterEvent(std::function<void(std::shared_ptr<BaseContentActor>, const AttackColMetaData& _Data)> _Event)
	{
		EnterEvent = _Event;
	}

	void AddCollision(std::vector<std::shared_ptr<GameEngineCollision>>& _Cols, const AttackColMetaData& _Data);

protected:
	
private:
	std::function<void(std::shared_ptr<BaseContentActor>, const AttackColMetaData& _Data)> EnterEvent = nullptr;
	std::map<UINT, std::shared_ptr<BaseContentActor>> AllCols;
};

