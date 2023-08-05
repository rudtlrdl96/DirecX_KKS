#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory
{
public:
	GameEngineDirectory();
	~GameEngineDirectory();

	GameEngineDirectory(const std::string_view& _Path)
		: Path(_Path)
	{

	}

	GameEngineDirectory(std::filesystem::path _Path)
		: Path(_Path)
	{

	}

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	bool MoveParent();

	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);

	std::vector<GameEngineFile> GetAllFile(std::vector<std::string_view> _Ext);

	const GameEnginePath& GetPath() 
	{
		return Path;
	}

protected:

private:
	GameEnginePath Path;
};

