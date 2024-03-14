// Copyright Nova DEV


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController() {
	
	// Indica que o estado do jogador precisa ser replicado na rede.
	bReplicates = true;
	
}
// Chamado quando o jogador entra no jogo.
void AAuraPlayerController::BeginPlay() {
	
	// Chama a função BeginPlay da classe base.
	Super::BeginPlay();
	// Verifica se o contexto de mapeamento de entrada foi configurado.
	check(AuraContext);

	// Obtém o subsistema de entrada local aprimorado.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	// Adiciona o contexto de mapeamento de entrada ao subsistema.
	Subsystem->AddMappingContext(AuraContext, 0);

	// Configura o cursor para ser visível.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Configura o modo de entrada para permitir movimento livre do mouse.
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}
