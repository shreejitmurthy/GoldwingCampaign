#pragma once

#define MAX_KEYS 3

#include <stdio.h>
#include <stdbool.h>

#include <initializer_list>

// TODO: Make this more 'C++-ified?'

typedef struct {
    int keys[MAX_KEYS];
    int numKeys;
    int held;
} action_t;

typedef struct {
    action_t forward;
    action_t back;
    action_t left;
    action_t right;
} controls_t;

typedef void (*control_bind_callback_t)(controls_t *controls);

void init_controls(controls_t *controls, control_bind_callback_t callback);
bool action_key_down(std::initializer_list<action_t> actions);

