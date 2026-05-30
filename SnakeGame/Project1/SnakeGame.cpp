#include "SnakeGame.h"
#include <raylib.h>

void SnakeGame::Start()
{
	Piece head1;
	head1.color = GREEN;
	head1.pos = Vector2{ borderGap.x / 2, borderGap.y / 2 };
	player.push_back(head1);

	Main();

}

void SnakeGame::ResetGame()
{
	player.clear();

	Piece head;
	head.color = GREEN;
	head.pos = Vector2{ borderGap.x / 2, borderGap.y / 2 };

	player.push_back(head);

	speed = Vector2{ TILE_SIZE, 0 };
	gameOver = false;
	gamePause = false;
	canMove = false;
	frameCount = 0;
	fruit.active = false;
}

void SnakeGame::Main()
{

	InitWindow(screenW, screenH, "First Window");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();
		BeginDrawing();
		ClearBackground(DARKGRAY);

		
		Draw();
		EndDrawing();

	}



	CloseWindow();

}

void SnakeGame::Update()
{
	Interaction();
	if (!gamePause)
	{
		frameCount++;
		

		if (frameCount % 20 == 0)
		{
			for (int i = player.size() - 1; i > 0; i--)
			{
				player[i].pos = player[i - 1].pos;
			}


			player[0].pos += speed;

			for (int i = 1; i < player.size(); i++)
			{
				if (player[0].pos == player[i].pos)
				{
					gameOver = true;
				}
			}

			if (player.size() >= totalCells)
			{
				gameWon = true;
			}

			canMove = true;
		}

		if (player[0].pos.x + TILE_SIZE > screenW - borderGap.x / 2 ||
			player[0].pos.x < borderGap.x / 2 ||
			player[0].pos.y + TILE_SIZE > screenH - borderGap.y / 2 ||
			player[0].pos.y < borderGap.y / 2)
		{
			gameOver = true;
		}

		if (!fruit.active)
		{
			fruit.active = true;
			fruit.NewRandomLocation(borderGap, player);

		}

		if (fruit.GotEaten(player[0].pos))
		{
			fruit.active = false;
			Piece newPiece;
			newPiece.color = DARKGREEN;
			player.push_back(newPiece);
		}
	}
	



}

void SnakeGame::Draw()
{
	if (gameOver)
	{
		int txtSize = MeasureText("GAME OVER", 50);
		DrawText("GAME OVER!", screenW / 2 - txtSize / 2, screenH / 2 - 50, 50, RED);
		txtSize = MeasureText("PRESS R TO RESTART", 50);
		DrawText("PRESS R TO RESTART", screenW / 2 - txtSize / 2, screenH / 2 + 10, 50, RED);
		return;
	}

	if (gameWon)
	{
		int txtSize = MeasureText("YOU WON!!!", 50);
		DrawText("YOU WON!!!", screenW / 2 - txtSize / 2, screenH / 2 - 50, 50, SKYBLUE);
		txtSize = MeasureText("PRESS R TO RESTART", 50);
		DrawText("PRESS R TO RESTART", screenW / 2 - txtSize / 2, screenH / 2 + 10, 50, SKYBLUE);
		return;
	}



	for (int i = 0; i < screenW / TILE_SIZE + 1; i++)
	{
		int yTop = borderGap.y / 2;
		int yBottom = screenH - borderGap.y / 2;

		int x = borderGap.x / 2 + i * TILE_SIZE;

		Vector2 start = Vector2{ (float)x,(float)yTop };
		Vector2 end = Vector2{ (float)x,(float)yBottom };



		DrawLineV(start, end, BLACK);
	}

	for (int i = 0; i < screenH / TILE_SIZE + 1; i++)
	{
		int xLeft = borderGap.x / 2;
		int xRight = screenW - borderGap.x / 2;

		int y = borderGap.y / 2 + i * TILE_SIZE;

		Vector2 start = Vector2{ (float)xLeft, (float)y };
		Vector2 end = Vector2{ (float)xRight, (float)y };

		DrawLineV(start, end, BLACK);
	}

	for (Piece head : player)
	{
		head.Draw();
	}

	fruit.Draw();

	if (gamePause)
	{
		int txtSize = MeasureText("GAME PAUSED", 50);
		DrawText("GAME PAUSED", screenW / 2 - txtSize / 2, screenH / 2 - 50, 50, PURPLE);
		txtSize = MeasureText("PRESS P TO UNPAUSE", 50);
		DrawText("PRESS P TO UNPAUSE", screenW / 2 - txtSize / 2, screenH / 2 + 10, 50, PURPLE);
		return;
	}


}



void SnakeGame::Interaction()
{

	if (IsKeyPressed(KEY_P))
	{
		gamePause = !gamePause;
	}
	
	if (IsKeyPressed(KEY_R) && gameOver || IsKeyPressed(KEY_R) && gameWon)
	{
		ResetGame();
	}

	if (gamePause || gameOver || gameWon)
	{
		return;
	}

	if (canMove)
	{
		if (IsKeyPressed(KEY_DOWN) && speed.y == 0)
		{

			speed = Vector2{ 0,TILE_SIZE }; 
			canMove = false;
		}
		if (IsKeyPressed(KEY_UP) && speed.y == 0)
		{
			speed = Vector2{ 0,-TILE_SIZE };
			canMove = false;
		}
		if (IsKeyPressed(KEY_LEFT) && speed.x == 0)
		{
			speed = Vector2{ -TILE_SIZE,0 };
			canMove = false;
		}
		if (IsKeyPressed(KEY_RIGHT) && speed.x == 0)
		{
			speed = Vector2{ TILE_SIZE,0 };
			canMove = false;
		}
	}

}

