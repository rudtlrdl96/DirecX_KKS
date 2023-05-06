#pragma once
#include "ContentLevel.h"

class BackgroundToolLevel : public ContentLevel
{
public:
	BackgroundToolLevel();
	~BackgroundToolLevel();

	BackgroundToolLevel(const BackgroundToolLevel& _Other) = delete;
	BackgroundToolLevel(BackgroundToolLevel&& _Other) noexcept = delete;
	BackgroundToolLevel& operator=(const BackgroundToolLevel& _Other) = delete;
	BackgroundToolLevel& operator=(BackgroundToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	void Save();
	void Load();

	std::shared_ptr<class MultiBackground> MultiBackgroundPtr = nullptr;
	std::shared_ptr<class BackgroundToolGUI> BackgroundToolGUIPtr = nullptr;

	std::shared_ptr<class DebugSpriteActor> DebugActor = nullptr;
	std::shared_ptr<class GameEngineActorGUI> ActorGUIPtr = nullptr;
};

