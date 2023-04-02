#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <memory>

class VertexActor;
class LogoLevel : public GameEngineLevel
{
public:
	LogoLevel();
	~LogoLevel();

	LogoLevel(const LogoLevel& _Other) = delete;
	LogoLevel(LogoLevel&& _Other) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

protected:

	void Loading() override;
	void Update(float _DeltaTime);
private:
	std::shared_ptr<VertexActor> Parent = nullptr;

	std::shared_ptr<VertexActor> Child0 = nullptr;
	std::shared_ptr<VertexActor> Child1 = nullptr;
	std::shared_ptr<VertexActor> Child2 = nullptr;
	std::shared_ptr<VertexActor> Child3 = nullptr;
	std::shared_ptr<VertexActor> Child4 = nullptr;
	std::shared_ptr<VertexActor> Child5 = nullptr;

};