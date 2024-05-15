#include <raylib.h>

typedef struct Node {
  struct Node* next;
  Vector2 position;
} Node;

typedef enum Directions {
  UP = 0,
  RIGHT,
  DOWN,
  LEFT,
} Directions;

typedef enum Collisions {
  NO_COLLISION = 0,
  COLLISION,
} Collisions;

typedef struct Snake {
  Directions direction;
  Collisions collision;
  Node* head;
  int length;
  const int size;
} Snake;

typedef struct Fruit {
  Vector2 position;
} Fruit;

typedef struct Game {
  Snake* snake;
  Fruit* fruit;
  int size;
} Game;

int main(void) {
  return 0;
}
