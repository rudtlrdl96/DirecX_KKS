#pragma once
#include "BaseContentActor.h"
#include "ContentSlice9UIRenderer.h"
#include "ContentUIFontRenderer.h"
#include "ContentUIRender.h"

class TalkButton : public BaseContentActor
{
public:
	TalkButton();
	~TalkButton();

	TalkButton(const TalkButton& _Other) = delete;
	TalkButton(TalkButton&& _Other) noexcept = delete;
	TalkButton& operator=(const TalkButton& _Other) = delete;
	TalkButton& operator=(TalkButton&& _Other) noexcept = delete;

	inline void SetText(const std::string_view& _Text)
	{
		FontRender->SetText(_Text);
	}

	inline void AddCallback(std::function<void()> _Callback)
	{
		UseCallback = _Callback;
	}

	void UseButton();

	void HoverOn();
	void HoverOff();

protected:
	void Start() override;
	
private:
	bool IsActive = false;
	std::function<void()> UseCallback = nullptr;

	std::shared_ptr<ContentUIFontRenderer> FontRender = nullptr;
	std::shared_ptr<ContentSlice9UIRenderer> FrameRender = nullptr;
};

