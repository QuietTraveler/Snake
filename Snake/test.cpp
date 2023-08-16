#include"snake.h"
#include"TimerClock.h"
TimerClock t1, t2;

int main()
{
	srand((unsigned int)time(NULL));
	initgraph(MAPW, MAPH);
	InitSnake();
	InitMap();
	InitFood();
	int ret = ALIVE;
	int conse = CONTINUE;
	while (conse)
	{ 
		ProduceFood();
		Draw();
		Input();
	    if ( t2.getMilliSec() > SPEED )
		{
		ret = Move();
		t2.update();
		}
		conse = IsStates(ret);
		t1.update();
		while (t1.getMilliSec() < SENSITIVITY);
	}
	return 0;
}