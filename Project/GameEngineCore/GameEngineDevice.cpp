#include "PrecompileHeader.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRenderTarget.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;
std::shared_ptr<GameEngineRenderTarget> GameEngineDevice::BackBufferTarget = nullptr;

GameEngineDevice::GameEngineDevice() 
{
}

GameEngineDevice::~GameEngineDevice() 
{
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Adapterindex, &CurAdapter);
		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();

	return Adapter;

}

void GameEngineDevice::CreateSwapChain()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {0,};

	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SwapChainDesc.Windowed = true;

	IDXGIDevice*  SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI 디바이스를 DirectX디바이스에서 얻어오지 못했습니다.");
		return;
	}

	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("스왑체인 생성에 실패했습니다.");
		return;
	}

	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	ID3D11Texture2D* SwapBackBufferTexture = nullptr;

	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&SwapBackBufferTexture));
	if (S_OK != Result)
	{
		MsgAssert("스왑체인 생성에 실패했습니다.");
		return;
	}

	std::shared_ptr<GameEngineTexture> BackBufferTexture = std::make_shared<GameEngineTexture>();
	BackBufferTexture->ResCreate(SwapBackBufferTexture);

	BackBufferTarget = GameEngineRenderTarget::Create("MainBackBufferTarget", BackBufferTexture, {0.0f, 0.0f, 1.0f, 1.0f});

	BackBufferTarget->CreateDepthTexture();

}

void GameEngineDevice::RenderStart() 
{
	BackBufferTarget->Clear();
	BackBufferTarget->Setting();
}

void GameEngineDevice::RenderEnd() 
{
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}
	
}

void GameEngineDevice::VidioRenderStart() 
{
	BackBufferTarget->Clear();
	BackBufferTarget->Reset();
}

void GameEngineDevice::VidioRenderEnd() 
{
	HRESULT Result = SwapChain->Present(0, 0);
}

void GameEngineDevice::Initialize() 
{
	if (nullptr ==  GameEngineWindow::GetHWnd())
	{
		MsgAssert("윈도우가 만들어지지 않았는데 디바이스를 초가화 할수는 없습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다.");
		return;
	}

	HRESULT Result = D3D11CreateDevice(
		Adapter, 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, 
		nullptr,
		iFlag,
		nullptr,
		0, 
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	CreateSwapChain();
}

void GameEngineDevice::Release()
{
	BackBufferTarget = nullptr;

	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}