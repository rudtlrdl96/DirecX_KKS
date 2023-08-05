#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineConstantBufferSetter;

public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			ConstantBufferRes[_Byte];
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			return ConstantBufferRes[_Byte][UpperName];
		}

		
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed();
		Buffer->SetName(UpperName);
		ConstantBufferRes[_Byte][UpperName] = Buffer;
		Buffer->ResCreate(_BufferDesc);

		return Buffer;
	}

	void ChangeData(const void* _Data, UINT _Size);

	static void ResourcesClear();

protected:
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc);

private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes;

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

