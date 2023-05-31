#pragma once
#include "BaseContentActor.h"

class KeyActor : public BaseContentActor
{
public:
	KeyActor();
	~KeyActor();

	KeyActor(const KeyActor& _Other) = delete;
	KeyActor(KeyActor&& _Other) noexcept = delete;
	KeyActor& operator=(const KeyActor& _Other) = delete;
	KeyActor& operator=(KeyActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentSpriteRenderer> KeyRender = nullptr;
	ColorBuffer Buffer;
};

