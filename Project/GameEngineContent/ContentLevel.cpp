#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

static UINT NewLevelCode = 0;

ContentLevel::ContentLevel() :
	LevelCode(++NewLevelCode)
{
}

ContentLevel::~ContentLevel()
{
}

float4 ContentLevel::GetMousePos() const
{
	float4 Result = GameEngineWindow::GetMousePosition();
	float4 CameraPos = MainCam->GetTransform()->GetWorldPosition();

	Result *= MainCam->GetViewPort().InverseReturn();
	Result *= MainCam->GetProjection().InverseReturn();
	Result *= MainCam->GetView().InverseReturn();

	return Result;
}

void ContentLevel::AddEvent(const std::string_view& _Event, UINT _ActorCode, std::function<void()> _Callback)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);
	EventCallback[UpperName][_ActorCode] = _Callback;
}

void ContentLevel::RemoveEvent(const std::string_view& _Event, UINT _ActorCode)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);

	std::map<UINT, std::function<void(void)>>& EventRef = EventCallback[UpperName];

	std::map<UINT, std::function<void(void)>>::iterator FindIter = EventRef.find(_ActorCode);

	if (FindIter != EventRef.end())
	{
		EventRef.erase(FindIter);
	}
}

void ContentLevel::CallEvent(const std::string_view& _Event)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);
	std::map<UINT, std::function<void(void)>>& EventRef = EventCallback[UpperName];

	std::map<UINT, std::function<void(void)>>::iterator LoopIter = EventRef.begin();
	std::map<UINT, std::function<void(void)>>::iterator EndIter = EventRef.end();

	while (LoopIter != EndIter)
	{
		if (nullptr == LoopIter->second)
		{
			MsgAssert_Rtti<GameEventManager>(" - nullptr callback 함수를 호출하려 했습니다");
			continue;
		}

		std::map<UINT, std::function<void(void)>>::iterator TempIter = LoopIter;
		++LoopIter;
		TempIter->second();
	}
}

void ContentLevel::Start()
{
	GameEngineLevel::Start();

	MainCam = GetMainCamera();
	MainCamCtrl.Start(MainCam);
	MainCam->SetSortType(0, SortType::ZSort);
	MainCam->GetTransform()->SetLocalPosition({0, 0, -5000});
	MainCam->GetTransform()->SetLocalRotation(float4::Zero);

	std::shared_ptr<GameEngineCamera> UICam = GetCamera(100);
	UICam->SetProjectionType(CameraType::Orthogonal);
	UICam->SetSortType(0, SortType::ZSort);
	UICam->GetTransform()->SetLocalPosition({ 0, 0, -5000 });

	std::shared_ptr<GameEngineCamera> FadeCam = CreateNewCamera(101);

	FadeCam->SetSortType(0, SortType::ZSort);
	FadeCam->SetProjectionType(CameraType::Orthogonal);
	FadeCam->GetTransform()->SetLocalPosition(float4(0, 0, -5000.0f));
	FadeCam->GetTransform()->SetLocalRotation(float4::Zero);
}

void ContentLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	MainCamCtrl.Update(_DeltaTime);
}

void ContentLevel::LevelChangeStart()
{
	PlayBaseBGM();
}

void ContentLevel::LevelChangeEnd()
{
	StopBaseBGM();
}

void ContentLevel::PlayBaseBGM()
{
	if ("" != BgmName)
	{
		if (false == BaseBgmPlayer.IsValid())
		{
			BaseBgmPlayer = GameEngineSound::Play(BgmName);
			BaseBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, 1.0f);
		}
		else
		{
			bool IsPlaying = false;
			BaseBgmPlayer.isPlaying(&IsPlaying);

			if (false == IsPlaying)
			{
				BaseBgmPlayer.setPosition(0);
				BaseBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, 1.0f);
			}
		}
	}
}

void ContentLevel::StopBaseBGM()
{
	if (true == BaseBgmPlayer.IsValid())
	{
		bool IsPlaying = false;
		BaseBgmPlayer.isPlaying(&IsPlaying);

		if (true == IsPlaying)
		{
			BaseBgmPlayer.SoundFadeOut(BGM_FadeOut_Time, 0.0f, false);
		}
	}
}

void ContentLevel::PlayCustomBgm(const std::string_view& _BgmName, float _FadeTime /*= 1.0f*/)
{
	StopCustomBgm();

	CustomBgmPlayer = GameEngineSound::Play(_BgmName);

	if (false == CustomBgmPlayer.IsValid())
	{
		MsgAssert_Rtti<ContentLevel>(" - Custom BGM 실행에 실패했습니다");
		return;
	}

	CustomBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, _FadeTime);
}

void ContentLevel::StopCustomBgm(float _FadeTime /*= 1.0f*/)
{
	if (true == CustomBgmPlayer.IsValid())
	{
		bool IsPlaying = false;
		CustomBgmPlayer.isPlaying(&IsPlaying);

		if (true == IsPlaying)
		{
			CustomBgmPlayer.SoundFadeOut(_FadeTime, true);
		}
	}
}
