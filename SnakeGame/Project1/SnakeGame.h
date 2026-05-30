#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <string.h>
#include <vector>
#include "rlgl.h"

using namespace std;


class SnakeGame
{
public:

#define TILE_SIZE 73


	static const int screenW = 1280;
	static const int screenH = 720;

	int tailCount = 1;

	typedef struct Piece
	{
		Vector2 pos;
		Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
		Color color;

		void Draw()
		{
			DrawRectangleV(pos, size, color);
		}

	} Piece;


	Vector2 speed = Vector2 {TILE_SIZE,0};
	vector<Piece> player;
	bool canMove = false;
	bool gamePause = false;
	bool gameOver = false;
	bool gameWon = false;
	int frameCount = 0;
	Vector2 borderGap = { screenW % TILE_SIZE, screenH % TILE_SIZE }; // vector represents the total gap for left+right and top+bottom gaps
	int totalCells = ((screenW - borderGap.x) / TILE_SIZE) * ((screenH - borderGap.y) / TILE_SIZE);

	typedef struct Fruit
	{
		Vector2 pos;
		Color color = GOLD;
		Vector2 size = Vector2{ TILE_SIZE, TILE_SIZE };
		bool active = false; // default is inactive. Spawn

		void NewRandomLocation(Vector2 borderGap, vector<Piece>& player)
		{
			bool validPosition = false;

			while (!validPosition)
			{
				validPosition = true;

				int x = GetRandomValue(0, screenW / TILE_SIZE - 1) * TILE_SIZE + borderGap.x / 2;
				int y = GetRandomValue(0, screenH / TILE_SIZE - 1) * TILE_SIZE + borderGap.y / 2;

				Vector2 newPos = Vector2{ (float)x, (float)y };

				for (int i = 0; i < player.size(); i++)
				{
					if (SamePos(player[i].pos, newPos))
					{
						validPosition = false;
						break;
					}
				}

				if (validPosition)
				{
					pos = newPos;
				}

			}
		}

		void Draw()
		{
			DrawRectangleV(pos, size, color);
		}

		bool GotEaten(Vector2 playerPos)
		{ 
			return abs(playerPos.x - pos.x) < 1 && abs(playerPos.y - pos.y) < 1;
		
		}

		bool SamePos(Vector2 a, Vector2 b)
		{
			return (int)a.x == (int)b.x &&
				(int)a.y == (int)b.y;
		}

	} Fruit;

	Fruit fruit = {0};



	void Main();
	void Update();
	void Start();
	void Interaction();
	void Draw();
	void ResetGame();



};