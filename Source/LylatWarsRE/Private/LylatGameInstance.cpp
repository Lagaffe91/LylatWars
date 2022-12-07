#include "LylatGameInstance.h"

ULylatGameInstance::ULylatGameInstance()
{
	Score = 0;
	BossRoom = false;
	RailPos = 0.0f;
	UseGyro = true;
	GyroFlipX = false;
	GyroFlipY = false;
	GyroScale = 3.0f;
	DrawDebug = false;
}