#pragma once
#include "BaseContentActor.h"

class MonsterDeadBodyActor : public BaseContentActor
{
public:
	MonsterDeadBodyActor();
	~MonsterDeadBodyActor();

	MonsterDeadBodyActor(const MonsterDeadBodyActor& _Other) = delete;
	MonsterDeadBodyActor(MonsterDeadBodyActor&& _Other) noexcept = delete;
	MonsterDeadBodyActor& operator=(const MonsterDeadBodyActor& _Other) = delete;
	MonsterDeadBodyActor& operator=(MonsterDeadBodyActor&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _TextureName, float _Ratio = 1.0f);
	void Death() override;

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentSpriteRenderer> BodyRender = nullptr;
	ColorBuffer Buffer;
};

