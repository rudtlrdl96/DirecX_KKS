#pragma once
#include <GameEngineBase/GameEngineMath.h>

class GameEngineInputLayOutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs() 
	{
		return Descs;
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	int Offset = 0;

public:
	void AddInputLayOut(
			LPCSTR SemanticName, 
			DXGI_FORMAT Format,
			D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
			UINT InstanceDataStepRate = 0,
			UINT AlignedByteOffset = -1,
			UINT InputSlot = 0,
			UINT SemanticIndex = 0
	);

};

class GameEngineVertex
{
public:
	static GameEngineInputLayOutInfo LayOut;

public:
	float4 POSITION;
	float4 UV;   
	float4 NORMAL;
};

