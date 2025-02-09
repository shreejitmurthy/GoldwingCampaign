#include "Controls.hpp"
#include "raylib.h"

void Action::addKey(int key) {
    if (numKeys < MAX_KEYS) {
        keys[numKeys++] = key;
    }
}

bool Action::isKeyDown() const {
    for (int i = 0; i < numKeys; i++) {
        if (IsKeyDown(keys[i])) {
            return true;
        }
    }
    return false;
}

void Controls::init(BindCallback callback) {
    if (callback) {
        callback(*this);
    }
}
