#pragma once
#include <random>

class GameEngineRandom
{

public:
	static GameEngineRandom MainRandom;

	GameEngineRandom();
	~GameEngineRandom();

	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution <float> Uniform(_Min, _Max);
		return Uniform(MtGen);
	}

	void SetSeed(__int64 _Seed) 
	{
		MtGen = std::mt19937_64(_Seed);
	}

protected:


private:
	std::mt19937_64 MtGen = std::mt19937_64();
};

