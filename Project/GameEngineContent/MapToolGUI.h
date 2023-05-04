#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class MapToolGUI : public GameEngineCoreWindow
{
public:
	MapToolGUI();
	~MapToolGUI();

	MapToolGUI(const MapToolGUI& _Other) = delete;
	MapToolGUI(MapToolGUI&& _Other) noexcept = delete;
	MapToolGUI& operator=(const MapToolGUI& _Other) = delete;
	MapToolGUI& operator=(MapToolGUI&& _Other) noexcept = delete;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
protected:
	
private:
	std::map<enum class TileArea, std::shared_ptr<class GameEngineTexture>> TileTexDatas;

	float4 TileSize = float4::Zero;

	float MinWidth = 0.0f;
	float MaxWitdh = 0.0f;
};

