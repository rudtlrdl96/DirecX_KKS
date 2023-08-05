#pragma once
#include <list>
#include <memory>
#include <string_view>

class GameEngineObjectBase
{
public:
	GameEngineObjectBase();
	~GameEngineObjectBase();

	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	virtual void On()
	{
		UpdateValue = true;
	}

	virtual void Off()
	{
		UpdateValue = false;
	}

	virtual void Death()
	{
		DeathValue = true;
	}

	virtual bool IsDeath()
	{
		return DeathValue;
	}

	virtual bool IsUpdate()
	{
		return UpdateValue && (false == DeathValue);
	}

	void DebugOn()
	{
		DebugValue = true;
	}

	void DebugOff()
	{
		DebugValue = false;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool UpdateValue = true;
	bool DeathValue = false;
	bool DebugValue = false;
	int Order = 0;

};

