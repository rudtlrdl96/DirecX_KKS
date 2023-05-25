#pragma once


class PlayerState
{
public:
	static float HP;
	static float MaxHP;


protected:
	
private:
	PlayerState();
	~PlayerState();

	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(PlayerState&& _Other) noexcept = delete;

};

