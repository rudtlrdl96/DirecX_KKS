#pragma once
#include "BaseContentActor.h"

class MouseCursorFollowTex : public BaseContentActor
{
public:
	MouseCursorFollowTex();
	~MouseCursorFollowTex();

	MouseCursorFollowTex(const MouseCursorFollowTex& _Other) = delete;
	MouseCursorFollowTex(MouseCursorFollowTex&& _Other) noexcept = delete;
	MouseCursorFollowTex& operator=(const MouseCursorFollowTex& _Other) = delete;
	MouseCursorFollowTex& operator=(MouseCursorFollowTex&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _TextureName);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> CursorTex = nullptr;

};

