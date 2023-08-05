#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"

enum class SAVEMODE
{
	Text,
	Bin,
};

class GameEngineFile
{
public:
	GameEngineFile();
	~GameEngineFile();
	GameEngineFile(std::filesystem::path _Path);

	std::string GetFullPath() 
	{
		return Path.Path.string();
	}

	void SaveBin(const GameEngineSerializer& _Data);
	void SaveText(const std::string_view& _View);

	void LoadBin(GameEngineSerializer& _Data);

	void LoadText(GameEngineSerializer& _Data);

	std::string GetString();

	uintmax_t GetFileSize();

protected:

private:
	GameEnginePath Path;
};

