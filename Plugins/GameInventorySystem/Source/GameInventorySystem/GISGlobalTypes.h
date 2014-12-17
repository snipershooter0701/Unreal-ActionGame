#pragma once

#include "GISGlobalTypes.generated.h"

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FPickupItemData
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FPickupItemContainer
{
	GENERATED_USTRUCT_BODY()
};

//hmp. This actually doesn't lend itself as extensible solution...
UENUM(BlueprintType)
namespace EGISSlotType
{
	enum Type
	{
		Inventory,
		Hotbar,
		Character,

		MAX_INVALID //always last.
	};
}

USTRUCT()
struct GAMEINVENTORYSYSTEM_API FGISLootSlotInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int32 SlotIndex;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISItemData> SlotData;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISInventoryBaseComponent> SlotComponent;
	UPROPERTY(BlueprintReadOnly)
		class AGISPickupActor* OwningPickupActor;
};

USTRUCT()
struct GAMEINVENTORYSYSTEM_API FGISSlotUpdateData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int32 TabIndex;
	UPROPERTY(BlueprintReadOnly)
		int32 SlotIndex;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISItemData> SlotData;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISInventoryBaseComponent> SlotComponent;
};

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FGISSlotSwapInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int32 LastTabIndex;
	UPROPERTY(BlueprintReadOnly)
		int32 LastSlotIndex;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISItemData> LastSlotData;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISInventoryBaseComponent> LastSlotComponent;
	UPROPERTY(BlueprintReadOnly)
		int32 TargetTabIndex;
	UPROPERTY(BlueprintReadOnly)
		int32 TargetSlotIndex;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISItemData> TargetSlotData;
	UPROPERTY(BlueprintReadOnly)
		TWeakObjectPtr<class UGISInventoryBaseComponent> TargetSlotComponent;
};

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FGISSlotInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		int32 SlotIndex;
	UPROPERTY(BlueprintReadOnly)
		int32 SlotTabIndex;
	UPROPERTY(BlueprintReadWrite)
		TWeakObjectPtr<class UGISItemData> ItemData;

	UPROPERTY(BlueprintReadWrite)
		TWeakObjectPtr<class UGISInventoryBaseComponent> CurrentInventoryComponent;
};

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FGISTabInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		int32 TabIndex;

	UPROPERTY(BlueprintReadWrite)
		int32 NumberOfSlots;

	UPROPERTY(BlueprintReadOnly)
		TArray<FGISSlotInfo> TabSlots;
};

USTRUCT(BlueprintType)
struct GAMEINVENTORYSYSTEM_API FGISInventoryTab
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		int32 NumberOfTabs;

	UPROPERTY(BlueprintReadOnly)
		TArray<FGISTabInfo> InventoryTabs;
};

USTRUCT()
struct FGISSlotsInTab
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfSlots;
};
