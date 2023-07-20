#include "PrecompileHeader.h"
#include "PlayerState.h"
#include "Inventory.h"


float PlayerState::MeleeAttack = 10.0f;
float PlayerState::MagicAttack = 10.0f;

float PlayerState::HP = 100.0f;
float PlayerState::MaxHP = 100.0f;

float PlayerState::GetMeleeAttack()
{
	return MeleeAttack;
}

float PlayerState::GetMagicAttack()
{
	return MagicAttack;
}

float PlayerState::GetHP()
{
	return HP;
}

float PlayerState::GetMaxHP()
{
	return MaxHP;
}

void PlayerState::SetMeleeAttack(float _Attack)
{
	MeleeAttack = _Attack;
}

void PlayerState::SetMagicAttack(float _Attack)
{
	MagicAttack = _Attack;
}

void PlayerState::SetHP(float _HP)
{
	HP = _HP;
}

void PlayerState::AddHP(float _HP)
{
	HP += _HP;
}

PlayerState::PlayerState()
{
}

PlayerState::~PlayerState()
{
}
