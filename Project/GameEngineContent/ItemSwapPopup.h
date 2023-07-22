#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class ItemSwapPopup : public BaseContentActor
{
public:
	ItemSwapPopup();
	~ItemSwapPopup();

	ItemSwapPopup(const ItemSwapPopup& _Other) = delete;
	ItemSwapPopup(ItemSwapPopup&& _Other) noexcept = delete;
	ItemSwapPopup& operator=(const ItemSwapPopup& _Other) = delete;
	ItemSwapPopup& operator=(ItemSwapPopup&& _Other) noexcept = delete;

	static void SetData(size_t _Index)
	{
		SetData(ContentDatabase<ItemData, ItemGrade>::GetData(_Index));
	}

	static void SetData(const ItemData& _Data)
	{
		Data = _Data;
	}

	static void SetSwapCallback(std::function<void()> _SwapCallback)
	{
		SwapCallback = _SwapCallback;
	}

	static void SetSwapCancel(std::function<void()> _CancelCallback)
	{
		CancelCallback = _CancelCallback;
	}

	void PopupOn();
	void PopupOff();

	static void SetSpawnPos(const float4& _Pos)
	{
		SpawnPos = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	static ItemData Data;
	static std::function<void()> SwapCallback;
	static std::function<void()> CancelCallback;
	static float4 SpawnPos;

	std::shared_ptr<GameEngineUIRenderer> SwapBackRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MainFrameRender = nullptr;

	std::vector<std::shared_ptr<class InventorySlot>> ItemSlots;

	size_t SlotIndex = 0;

	void MoveSlot_Up();
	void MoveSlot_Down();
	void MoveSlot_Left();
	void MoveSlot_Right();

};

