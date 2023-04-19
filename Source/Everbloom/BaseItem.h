// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class EVERBLOOM_API ABaseItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InteractWith(class AEmilia* player) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TSubclassOf<class UBaseItemObject> GetItemClass() const { return  ItemClass; }


private:


	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class USphereComponent* HitSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<class UBaseItemObject> ItemClass;



};
