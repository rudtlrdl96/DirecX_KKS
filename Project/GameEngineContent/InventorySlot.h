#pragma once
#include "BaseContentActor.h"

enum class InventorySlotType
{
	None,
	Item,
	Skull
};

class InventorySlot : public BaseContentActor
{

public:
	InventorySlot();
	~InventorySlot();

	InventorySlot(const InventorySlot& _Other) = delete;
	InventorySlot(InventorySlot&& _Other) noexcept = delete;
	InventorySlot& operator=(const InventorySlot& _Other) = delete;
	InventorySlot& operator=(InventorySlot&& _Other) noexcept = delete;

	inline void SetInventorySlotType(InventorySlotType _Type)
	{
		Type = _Type;
	}

	inline InventorySlotType GetInventorySlotType() const
	{
		return Type;
	}

	void SetMoveIndex(size_t _Up, size_t _Down, size_t _Left, size_t _Right);

	inline size_t GetUpIndex() const
	{
		return UpIIndex;
	}

	inline size_t GetDownIndex() const
	{
		return DownIIndex;
	}

	inline size_t GetLeftIndex() const
	{
		return LeftIIndex;
	}

	inline size_t GetRightIndex() const
	{
		return RightIIndex;
	}

	inline void SelectOn()
	{
		SlotSelectRender->On();
	}

	inline void SelectOff()
	{
		SlotSelectRender->Off();
	}

	void SetDataIndex(size_t _Index);

	inline size_t GetDataIndex() const
	{
		return DataIndex;
	}


protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> SlotFrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SlotImageRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SlotSelectRender = nullptr;

	InventorySlotType Type = InventorySlotType::None;

	size_t DataIndex = -1;

	size_t UpIIndex = -1;
	size_t DownIIndex = -1;
	size_t LeftIIndex = -1;
	size_t RightIIndex = -1;

};

