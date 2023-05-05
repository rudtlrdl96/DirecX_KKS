#pragma once


class int2
{
public:
	static const int2 Up;
	static const int2 Down;
	static const int2 Left;
	static const int2 Right;
	static const int2 Zero;

public:
	int x = 0;
	int y = 0;

	bool operator==(const int2& _Other)
	{
		return (this->x == _Other.x) && (this->y == _Other.y);
	}

	bool operator!=(const int2& _Other)
	{
		return (this->x != _Other.x) || (this->y != _Other.y);
	}

	int2 operator+(const int2& _Other)
	{
		int2 Result = *this;

		Result.x += _Other.x;
		Result.y += _Other.y;

		return Result;
	}

	int2& operator+=(const int2& _Other)
	{
		this->x += _Other.x;
		this->y += _Other.y;

		return *this;
	}

	int2 operator-(const int2& _Other)
	{
		int2 Result = *this;

		Result.x -= _Other.x;
		Result.y -= _Other.y;

		return Result;
	}

	int2& operator-=(const int2& _Other)
	{
		this->x -= _Other.x;
		this->y -= _Other.y;

		return *this;
	}

	int2 operator*(const int2& _Other)
	{
		int2 Result = *this;

		Result.x *= _Other.x;
		Result.y *= _Other.y;

		return Result;
	}

	int2 operator*(int _Scale)
	{
		int2 Result = *this;

		Result.x *= _Scale;
		Result.y *= _Scale;

		return Result;
	}

	float4 operator*(const float4& _Other)
	{
		float4 Result = { static_cast<float>(this->x), static_cast<float>(this->y)};

		Result.x *= _Other.x;
		Result.y *= _Other.y;

		return Result;
	}


	int2& operator*=(const int2& _Other)
	{
		this->x *= _Other.x;
		this->y *= _Other.y;

		return *this;
	}

	int2& operator*=(int _Scale)
	{
		this->x *= _Scale;
		this->y *= _Scale;

		return *this;
	}
};