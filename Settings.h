#pragma once
#include <string>

// VIEW SIZE SETTINGS
constexpr int VIEW_SIZE = 400;

// BALLS SIZE SETTINGS
constexpr float BALL_I = 12.f;		// PEA				25%		0		-	250
constexpr float BALL_II = 16.f;		// BILARD			25%		251		-	500
constexpr float BALL_III = 18.f;	// EYEBALL			25%		501		-	750
constexpr float BALL_IV = 22.f;		// PONG ??			15%		751		-	900
constexpr float BALL_V = 26.f;		// TENIS			7.5%	901		-	975
constexpr float BALL_VI = 30.f;		// BAWLING BALL		2%		976		-	995
constexpr float BALL_VII = 32.f;	// BASKETBALL		0.4%	996		-	999
constexpr float BALL_VIII = 36.f;	// BEACHBALL		0.1%	1000	-	1000
constexpr float BALL_IX = 40.f;		// MOON
constexpr float BALL_X = 42.f;		// PLANET
constexpr float BALL_XI = 44.f;		// GALAXY
constexpr float BALL_XII = 48.f;	// BLACK HOLE

// WHEN BLACK HOLE APEARS IT DESTROY EVERYTHING LEAVING ONLY ITSELF
// TO DO:
//		- ss after end
//		- serializing files *.png

constexpr float FINAL_SIZE = 48.f;

// ENCRYPTING HIGHSCORE
constexpr std::string HIGHSCORE_FILE = "res/data.a";
constexpr char XORKEY = 'a';
constexpr std::string FIRST_EN = "fdsi";
constexpr std::string SECOND_EN = "iop";

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
constexpr float GRAVITI_MULITPLIER = 155.f;


// NEXT POSITION
constexpr float NEXT_POSITION_X = (VIEW_SIZE / 2.f) - FINAL_SIZE;
constexpr float NEXT_POSITION_Y = -(VIEW_SIZE / 2.f) + (2.f * FINAL_SIZE);

// END TIME
constexpr float TIME_TO_END = 2.5f;

constexpr float CLICK_DELAY_END = 0.3f;