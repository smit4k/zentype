#include "SoundManager.h"

SoundManager::SoundManager() : initialized(false) {
    
}

void SoundManager::Initialize() {
    if (!initialized) {
        keyPressSound = LoadSound("assets/sounds/keypress.wav");
        deleteSound = LoadSound("assets/sounds/delete.wav");
        initialized = true;
    }
}

SoundManager::~SoundManager() {
    if (initialized) {
        UnloadSound(keyPressSound);
        UnloadSound(deleteSound);
    }
}

void SoundManager::PlayKeyPress() { 
    if (initialized) PlaySound(keyPressSound); 
}

void SoundManager::PlayDelete() { 
    if (initialized) PlaySound(deleteSound); 
}