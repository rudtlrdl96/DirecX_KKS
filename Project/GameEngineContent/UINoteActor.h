#pragma once
#include "BaseContentActor.h"
#include "ContentUIRender.h"

class UINoteActor : public BaseContentActor
{
public:
	UINoteActor();
	~UINoteActor();

	UINoteActor(const UINoteActor& _Other) = delete;
	UINoteActor(UINoteActor&& _Other) noexcept = delete;
	UINoteActor& operator=(const UINoteActor& _Other) = delete;
	UINoteActor& operator=(UINoteActor&& _Other) noexcept = delete;

	void SetText(const std::string_view& _Text);
	std::shared_ptr<GameEngineUIRenderer> AddKeyImage(const std::string_view& _KeyImage, const float4& _Pos);

protected:
	void Start() override;

private:
	std::string NoteText = "Å×½ºÆ®";

	std::shared_ptr<ContentUIRender> BackRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> TextRender = nullptr;
	ColorBuffer Buffer;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> KeyImageRenders;


};

