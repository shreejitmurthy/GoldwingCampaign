#include "Controls.hpp"
#include "raylib.h"

void init_controls(controls_t *controls, control_bind_callback_t callback) {
    // Initialize controls with emtpy values
    controls->forward = (action_t){{}, 0, 0};
    controls->back = (action_t){{}, 0, 0};
    controls->left = (action_t){{}, 0, 0};
    controls->right = (action_t){{}, 0, 0};

    // Let the user-defined callback customize the controls
    if (callback) {
        callback(controls);
    }
}

bool action_key_down(std::initializer_list<action_t> actions) {
    for (const action_t& action : actions) {
        for (int i = 0; i < action.numKeys; i++) {
            if (IsKeyDown(action.keys[i])) {
                return true;
            }
        }
    }
    return false;
}
