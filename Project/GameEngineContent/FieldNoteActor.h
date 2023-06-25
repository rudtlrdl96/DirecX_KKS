#pragma once
#include "BaseContentActor.h"

class FieldNoteActor : public BaseContentActor
{
public:
	FieldNoteActor();
	~FieldNoteActor();

	FieldNoteActor(const FieldNoteActor& _Other) = delete;
	FieldNoteActor(FieldNoteActor&& _Other) noexcept = delete;
	FieldNoteActor& operator=(const FieldNoteActor& _Other) = delete;
	FieldNoteActor& operator=(FieldNoteActor&& _Other) noexcept = delete;

	void SetText(const std::string_view& _Text);
	void AddKeyImage(const std::string_view& _KeyImage, const float4& _Pos);

protected:
	void Start() override;

private:
	std::string NoteText = "Å×½ºÆ®";

	std::shared_ptr<ContentSpriteRenderer> BackRender = nullptr;
	std::shared_ptr<GameEngineFontRenderer> TextRender = nullptr;
	ColorBuffer Buffer;
	
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> KeyImageRenders;


};

