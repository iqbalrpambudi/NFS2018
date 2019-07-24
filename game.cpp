#include "car.h"
#include "truck.h"
#include "global.h"
#include "misc.h"

#include <sl.h>
#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>
//====================================//CREATE OBJECT\\===============================
Car car(200,100);				//car
truck vehicle(200,400,2);		//vehcile
truck vehicle2(250,600,2.5);	//vehicle 2

misc tree1(365,700,1);			//tree 1
misc tree2(365,900,1);			//tree 2
misc tree3(365,1100,1);			//tree 3

misc coins(66,750,2);			//coins
misc gasoline(100,2500,2);		//gasoline
//=================================================================================

//state game
enum GameState:int {Start, CarSelect,Play, Pause, GameOver};
GameState state = GameState::Start;

int road;
int font;
int sfxmusic;
int sfxcrash;
int sfxcoins;
int IcoCoin;
int IcoGasoline;
std::string player;

//score
int score=0;
int count=0;
int hiscore = 0;
int fuel=20;

//prototype
void info();
void key();
bool isCollide(object* e1, object* e2,const double h);

namespace game
{
	void init()
	{
		
		std::cout << "	||===============================================================||\n";
		std::cout << "	||     ___   __   _____   _____     _____   ____   __   ____     ||\n";
		std::cout << "	||    /   | / /  / ___/  /  __/    /__  /  /   /  / /  /   /     ||\n";
		std::cout << "	||   / /| |/ /  / __/   /__  /    /  __/  /   /  / /  /---/      ||\n";
		std::cout << "	||  /_/ |___/  /_/     /____/    /____/  /___/  /_/  /___/       ||\n";
		std::cout << "	||===============================================================||\n";
		std::cout << "	||                 ''Not   For   Speed   2018''                  ||\n";
		std::cout << "	||===============================================================||\n";
		std::cout << "	|| v1.0                                                          ||\n";
		std::cout << "	||===============================================================||\n\n";


		//set name player
		std::cout << "		Your nickname: ";
		std::getline(std::cin, player);
		if (player == "")
			player = "Noname";

		//create windows
		std::cout <<		"		creating windows...\n";
		slWindow(480, 640, "Not For Speed 2018 v1.0", false);
		slSetBackColor(0, 0.4, 0.2);

		//load texture & font
		std::cout<<"		loading texture...\n";
		car.loadTexture();
		vehicle.loadTexture();
		vehicle2.loadTexture();
		tree1.loadTexture();
		tree2.loadTexture();
		tree3.loadTexture();
		coins.loadTextureCoins();
		gasoline.loadTextureGasoline();

		road=slLoadTexture(TEX_ROAD);
		font=slLoadFont(FNT_STYLE);
		IcoCoin=slLoadTexture(TEX_COINS);
		IcoGasoline=slLoadTexture(TEX_GASOLINE);
		slSetFont(font,20);

		//load audio
		std::cout<<"		loading audio...\n";
		sfxmusic=slLoadWAV(SFX_MUSIC);
		sfxcrash=slLoadWAV(SFX_CRASH);
		sfxcoins=slLoadWAV(SFX_COINS);

		//play game music
		slSoundLoop(sfxmusic);

		//set object speed
		vehicle.setTruckSpd(-3);
		vehicle2.setTruckSpd(-2);
		tree1.setMiscSpd(-1);
		tree2.setMiscSpd(-1);
		tree3.setMiscSpd(-1);
		coins.setMiscSpd(-4);
		gasoline.setMiscSpd(-6);
	}


	void run()
	{
		std::cout << "		Game: Run\n";
		while (!slShouldClose())
		{

			//draw road texrure
			slSprite(road,SCR_W/2,SCR_H/2,SCR_W,SCR_H);

			//draw car & vehicles texture
			car.draw();
			vehicle.draw();
			vehicle2.draw();

			//draw miscellaneous
			tree1.draw();
			tree2.draw();
			tree3.draw();
			coins.drawcoins();
			gasoline.drawgasoline();

			//draw info & key
			info();
			key();

			//state play
			if(state ==GameState::Play)
				{
					//update car & vehicle
					
					car.update();
					vehicle.update();
					vehicle2.update();

					//update miscellaneous
					tree1.update();
					tree2.update();
					tree3.update();
					coins.updatecoins();
					gasoline.updatecoins();
					//penghitung score
					count++;
					if(count==100)
					{
						score++;
						count=0;
					}

					if(count==30)
					{
						fuel--;
					}

					//mengecek apakah 2 objek bertabrakan
					if (isCollide(&car, &vehicle,50.0))
						{
							if(score>=hiscore)
							{
								hiscore=score;
							}
							slSoundPlay(sfxcrash);
							state = GameState::GameOver;
							std::cout<<"		*Game Over!\n";
						}

					if (isCollide(&car, &vehicle2,50.0))
						{
							if(score>=hiscore)
							{
								hiscore=score;
							}
							slSoundPlay(sfxcrash);
							state = GameState::GameOver;
							std::cout<<"		*Game Over!\n";
						}
					if (isCollide(&car, &coins,40.0))
						{
							score+=10;
							coins.resetCoins();
							slSoundPlay(sfxcoins);
						}
					if (isCollide(&car, &gasoline,40.0))
						{
							fuel+=5;
							gasoline.resetGasoline();
							slSoundPlay(sfxcoins);
						}
					if(fuel==0)
					{
						state = GameState::GameOver;
					}

				}

			slRender();
		}

	}

