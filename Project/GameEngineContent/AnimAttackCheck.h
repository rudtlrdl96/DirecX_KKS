#pragma once
#include "ColEnterCheck.h"

class AnimAttackCheck
{
public:
	AnimAttackCheck();
	~AnimAttackCheck();

	AnimAttackCheck(const AnimAttackCheck& _Other) = delete;
	AnimAttackCheck(AnimAttackCheck&& _Other) noexcept = delete;
	AnimAttackCheck& operator=(const AnimAttackCheck& _Other) = delete;
	AnimAttackCheck& operator=(AnimAttackCheck&& _Other) noexcept = delete;

	inline void SetRender(std::shared_ptr<ContentSpriteRenderer> _Redner)
	{
		Render = _Redner;
	}

	inline void SetCol(std::shared_ptr<GameEngineCollision> _Col, UINT _Order)
	{
		Col = _Col;
		Order = _Order;
	}

	inline void Reset()
	{
		Frame = 0;
		ColCheck.FrameReset();
	}

	inline void SetColData(const AnimationAttackMetaData& _Data)
	{
		Reset();
		ColData = _Data;
	}
	
	inline void SetEvent(std::function<void(std::shared_ptr<BaseContentActor>, const AttackColMetaData& _Data)> _Event)
	{
		Reset();
		ColCheck.SetEnterEvent(_Event);
	}

	bool Update();

protected:
	
private:
	ColEnterCheck ColCheck;
	AnimationAttackMetaData ColData = AnimationAttackMetaData();

	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	std::shared_ptr<GameEngineCollision> Col = nullptr;

	UINT Order = static_cast<UINT>(-1);
	UINT Frame = 0;
};