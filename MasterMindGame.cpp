#include <iostream>

using namespace std;

#include "MasterMind.h"
#include <hge.h>
#include <Windows.h>
#include <hgeresource.h>
#include <hgesprite.h>
#include <hgefont.h>
#pragma comment(lib, "hge.lib")
#pragma comment(lib, "hgehelp.lib")

HGE *hge = NULL;
hgeFont* font;
hgeSprite* bgSprite = NULL;
hgeSprite* blueMarbleSprite = NULL;
hgeSprite* whiteMarbleSprite = NULL;
hgeSprite* orangeMarbleSprite = NULL;
hgeSprite* blackMarbleSprite = NULL;
hgeSprite* redMarbleSprite = NULL;
hgeSprite* greenMarbleSprite = NULL;
hgeSprite* menuSprite = NULL;
hgeSprite* checkSprite = NULL;
hgeSprite* existSprite = NULL;
hgeSprite* correctPosSprite = NULL;
hgeSprite* bg = NULL;
hgeSprite* startMenu = NULL;
hgeSprite* board = NULL;
hgeSprite* helpMenu = NULL;
hgeSprite* continueMenu = NULL;
hgeSprite* menuButtonSprite = NULL;
hgeResourceManager* myRes = NULL;
using namespace std;
bool done = false;
bool gameWon = false;
bool gameLost = false;
bool answerMade = false;
bool roundIncrease = false;
bool checkAvailable = false;
bool startGame = false;
bool help = false;
bool showAnswer = false;
bool showMenu = false;
float mouseX = 0;
float mouseY = 0;
float x = 300;
float y = 100;
float arrowPos = y+20;
int nrExist = 0;
int nrCorrectPos = 0;
int position = 5;
int control[10][2];
MasterMind player;
string color = "Undecided";

bool enableCheats = false;

