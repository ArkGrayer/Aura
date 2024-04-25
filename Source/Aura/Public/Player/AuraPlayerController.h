// Copyright NovaDev
// Este código define a classe do controlador de jogador para o jogo "Aura".
// O controlador do jogador é responsável por processar as entradas do jogador e controlar o comportamento do jogador no jogo.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

// Declaração prévia das classes.
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

// Classe do controlador de jogador.
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Contexto de mapeamento de entrada para o Aura.
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	// Ação de movimento.
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	// Função para mover o jogador.
	void Move(const FInputActionValue& InputActionValue);
	
};
