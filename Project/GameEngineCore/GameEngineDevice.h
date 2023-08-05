#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

class GameEngineDevice
{
public:
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	static void Initialize();

	static void CreateSwapChain();

	static void Release();

	static void RenderStart();

	static void RenderEnd();

	static void VidioRenderStart();

	static void VidioRenderEnd();

	static ID3D11Device* GetDevice()
	{
		return Device;
	}

	static ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	static std::shared_ptr<class GameEngineRenderTarget> GetBackBufferTarget()
	{
		return BackBufferTarget;
	}

protected:

private:
	static ID3D11Device* Device;

	static ID3D11DeviceContext* Context;

	static IDXGISwapChain* SwapChain;

	static IDXGIAdapter* GetHighPerformanceAdapter();

	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	GameEngineDevice();
	~GameEngineDevice();
};

