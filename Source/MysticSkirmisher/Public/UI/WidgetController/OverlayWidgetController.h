// Copyright David-6

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/SkirmisherWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthMaxChangedSignature, float, NewHealthMax);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaMaxChangedSignature, float, NewManaMax);



USTRUCT(BlueprintType)
struct FWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class USkirmisherUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FWidgetRow, Row);


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

	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FOnManaMaxChangedSignature OnManaMaxChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Messages")
	FMessageWidgetRowSignature MessageWidgetRowDeletage;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void HealthMaxChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void ManaMaxChanged(const FOnAttributeChangeData& Data) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
inline T *UOverlayWidgetController::GetDataTableRowByTag(UDataTable *DataTable, const FGameplayTag &Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
