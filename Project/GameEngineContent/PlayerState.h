#pragma once


class PlayerState
{
public:
	static float GetMeleeAttack();
	static float GetMagicAttack();
	static float GetHP();
	static float GetMaxHP();

	static void SetMeleeAttack(float _Attack);
	static void SetMagicAttack(float _Attack);

	static void SetHP(float _HP);
	static void AddHP(float _HP);

private:
	static float MeleeAttack;
	static float MagicAttack;	
	
	static float HP;
	static float MaxHP;

	PlayerState();
	~PlayerState();

	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(PlayerState&& _Other) noexcept = delete;

};

