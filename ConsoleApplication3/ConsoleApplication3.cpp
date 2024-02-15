// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <random>
#include <time.h>


using namespace std;

string map[20][20];
int tail[20][2];
int fruit[2];
int j, i, headY = 10, headX = 9, dir = 80, LenTail = 3;
bool playing = true, isfruit = true;




void render() {
	Sleep(200);
	system("cls");
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
}

void controller() {
	while (playing) {	
		dir = _getch();
		
	}
}

void move() {

		switch (dir) {
		case 72: //UP
			headX--;
			break;
		case 80: //DOWN
			headX++;
			break;
		case 75: //LEFT
			headY--;
			break;
		case 77: //RIGHT
			headY++;
			break;
	}
	

}

void constructor() {
	//Map
	for (i = 1; i < 19; i++) {
		for (j = 1; j < 19; j++) {
			map[i][j] = " ";
		}

	}
	//Borders
	for (i = 0; i < 20; i++) {
		map[i][19] = "#";
		map[i][0] = "#";
		map[19][i] = "#";
		map[0][i] = "#";
	}
	//Snake
	map[headX][headY] = "0";
	for (i = LenTail; i >= 1; i--) {
		map[tail[i][0]][tail[i][1]] = "o";
		
	}
	//Fruit
	map[fruit[0]][fruit[1]] = "&";

}

void MkTail() {
	for (i = LenTail; i >= 1; i--) {
		tail[i][0] = tail[i - 1][0];
		tail[i][1] = tail[i - 1][1];
	}
	tail[0][0] = headX;
	tail[0][1] = headY;
}

void eat() {
	for (i = LenTail + 1; i >= 1; i--) {
		tail[i][0] = tail[i - 1][0];
		tail[i][1] = tail[i - 1][1];
	}
	LenTail++;
	isfruit = 0;
	fruit[0] = 21;
	fruit[1] = 21;
}

void MkFruit() {
	int fpx, fpy, f = 0;
	while (f == 0) {
		fpx = (rand() % 18)+1;
		fpy = (rand() % 18)+1;
		if (map[fpx][fpy] != "o" && map[fpx][fpy] != "0") {
			fruit[0] = fpx;
			fruit[1] = fpy;
			f = 1;
			isfruit = true;
		}
	}
	
	

}
void colision() {
	if (map[headX][headY] == "o" || map[headX][headY] == "#")
		playing = false;
		
}

void mechanics() {
	srand(time(0));
	//debug << "Mechanics" << '\n';

	//Makes The Fruit
	if (!isfruit) {
		//debug << "RUN" << "\n";
		MkFruit();
	}

	//Checks The Fruit
	if (headX == fruit[0] && headY == fruit[1]) {
		eat();
	}

	//Checks Colisions
	colision();
}

void YouLostScreen() {
	system("cls");
	cout << "\n\n\n           YOU LOST !         \n\n           Press Anything Yo Continue\n";

}


int main()

{
	//Tail Initialization
	tail[0][0] = 9;
	tail[0][1] = 10;
	tail[1][0] = 8;
	tail[1][1] = 10;
	tail[2][0] = 7;
	tail[2][1] = 10;
	tail[3][0] = 6;
	tail[3][1] = 10;
	//End Of Tail Initialization

	//Fruit Initialization
	fruit[0]= 15;
	fruit[1]= 15;
	//End Of Tail Initialization

	//Map Initialization
	for (i = 1; i < 19; i++) {
		for (j = 1; j < 19; j++) {
			map[i][j] = " ";
		}
		
	}
	for (i = 0; i < 20; i++) {
		map[i][19] = "#";
		map[i][0] = "#";
		map[19][i] = "#";
		map[0][i] = "#";
	}
	//End Of Map Initialization

	render();
	thread t1(controller);
	
	//thread t2(move);
	//t1.join();

	while (playing) {
		move();
		mechanics();
		MkTail();
		constructor();
		render();
	}
	t1.detach();
	YouLostScreen();


	i = _getch();

    return 0;
}

