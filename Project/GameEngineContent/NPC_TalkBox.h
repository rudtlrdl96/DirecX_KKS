#pragma once
#include "BaseContentActor.h"
#include "TalkNameTag.h"
#include "TalkboxDebugGUI.h"
#include "ContentUIFontRenderer.h"
#include "TalkButton.h"

class NPC_TalkBox : public BaseContentActor
{
public:
	NPC_TalkBox();
	~NPC_TalkBox();

	NPC_TalkBox(const NPC_TalkBox& _Other) = delete;
	NPC_TalkBox(NPC_TalkBox&& _Other) noexcept = delete;
	NPC_TalkBox& operator=(const NPC_TalkBox& _Other) = delete;
	NPC_TalkBox& operator=(NPC_TalkBox&& _Other) noexcept = delete;

	void SetTalkBoxName(const std::string_view& _Name, const float4& _NamePivot = float4::Zero, const float4& _ForceSize = float4::Zero);
	void AddMainText(const std::wstring_view& _MainText);

	void SetNextText();
	void SetTalkMainText(const std::wstring_view& _Text, std::function<void()> _TalkEndCallback);

	inline void SetReadSpeed(float _ReadSpeed)
	{
		ReadSpeed = _ReadSpeed;
	}

	inline void SetButtonInterval(const float4& _Inter)
	{
		ButtonInterval = _Inter;
	}

	void On() override;
	void Off() override;

	void AddButton(const std::string_view& _Text, std::function<void()> _Callback);

	void ButtonActive();
	void ButtonDisable();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<ContentUIRender> Render = nullptr;
	std::shared_ptr<ContentUIFontRenderer> FontTextRender = nullptr;
	std::shared_ptr<TalkNameTag> NameTagPtr = nullptr;
	std::shared_ptr<class TalkArrow> ArrowPtr = nullptr;
	std::shared_ptr<GameEngineComponent> ButtonPivot = nullptr;

	std::vector<std::shared_ptr<TalkButton>> TalkButtonActors;

	std::string NameText = "";
	std::wstring MainText = L"";

	std::vector<std::wstring> TalkList;

	std::function<void()> TalkEndCallback = nullptr;

	ColorBuffer Buffer;

	bool IsReadEnd = true;
	bool IsButtonActive = false;
	bool IsTalk = false;
	bool IsBoost = false;

	float ReadSpeed = 25.0f;
	float Progress = 0.0f;

	float ArrowAlpha = 0.0f;
	float FontSize = 16.0f;

	int ReadTalkIndex = -1;
	int ButtonIndex = 0;
	int ReadSoundCount = 0;
	int PrevAddIndex = 0;

	float BoostSpeed = 1.0f;

	float4 ButtonInterval = float4::Zero;

	void ButtonUp();
	void ButtonDown();
	void ButtonUse();
	void ButtonCancel();
	void ResetButton();

};

