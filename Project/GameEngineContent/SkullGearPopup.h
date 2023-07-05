#pragma once
#include "BaseContentActor.h"
#include "SkullData.h"
#include "ContentSlice9UIRenderer.h"

class SkullGearPopup : public BaseContentActor
{
public:
	SkullGearPopup();
	~SkullGearPopup();

	SkullGearPopup(const SkullGearPopup& _Other) = delete;
	SkullGearPopup(SkullGearPopup&& _Other) noexcept = delete;
	SkullGearPopup& operator=(const SkullGearPopup& _Other) = delete;
	SkullGearPopup& operator=(SkullGearPopup&& _Other) noexcept = delete;

	static void SetSkullData(size_t _Index)
	{
		SetSkullData(ContentDatabase<SkullData, SkullGrade>::GetData(_Index));
	}

	static void SetSkullData(const SkullData& _Data)
	{
		Data = _Data;
	}
	
	void PopupOn();
	void PopupOff();

protected:
	void Start() override;

private:
	static SkullData Data;

	std::shared_ptr<ContentSlice9UIRenderer> ItemFrameRender = nullptr;
	std::shared_ptr<ContentSlice9UIRenderer> NoteRender = nullptr;

	std::shared_ptr<GameEngineUIRenderer> SkillFrame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SkillIconA = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SkillIconB = nullptr;
};

