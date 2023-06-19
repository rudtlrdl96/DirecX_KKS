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

protected:
	void Start() override;

private:
	std::string NoteText = "�׽�Ʈ";

	std::shared_ptr<ContentSpriteRenderer> BackRender = nullptr;
	std::shared_ptr<GameEngineFontRenderer> TextRender = nullptr;
	ColorBuffer Buffer;

	std::vector<std::shared_ptr<class KeyActor>> KeyActors;


};

