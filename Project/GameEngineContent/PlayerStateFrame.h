#pragma once
#include "BaseContentActor.h"

class PlayerStateFrame : public BaseContentActor
{
public:
	PlayerStateFrame();
	~PlayerStateFrame();

	PlayerStateFrame(const PlayerStateFrame& _Other) = delete;
	PlayerStateFrame(PlayerStateFrame&& _Other) noexcept = delete;
	PlayerStateFrame& operator=(const PlayerStateFrame& _Other) = delete;
	PlayerStateFrame& operator=(PlayerStateFrame&& _Other) noexcept = delete;

	void SetParentPlayer(class Player* _Player);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	class Player* ParentPlayer = nullptr;

	std::shared_ptr<class PlayerHealthBar> HealthBarPtr = nullptr;

	std::shared_ptr<class ContentUIRender> MainFrame = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_MainSkull = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_MainSkillA = nullptr;
	std::shared_ptr<class ProgressUI_Circle> Progress_Switch= nullptr;
	std::shared_ptr<class ProgressUI_Circle> Progress_MainSkillA= nullptr;
	std::shared_ptr<class ProgressUI_Circle> Progress_MainSkillB= nullptr;

	std::shared_ptr<class ContentUIRender> MainSkillBFrame = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_MainSkillB = nullptr;

	std::shared_ptr<class ContentUIRender> SubSkullFrame = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_SubSkull = nullptr;

	std::shared_ptr<class ContentUIRender> SubSkillFrame_A = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_SubSkillA = nullptr;

	std::shared_ptr<class ProgressUI_Circle> Progress_SubSkillA = nullptr;
	std::shared_ptr<class ProgressUI_Circle> Progress_SubSkillB = nullptr;

	std::shared_ptr<class ContentUIRender> SubSkillFrame_B = nullptr;
	std::shared_ptr<class ContentUIRender> TexRender_SubSkillB = nullptr;

	std::shared_ptr<class ContentUIRender> QuintessenceFrame = nullptr;

	ColorBuffer Buffer;

	std::shared_ptr<class GameEngineActorGUI> ActorGui = nullptr;

	void RenderCreate(std::shared_ptr<class ContentUIRender>& _Render, const float4& _LocalPos, const std::string_view& _TextureName = "Empty.png");

};

