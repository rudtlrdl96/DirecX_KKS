#include "PrecompileHeader.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() 
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
}


void GameEngineVertexBuffer::ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.ByteWidth = VertexSize * VertexCount;
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

void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer가 만들어지지 않은 버텍스 버퍼 입니다.");
		return;
	}
	
	GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
}