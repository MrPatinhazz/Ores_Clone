#pragma once

// ----- WALL CONSTANTS -----
// Block types (equal to bomb types)
constexpr unsigned int BTYPES = 5;
// Number of rows and columns
constexpr unsigned int NROW = 10;						
constexpr unsigned int NCOL = 17;
// Starting column of a new wall (left to right)
constexpr unsigned int INITCOL = (NCOL / 2);
// Block width and height
constexpr unsigned int B_WIDTH = 32;
constexpr unsigned int B_HEIGHT = 32;
// Wall width and height
constexpr unsigned int W_WIDTH = (B_WIDTH * NCOL);
constexpr unsigned int W_HEIGHT = (B_HEIGHT * NROW);

// ----- GAME CONSTANTS -----
// Stage points needed to pass to the next level
constexpr unsigned int STG_PTS = 400;
// Max clicks allowed when aim bomb is on
constexpr unsigned int AIM_CLICKS = 9;
// Push wall interval in ms
extern constexpr double PSH_INTV = 6000;

// ----- RENDER CONSTANTS -----
// Screen size
constexpr bool FULLSCREEN = false;
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

// MENU SCREEN - Start and Quit button
constexpr unsigned int START_BT_X = (SCREEN_WIDTH / 2) - 150;
constexpr unsigned int START_BT_Y = 200;
constexpr unsigned int QUIT_BT_X = (SCREEN_WIDTH / 2) - 150;
constexpr unsigned int QUIT_BT_Y = 400;

// PAUSED SCREEN - Paused text
constexpr unsigned int PAUSED_TXT_X = 0;
constexpr unsigned int PAUSED_TXT_Y = (SCREEN_HEIGHT / 2) - 200;

// Wall start and end x & y coordinate
constexpr unsigned int WALL_X1 = (SCREEN_WIDTH - W_WIDTH);
constexpr unsigned int WALL_X2 = (W_WIDTH + WALL_X1);
constexpr unsigned int WALL_Y1 = ((SCREEN_HEIGHT - W_HEIGHT) / 2);
constexpr unsigned int WALL_Y2 = (W_HEIGHT + WALL_Y1);

// Score text X & Y
constexpr unsigned int SCR_TXT_X = 0;
constexpr unsigned int SCR_TXT_Y = 0;

// Timer text and bar
constexpr unsigned int TM_TXT_X = (SCREEN_WIDTH / 2)-200;
constexpr unsigned int TM_TXT_Y = 0;
constexpr double TM_MAX_WIDTH = 200;

// Current stage text
constexpr unsigned int STG_TXT_X = (SCREEN_WIDTH - (SCREEN_WIDTH / 5));
constexpr unsigned int STG_TXT_Y = 0;

// Next stage button
constexpr unsigned int NSB_BT_X = (WALL_X2 - (B_WIDTH * 1.5));
constexpr unsigned int NSB_BT_Y = (WALL_Y2 + (B_HEIGHT / 2));

// Multi bomb info text 
constexpr unsigned int MBOMB_TXT_X = (SCREEN_WIDTH / 3);
constexpr unsigned int MBOMB_TXT_Y = 50;

// Aim bomb info text 
constexpr unsigned int ABOMB_TXT_X = (SCREEN_WIDTH / 3);
constexpr unsigned int ABOMB_TXT_Y = 50;