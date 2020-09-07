// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "BaseItem.generated.h"

UENUM(BlueprintType)
enum class EItmeType:uint8
{
	EWeapon        UMETA(DisplayName="武器"),
	EOther         UMETA(DisplayName="其他")
};
UCLASS()
class SWORDFLY_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual EItmeType GetItemType();

	UFUNCTION(BlueprintCallable)
	virtual void SetItmeType(EItmeType Type);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	EItmeType thisItmeType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class ASwordFlyCharacter* thisOwner;
	
	/*Component*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	USlateBrushAsset* ItemIcon;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FString ItemName;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class USphereComponent* Collision_Pack;
	
	UFUNCTION(Server, WithValidation, Reliable)
	virtual void Collision_Pack_BeginOverlapServer(class UPrimitiveComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void Collision_Pack_BeginOverlapNetMulticast(class UPrimitiveComponent* Component, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void Collision_Pack_BeginOverlap(class UPrimitiveComponent* Component,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void AfterThroud(class ASwordFlyCharacter* theOwner);

	UFUNCTION(Server, WithValidation, Reliable)
	virtual void AfterThroudServer(class ASwordFlyCharacter* theOwner);


	UFUNCTION(NetMulticast, Reliable)
	virtual void AfterThroudNetMulticast(class ASwordFlyCharacter* theOwner);
	//拾取定时器
	FTimerHandle MemberTimerHandle;
	//重置定时器
	void ReSetPackupFTimerHndle();

	private:
	
	
};
