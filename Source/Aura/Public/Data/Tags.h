#pragma once


#include "NativeGameplayTags.h"

namespace Tags
{
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
}
