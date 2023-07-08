#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentLevelLightGUI.h"

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

	WorldLight = GetCamera((int)CameraOrder::Main)->GetCamTarget()->CreateEffect<WorldLightEffect>();

	std::shared_ptr<PointLightEffect> Effect = CreatePointLight(LightType::Circle);

	Effect->LightBuffer.LightColor = float4(0.5f, 0.0f, 0.0f, 1.0f);
	Effect->LightBuffer.LightPos = float4(1280 / 2, 720 / 2);
	Effect->LightBuffer.LightOption.x = 200.0f;
	Effect->LightBuffer.LightOption.y = 1.0f;

}

void ContentLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	MainCamCtrl.Update(_DeltaTime);
}

void ContentLevel::LevelChangeStart()
{
	PlayBaseBGM();

	GameEngineGUI::FindGUIWindowConvert<ContentLevelLightGUI>("ContentLevelLightGUI")->SetLevel(DynamicThis<ContentLevel>());
}

void ContentLevel::LevelChangeEnd()
{
	StopBaseBGM();
}

void ContentLevel::PlayBaseBGM(bool _IsFade /*= true*/)
{
	if ("" != BgmName)
	{
		BaseBgmPlayer = GameEngineSound::Play(BgmName);
		BaseBgmPlayer.SetLoop();

		if (true == _IsFade)
		{
			BaseBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, 1.0f);
		}
	}
}

void ContentLevel::StopBaseBGM(bool _IsFade /*= true*/)
{
	if (true == BaseBgmPlayer.IsValid())
	{
		bool IsPlaying = false;
		BaseBgmPlayer.isPlaying(&IsPlaying);

		if (true == IsPlaying)
		{
			if (true == _IsFade)
			{
				BaseBgmPlayer.SoundFadeOut(BGM_FadeOut_Time, 0.0f, true);
			}
			else
			{
				BaseBgmPlayer.SetPause(true);
			}
		}
	}
}

void ContentLevel::PlayCustomBgm(const std::string_view& _BgmName, bool _IsFade /*= true*/, float _FadeTime /*= 1.0f*/)
{
	StopCustomBgm();

	CustomBgmPlayer = GameEngineSound::Play(_BgmName);

	if (false == CustomBgmPlayer.IsValid())
	{
		MsgAssert_Rtti<ContentLevel>(" - Custom BGM 실행에 실패했습니다");
		return;
	}

	CustomBgmPlayer.SetLoop(true);

	if (true == _IsFade)
	{
		CustomBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, _FadeTime);
	}
}

void ContentLevel::StopCustomBgm(float _FadeTime /*= 1.0f*/, bool _IsFade /*= true*/)
{
	if (true == CustomBgmPlayer.IsValid())
	{
		bool IsPlaying = false;
		CustomBgmPlayer.isPlaying(&IsPlaying);

		if (true == IsPlaying)
		{
			if (true == _IsFade)
			{
				CustomBgmPlayer.SoundFadeOut(_FadeTime, 0.0f, true);
			}
			else
			{
				CustomBgmPlayer.Stop();
			}
		}
	}
}

std::shared_ptr<PointLightEffect> ContentLevel::CreatePointLight(LightType _Type)
{
	std::shared_ptr<PointLightEffect> NewEffect = GetCamera((int)CameraOrder::Main)->GetCamTarget()->CreateEffect<PointLightEffect>();
	NewEffect->SetState(_Type);
	return NewEffect;
}