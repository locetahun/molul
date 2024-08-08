#include "YourActor.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

AYourActor::AYourActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AYourActor::BeginPlay()
{
    Super::BeginPlay();
}

void AYourActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AYourActor::MoveToLocation(const FVector& Location)
{
    // Assuming this actor has an AIController
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
        if (NavSys)
        {
            FNavLocation NavLocation;
            if (NavSys->ProjectPointToNavigation(Location, NavLocation))
            {
                FPathFollowingRequestResult Result = AIController->MoveToLocation(NavLocation.Location);
                if (Result.Code == EPathFollowingRequestResult::RequestSuccessful)
                {
                    // Bind the completion event to our handler
                    AIController->ReceiveMoveCompleted.AddDynamic(this, &AYourActor::HandleMoveToLocationComplete);
                }
            }
        }
    }
}

void AYourActor::HandleMoveToLocationComplete(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    // Unbind the delegate to prevent multiple bindings
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->ReceiveMoveCompleted.RemoveDynamic(this, &AYourActor::HandleMoveToLocationComplete);
    }

    // Trigger the custom delegate
    OnMoveToLocationComplete.Broadcast();
}
