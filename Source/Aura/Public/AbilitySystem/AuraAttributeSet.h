// Copyright NovaDev

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//Start the constructor for AttributeSet
	UAuraAttributeSet();
	//Create a function to rep server and client values (or attributes)
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	* Property for MaxHealth can be read on blueprints, it's replicated using the function OnRep_Health when using
	* it and categorized on "Vital Attributes"
	**/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	/**
	* Property for MaxHealth can be read on blueprints, it's replicated using the function OnRep_MaxHealth when using
	* it and categorized on "Vital Attributes"
	**/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	/**
	* Property for MaxHealth can be read on blueprints, it's replicated using the function OnRep_Mana when using
	* it and categorized on "Vital Attributes"
	**/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	/**
	* Property for MaxHealth can be read on blueprints, it's replicated using the function OnRep_MaxMana when using
	* it and categorized on "Vital Attributes"
	**/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	//Function to use the old health value to check if it's valid
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//Function to use the old MaxHealth value to check if it's valid
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//Function to use the old MaxHealth value to check if it's valid
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//Function to use the old Max_Mana value to check if it's valid
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	
	
	
};
