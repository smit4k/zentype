#include "SoundManager.h"

SoundManager::SoundManager() {
    keyPressSound = LoadSound("assets/sounds/keypress.wav");
    deleteSound = LoadSound("assets/sounds/delete.wav");
}

SoundManager::~SoundManager() {
    UnloadSound(keyPressSound);
    UnloadSound(deleteSound);
}

void SoundManager::PlayKeyPress() { PlaySound(keyPressSound); }
void SoundManager::PlayDelete() { PlaySound(deleteSound); }
