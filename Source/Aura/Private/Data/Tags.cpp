
#include "Data/Tags.h"

namespace Aura
{
	namespace Characters
	{
		UE_DEFINE_GAMEPLAY_TAG(Player,"Aura.Characters.Player")
		UE_DEFINE_GAMEPLAY_TAG(GoblinSpear,"Aura.Characters.GoblinSpear")
		UE_DEFINE_GAMEPLAY_TAG(GoblinSlingShot,"Aura.Characters.GoblinSlingShot")
		UE_DEFINE_GAMEPLAY_TAG(GoblinShaman,"Aura.Characters.GoblinShaman")
		UE_DEFINE_GAMEPLAY_TAG(Ghoul,"Aura.Characters.Ghoul")
		UE_DEFINE_GAMEPLAY_TAG(DemonMelee,"Aura.Characters.DemonMelee")
		UE_DEFINE_GAMEPLAY_TAG(DemonRanged,"Aura.Characters.DemonRanged")
	}
	namespace Montages
	{
		UE_DEFINE_GAMEPLAY_TAG(PrimaryAttack,"Aura.Montages.PrimaryAttack")
		UE_DEFINE_GAMEPLAY_TAG(HitReact,"Aura.Montages.HitReact")
		UE_DEFINE_GAMEPLAY_TAG(Death,"Aura.Montages.Death")
	}
	namespace Projectiles
	{
		UE_DEFINE_GAMEPLAY_TAG(FireBall,"Aura.Projectiles.FireBall")
		UE_DEFINE_GAMEPLAY_TAG(Stone,"Aura.Projectiles.Stone")
	}
	namespace Effects
	{
		UE_DEFINE_GAMEPLAY_TAG(PrimaryAttributes,"Aura.Effects.PrimaryAttributes")
		UE_DEFINE_GAMEPLAY_TAG(SecondaryAttributes,"Aura.Effects.SecondaryAttributes")
		UE_DEFINE_GAMEPLAY_TAG(VitalAttributes,"Aura.Effects.VitalAttributes")
		UE_DEFINE_GAMEPLAY_TAG(Damage,"Aura.Effects.Damage")
		UE_DEFINE_GAMEPLAY_TAG(HealUp,"Aura.Effects.HealUp")
		UE_DEFINE_GAMEPLAY_TAG(ManaUp,"Aura.Effects.ManaUp")
		UE_DEFINE_GAMEPLAY_TAG(StopMove,"Aura.Effects.StopMove")
	}
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG(HighLight,"Aura.Abilities.HighLight")
		UE_DEFINE_GAMEPLAY_TAG(PrimaryAttack,"Aura.Abilities.PrimaryAttack")
		UE_DEFINE_GAMEPLAY_TAG(MoveTo,"Aura.Abilities.MoveTo")
		UE_DEFINE_GAMEPLAY_TAG(StopMove,"Aura.Abilities.StopMove")
		UE_DEFINE_GAMEPLAY_TAG(MeleeAttack,"Aura.Abilities.MeleeAttack")
		UE_DEFINE_GAMEPLAY_TAG(ThrowDirectionalProjectile,"Aura.Abilities.ThrowDirectionalProjectile")
		UE_DEFINE_GAMEPLAY_TAG(ThrowFollowUpProjectile,"Aura.Abilities.ThrowFollowUpProjectile")
		UE_DEFINE_GAMEPLAY_TAG(Summoning,"Aura.Abilities.Summoning")
		UE_DEFINE_GAMEPLAY_TAG(HitReact,"Aura.Abilities.HitReact")
		UE_DEFINE_GAMEPLAY_TAG(Death,"Aura.Abilities.Death")
	}
	namespace Tasks
	{
		UE_DEFINE_GAMEPLAY_TAG(WeaponAction,"Aura.Tasks.WeaponAction")
		UE_DEFINE_GAMEPLAY_TAG(OnProjectileHitTarget,"Aura.Tasks.OnProjectileHitTarget")
		UE_DEFINE_GAMEPLAY_TAG(AISenseTarget,"Aura.Tasks.AISenseTarget")
		UE_DEFINE_GAMEPLAY_TAG(AIForgotTarget,"Aura.Tasks.AIForgotTarget")
	}
	namespace UI
	{
		UE_DEFINE_GAMEPLAY_TAG(PickUp,"Aura.UI.PickUp")
	}
	namespace InputMappingContexts
	{
		UE_DEFINE_GAMEPLAY_TAG(Default,"Aura.InputMappingContexts.Default")
	}
	namespace InputActions
	{
		UE_DEFINE_GAMEPLAY_TAG(RMB,"Aura.InputActions.RMB")
		UE_DEFINE_GAMEPLAY_TAG(Arcane,"Aura.InputActions.Arcane")
		UE_DEFINE_GAMEPLAY_TAG(FireBlast,"Aura.InputActions.FireBlast")
		UE_DEFINE_GAMEPLAY_TAG(Electrocute,"Aura.InputActions.Electrocute")
	}
}
