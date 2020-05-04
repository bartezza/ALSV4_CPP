// Copyright (C) 2020, Doga Can Yanikoglu


#include "Character/Animation/Notify/BMAnimNotifyFootstep.h"


#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UBMAnimNotifyFootstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetAnimInstance())
	{
		return;
	}

	const float MaskCurveValue = MeshComp->GetAnimInstance()->GetCurveValue(FootstepMaskCurveName);
	const float FinalVolMult = bOverrideMaskCurve ? VolumeMultiplier : VolumeMultiplier * (1.0f - MaskCurveValue);

	if (Sound)
	{
		UAudioComponent* SpawnedAudio = UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachPointName,
		                                                                     FVector::ZeroVector, FRotator::ZeroRotator,
		                                                                     EAttachLocation::Type::KeepRelativeOffset,
		                                                                     true, FinalVolMult, PitchMultiplier);
		if (SpawnedAudio)
		{
			SpawnedAudio->SetIntParameter(CueFootstepTypeParamName, static_cast<int32>(FootstepType));
		}
	}
}
