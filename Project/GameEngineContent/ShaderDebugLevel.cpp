#include "PrecompileHeader.h"
#include "ShaderDebugLevel.h"

// Actors
#include "DebugBoxActor.h"

ShaderDebugLevel::ShaderDebugLevel()
{
}

ShaderDebugLevel::~ShaderDebugLevel()
{
}

void ShaderDebugLevel::Start()
{
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("Debug");

		std::vector<GameEngineFile> File = Path.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	CreateActor<DebugBoxActor>();
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetWorldPosition(float4(0, 0, -1000, 1));
}

void ShaderDebugLevel::Update(float _DeltaTime)
{
	BaseDebugLevel::Update(_DeltaTime);
}
