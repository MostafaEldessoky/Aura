
#include "Data/Tags.h"

namespace Tags
{
	namespace Characters
	{
		UE_DEFINE_GAMEPLAY_TAG(Player,"Tags.Characters.Player")
	}
	namespace EventTasks
	{
		UE_DEFINE_GAMEPLAY_TAG(SpawnProjectile,"Tags.EventTasks.SpawnProjectile")
	}
	namespace Projectiles
	{
		UE_DEFINE_GAMEPLAY_TAG(FireBall,"Tags.Projectiles.FireBall")
	}
	namespace UIMassage
	{
		UE_DEFINE_GAMEPLAY_TAG(UIMassage,"Tags.UIMassage")
		namespace EffectType
		{
			UE_DEFINE_GAMEPLAY_TAG(Heal,"Tags.UIMassage.Heal")
			UE_DEFINE_GAMEPLAY_TAG(ManaUp,"Tags.UIMassage.ManaUp")
		}
	}
	namespace Inputs
	{
		namespace MappingContexts
		{
			UE_DEFINE_GAMEPLAY_TAG(Default,"Tags.Inputs.MappingContexts.Default")
		}

		namespace InputActions
		{
			UE_DEFINE_GAMEPLAY_TAG(AttackMove,"Tags.Inputs.InputActions.AttackMove")
		}
	}
	namespace Montages
	{
		UE_DEFINE_GAMEPLAY_TAG(AttackMontage,"Tags.Montages.AttackMontage")
	}
}