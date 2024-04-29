// Copyright NovaDev
// Este código define a implementação das funções do controlador de jogador para o jogo "Aura".
// O controlador do jogador é responsável por processar as entradas do jogador e controlar o comportamento do jogador no jogo.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

// Construtor padrão da classe AAuraPlayerController.
AAuraPlayerController::AAuraPlayerController() {
	
	// Define que este controlador será replicado para os clientes.
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	CursorTrace();	
	
}

void AAuraPlayerController::CursorTrace() {

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/*
	 * Linha de traçado do cursor. Estes são os possíveis cenários:
	 *  A. O LastActor é null e ThisActor é null
	 *		- Não faça nada
	 *	B. LastActor é null e ThisActor é válido (valid)
	 *		- Highlight ThisActor
	 *	C. LastActor é válido (valid) e ThisActor é null
	 *		- UnHighlight LastActor
	 *	D. Os dois atores são válidos, mas LastActor != ThisActor
	 *		- UnHilight LastActor, e Highlight ThisActor
	 *	E. Os dois atores são válidos, e os dois atores são os mesmos
	 *		- Não faça nada
	 */

	if (LastActor == nullptr) {
		
		if(ThisActor != nullptr) {
			//Caso B
			ThisActor->HighlightActor();
			
		} else {
			// Caso A - Os dois são nulos, não faça nada.
			
		}
		
	} else {	//LastActor é válido

		if (ThisActor == nullptr) {

			//Caso C
			LastActor->UnHighlightActor();
			
		} else {	// Os dois atores são válidos

			if (LastActor != ThisActor) {
				//Caso D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			} else {
				//Caso E - Não faça nada.
			}
			
		}
		
	}
	
}

// Função chamada quando o jogo começa.
void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();
	// Garante que o contexto do Aura esteja presente.
	check(AuraContext);

	// Obtém o subsistema local de entrada aprimorada para o jogador atual e checa para caso não passe no teste, dê um
	//crash
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	// Adiciona o contexto do Aura ao subsistema de mapeamento de entrada.
	Subsystem->AddMappingContext(AuraContext, 0);

	// Configuração do modo de entrada para o jogo e UI.
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// Habilita a exibição do cursor do mouse e define o cursor padrão.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Obtém o componente de entrada aprimorada e o vincula a ação de movimento e ao mesmo tempo que obtém o componente
	//faz uma checagem de teste para caso o Input não funcione, dê um crash para saber que o problema foi aqui.
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

// Função para mover o jogador com base na entrada do jogador.
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue) {

	// Obtém o vetor de entrada do eixo X e Y.
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// Obtém a rotação de controle atual.
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Obtém as direções para frente e para a direita com base na rotação do controle.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Verifica se o controlador possui um pawn controlado.
	if (APawn* ControlledPawn= GetPawn<APawn>()) {

		// Adiciona entrada de movimento para frente e para trás com base no vetor de entrada do eixo Y.
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		// Adiciona entrada de movimento para a direita e esquerda com base no vetor de entrada do eixo X.
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
		
	}
}




