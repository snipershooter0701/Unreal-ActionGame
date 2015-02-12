// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "GameAttributes.h"

#include "IGAAttributes.h"
#include "GAAttributesBase.h"
#include "GAAttributeComponent.h"
#include "Effects/GAEffect.h"
#include "GAAttributesBlueprintFunctionLibrary.h"



UGAAttributesBlueprintFunctionLibrary::UGAAttributesBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UGAAttributesBlueprintFunctionLibrary::EqualAttribute(const FGAAttribute& Compare, FGAAttribute Against)
{
	return Compare == Against;
}
FName UGAAttributesBlueprintFunctionLibrary::GetAttribute(FGAAttribute AttributeIn)
{
	return AttributeIn.AttributeName;
}
float UGAAttributesBlueprintFunctionLibrary::GetFinalAttributeValue(AActor* Target, FGAAttribute Name)
{
	IIGAAttributes* attributeInt = Cast<IIGAAttributes>(Target);
	if (!attributeInt)
		return 0;
	return attributeInt->GetAttributes()->GetFinalAttributeValue(Name);
}
float UGAAttributesBlueprintFunctionLibrary::GetCurrentAttributeValue(AActor* Target, FGAAttribute Name)
{
	IIGAAttributes* attributeInt = Cast<IIGAAttributes>(Target);
	if (!attributeInt)
		return 0;
	return attributeInt->GetAttributes()->GetCurrentAttributeValue(Name);
}
float UGAAttributesBlueprintFunctionLibrary::GetAttributeFloat(AActor* Target, FGAAttribute AttributeIn)
{
	IIGAAttributes* attributeInt = Cast<IIGAAttributes>(Target);
	if (!attributeInt)
		return 0;

	return  attributeInt->GetAttributes()->GetFloatValue(AttributeIn);
}