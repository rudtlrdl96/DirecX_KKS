#pragma once
#include "ContentLevel.h"

class BrokenObjectTool : public ContentLevel
{
public:
	BrokenObjectTool();
	~BrokenObjectTool();

	BrokenObjectTool(const BrokenObjectTool& _Other) = delete;
	BrokenObjectTool(BrokenObjectTool&& _Other) noexcept = delete;
	BrokenObjectTool& operator=(const BrokenObjectTool& _Other) = delete;
	BrokenObjectTool& operator=(BrokenObjectTool&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Save();
	void Load();


};

