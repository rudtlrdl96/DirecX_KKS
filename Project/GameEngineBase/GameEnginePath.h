#pragma once
#include <filesystem>

class GameEnginePath
{
	friend class GameEngineFile;
	friend class GameEngineDirectory;

public:
	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetFileName() const;
	std::string GetFullPath() const;
	std::string GetExtension() const;

	void MoveParent();

	void MoveParentToChildPath(const std::string_view& _String);

	bool IsExists();
	bool IsExistsToPlusString(const std::string_view& _String);

	bool IsDirectory() const;

	bool IsRoot();

	bool Move(const std::string_view& _Path);

	void SetPath(const std::string_view& _Path);


protected:

private:
	std::filesystem::path Path;

};

