#pragma once
#include "GameplayTags.h"
#include "GISItemData.generated.h"
/*
	This is base class for item container used in InventoryComponent, to store items.

	How you use this container is up to you. I assume that item container will contain only TSubclassOf<>
	properties, which will in turn reference proper items (like weapons, construction elements, 
	consumable, armor items etc), along with any accompaning data for them (like upgrades, stats mods,
	count of how many items player have etc).

	If you so desire, you can of course just extend any item from this class but I do not recommend it.
*/
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew) // proly don't need that.
class GAMEINVENTORYSYSTEM_API UGISItemData : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item Properties")
		bool bCanBeAddedToHotbar;

	/**
		Can item stack ? For example, can more than one item occupy single inventory slot ?
	*/
	UPROPERTY(EditAnywhere, Category = "Item Properties")
		bool bCanStack;

	/*
		On technical side. If you are doing some seriously big stuff, change it to int8 ;)
		I use in32, because it doesn't have any problems with blueprint interaction.
	*/
	/*
		How much items is currently stacked here ? Set number to tell how many items there is initlally.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
		int32 StackCounter;
	/*
		Class of actor, which will be spawned when item is placed on level.
		Deliberetly subclass of AGISPickupActor, as we want to be able to pick item back
		to inventory.
	*/
	UPROPERTY(EditAnywhere, Category = "Item Properties")
		TSubclassOf<class AGISPickupActor> ItemLootActorClass;
	/*
		There are item behind specific items. It's another layer of checking to make setup even 
		more flexible. Since you might want certain components to acceept items from two different
		component, but you don't want those two component to accept items between them.

		OwnedTags are checked against COMPONENT to which item is dropped RequiredTags.
		If component have any of tags in RequiredTags property, this item can be added to it.

		Tags which I own.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Tags")
		FGameplayTagContainer OwnedTags;

	/*
		Then why do we have OwnedTags ? It Might be useful if you want direct item-to-item
		interaction coded.

		Tags this item requre to interact with other item and inventory component.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Tags")
		FGameplayTagContainer RequeredTags;

	bool IsNameStableForNetworking() const override;

	bool IsSupportedForNetworking() const override
	{
		return true;
	}
	void SetNetAddressable();
	/*
		Cosmetic stuff.
	*/
	/*
		I probabaly need to do it blueprint native events 0o. So those functions can be overriden 
		in blueprints.
	*/
	/*
		Get name of current item.
	*/
	virtual FText GetItemName() { return FText::FromString("Name None"); };
	/*
		Get image to display. Intentionally void for now, since
		I'm not sure if I want to return texture 2d or material.
		maybe just create functions for both..
	*/
	virtual UTexture2D* GetImage() { return nullptr; };

	/*
		Get item description. I would assume you want to return some kind of preformated
		description to show.
	*/
	virtual FText GetDescription() { return FText::FromString("No Description"); };
	/*
		Called when item is added to slot. 
		Might for example spawn objects from data in item, if you need object to be interactable.
	*/
	virtual bool OnItemAddedToSlot() { return false; }
	virtual bool OnItemRemovedFromSlot() { return false; }

	/*
		Called when item is added to inventory. And only then.
	*/
	virtual bool OnItemAddedToInventory() { return false; }

	/*
		Override when you need to activate item. For example from hotbar. Or something.
	*/
	virtual void ActivateItem() {}

	/*
		Override to perform action, when item is droped out of inventory.
		Most likely you will want to spawn actor on level, which will represent dropped item.
	*/
	virtual void OnDropFromInventory() {};

	/*
		Don't like this crap, but it is best way to expose it to blueprint (;.
	*/
	/*
		Actually it's completly useless ;)
	*/
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	//	bool OnKeyPressedDown();
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Input")
	//	bool OnKeyPressedUp();
	/*
		Below is mainly for convinience. We could just as well use Cast<> to determine class type.
		And at some point you will have to do Cast. To get item from inventory for example.
		But you don't need if you want to, for example just iterate over all items
		to check what types of items are in.
	*/
	/*
		Unique! Id of item container. 
	*/
	static const int32 ItemTypeID = 0;

	virtual int32 GetItemTypeID() const { return UGISItemData::ItemTypeID; }

	virtual bool IsOfType(int32 ItemTypeIDIn) { return UGISItemData::ItemTypeID == ItemTypeIDIn; }

protected:
	bool bNetAddressable;

};

template< class T >
T* CreateDataItem(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	if (!UserWidgetClass->IsChildOf(UGISItemData::StaticClass()))
	{
		// TODO UMG Error?
		return nullptr;
	}

	// Assign the outer to the game instance if it exists, otherwise use the player controller's world
	UWorld* World = OwningPlayer->GetWorld();
	//UObject* Outer = World->GetGameInstance() ? StaticCast<UObject*>(World->GetGameInstance()) : StaticCast<UObject*>(World);
	UGISItemData* NewWidget = ConstructObject<UGISItemData>(UserWidgetClass, OwningPlayer);

	return Cast<T>(NewWidget);
}