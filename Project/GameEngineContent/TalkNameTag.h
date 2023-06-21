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

	void SetNameTag(const std::string_view& _Name, const float4& _Pivot = float4::Zero, const float4& _ForceSize = float4::Zero);
	void SetFontSize(float _FontSize);
	void SetFontInterval(float _FontInterval);

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentUIRender> LeftRender = nullptr;
	std::shared_ptr<ContentUIRender> RightRender = nullptr;
	std::shared_ptr<ContentUIRender> CenterRender = nullptr;

	std::shared_ptr<class ContentUIFontRenderer> FontNameRender = nullptr;

	ColorBuffer Buffer;

	std::string NameText = "";

	float FontSize = 15.0f;
	float FontInterval = 10.0f;

	float4 FontPivot = float4::Zero;
	float4 ForceSize = float4::Zero;

	void SortText();
};

