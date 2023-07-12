#include "PrecompileHeader.h"
#include "BackgroundToolGUI.h"

BackgroundToolGUI::BackgroundToolGUI()
{
}

BackgroundToolGUI::~BackgroundToolGUI()
{
}

bool BackgroundToolGUI::CheckCreateTrigger()
{
	bool CheckResult = IsCreateTrigger;

	IsCreateTrigger = false;

	return CheckResult;
}

bool BackgroundToolGUI::CheckSaveTrigger()
{
	bool CheckResult = IsSaveTrigger;

	IsSaveTrigger = false;

	return CheckResult;
}

bool BackgroundToolGUI::CheckLoadTrigger()
{
	bool CheckResult = IsLoadTrigger;

	IsLoadTrigger = false;

	return CheckResult;
}

void BackgroundToolGUI::Start()
{
	BackgroundDatasLoad(LevelArea::None);
	BackgroundDatasLoad(LevelArea::Opening);
	BackgroundDatasLoad(LevelArea::Castle);
	BackgroundDatasLoad(LevelArea::ForestOfHarmory);
	BackgroundDatasLoad(LevelArea::GrandHall);
	BackgroundDatasLoad(LevelArea::HolyCourtyard);
	BackgroundDatasLoad(LevelArea::Shop);

}

void BackgroundToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{

	if (true == ImGui::Button("Save", ImVec2(60, 25)))
	{
		IsSaveTrigger = true;
		return;
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Load", ImVec2(60, 25)))
	{
		IsLoadTrigger = true;
		return;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	static int CurrentAreaIndex = 0;
	ImGui::Combo("Area", &CurrentAreaIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));

	CurShowAreaTile = (LevelArea)CurrentAreaIndex;

	if (CurShowAreaTile < LevelArea::None || CurShowAreaTile > LevelArea::Shop)
	{
		MsgAssert_Rtti<BackgroundToolGUI>(" - 잘못된 Area 타입이 입력되었습니다");
	}

	ImGui::Spacing();

	for (size_t i = 0; i < OnGuiCallback.size(); i++)
	{
		if (nullptr == OnGuiCallback[i])
		{
			continue;
		}

		OnGuiCallback[i]();
	}

	std::vector<BackgroundToolData>& BackDataRef =  BackgroundDatas[CurShowAreaTile];

	for (size_t i = 0; i < BackDataRef.size(); i++)
	{
		if (0 != i % 2)
		{
			ImGui::SameLine();
		}

		if (true == ImGui::ImageButton((void*)BackDataRef[i].TexturePtr->GetSRV(), ImVec2(200, 100)))
		{
			SelectBackgroundIndex = static_cast<int>(BackDataRef[i].Data.Index);
			IsCreateTrigger = true;
		}

		if (true == ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(BackDataRef[i].Data.Name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}

void BackgroundToolGUI::BackgroundDatasLoad(LevelArea _Area)
{
	std::vector<BackgroundToolData>& BufferTextureDatas = BackgroundDatas[_Area];

	std::vector<BackgroundMetaData> CopyDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

	BufferTextureDatas.reserve(CopyDatas.size());

	for (size_t i = 0; i < CopyDatas.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(CopyDatas[i].Name);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<BackgroundToolGUI>(" - 백그라운드 데이터의 텍스쳐를 찾을 수 없습니다");
		}

		BufferTextureDatas.push_back(BackgroundToolData(CopyDatas[i], FindTex));
	}
}
