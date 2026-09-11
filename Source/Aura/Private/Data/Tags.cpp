
#include "Data/Tags.h"

namespace Tags
{
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
}