bool UpdateGame()
{
	int checkShow = 0;

	if (startGame == true)
	{
		if (answerMade == false)			//kollar om ett svar har skapats om inte så skapas ett nytt
		{
			player.createAnswer();
			answerMade = true;
			for (int i = 0; i < 10; i++)
			{
				for (int n = 0; n < 2; n++)
				{
					control[i][n] = 0;
				}
			}

		}
		if (help == true)
		{
			if (hge->Input_GetKey() == HGEK_LBUTTON)
			{
				hge->Input_GetMousePos(&mouseX, &mouseY);
				if (mouseX >= 340 && mouseX <= 554)
				{
					if (mouseY >= 340 && mouseY <= 395)
					{
						help = false;
					}
				}
			}
		}
		else if (showMenu == true)
		{
			if (hge->Input_GetKey() == HGEK_LBUTTON)
			{
				hge->Input_GetMousePos(&mouseX, &mouseY);
				if (mouseY >= 325 && mouseY <= 377)				//kollar om musen finns innanför help rutan
				{
					if (mouseX >= 340 && mouseX <= 430)
					{
						help = true;
					}
				}
				else if (mouseY >= 395 && mouseY <= 450)			//kollar om musen finns innanför continue game rutan
				{
					if (mouseX >= 340 && mouseX <= 554)
					{
						showMenu = false;
					}
				}
				else if (mouseY >= 205 && mouseY <= 250)			//kollar om musen finns innanför restart rutan
				{
					if (mouseX >= 345 && mouseX <= 475)
					{
						player.clear();
						nrExist = 0;
						nrCorrectPos = 0;
						gameLost = false;
						gameWon = false;
						answerMade = false;
						showAnswer = false;
						showMenu = false;
					}
				}
				else if (mouseY >= 268 && mouseY <= 313)			//kollar om musen finns innanför end game rutan	
				{
					if (mouseX >= 345 && mouseX <= 475)
					{
						done = true;
					}

				}
			}

		}
		else
		{
			if (roundIncrease == true)
			{
				player.setNrOfRounds(player.getNrOfRounds() + 1);
				roundIncrease = false;
			}
			if (player.getNrOfRounds() >= 9)
			{
				gameLost = true;
			}
			arrowPos = (104 + (player.getNrOfRounds() * 50) + 10);

			if (hge->Input_GetKey() == HGEK_LBUTTON)
			{
				hge->Input_GetMousePos(&mouseX, &mouseY);

				if (mouseX >= 10 && mouseX <= 110)
				{
					if (mouseY >= 345 && mouseY <= 398)
					{

						showMenu = true;

					}
				}
				if (mouseX >= 10 && mouseX <= 152)		//kollar om musen finns innanför check rutan och óm den finns  					
				{
					if (mouseY >= 296 && mouseY <= 332)
					{
						if (checkAvailable == true)
						{
							nrExist = player.checkAmountExist();		//kollas hur många som finns med
							if (nrExist > 0)
							{
								nrCorrectPos = player.checkCorrectPos();		//kollas hur många som finns på rätt position
								if (nrCorrectPos == 5)
								{
									gameWon = true;
								}
							}
							control[player.getNrOfRounds()][0] = nrExist;
							control[player.getNrOfRounds()][1] = nrCorrectPos;
							roundIncrease = true;

						}
					}
				}

				if (mouseX >= 10 && mouseX <= 59)			//kollar om musen finns innanför någon av kulorna för att bestämma vilken färg man valt
				{
					if (mouseY >= 110 && mouseY <= 155)
					{
						color = "Blue";
					}
					else if (mouseY >= 60 && mouseY <= 105)
					{
						color = "Green";
					}
					else if (mouseY >= 10 && mouseY <= 55)
					{
						color = "Red";
					}
				}
				else if (mouseX >= 60 && mouseX <= 105)
				{

					if (mouseY >= 60 && mouseY <= 105)
					{
						color = "White";
					}
					else if (mouseY >= 110 && mouseY <= 155)
					{
						color = "Orange";
					}
					else if (mouseY >= 10 && mouseY <= 55)
					{
						color = "Black";
					}
				}
				if (mouseY >= (104 + player.getNrOfRounds() * 50) && mouseY <= 103 + (player.getNrOfRounds() + 1) * 50)	//kollar om musen finns innanför den aktualla rutorna spm väljer positionen
				{
					if (mouseX >= 345 && mouseX <= 395)
					{
						position = 0;
					}
					else if (mouseX >= 396 && mouseX <= 446)
					{
						position = 1;
					}
					else if (mouseX >= 447 && mouseX <= 497)
					{
						position = 2;
					}
					else if (mouseX >= 498 && mouseX <= 548)
					{
						position = 3;
					}
					else if (mouseX >= 549 && mouseX <= 599)
					{
						position = 4;
					}
				}
			}
			if (color != "Undecided" && position < 5)
			{
				player.makeGuess(color, position);
				position = 5;
				color = "Undecided";
			}
			for (int i = 0; i < 5; i++)	//kollar om 5 färger har valts
			{
				if (player.getGuess(i, player.getNrOfRounds()) != "Unknown")
				{
					checkShow++;
				}

			}
			if (checkShow >= 5)	//om 5 färger valts så visas check knappen
			{
				checkAvailable = true;
			}
			else
			{
				checkAvailable = false;
			}
		}
	}
	else
	{
		if (hge->Input_GetKey() == HGEK_LBUTTON)
		{
			hge->Input_GetMousePos(&mouseX, &mouseY);
			if (mouseX >= 300 && mouseX <= 480)
			{
				if (mouseY >= 340 && mouseY <= 390)
				{
					startGame = true;
				}
			}
		}
	}
	if (enableCheats)
	{
		//kontroll knappar för att snabbt kunna få upp en vinst/förlust samt svaret
		if (hge->Input_GetKey() == HGEK_F1)
		{
			if (showAnswer == false)
			{
				showAnswer = true;
			}
			else
			{
				showAnswer = false;
			}
		}
		else if (hge->Input_GetKey() == HGEK_F2)
		{
			if (gameWon == false)
			{
				gameWon = true;
			}
		}
		else if (hge->Input_GetKey() == HGEK_F3)
		{
			if (gameLost == false)
			{
				gameLost = true;
			}
		}
		if (hge->Input_GetKey() == HGEK_ESCAPE)	//visar menyn om esc trycks
		{
			showMenu = true;
		}
	}
	return done;
}
bool RenderGame()
{
	
	string thisColor = "Unknown";
	float correctX = 250;
	float correctY = 0;
	hge->Gfx_BeginScene();
	font->SetColor(ARGB(255,0,0,0));
	font->SetScale(1.0);
	hge->Gfx_Clear(0xff000000);
	bgSprite->RenderStretch(0, 0, 800, 600);
	if(startGame == false)
	{
		font->SetScale(1.0);
		font->printf(20, 100, HGETEXT_LEFT, "Mastermind is designed so that the codebreaker (the player)");
		font->printf(20, 120, HGETEXT_LEFT, "tries to guess the correct pattern in both order and color.");
		font->printf(20, 140, HGETEXT_LEFT, "The correct pattern has been chosen by the computer.");
		font->printf(20, 160, HGETEXT_LEFT, "You choose color by clicking the marbles on the left side of the screen");
		font->printf(20, 180, HGETEXT_LEFT, "And choose the position by clicking in the boxes in the middle of the screen ");
		font->printf(20, 200, HGETEXT_LEFT, "the ones that are equal size and where the arrow is pointing ");
		font->printf(20, 220, HGETEXT_LEFT, "When you have choosen five colors and feel you are done press the Check box on the left side of the screen ");
		font->printf(20, 240, HGETEXT_LEFT,"the box will appear when five colors on different positions have been choosen.");
		font->printf(20, 260, HGETEXT_LEFT, "After you've pressed the Check box the correct amount of pegs will appear ");
		font->printf(20, 280, HGETEXT_LEFT, "Showing how many of the colors are on the correct position");
		font->printf(20, 300, HGETEXT_LEFT, "And how many color exist but are in the wrong position.");
		font->printf(20, 320, HGETEXT_LEFT, "Pressing the escape key will bring you to the menu." );
		startMenu->Render(300, 340);
		existSprite->Render(440, 305);
		correctPosSprite->Render(440, 285);

	}
	else if(help == true)
	{
		font->SetScale(1.0);
		font->printf(20, 100, HGETEXT_LEFT, "Mastermind is designed so that the codebreaker (the player).");
		font->printf(20, 120, HGETEXT_LEFT, "tries to guess the correct pattern in both order and color.");
		font->printf(20, 140, HGETEXT_LEFT, "The correct pattern has been chosen by the computer ");
		font->printf(20, 160, HGETEXT_LEFT, "You choose color by clicking the marbles on the left side of the screen");
		font->printf(20, 180, HGETEXT_LEFT, "And choose the position by clicking in the boxes in the middle of the screen ");
		font->printf(20, 200, HGETEXT_LEFT, "the ones that are equal size and where the arrow is pointing ");
		font->printf(20, 220, HGETEXT_LEFT, "When you have choosen five colors and feel you are done press the Check box on the left side of the screen ");
		font->printf(20, 240, HGETEXT_LEFT,"( the box will appear when five colors on different positions have been choosen).");
		font->printf(20, 260, HGETEXT_LEFT, "After you've pressed the Check box the correct amount of pegs will appear ");
		font->printf(20, 280, HGETEXT_LEFT, "Showing how many of the colors are on the correct position");
		font->printf(20, 300, HGETEXT_LEFT, "And how many color exist but are in the wrong position.");
		font->printf(20, 320, HGETEXT_LEFT, "Pressing the escape key will bring you to the menu." );
		continueMenu->Render(300, 340);
		existSprite->Render(440, 305);
		correctPosSprite->Render(440, 285);
	}
	else if(showMenu == true)
	{
		menuSprite->Render(340, 200);
		helpMenu->Render(341, 330);
		continueMenu->Render(341, 390);
	}
	else
	{
		blueMarbleSprite->Render(10, 110);
		whiteMarbleSprite->Render(60, 60);
		blackMarbleSprite->Render(60, 10);
		redMarbleSprite->Render(10, 10);
		orangeMarbleSprite->Render(60, 110);
		greenMarbleSprite->Render(10, 60);
		menuButtonSprite->Render(10, 345);
		board->Render(250, 0);
		font->SetScale(1.5);
		if(player.getNrOfRounds() != 9)
		{
			font->printf(600, arrowPos, HGETEXT_LEFT, " <--");
		}
		font->SetScale(1.0);
		if(checkAvailable == true)
		{
			checkSprite->Render(8, 290);
		}
		if(gameWon == true)
		{
			bg->Render(0, 0);
			font->SetScale(1.2);
			font->printf(10, 10, HGETEXT_LEFT, "Congratulation ");
			font->printf(10, 30, HGETEXT_LEFT, "You managed");
			font->printf(10, 50, HGETEXT_LEFT, "to figure out"); 
			font->printf(10, 70, HGETEXT_LEFT,"The correct pattern");
			font->printf(255, 30, HGETEXT_LEFT, "Answer -> ");
			font->SetScale(1.0);
			for(int i = 0; i < 5; i++)
			{
				thisColor = player.getAnswer(i);
				x = 350 + (i*50);
				y = 10 ;
				if(thisColor != "Unknown")
				{
					if(thisColor == "Blue")
					{
						blueMarbleSprite->Render(x, y);
					}
					else if(thisColor == "White")
					{
						whiteMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Orange")
					{
						orangeMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Green")
					{
						greenMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Red")
					{
						redMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Black")
					{
						blackMarbleSprite->Render(x, y);
					}
				}
			}
		}
		else if(gameLost == true)
		{
			bg->Render(0, 0);
			font->SetScale(1.2);
			font->printf(10, 10, HGETEXT_LEFT, "You didnt manage"); 
			font->printf(10, 30, HGETEXT_LEFT, "to figure out");
			font->printf(10, 50, HGETEXT_LEFT, "the correct pattern");
			font->printf(255, 30, HGETEXT_LEFT, "Answer -> ");
			font->SetScale(1.0);
			for(int i = 0; i < 5; i++)
			{
				thisColor = player.getAnswer(i);
				x = 350 + (i*50);
				y = 10 ;
				if(thisColor != "Unknown")
				{
					if(thisColor == "Blue")
					{
						blueMarbleSprite->Render(x, y);
					}
					else if(thisColor == "White")
					{
						whiteMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Orange")
					{
						orangeMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Green")
					{
						greenMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Red")
					{
						redMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Black")
					{
						blackMarbleSprite->Render(x, y);
					}
				}
			}
		}
		if(showAnswer == true)
		{
			for(int i = 0; i < 5; i++)
			{
				thisColor = player.getAnswer(i);
				x = 350 + (i*50);
				y = 10 ;
				if(thisColor != "Unknown")
				{
					if(thisColor == "Blue")
					{
						blueMarbleSprite->Render(x, y);
					}
					else if(thisColor == "White")
					{
						whiteMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Orange")
					{
						orangeMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Green")
					{
						greenMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Red")
					{
						redMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Black")
					{
						blackMarbleSprite->Render(x, y);
					}
				}
			}
		}
		for(int n = 0; n < (player.getNrOfRounds() + 1); n++)
		{
			for(int i = 0; i < 5; i++)
			{
				thisColor = player.getGuess(i, n);
				x = 350 + (i*50);
				y = 103 + (n*50);
				if(thisColor != "Unknown")
				{
					if(thisColor == "Blue")
					{
						blueMarbleSprite->Render(x, y);
					}
					else if(thisColor == "White")
					{
						whiteMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Orange")
					{
						orangeMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Green")
					{
						greenMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Red")
					{
						redMarbleSprite->Render(x, y);
					}
					else if(thisColor == "Black")
					{
						blackMarbleSprite->Render(x, y);
					}
				}
			}
			if(control[n][0] > 0)			
			{
				correctY = y + 10;
				correctX = 252;
				nrExist = control[n][0];
				nrCorrectPos = control[n][1];
				nrExist -= nrCorrectPos; 
				for(int i = 0; i < nrCorrectPos; i++)
				{
					correctPosSprite->Render(correctX, correctY);
					correctX += 20;
				}
				for(int m = 0; m < nrExist; m++)
				{
					existSprite->Render(correctX, correctY);
					correctX += 20;
				}
			}
		}
		
	}
	hge->Gfx_EndScene();
	return false;
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_TITLE, "MasterMind");
	hge->System_SetState(HGE_FRAMEFUNC, UpdateGame);
	hge->System_SetState(HGE_RENDERFUNC, RenderGame);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);

	if(hge->System_Initiate())
	{
		myRes = new hgeResourceManager("Resource.res");
		
		font = myRes->GetFont("font");
		bgSprite = myRes->GetSprite("bgSprite");
		whiteMarbleSprite = myRes->GetSprite("WhiteMarbleSprite");
		blueMarbleSprite = myRes->GetSprite("BlueMarbleSprite");
		orangeMarbleSprite = myRes->GetSprite("OrangeMarbleSprite");
		blackMarbleSprite = myRes->GetSprite("BlackMarbleSprite");
		redMarbleSprite = myRes->GetSprite("RedMarbleSprite");
		greenMarbleSprite = myRes->GetSprite("GreenMarbleSprite");
		menuSprite = myRes->GetSprite("OptionMenu");
		existSprite = myRes->GetSprite("Exist");
		correctPosSprite = myRes->GetSprite("CorrectPos");
		bg = myRes->GetSprite("White");
		checkSprite = myRes->GetSprite("CheckMenu");
		startMenu = myRes->GetSprite("StartGame");
		board = myRes->GetSprite("Board");
		helpMenu = myRes->GetSprite("Help");
		continueMenu = myRes->GetSprite("Continue");
		menuButtonSprite = myRes->GetSprite("MenuButton");
		hge->System_Start();
	}
	else
	{
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}
	delete myRes;
	hge->System_Shutdown();
	hge->Release();
	return 0;



}