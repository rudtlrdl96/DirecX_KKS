#pragma once
#include "BaseContentActor.h"

class Minimap : public BaseContentActor
{
public:
	Minimap();
	~Minimap();

	Minimap(const Minimap& _Other) = delete;
	Minimap(Minimap&& _Other) noexcept = delete;
	Minimap& operator=(const Minimap& _Other) = delete;
	Minimap& operator=(Minimap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class ContentUIRender> MinimapFrameRender = nullptr;
	ColorBuffer Buffer;
};

