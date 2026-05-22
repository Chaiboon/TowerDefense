// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameOverWidget.h"
#include "Kismet/GameplayStatics.h"

void UTDGameOverWidget::RestartGame() 
{
	UGameplayStatics::OpenLevel(this, FName("NewMap.umap"));
}