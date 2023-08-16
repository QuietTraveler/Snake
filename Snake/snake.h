#pragma once
#ifndef Y
#include<stdio.h>
#include<easyx.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define Y 22
#define X  25
#define MAPH   780
#define MAPW  1024
#define MAX (Y*X-(X+Y-2)*2)
#define SIZE 35
#define SENSITIVITY 50
#define SPEED 170

struct position {
	int x;
	int y;
};           //зјБъ

enum {
	EXIT = 0,
	ALIVE,
	ENLONG,
	DEAD,
	CONTINUE
};

#endif 

void InitSnake();
void InitFood();
void InitMap();
void ProduceFood();
void Draw();
void Input();
void Enlongate();
bool Crash(int headx, int heady);
int Move();
int IsStates(int ret);
