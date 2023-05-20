#include "PrecompileHeader.h"
#include "FPSCheckGUI.h"

FPSCheckGUI::FPSCheckGUI()
{
}

FPSCheckGUI::~FPSCheckGUI()
{
}

void FPSCheckGUI::Reset()
{
	Time = 0.0f;
	TotalFrameCount = 0;
}

void FPSCheckGUI::Start()
{
}

void FPSCheckGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	Time += _DeltaTime;
	TotalFrameCount++;

	if (Time >= 1.0f)
	{
		FPS = static_cast<size_t>(TotalFrameCount / Time);
		TotalFrameCount = 0;
		Time = 0.0f;
	}


	ImGui::Text(std::to_string(FPS).c_str());

}
