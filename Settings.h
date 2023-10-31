#pragma once

// WINDOW SIZE SETTINGS
constexpr int SCREEN_SIZE = 1200;
constexpr int VIEW_SIZE = 400;

// BALLS SIZE SETTINGS
constexpr float STRAWBERRY_SIZE = 12;
constexpr float APPLE_SIZE = 18;
constexpr float ORANGE_SIZE = 22;
constexpr float MELON_SIZE = 26;
constexpr float WATERMELON_SIZE = 32;
constexpr float FINAL_SIZE = 36;

// WALLS SIZE SETTING
constexpr float X_BOUNDRY = 100;
constexpr float Y_BOUNDRY = 180;

constexpr float TOP_BOUNDRY = -115;

// MASS MULTIPLIER
constexpr float MASS_MULTIPLIER = 12.f;

// ACCELERATION SLOWDOWN MULTIPLIER
constexpr float A_SLOWDOWN_MULITPLIER = 0.6f;

// VELOCITY SLOWDOWN MULTIPLIER
constexpr float V_SLOWDOWN_MULITPLIER = 0.04f;

// GRAVITI MULTIPLIER
constexpr float GRAVITI_MULITPLIER = 150.f;


// NEXT POSITION
constexpr float NEXT_POSITION_X = (VIEW_SIZE / 2) - FINAL_SIZE;
constexpr float NEXT_POSITION_Y = -(VIEW_SIZE / 2) + FINAL_SIZE;

// END TIME
constexpr float TIME_TO_END = 2.5f;

constexpr float CLICK_DELAY_END = 0.5f;