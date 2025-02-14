// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SkirmisherWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FSkirmisherAttributeInfo;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FSkirmisherAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYSTICSKIRMISHER_API UAttributeMenuWidgetController : public USkirmisherWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;


protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
