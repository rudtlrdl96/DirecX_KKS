#pragma once
#include "BaseContentActor.h"
#include "TalkNameTag.h"
#include "TalkboxDebugGUI.h"
#include "ContentUIFontRenderer.h"

class TalkboxKeyImageData
{
public:
	std::string KeyImageName = "";
	float4 LocaPos = float4(-300, 25, -2);
};

class TalkBox : public BaseContentActor
{
	friend class BattleLevel;
public:
	TalkBox();
	~TalkBox();

	TalkBox(const TalkBox& _Other) = delete;
	TalkBox(TalkBox&& _Other) noexcept = delete;
	TalkBox& operator=(const TalkBox& _Other) = delete;
	TalkBox& operator=(TalkBox&& _Other) noexcept = delete;
	
	void ActiveTalkBox(const std::string_view& _Name, const float4& _NamePivot = float4::Zero, const float4& _ForceSize = float4::Zero);
	void SetMainText(const std::wstring_view& _MainText, std::function<void()> _Callback, std::vector<TalkboxKeyImageData> _KeyImageData = {});

	inline void SetReadSpeed(float _ReadSpeed)
	{
		ReadSpeed = _ReadSpeed;
	}

	void On() override;
	void Off() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<ContentUIRender> Render = nullptr;
	std::shared_ptr<ContentUIFontRenderer> FontTextRender = nullptr;

	std::shared_ptr<class TalkArrow> ArrowPtr = nullptr;
	std::shared_ptr<TalkNameTag> NameTagPtr = nullptr;

	std::string NameText = "";
	std::wstring MainText = L"";

	ColorBuffer Buffer;
	
	bool IsReadEnd = true;
	bool IsBoost = false;

	float ReadSpeed = 1.0f;
	float Progress = 0.0f;

	float ArrowAlpha = 0.0f;
	float BoostSpeed = 1.0f;
	float FontSize = 16.0f;

	int ReadSoundCount = 0;
	int PrevAddIndex = 0;

	std::vector<TalkboxKeyImageData> KeyImageDatas;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> KeyImages;

	std::function<void()> ReadEndCallback = nullptr;

};

