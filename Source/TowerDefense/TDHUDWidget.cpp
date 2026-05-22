// Fill out your copyright notice in the Description page of Project Settings.


#include "TDHUDWidget.h"

void UTDHUDWidget::UpdateHUD(int32 NewGold, int32 NewLives, int32 NewWave)
{
	Gold = NewGold;
	Lives = NewLives;
	Wave = NewWave;
}