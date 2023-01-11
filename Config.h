#pragma once
#include <string>

constexpr int TILE_SIZE = 64;
constexpr int TILEMAP_WIDTH = 40;
constexpr int TILEMAP_HEIGHT = 8;
constexpr int TOTAL_TILES = TILEMAP_WIDTH * TILEMAP_HEIGHT;
constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 800;
const std::string p1Name = "Player1";
const std::string p2Name = "Player2";
// ==Jump params== //
constexpr double JUMP_HEIGHT = 256;
constexpr double JUMP_RANGE = 64;
constexpr double JUMP_TIME = 400;
constexpr double GRAVITY = 0.1;