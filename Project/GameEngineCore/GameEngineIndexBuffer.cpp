#include "PrecompileHeader.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer() 
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer() 
{
}

void GameEngineIndexBuffer::ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	IndexSize = _VertexSize;

	switch (IndexSize)
	{
	case 2:
		Format = DXGI_FORMAT_R16_UINT;
		break;
	case 4:
		Format = DXGI_FORMAT_R32_UINT;
		break;
	default:
		break;
	}

	IndexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.ByteWidth = IndexSize * IndexCount;

	BufferInfo.CPUAccessFlags = 0;
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else {
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}

}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer가 만들어지지 않은 버텍스 버퍼 입니다.");
		return;
	}
		
	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}