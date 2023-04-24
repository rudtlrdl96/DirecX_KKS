#pragma once
#include <GameEngineCore/GameEngineComponent.h>
#include <GameEngineCore/GameEngineCollision.h>

enum class ColState
{
	None	= 0,
	Enter,
	Update,
	End,
};

class Collision2D : public GameEngineComponent
{
public:
	Collision2D();
	~Collision2D();

	Collision2D(const Collision2D& _Other) = delete;
	Collision2D(Collision2D&& _Other) noexcept = delete;
	Collision2D& operator=(const Collision2D& _Other) = delete;
	Collision2D& operator=(Collision2D&& _Other) noexcept = delete;

	void AddColType(int _ColType, bool _IsCol = true);

	inline void LinkColEnterFunc(const std::function<void()>& _EnterFunc)
	{
		EnterFunc = _EnterFunc;
	}

	inline void LinkColUpdateFunc(const std::function<void(float)>& _UpdateFunc)
	{
		UpdateFunc = _UpdateFunc;
	}

	inline void LinkColEndFunc(const std::function<void()>& _EndFunc)
	{
		EndFunc = _EndFunc;
	}


protected:
	void Update(float _DeltaTime) override;
	
private:
	// True == Col, False == Trigger
	std::vector<std::pair<int, bool>> ColTypes;

	std::function<void()> EnterFunc = nullptr;
	std::function<void(float)> UpdateFunc = nullptr;
	std::function<void()> EndFunc = nullptr;

	std::map<UINT, ColState> PrevColDatas;

	std::shared_ptr<GameEngineCollision> EngineCol = nullptr;
};