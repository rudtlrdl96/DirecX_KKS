#pragma once
#include "BaseContentActor.h"
#include "ContentUIRender.h"

class TalkNameTag : public BaseContentActor
{
public:
	TalkNameTag();
	~TalkNameTag();

	TalkNameTag(const TalkNameTag& _Other) = delete;
	TalkNameTag(TalkNameTag&& _Other) noexcept = delete;
	TalkNameTag& operator=(const TalkNameTag& _Other) = delete;
	TalkNameTag& operator=(TalkNameTag&& _Other) noexcept = delete;

	void SetNameTag(const std::string_view& _Name);
	void SetFontSize(float _FontSize);
	void SetFontInterval(float _FontInterval);

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentUIRender> LeftRender = nullptr;
	std::shared_ptr<ContentUIRender> RightRender = nullptr;
	std::shared_ptr<ContentUIRender> CenterRender = nullptr;

	ColorBuffer Buffer;

	std::string NameText = "";

	float FontSize = 15.0f;
	float FontInterval = 10.0f;

	void SortText();
};

