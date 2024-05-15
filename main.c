#include <raylib.h>

typedef enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  ENDING 
} GameScreen;

typedef enum Directions {
  NORTH = 0,
  EAST,
  SOUTH,
  WEST,
} Directions;

typedef enum Collisions {
  NO_COLLISION = 0,
  COLLISION,
} Collisions;

typedef struct Player {
  Vector2 position;
  Directions dir;
  Collisions collision;
  int size;
  int length;
  int speed;
} Player;

void player_update(Player *player, float delta);
void player_check_collisions(Player *player);

const int screenWidth = 800;
const int screenHeight = 450;

int main(void) {
  InitWindow(screenWidth, screenHeight, "MyWindow");
  SetTargetFPS(60);
  SetExitKey(0);

  Player player = {0};
  player.speed = 200.0f;
  player.length = 5;
  player.dir = NORTH;
  player.size = 25;
  player.collision = NO_COLLISION;
  player.position = (Vector2){ screenWidth/2-player.size, screenHeight/2-player.size };

  GameScreen currentScreen = TITLE;

  while(!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    switch(currentScreen) {
      case TITLE:
        {
          if (IsKeyPressed(KEY_ENTER)) {
            currentScreen = GAMEPLAY;
          }
        } break;
      case GAMEPLAY:
        {
          if (player.collision == COLLISION) {
            currentScreen = ENDING;
          }
        } break;
      case ENDING:
        {
          player.collision = NO_COLLISION;
          player.position = (Vector2){ screenWidth/2-player.size, screenHeight/2-player.size };

          if (IsKeyPressed(KEY_ENTER)) {
            currentScreen = GAMEPLAY;
          }
        } break;
      default: break;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    switch(currentScreen) {
      case TITLE:
        {
          DrawText("Snake", 20, 20, 40, RAYWHITE);
          DrawText("Press enter to start.", 20, 60, 40, RAYWHITE);
        } break;
      case GAMEPLAY:
        {
          player_update(&player, deltaTime);
          player_check_collisions(&player);
        } break;
      case ENDING:
        {
          DrawText("Snake dead", 20, 20, 40, RAYWHITE);
          DrawText("Press enter to go again.", 20, 60, 40, RAYWHITE);
        } break;
      default: break;
    }

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void player_update(Player *player, float delta) {
  for(int i = 0; i < player->length; ++i) {
    DrawRectangle(player->position.x + (i*player->size), player->position.y, player->size, player->size, RAYWHITE);
  }

  if (IsKeyDown(KEY_LEFT)) player->dir = WEST;
  if (IsKeyDown(KEY_RIGHT)) player->dir = EAST;
  if (IsKeyDown(KEY_UP)) player->dir = NORTH;
  if (IsKeyDown(KEY_DOWN)) player->dir = SOUTH;

  switch (player->dir) {
    case NORTH:
      player->position.y -= player->speed*delta;
      break;
    case EAST:
      player->position.x += player->speed*delta;
      break;
    case SOUTH:
      player->position.y += player->speed*delta;
      break;
    case WEST:
      player->position.x -= player->speed*delta;
      break;
    default: break;

  }
}

void player_check_collisions(Player *player) {
  if (player->position.y < 0 || player->position.y > screenHeight) player->collision = COLLISION;
  if (player->position.x < 0 || player->position.x > screenWidth) player->collision = COLLISION;
}
