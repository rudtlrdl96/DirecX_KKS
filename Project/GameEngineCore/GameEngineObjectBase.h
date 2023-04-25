#pragma once
#include <list>
#include <memory>
#include <string_view>

// ���� :
class GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineObjectBase();
	~GameEngineObjectBase();

	// delete Function
	GameEngineObjectBase(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _Other) noexcept = delete;
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _Other) = delete;
	GameEngineObjectBase& operator=(GameEngineObjectBase&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void On()
	{
		ActiveValue = true;
	}

	void Off()
	{
		ActiveValue = false;
	}

	bool IsUpdate() const
	{
		return ActiveValue;
	}

	void Death()
	{
		DeathValue = true;
	}

	bool IsDeath() const
	{
		return DeathValue;
	}

	void DebugOn()
	{
		DebugValue = true;
	}

	bool IsDebug()
	{
		return DebugValue;
	}

protected:

private:
	bool ActiveValue = true; // ������ ������
	bool DeathValue = false; // �׾��� ��Ҵ�
	bool DebugValue = false;
	int Order = 0;
	////////////////////////////////////////////////////////////// Transform ���ϱ���
};

