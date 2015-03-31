// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GameInventorySystem.h"

#include "../GISItemData.h"
#include "../GISPickupActor.h"
#include "../GISInventoryBaseComponent.h"
#include "GISItemBaseWidget.h"
#include "GISLootSlotBaseWidget.h"
#include "GISLootContainerBaseWidget.h"

UGISLootContainerBaseWidget::UGISLootContainerBaseWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UGISLootContainerBaseWidget::InitializeLootWidget()
{
	OwningComp->OnLootingStart.BindUObject(this, &UGISLootContainerBaseWidget::UpdateLootWidget);
	Slots.Empty();
	if (SlotClass)
	{
		int32 MaxSlots = 20;
		for (int32 SlotIndex = 0; SlotIndex < MaxSlots; SlotIndex++)
		{
			UGISLootSlotBaseWidget* ItemSlot = CreateWidget<UGISLootSlotBaseWidget>(GetWorld(), SlotClass);
			if (ItemSlot)
			{
				if (LootItemClass)
				{
					UGISItemBaseWidget* item = CreateWidget<UGISItemBaseWidget>(GetWorld(), LootItemClass);
					ItemSlot->ItemWidget = item;
					
					if (LootItemSlotName != NAME_None)
					{
						UWidget* superWidget = ItemSlot->GetWidgetFromName(LootItemSlotName);
						UOverlay* overlay = Cast<UOverlay>(superWidget);
						overlay->AddChild(item);
					}
				}
			}

			Slots.Add(ItemSlot);
		}
		PostLootWidgetInitialized();
	}
}

void UGISLootContainerBaseWidget::UpdateLootWidget()
{
	int32 ItemNum = OwningComp->LootFromPickup.Loot.Num();
	TArray<FGISLootSlotInfo>& ItemRef = OwningComp->LootFromPickup.Loot;
	for (int32 ItemIndex = 0; ItemIndex < ItemNum; ItemIndex++)
	{
		Slots[ItemIndex]->LootSlotInfo = ItemRef[ItemIndex];
		Slots[ItemIndex]->SetItemInfo(ItemIndex);// = ItemRef[ItemIndex];
	}
	if (ItemNum <= 0)
	{
		int32 SlotNum = Slots.Num();
		for (int32 ItemIndex = 0; ItemIndex < SlotNum; ItemIndex++)
		{
			Slots[ItemIndex]->ResetSlot();
		}
	}
}