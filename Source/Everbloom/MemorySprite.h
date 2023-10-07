// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "MemorySprite.generated.h"

UCLASS()
class EVERBLOOM_API AMemorySprite : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMemorySprite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TSubclassOf<class UEBGameplayAbilityBase> GetAbility() const { return MagicToGive; }
	FText GetIncantation() const { return Incantation; }
	FText GetKeyword() const { return Keyword; }

	UFUNCTION(BlueprintCallable, Category = "Memory Sprite")
	class UDialogueComponent* GetDialogueComponent() const { return DialogueComponent; }



private:
	virtual void InteractWith(AEmilia* Player);

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	class UBoxComponent* HitBox;

	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	USkeletalMeshComponent* SpriteMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Sprite")
	TSubclassOf<class UEBGameplayAbilityBase> MagicToGive;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText Incantation;
	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText Keyword;

	UPROPERTY(EditDefaultsOnly, Category = "Apple")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Apple")
	class UCameraComponent* Camera;





};
