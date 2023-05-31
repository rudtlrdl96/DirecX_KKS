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

protected:
	void Start() override;

private:
	std::string NoteText = "Å×½ºÆ®";

	std::shared_ptr<ContentSpriteRenderer> BackRender = nullptr;
	ColorBuffer Buffer;
};

