#pragma once

#ifndef ANDROID
#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, this->GetName() + L": " + FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, this->GetName() + L": " + FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + L": " + FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugFVector(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, this->GetName() + L": " + FString::Printf(TEXT("%f, %f, %f"), x.X, x.Y, x.Z));}
#else
#define Debug(x, ...) 
#define DebugError(x, ...) 
#define DebugWarning(x, ...) 
#define DebugFVector(x) 
#endif