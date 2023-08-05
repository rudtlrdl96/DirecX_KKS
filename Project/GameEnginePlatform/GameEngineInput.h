#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� :
class GameEngineWindow;
class GameEngineInput
{
	friend GameEngineWindow;

private:
	class GameEngineKey 
	{
		friend GameEngineInput;

		bool Down = false;
		bool Press = false; 
		bool Up = false;
		bool Free = true; 

		float PressTime = 0.0f;
		int Key = -1;

		void Reset() 
		{
			GetAsyncKeyState(Key);

			Down = false; 
			Press = false; 
			Up = false; 
			Free = true; 
		}

		bool KeyCheck() 
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);

	static void CreateKey(const std::string_view& _Name, int _Key);

	static bool IsKey(const std::string_view& _Name);

	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);
	static float GetPressTime(const std::string_view& _Name);

	static void MouseCursorOff();

	static bool IsAnyKey() 
	{
		return IsAnyKeyValue;
	}

	static float4 GetMousePosition() 
	{
		return MousePos;
	}

	static float4 GetMouseDirection()
	{
		return MouseDirection;
	}

	static float4 GetMouseDirectionNormal()
	{
		return MouseDirection.NormalizeReturn();
	}

protected:

private:
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;
	static bool IsAnyKeyValue;
	static bool IsFocus;

	static float4 MousePos;
	static float4 PrevMousePos;
	static float4 MouseDirection;

	static void IsFocusOn()
	{
		IsFocus = true;
	}

	static void IsFocusOff()
	{
		IsFocus = false;
	}

	static void IsAnyKeyOn()
	{
		IsAnyKeyValue = true;
	}

	static void IsAnyKeyOff()
	{
		IsAnyKeyValue = false;
	}
};


