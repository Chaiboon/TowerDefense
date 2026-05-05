#pragma once

#include "CoreMinimal.h"
#include "ETDTeam.generated.h"

UENUM(BlueprintType)
enum class ETDTeam : uint8
{
	Friendly	UMETA(DisplayName = "Friendly"),
	Enemy		UMETA(DisplayName = "Enemy")
};
