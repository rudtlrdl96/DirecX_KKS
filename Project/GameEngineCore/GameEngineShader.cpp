#include "PrecompileHeader.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

GameEngineShader::GameEngineShader() 
{
}

GameEngineShader::~GameEngineShader() 
{
	if (nullptr != BinaryCode)
	{
		BinaryCode->Release();
		BinaryCode = nullptr;
	}
}

void GameEngineShader::CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigt /*= 5*/, UINT _VersionLow /*= 0*/)
{
	// vs_5_0
	Version += _ShaderType;
	Version += "_";
	Version += std::to_string(_VersionHigt);
	Version += "_";
	Version += std::to_string(_VersionLow);
}


void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryCode)
	{
		MsgAssert("쉐이더가 컴파일 되지 않아서 쉐이더의 리소스를 조사할 수 없습니다.");
		return;
	}

	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgAssert("쉐이더 리플렉션에 실패했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info;

	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc;

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		std::string Name = ResDesc.Name;

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{

			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);
			
			std::shared_ptr<GameEngineConstantBuffer> Res = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);

			GameEngineConstantBufferSetter Setter;

			Setter.ParentShader = this;
			Setter.Name = UpperName;
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			ResHelper.CreateConstantBufferSetter(Setter);


			int a = 0;

			break;
		}
		case D3D_SIT_TEXTURE:
		{
			std::shared_ptr<GameEngineTexture> Res = GameEngineTexture::Find("EngineBaseTex.png");

			GameEngineTextureSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			ResHelper.CreateTextureSetter(Setter);
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			std::shared_ptr<GameEngineSampler> Res = GameEngineSampler::Find(UpperName);

			if (nullptr == Res)
			{
				Res = GameEngineSampler::Find("ENGINEBASE");
			}

			GameEngineSamplerSetter Setter;
			Setter.ParentShader = this;
			Setter.Name = UpperName;
			Setter.BindPoint = ResDesc.BindPoint;
			Setter.Res = Res;

			ResHelper.CreateSamplerSetter(Setter);
			break;
		}
		default:
			break;
		}

	}
}

void GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	std::string ShaderCode = _File.GetString();

	{
		size_t EntryIndex = ShaderCode.find("_VS(");

		if (EntryIndex != std::string::npos)
		{
			{
				size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
				std::string EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex - 1);
				EntryName += "_VS";
				GameEngineVertexShader::Load(_File.GetFullPath(), EntryName);
			}
		}
	}


	{
		size_t EntryIndex = ShaderCode.find("_PS(");

		if (EntryIndex != std::string::npos)
		{
			{
				size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
				std::string EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex - 1);
				EntryName += "_PS";
				GameEnginePixelShader::Load(_File.GetFullPath(), EntryName);
			}
		}
	}

}