// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TipTextSender.generated.h"

UCLASS()
class EVERBLOOM_API ATipTextSender : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATipTextSender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Tip Sender")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Tip Sender", meta = (MultiLine = true))
	FText TextToSend;

	UFUNCTION()
	void PlayerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
