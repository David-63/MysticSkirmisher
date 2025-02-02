// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SkirmisherWidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthMaxChangedSignature, float, NewHealthMax);

struct FOnAttributeChangeData;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYSTICSKIRMISHER_API UOverlayWidgetController : public USkirmisherWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnHealthMaxChangedSignature OnHealthMaxChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void HealthMaxChanged(const FOnAttributeChangeData& Data) const;
};
