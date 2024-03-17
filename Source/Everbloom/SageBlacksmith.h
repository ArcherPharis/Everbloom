// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplePerson.h"
#include "SageBlacksmith.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API ASageBlacksmith : public AApplePerson
{
	GENERATED_BODY()

private:
	virtual void InteractWith(AEmilia* Player);
	
};
