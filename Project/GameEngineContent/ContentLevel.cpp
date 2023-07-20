#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentLevelLightGUI.h"
#include "MouseCursor.h"

static UINT NewLevelCode = 0;

ContentLevel::ContentLevel() :
	LevelCode(++NewLevelCode)
{
}

ContentLevel::~ContentLevel()
{
}

float4 ContentLevel::GetMousePos(int _CamOrder /*= 0*/)
{
	std::shared_ptr<GameEngineCamera> Cam = GetCamera(_CamOrder);
	
	float4 Result = GameEngineWindow::GetMousePosition();
	float4 CameraPos = Cam->GetTransform()->GetWorldPosition();

	Result *= Cam->GetViewPort().InverseReturn();
	Result *= Cam->GetProjection().InverseReturn();
	Result *= Cam->GetView().InverseReturn();

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

	MainCam = GetMainCamera().get();
	MainCamCtrl.Start(MainCam);
	MainCam->SetSortType(0, SortType::ZSort);
	MainCam->GetTransform()->SetLocalPosition({ 0, 0, -5000 });
	MainCam->GetTransform()->SetLocalRotation(float4::Zero);

	std::shared_ptr<GameEngineCamera> UICam = GetCamera(100);
	UICam->SetProjectionType(CameraType::Orthogonal);
	UICam->SetSortType(0, SortType::ZSort);
	UICam->GetTransform()->SetLocalPosition({ 0, 0, -5000 });

	std::shared_ptr<GameEngineCamera> FadeCam = CreateNewCamera((int)CameraOrder::Fade);

	FadeCam->SetSortType(0, SortType::ZSort);
	FadeCam->SetProjectionType(CameraType::Orthogonal);
	FadeCam->GetTransform()->SetLocalPosition(float4(0, 0, -5000.0f));
	FadeCam->GetTransform()->SetLocalRotation(float4::Zero);


	WorldLight = GetCamera((int)CameraOrder::Main)->GetCamTarget()->CreateEffect<WorldLightEffect>();
	WorldLight->WorldLight = float4(1.0f, 1.0f, 1.0f, 1.0f);

	CreateActor<MouseCursor>();


	AddEvent("RewardWorldLightOn", LevelCode, [this]()
		{
			FadeWorldLightEffect(WorldLight->WorldLight, float4(0.8f, 0.8f, 0.8f, 1.0f), 2.0f);
		});

	AddEvent("RewardWorldLightOff", LevelCode, [this]()
		{
			FadeWorldLightEffect(WorldLight->WorldLight, float4::One, 2.0f);
		});
}

void ContentLevel::Update(float _DeltaTime)
{
	SoundDoubleCheck::SoundListReset();

	if (1.0f > WorldLightProgress)
	{
		WorldLightProgress += _DeltaTime * WorldLightSpeed;
		WorldLight->WorldLight = float4::LerpClamp(WorldLightStart, WorldLightEnd, WorldLightProgress);
	}

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
		if (false == BaseBgmPlayer.IsValid())
		{
			BaseBgmPlayer = GameEngineSound::Play(BgmName);
			BaseBgmPlayer.SetLoop();

			if (true == _IsFade)
			{
				BaseBgmPlayer.setPosition(0);
				BaseBgmPlayer.SoundFadeIn(BGM_FadeIn_Time, 1.0f);
			}
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
				BaseBgmPlayer.Stop();
			}
		}
	}

	BaseBgmPlayer.Clear();
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

	CustomBgmPlayer.Clear();
}

std::shared_ptr<PointLightEffect> ContentLevel::CreatePointLight(PointLightType _Type)
{
	std::shared_ptr<PointLightEffect> NewEffect = GetCamera((int)CameraOrder::Main)->GetCamTarget()->CreateEffect<PointLightEffect>();
	NewEffect->SetState(_Type);
	PointLightEffects.push_back(NewEffect);
	return NewEffect;
}

void ContentLevel::ReleasePointLight(std::shared_ptr<PointLightEffect> _Effect)
{
	std::vector<std::shared_ptr<PointLightEffect>>::iterator LoopIter = PointLightEffects.begin();
	std::vector<std::shared_ptr<PointLightEffect>>::iterator EndIter = PointLightEffects.end();

	for (; LoopIter != EndIter; ++LoopIter)
	{
		if ((*LoopIter) == _Effect)
		{
			LoopIter = PointLightEffects.erase(LoopIter);
			break;
		}
	}

	GetCamera((int)CameraOrder::Main)->GetCamTarget()->ReleaseEffect(_Effect);
}

void ContentLevel::FadeWorldLightEffect(const float4& _Start, const float4& _End, float _Speed)
{
	WorldLightStart = _Start;
	WorldLightEnd = _End;

	WorldLightProgress = 0.0f;
	WorldLightSpeed = _Speed;
}
