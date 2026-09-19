#pragma once


#include "NativeGameplayTags.h"

namespace Tags
{
	namespace Characters
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player)
	}
	namespace EventTasks
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpawnProjectile)
	}

	namespace Projectiles
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(FireBall)
	}
	namespace UIMassage
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(UIMassage)
		namespace EffectType
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Heal)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaUp)
		}
	}
	namespace Inputs
	{
		namespace MappingContexts
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
		}

		namespace InputActions
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackMove)
		}
	}
	namespace Montages
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackMontage)
	}
}