	void end()
	{
		std::cout<<"		Game End\n";
	}

}
void key()
{
	if (state == GameState::Start)
	{
		if (slGetKey(SL_KEY_ENTER))
			state = GameState::Play;
	}

	else if (state==GameState::CarSelect)
	{

	}

	else if (state == GameState::Play)
	{
		if(slGetKey(SL_KEY_RIGHT))
			car.control(0.2);
		if(slGetKey(SL_KEY_LEFT))
			car.control(-0.2);
		if (slGetKey('P'))
			state = GameState::Pause;
	}

	else if (state == GameState::Pause)
	{
		// resume:
		if (slGetKey('R'))
		{	
			state = GameState::Play;
		}
	}

	else if (state == GameState::GameOver)
	{
		// replay:
		if (slGetKey('R'))
		{
			//reset all object
			score=0;
			fuel=20;
			state = GameState::Play;
			vehicle.reset();
			vehicle.setTruckSpd(-1.5);
			vehicle2.reset();
			vehicle2.setTruckSpd(-2);
			coins.resetCoins();
			gasoline.resetGasoline();
		}
	}

}

void info()
{
	slSetFontSize(20);
	slSetTextAlign(SL_ALIGN_CENTER);
	slText(SCR_W-50,SCR_H-50, player.c_str());
	slSetFontSize(16);
	slSetTextAlign(SL_ALIGN_CENTER);
	slText(SCR_W-50, SCR_H - 100, "score");
	slText(SCR_W-50, SCR_H - 120, std::to_string(score).c_str());
	slText(SCR_W-50, SCR_H - 150, "hiscore");
	slText(SCR_W-50, SCR_H - 170, std::to_string(hiscore).c_str());
	slText(SCR_W-50, SCR_H - 210, "FUEL");
	slText(SCR_W-50, SCR_H - 230, std::to_string(fuel).c_str());

	if (state == GameState::Start)
	{
		// menampilkan instruksi:
		slSetForeColor(0.0, 0.0, 0.0, 0.7);
		slRectangleFill(SCR_W / 2.0, SCR_H / 2.0, SCR_W, SCR_H);
		slSetFontSize(16);
		slSetTextAlign(SL_ALIGN_CENTER);
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slText(SCR_W / 2, 480, "Drive the Car so as not to crash");
		slText(SCR_W / 2, 460, "using LEFT or RIGHT key.");
		slSprite(IcoCoin,120,405,40,40);
		slSprite(IcoGasoline,120,350,30,40);
		slText(SCR_W / 2+25, 400, "Pick Coins for Extra Score");
		slText(SCR_W / 2+35, 350, "Pick Gasoline for Extra Fuel");
		slText(SCR_W / 2, 256, "Press ENTER to Start");
	}
	else if (state == GameState::GameOver)
	{
		// menampilkan Game Over dan perolehan score:
		slSetForeColor(0.0, 0.0, 0.0, 0.7);
		slSetFontSize(40);
		slSetTextAlign(SL_ALIGN_CENTER);
		slText(SCR_W / 2.0, SCR_H / 2.0, "Game Over");
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(16);
		slText(SCR_W / 2.0 - 10, SCR_H / 2.0 - 25, "Your score:");
		slText(SCR_W / 2.0 + 50, SCR_H / 2.0 - 25, std::to_string(score).c_str());
		slText(SCR_W / 2.0, SCR_H / 2.0 - 60, "Press 'R' to Replay");
		
	}
	else if (state == GameState::Pause)
	{
		// menampilkan informasi instruksi untuk resume game:
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(16);
		slSetTextAlign(SL_ALIGN_CENTER);
		slText(SCR_W / 2.0, SCR_H / 2.0, "Press R to Resume");
	}
	else if (state == GameState::Play)
	{
		// menampilkan informasi instruksi pause game:
		slSetForeColor(1.0, 1.0, 1.0, 1.0);
		slSetFontSize(16);
		slSetTextAlign(SL_ALIGN_RIGHT);
		slText(SCR_W - 15, SCR_H - 25, "Press P to Pause");
	}
}

bool isCollide(object* e1, object* e2,const double h)
{
	return (std::hypot(e1->getX() - e2->getX(), e1->getY() - e2->getY()) <= h);
}