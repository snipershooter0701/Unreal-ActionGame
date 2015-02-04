#pragma once
#include "IGIInteractable.generated.h"

/*
	Implement this interface if you want to make object interactable, with actor.
*/

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class GAMEINTERFACES_API UIGIInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IIGIInteractable
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void Interact(); //AActor* InteractingActor ?
};