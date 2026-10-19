
#include "Data/Tags.h"

namespace Aura
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG(Damage,"Aura.SetByCaller.Damage")
	}
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
	namespace Cooldown
	{
		UE_DEFINE_GAMEPLAY_TAG(Cooldown,"Aura.Cooldown")
		UE_DEFINE_GAMEPLAY_TAG(Arcane,"Aura.Cooldown.Arcane")
		UE_DEFINE_GAMEPLAY_TAG(Electrcude,"Aura.Cooldown.Electrcude")
		UE_DEFINE_GAMEPLAY_TAG(FireBall,"Aura.Cooldown.FireBall")
		UE_DEFINE_GAMEPLAY_TAG(FireBleast,"Aura.Cooldown.FireBleast")
		UE_DEFINE_GAMEPLAY_TAG(Melee,"Aura.Cooldown.Melee")
		UE_DEFINE_GAMEPLAY_TAG(Summon,"Aura.Cooldown.Summon")
	}
	namespace Abilities
	{
		UE_DEFINE_GAMEPLAY_TAG(Abilities,"Aura.Abilities")
		namespace Passive
		{
			UE_DEFINE_GAMEPLAY_TAG(CriticalChance,"Aura.Abilities.Passive.CriticalChance")
			UE_DEFINE_GAMEPLAY_TAG(LifeSteal,"Aura.Abilities.Passive.LifeSteal")
			UE_DEFINE_GAMEPLAY_TAG(PhysicalPenetration,"Aura.Abilities.Passive.PhysicalPenetration")
			UE_DEFINE_GAMEPLAY_TAG(MagicalPenetration,"Aura.Abilities.Passive.MagicalPenetration")
			
		}
		UE_DEFINE_GAMEPLAY_TAG(FireBall,"Aura.Abilities.FireBall")
		UE_DEFINE_GAMEPLAY_TAG(HomingFireBall,"Aura.Abilities.HomingFireBall")
		UE_DEFINE_GAMEPLAY_TAG(Arcane,"Aura.Abilities.Arcane")
		UE_DEFINE_GAMEPLAY_TAG(Electrocute,"Aura.Abilities.Electrocute")
		UE_DEFINE_GAMEPLAY_TAG(FireBlest,"Aura.Abilities.FireBlest")
		UE_DEFINE_GAMEPLAY_TAG(KnockBack,"Aura.Abilities.KnockBack")
		UE_DEFINE_GAMEPLAY_TAG(Stun,"Aura.Abilities.Stun")
		UE_DEFINE_GAMEPLAY_TAG(HighLight,"Aura.Abilities.HighLight")
		UE_DEFINE_GAMEPLAY_TAG(TraceUnderMouse,"Aura.Abilities.TraceUnderMouse")
		UE_DEFINE_GAMEPLAY_TAG(MoveTo,"Aura.Abilities.MoveTo")
		UE_DEFINE_GAMEPLAY_TAG(StopMove,"Aura.Abilities.StopMove")
		UE_DEFINE_GAMEPLAY_TAG(MeleeAttack,"Aura.Abilities.MeleeAttack")
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
		UE_DEFINE_GAMEPLAY_TAG(LMB,"Aura.InputActions.LMB")
		UE_DEFINE_GAMEPLAY_TAG(SB1,"Aura.InputActions.SB1")
		UE_DEFINE_GAMEPLAY_TAG(SB2,"Aura.InputActions.SB2")
	}
}
