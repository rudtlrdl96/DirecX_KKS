#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
}


GameEngineFile::GameEngineFile(std::filesystem::path _Path) 
	: Path(_Path)
{

}

void GameEngineFile::Save(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	std::string PathString = Path.GetPathToString();

	// "w" // ������ ���� ���࿡ ��ο� ������ �������� �ʴ´ٸ�
	// ����ڴ�.
	fopen_s(&FilePtr, PathString.c_str(), "wb");

	if (nullptr == FilePtr)
	{
		MsgAssert("���� ���¿� �����߽��ϴ�." + PathString);
	}

	fwrite(_Data);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}