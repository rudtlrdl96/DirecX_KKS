#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContent/ContentCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContent.lib")

float map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
	return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdline,
	_In_ int nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentCore::CoreLoading, ContentCore::CoreEnd);
	return 0;
}