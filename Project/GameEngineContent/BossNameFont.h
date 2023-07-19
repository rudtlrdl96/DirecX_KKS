#pragma once
#include "BaseContentActor.h"

class BossNameFont : public BaseContentActor
{
private:
	enum class State
	{
		None,
		FadeIn,
		FadeOut
	};

public:
	BossNameFont();
	~BossNameFont();

	BossNameFont(const BossNameFont& _Other) = delete;
	BossNameFont(BossNameFont&& _Other) noexcept = delete;
	BossNameFont& operator=(const BossNameFont& _Other) = delete;
	BossNameFont& operator=(BossNameFont&& _Other) noexcept = delete;

	void ShowBossName(const std::string_view& _Name, const std::string_view& _Note, std::function<void()> _EndCallback = nullptr);

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::shared_ptr<ContentUIFontRenderer> FontRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> NoteRender = nullptr;
	std::function<void()> EndCallback = nullptr;

	float ProgressTime = 0.0f;

	State FontState = State::None;

	float4 StartColor = float4(0.98f, 0.98f, 0.96f, 0.0f);
	float4 EndColor = float4(0.98f, 0.98f, 0.96f, 1);
};

