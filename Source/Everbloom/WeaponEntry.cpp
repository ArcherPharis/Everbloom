// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponEntry.h"
#include "Weapon.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UWeaponEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	AWeapon* Weapon = Cast<AWeapon>(ListItemObject);
	SwordIcon->SetBrushFromTexture(Weapon->GetWeaponIcon());
	WeaponText->SetText(Weapon->GetWeaponName());
}
