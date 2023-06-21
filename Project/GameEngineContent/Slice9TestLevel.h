#pragma once
#include "ContentLevel.h"

class Slice9TestLevel : public ContentLevel
{
public:
	Slice9TestLevel();
	~Slice9TestLevel();

	Slice9TestLevel(const Slice9TestLevel& _Other) = delete;
	Slice9TestLevel(Slice9TestLevel&& _Other) noexcept = delete;
	Slice9TestLevel& operator=(const Slice9TestLevel& _Other) = delete;
	Slice9TestLevel& operator=(Slice9TestLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineActor> TestActor = nullptr;
	std::shared_ptr<class ContentSlice9Renderer> SliceRender = nullptr;
};

