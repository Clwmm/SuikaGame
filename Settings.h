#pragma once

// WINDOW SIZE SETTINGS
constexpr int SCREEN_SIZE = 1200;
constexpr int VIEW_SIZE = 400;

// BALLS SIZE SETTINGS
constexpr float BALL_I = 12.f; // PEA
constexpr float BALL_II = 16.f; // BILARD
constexpr float BALL_III = 18.f; // EYEBALL
constexpr float BALL_IV = 22.f; // PONG ??
constexpr float BALL_V = 26.f; // TENIS
constexpr float BALL_VI = 30.f; // BAWLING BALL
constexpr float BALL_VII = 32.f; // BASKETBALL
constexpr float BALL_VIII = 36.f; // BEACHBALL
constexpr float BALL_IX = 40.f; // MOON
constexpr float BALL_X = 42.f; // PLANET

constexpr float FINAL_SIZE = 42.f;

// WALLS SIZE SETTING
constexpr float X_BOUNDRY = 100.f;
constexpr float Y_BOUNDRY = 180.f;

constexpr float TOP_BOUNDRY = -115.f;

// MASS MULTIPLIER
constexpr float MASS_MULTIPLIER = 12.f;

// ACCELERATION SLOWDOWN MULTIPLIER
constexpr float A_SLOWDOWN_MULITPLIER = 0.6f;

// VELOCITY SLOWDOWN MULTIPLIER
constexpr float V_SLOWDOWN_MULITPLIER = 0.04f;

// GRAVITI MULTIPLIER
constexpr float GRAVITI_MULITPLIER = 150.f;


// NEXT POSITION
constexpr float NEXT_POSITION_X = (VIEW_SIZE / 2.f) - FINAL_SIZE;
constexpr float NEXT_POSITION_Y = -(VIEW_SIZE / 2.f) + (2.f * FINAL_SIZE);

// END TIME
constexpr float TIME_TO_END = 2.5f;

constexpr float CLICK_DELAY_END = 0.3f;