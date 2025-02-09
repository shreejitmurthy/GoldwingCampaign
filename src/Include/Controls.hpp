#pragma once

#include "raylib.h"
#include <array>
#include <initializer_list>
#include <functional>

constexpr int MAX_KEYS = 3;

class Action {
public:
    std::array<int, MAX_KEYS> keys{};
    int numKeys = 0;
    int held = 0;

    Action() = default;

    void addKey(int key);

    bool isKeyDown() const;
};

class Controls {
public:
    Action forward;
    Action back;
    Action left;
    Action right;

    using BindCallback = std::function<void(Controls&)>;
    
    void init(BindCallback callback = nullptr);
};

inline bool actionKeyDown(std::initializer_list<Action> actions) {
    for (const auto& action : actions) {
        if (action.isKeyDown()) {
            return true;
        }
    }
    return false;
}
