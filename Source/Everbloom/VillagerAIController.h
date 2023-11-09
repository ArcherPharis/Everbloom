
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include <Perception/AIPerceptionTypes.h>
#include "VillagerAIController.generated.h"
/**
 * 
 */

UENUM()
enum EVillagerState
{
	Default UMETA(DisplayName = "Default"),
	Working UMETA(DisplayName = "Working"),
	Vibing UMETA(DisplayName = "Vibing"),
	Following UMETA(DisplayName = "Following")
};

UCLASS()
class EVERBLOOM_API AVillagerAIController : public AAIController
{
	GENERATED_BODY()

public:

	AVillagerAIController();
	/** Assigns Team Agent to given TeamID */
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	void ChangeState(TEnumAsByte<EVillagerState> NewState);
private:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category = "Villager State")
	TEnumAsByte<EVillagerState> CurrentVillagerState;


	FGenericTeamId TeamID;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	class UAIPerceptionComponent* PerceptionComp;
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
};
