#include "iGraphics.h"
#include <windows.h>
#define screenwidth 1344
#define screenheight 760
#define bgSkyspeed 10
#define maxBullets 6

struct Explosion
{
	int x, y;
	int explosionIdx;
	bool active;
	float timer;
};

struct meteorDam
{
	int x, y;
	int explosionIdx;
	bool active;
	float timer;
};

void checkgameOver();
void musicplay();
void musicplay();
void bossMovement();
void gameReset();
void shootbossbullets();
void killingBoss();
void movebossbullets();
void gamedonepage();
void drawaboutPage();
void startButtonClick();
void aboutButtonClick();
void drawScorepage();
void scoreButtonClick();
void backButtonClick();
void drawHomePage();
void changeBg();
void checkbossplayercollision();
void checkgamedone();
void drawTimer();
void renderShield();
void newHighscore();
void drawgameoverpage();
void gameoverpic();
void show_char();
void musicButtonClick();
void drawSettingpage();
void readScore();
void takeInput(unsigned key);
void resetExplosions(Explosion explosions[], int count);
void resetmeteorExplosions(meteorDam explosions[], int explosionCount);

int playershipx = 755, playershipy = 35;
int enemyx1 = 200, enemyy1 = 750;
int enemyx2 = 550, enemyy2 = 750;
int enemyx3 = 700, enemyy3 = 750;
int enemyx4 = 1000, enemyy4 = 750;
int bossX = 640, bossY = 870;
int meteorX1 = 350, meteorY1 = 760;
bool musicOn = true;
int health = 200;
int bossHealth = 200;

int meteorX2 = 790, meteorY2 = 760;
int meteorX3 = 1250, meteorY3 = 760;
int powerX = rand() % 1000, powerY = 750;
int power1X = rand() % 1000, power1Y = 750, timer1 = 0, interval1 = 100;
int enemyCount1 = 0, enemyCount2 = 0, enemyCount3 = 0, meteorCount1 = 0, meteorCount2 = 0;
int shieldDuration = 1000;
bool hasShield = false;
bool hasBullet = false;
bool bossTime = false;
int bulletTimer = 0, shieldTimer = 0, gameScore = 0, homePage = 1, startpage = 0, startButtonclick = 0, aboutButtonclick = 0, aboutPage = 0, scorepage = 0, gameoverpage = 0, settingpage = 0, musicpage = 0, gamecompletepage = 0, musicstate1 = 0, musicstate2 = 0, musicstate3 = 1, bossState = 0;


char bgsky[30][50] = {"tile000.bmp", "tile001.bmp", "tile002.bmp", "tile003.bmp", "tile004.bmp", "tile005.bmp", "tile006.bmp", "tile007.bmp", "tile008.bmp", "tile009.bmp",
					  "tile010.bmp", "tile011.bmp", "tile012.bmp", "tile013.bmp", "tile014.bmp", "tile015.bmp", "tile016.bmp", "tile017.bmp", "tile018.bmp", "tile019.bmp", "tile020.bmp",
					  "tile021.bmp", "tile022.bmp", "tile023.bmp", "tile024.bmp", "tile025.bmp", "tile026.bmp", "tile027.bmp", "tile028.bmp", "tile029.bmp"};

char playership[1][50] = {"playershipnew.bmp"};

char bossShip[1][20] = {"alienship.bmp"};

char fireEffect[5][15] = {"shoot.bmp", "fire14.bmp", "fire16.bmp", "image.bmp", "image1.bmp"};

char enemySpaceship[3][30] = {"enemyshipnew3.bmp", "enemyshipnew1.bmp", "enemyshipnew2.bmp"};

char meteor[3][30] = {"Meteor_02.bmp", "Meteor_07.bmp", "Meteor_10.bmp"};

char explosionEffect[8][30] = {"explosion1.bmp", "explosion2.bmp", "explosion3.bmp", "explosion4.bmp", "explosion5.bmp", "explosion6.bmp", "explosion7.bmp", "explosion8.bmp"};

char meteordamage[3][30] = {"Meteordamage1.bmp", "Meteordamage2.bmp", "Meteordamage1.bmp"};

char enemyExplosion[6][30] = {"enemyexplosion1.bmp", "enemyexplosion2.bmp", "enemyexplosion3.bmp", "enemyexplosion4.bmp", "enemyexplosion5.bmp", "enemyexplosion6.bmp"};

char powerup[2][30] = {"powerup1.bmp", "powerup2.bmp"};

char playershipDamage[10][30] = {"Explosion_1.bmp", "Explosion_2.bmp", "Explosion_3.bmp", "Explosion_4.bmp", "Explosion_5.bmp", "Explosion_6.bmp", "Explosion_7.bmp", "Explosion_8.bmp", "Explosion_9.bmp", "Explosion_10.bmp"};

char alienShip[3][30] = {"alienship.bmp", "alienship2.bmp", "alienship3.bmp"};
char bossExplosion[10][30] = {"exp1.bmp", "exp2.bmp", "exp3.bmp", "exp4.bmp", "exp5.bmp", "exp6.bmp", "exp7.bmp", "exp8.bmp", "exp9.bmp", "exp10.bmp"};
char shield[1][20] = {"shield.bmp"};
char scorecard[1][20] = {"scorecard.bmp"};
char menupic[10][30] = {"aboutme.bmp", "startmenu.bmp", "scoreboard.bmp", "backbutton.bmp"};
char bossbullet[1][15] = {"bossbullet.bmp"};
char gameover[1][15] = {"gameover.bmp"};
char settings[1][30] = {"settings.bmp"};
char startmusic[3][30] = {"musicon.bmp", "startpagemusicon.bmp", "startpagemusicoff.bmp"};
char gamedone[1][30] = {"gamedone.bmp"};

struct background
{
	int x;
	int y;
};

struct BulletFire
{
	int x;
	int y;
};

typedef struct PowerUp
{
	int x, y;
	bool active;
	int timer;
	int imgidx;
};

PowerUp powerups[100];
int powerUpCount = 0;
int powerUpTimer = 0;
int powerUpInterval = 300;

meteorDam meteordamage2[100];
meteorDam meteordamage3[100], meteordamage4[100], meteordamage5[100], meteordamage6[100], meteordamage7[100], meteordamage8[100], meteordamage9[100];
int meteorExpcount2 = 0, meteorExpcount3 = 0, meteorExpcount4 = 0, meteorExpcount5 = 0, meteorExpcount6 = 0, meteorExpcount7 = 0, meteorExpcount8 = 0, meteorExpcount9 = 0;

Explosion explosions[100];
Explosion explosions1[100];
Explosion explosions2[100];
Explosion explosions3[100];
Explosion explosions4[100];
Explosion explosions5[100], explosions6[100], explosions7[100], explosions8[100], explosions9[100], explosions10[100], explosions11[100], explosions12[100], explosions13[100], explosions14[100], explosions15[100], explosions16[100], explosions17[100], explosions18[100], explosions19[100], explosions20[100], explosions21[100], explosions22[100], explosions23[100];
int explosionCount = 0, explosionCount1 = 0, explosionCount2 = 0, explosionCount3 = 0, explosionCount4 = 0, explosionCount5 = 0, explosionCount6 = 0, explosionCount7 = 0, explosionCount8 = 0, explosionCount9 = 0, explosionCount10 = 0, explosionCount11 = 0,
	explosionCount12 = 0, explosionCount13 = 0, explosionCount14 = 0, explosionCount15 = 0, explosionCount16 = 0, explosionCount17 = 0, explosionCount18 = 0, explosionCount19 = 0, explosionCount20 = 0, explosionCount21 = 0, explosionCount22 = 0, explosionCount23 = 0;

BulletFire bullets[50];
BulletFire bullets1[50];
BulletFire bullets2[50];
BulletFire bullets3[50];
BulletFire bullets4[50];
BulletFire bullets5[50];
BulletFire bullets6[50];
BulletFire bullets11[50];
BulletFire bullets22[50];
BulletFire bullets33[50];
BulletFire bullets44[50];
BulletFire bullets55[50];
BulletFire bullets66[50];
int bulletCount = 0, bulletcount1 = 0, bulletcount2 = 0;
int bulletcount11 = 0, bulletcount22 = 0, bulletcount33 = 0, bulletcount44 = 0, bulletcount55 = 0, bulletcount66 = 0;

background backgroundSky[30];

void spawnPowerUp()
{
	if (startpage == 1)
	{
		powerUpTimer += 1;

		if (powerUpTimer >= powerUpInterval)
		{

			powerUpTimer = 0;

			if (powerUpCount < 105)
			{
				powerups[powerUpCount].x = 30 + rand() % 1250;
				powerups[powerUpCount].y = screenheight;
				powerups[powerUpCount].active = true;

				powerups[powerUpCount].imgidx = rand() % 2;
				powerUpCount++;
			}
		}
	}
}

void updatePowerUps()
{
	if (startpage == 1)
	{
		for (int i = 0; i < powerUpCount; i++)
		{
			if (powerups[i].active == true)
			{
				powerups[i].y -= 5;

				if (powerups[i].imgidx == 1)
				{
					iShowBMP2(powerups[i].x, powerups[i].y, powerup[0], 0);
				}
				else
				{
					iShowBMP2(powerups[i].x, powerups[i].y, powerup[1], 0);
				}

				if (powerups[i].y < 0)
				{
					powerups[i].active = false;
				}
			}
		}
	}
}

void powerupWork()
{
	if (startpage == 1)
	{
		for (int i = 0; i < powerUpCount; i++)
		{
			if (powerups[i].active == true && powerups[i].x <= playershipx + 100 && powerups[i].x >= playershipx - 100 && powerups[i].y <= playershipy + 100 && powerups[i].y >= playershipy - 100)
			{
				if (powerups[i].imgidx == 0)
				{
					if (!hasShield)
					{
						hasShield = true;
						shieldTimer = 220;
						powerups[i].active = false;
					}
				}

				if (powerups[i].imgidx == 1)
				{
					if (!hasBullet)
					{
						hasBullet = true;
						bulletTimer = 220;
						powerups[i].active = false;
					}
				}
			}
		}
	}
}

void renderShield()
{
	if (startpage == 1)
	{
		if (hasShield == true)
		{
			iShowBMP2(playershipx - 34, playershipy - 25, shield[0], 0);
			shieldTimer--;

			if (shieldTimer <= 0)
			{
				hasShield = false;
			}
		}

		if (hasBullet)
		{
			bulletTimer--;
			if (bulletTimer <= 0)
			{
				hasBullet = false;
			}
		}
	}
}

int score = 0;

void collision()
{
	if (startpage == 1)
	{
		for (int i = 0; i < bulletCount; i++)
		{
			if (!bossTime)
			{
				if (((bullets[i].y + 85) >= enemyy1 && bullets[i].y <= enemyy1 + 85 && bullets[i].x >= enemyx1 - 85 && bullets[i].x <= enemyx1 + 85) ||
					(bullets1[i].y >= enemyy1 - 85 && bullets1[i].y <= enemyy1 + 85 && bullets1[i].x >= enemyx1 - 85 && bullets1[i].x <= enemyx1 + 85))
				{
					if (explosionCount < 100)
					{
						explosions[explosionCount].x = enemyx1 + 40;
						explosions[explosionCount].y = enemyy1 + 20;
						explosions[explosionCount].explosionIdx = 0;
						explosions[explosionCount].active = true;
						explosions[explosionCount].timer = 0.0;
						explosionCount++;
					}
					gameScore += 10;

					enemyy1 = 750;
					enemyx1 = 50 + rand() % 1250;
					bullets[i].y = playershipy + 80;
					bullets[i].x = playershipx + 43;
					bullets1[i].x = playershipx + 95;
					bullets1[i].y = playershipy + 80;
					enemyCount1++;
					break;
				}

				if ((bullets5[i].y >= enemyy1 - 85 && bullets5[i].y <= enemyy1 + 85 && bullets5[i].x >= enemyx1 - 85 && bullets5[i].x <= enemyx1 + 85))
				{
					if (explosionCount6 < 100)
					{
						explosions6[explosionCount6].x = enemyx1 + 40;
						explosions6[explosionCount6].y = enemyy1 + 20;
						explosions6[explosionCount6].explosionIdx = 0;
						explosions6[explosionCount6].active = true;
						explosions6[explosionCount6].timer = 0.0;
						explosionCount6++;
					}
					gameScore += 10;

					enemyy1 = 750;
					enemyx1 = 50 + rand() % 1250;
					bullets5[i].y = playershipy + 80;
					bullets5[i].x = playershipx + 43;
					enemyCount1++;
					break;
				}

				if ((bullets5[i].y >= enemyy2 - 65 && bullets5[i].y <= enemyy2 + 65 && bullets5[i].x >= enemyx2 - 50 && bullets5[i].x <= enemyx2 + 50))
				{
					if (explosionCount7 < 100)
					{
						explosions7[explosionCount7].x = enemyx2 + 40;
						explosions7[explosionCount7].y = enemyy2 + 20;
						explosions7[explosionCount7].explosionIdx = 0;
						explosions7[explosionCount7].active = true;
						explosions7[explosionCount7].timer = 0.0;
						explosionCount7++;
					}
					gameScore += 10;

					enemyy2 = 750;
					enemyx2 = 50 + rand() % 1250;
					bullets5[i].y = playershipy + 80;
					bullets5[i].x = playershipx + 43;
					enemyCount2++;
					break;
				}

				if ((bullets5[i].y >= enemyy3 - 65 && bullets5[i].y <= enemyy3 + 65 && bullets5[i].x >= enemyx3 - 50 && bullets5[i].x <= enemyx3 + 50))
				{
					if (explosionCount8 < 100)
					{
						explosions8[explosionCount8].x = enemyx3 + 40;
						explosions8[explosionCount8].y = enemyy3 + 20;
						explosions8[explosionCount8].explosionIdx = 0;
						explosions8[explosionCount8].active = true;
						explosions8[explosionCount8].timer = 0.0;
						explosionCount8++;
					}
					gameScore += 10;

					enemyy3 = 750;
					enemyx3 = 50 + rand() % 1250;
					bullets5[i].y = playershipy + 80;
					bullets5[i].x = playershipx + 43;
					enemyCount3++;
					break;
				}

				if ((bullets6[i].y >= enemyy1 - 85 && bullets6[i].y <= enemyy1 + 85 && bullets6[i].x >= enemyx1 - 85 && bullets6[i].x <= enemyx1 + 85))
				{
					if (explosionCount9 < 100)
					{
						explosions9[explosionCount9].x = enemyx1 + 40;
						explosions9[explosionCount9].y = enemyy1 + 20;
						explosions9[explosionCount9].explosionIdx = 0;
						explosions9[explosionCount9].active = true;
						explosions9[explosionCount9].timer = 0.0;
						explosionCount9++;
					}
					gameScore += 10;

					enemyy1 = 750;
					enemyx1 = 50 + rand() % 1250;
					bullets6[i].y = playershipy + 80;
					bullets6[i].x = playershipx + 43;
					enemyCount1++;
					break;
				}

				if ((bullets6[i].y >= enemyy2 - 50 && bullets6[i].y <= enemyy2 + 50 && bullets6[i].x >= enemyx2 - 65 && bullets6[i].x <= enemyx2 + 65))
				{
					if (explosionCount10 < 100)
					{
						explosions10[explosionCount10].x = enemyx2 + 40;
						explosions10[explosionCount10].y = enemyy2 + 20;
						explosions10[explosionCount10].explosionIdx = 0;
						explosions10[explosionCount10].active = true;
						explosions10[explosionCount10].timer = 0.0;
						explosionCount10++;
					}
					gameScore += 10;

					enemyy2 = 750;
					enemyx2 = 50 + rand() % 1250;
					bullets6[i].y = playershipy + 80;
					bullets6[i].x = playershipx + 43;
					enemyCount2++;
					break;
				}

				if ((bullets6[i].y >= enemyy3 - 50 && bullets6[i].y <= enemyy3 + 50 && bullets6[i].x >= enemyx3 - 65 && bullets6[i].x <= enemyx3 + 65))
				{
					if (explosionCount11 < 100)
					{
						explosions11[explosionCount11].x = enemyx3 + 40;
						explosions11[explosionCount11].y = enemyy3 + 20;
						explosions11[explosionCount11].explosionIdx = 0;
						explosions11[explosionCount11].active = true;
						explosions11[explosionCount11].timer = 0.0;
						explosionCount11++;
					}
					gameScore += 10;

					enemyy3 = 750;
					enemyx3 = 50 + rand() % 1250;
					bullets5[i].y = playershipy + 80;
					bullets5[i].x = playershipx + 43;
					enemyCount3++;
					break;
				}

				if ((bullets[i].y >= enemyy2 - 65 && bullets[i].y <= enemyy2 + 65 && bullets[i].x >= enemyx2 - 50 && bullets[i].x <= enemyx2 + 50) ||
					(bullets1[i].y >= enemyy2 - 65 && bullets1[i].y <= enemyy2 + 65 && bullets1[i].x >= enemyx2 - 50 && bullets1[i].x <= enemyx2 + 50))
				{
					if (explosionCount1 < 100)
					{
						explosions1[explosionCount1].x = enemyx2;
						explosions1[explosionCount1].y = enemyy2;
						explosions1[explosionCount1].explosionIdx = 0;
						explosions1[explosionCount1].active = true;
						explosions1[explosionCount1].timer = 0.0;
						explosionCount1++;
					}
					gameScore += 10;

					enemyy2 = 750;
					enemyx2 = 50 + rand() % 1250;
					bullets[i].y = playershipy + 80;
					bullets[i].x = playershipx + 43;
					bullets1[i].x = playershipx + 95;
					bullets1[i].y = playershipy + 80;
					enemyCount2++;
					break;
				}

				if ((bullets[i].y >= enemyy3 - 65 && bullets[i].y <= enemyy3 + 65 && bullets[i].x >= enemyx3 - 50 && bullets[i].x <= enemyx3 + 50) ||
					(bullets1[i].y >= enemyy3 - 65 && bullets1[i].y <= enemyy3 + 65 && bullets1[i].x >= enemyx3 - 50 && bullets1[i].x <= enemyx3 + 50))
				{
					if (explosionCount2 < 100)
					{
						explosions2[explosionCount2].x = enemyx3;
						explosions2[explosionCount2].y = enemyy3;
						explosions2[explosionCount2].explosionIdx = 0;
						explosions2[explosionCount2].active = true;
						explosions2[explosionCount2].timer = 0.0;
						explosionCount2++;
					}
					gameScore += 10;

					enemyy3 = 750;
					enemyx3 = 50 + rand() % 1250;
					bullets[i].y = playershipy + 80;
					bullets[i].x = playershipx + 43;
					bullets1[i].x = playershipx + 95;
					bullets1[i].y = playershipy + 80;
					enemyCount3++;
					break;
				}
			}

			if ((bullets[i].y >= meteorY2 - 65 && bullets[i].y <= meteorY2 + 65 && bullets[i].x >= meteorX2 - 50 && bullets[i].x <= meteorX2 + 50) ||
				(bullets1[i].y >= meteorY2 - 65 && bullets1[i].y <= meteorY2 + 65 && bullets1[i].x >= meteorX2 - 50 && bullets1[i].x <= meteorX2 + 50))
			{
				if (meteorExpcount2 < 100)
				{
					meteordamage2[meteorExpcount2].x = meteorX2;
					meteordamage2[meteorExpcount2].y = meteorY2;
					meteordamage2[meteorExpcount2].explosionIdx = 0;
					meteordamage2[meteorExpcount2].active = true;
					meteordamage2[meteorExpcount2].timer = 0.0;
					meteorExpcount2++;
				}
				gameScore += 10;

				meteorY2 = 760;
				meteorX2 = 50 + rand() % 1250;
				bullets[i].y = playershipy + 80;
				bullets[i].x = playershipx + 43;
				bullets1[i].x = playershipx + 95;
				bullets1[i].y = playershipy + 80;
				break;
			}

			if ((bullets[i].y >= meteorY3 - 65 && bullets[i].y <= meteorY3 + 65 && bullets[i].x >= meteorX3 - 50 && bullets[i].x <= meteorX3 + 55) ||
				(bullets1[i].y >= meteorY3 - 65 && bullets1[i].y <= meteorY3 + 65 && bullets1[i].x >= meteorX3 - 55 && bullets1[i].x <= meteorX3 + 50))
			{
				if (meteorExpcount3 < 100)
				{
					meteordamage3[meteorExpcount3].x = meteorX3;
					meteordamage3[meteorExpcount3].y = meteorY3;
					meteordamage3[meteorExpcount3].explosionIdx = 0;
					meteordamage3[meteorExpcount3].active = true;
					meteordamage3[meteorExpcount3].timer = 0.0;
					meteorExpcount3++;
				}
				gameScore += 10;

				meteorY3 = 760;
				meteorX3 = 50 + rand() % 1250;
				bullets[i].y = playershipy + 80;
				bullets[i].x = playershipx + 43;
				bullets1[i].x = playershipx + 95;
				bullets1[i].y = playershipy + 80;
				break;
			}

			if ((bullets5[i].y >= meteorY3 - 65 && bullets5[i].y <= meteorY3 + 65 && bullets5[i].x >= meteorX3 - 50 && bullets5[i].x <= meteorX3 + 50))
			{
				if (meteorExpcount6 < 100)
				{
					meteordamage6[meteorExpcount6].x = meteorX3;
					meteordamage6[meteorExpcount6].y = meteorY3;
					meteordamage6[meteorExpcount6].explosionIdx = 0;
					meteordamage6[meteorExpcount6].active = true;
					meteordamage6[meteorExpcount6].timer = 0.0;
					meteorExpcount6++;
				}
				gameScore += 10;

				meteorY3 = 760;
				meteorX3 = 50 + rand() % 1250;
				bullets5[i].y = playershipy + 80;
				bullets5[i].x = playershipx + 43;
				break;
			}
			if ((bullets5[i].y >= meteorY2 - 65 && bullets5[i].y <= meteorY2 + 65 && bullets5[i].x >= meteorX2 - 50 && bullets5[i].x <= meteorX2 + 50))
			{
				if (meteorExpcount7 < 100)
				{
					meteordamage7[meteorExpcount7].x = meteorX3;
					meteordamage7[meteorExpcount7].y = meteorY3;
					meteordamage7[meteorExpcount7].explosionIdx = 0;
					meteordamage7[meteorExpcount7].active = true;
					meteordamage7[meteorExpcount7].timer = 0.0;
					meteorExpcount7++;
				}
				gameScore += 10;

				meteorY2 = 760;
				meteorX2 = 50 + rand() % 1250;
				bullets5[i].y = playershipy + 80;
				bullets5[i].x = playershipx + 43;
				break;
			}
			if ((bullets6[i].y >= meteorY3 - 65 && bullets6[i].y <= meteorY3 + 65 && bullets6[i].x >= meteorX3 - 50 && bullets6[i].x <= meteorX3 + 50))
			{
				if (meteorExpcount8 < 100)
				{
					meteordamage8[meteorExpcount8].x = meteorX3;
					meteordamage8[meteorExpcount8].y = meteorY3;
					meteordamage8[meteorExpcount8].explosionIdx = 0;
					meteordamage8[meteorExpcount8].active = true;
					meteordamage8[meteorExpcount8].timer = 0.0;
					meteorExpcount8++;
				}
				gameScore += 10;

				meteorY3 = 760;
				meteorX3 = 50 + rand() % 1250;
				bullets6[i].y = playershipy + 80;
				bullets6[i].x = playershipx + 43;
				break;
			}
			if ((bullets6[i].y >= meteorY2 - 65 && bullets6[i].y <= meteorY2 + 65 && bullets6[i].x >= meteorX2 - 50 && bullets6[i].x <= meteorX2 + 50))
			{
				if (meteorExpcount9 < 100)
				{
					meteordamage9[meteorExpcount9].x = meteorX3;
					meteordamage9[meteorExpcount9].y = meteorY3;
					meteordamage9[meteorExpcount9].explosionIdx = 0;
					meteordamage9[meteorExpcount9].active = true;
					meteordamage9[meteorExpcount9].timer = 0.0;
					meteorExpcount9++;
				}
				gameScore += 10;

				meteorY2 = 760;
				meteorX2 = 50 + rand() % 1250;
				bullets6[i].y = playershipy + 80;
				bullets6[i].x = playershipx + 43;
				break;
			}
		}
	}
}

void detectPlayerCollision()
{
	if (startpage == 1)
	{
		if (!hasShield)
		{
			if (!bossTime)
			{
				if ((playershipx + 150 >= enemyx1 && playershipx <= enemyx1 + 192) &&
					(playershipy + 150 >= enemyy1 && playershipy <= enemyy1 + 192))
				{
					if (explosionCount3 < 100)
					{
						explosions3[explosionCount3].x = playershipx + 20;
						explosions3[explosionCount3].y = playershipy + 25;
						explosions3[explosionCount3].explosionIdx = 0;
						explosions3[explosionCount3].active = true;
						explosions3[explosionCount3].timer = 0.0;
						explosionCount3++;
					}
					health -= 5;
					enemyy1 = 750;
					enemyx1 = 50 + rand() % 1300;
				}

				if ((playershipx + 150 >= enemyx2 && playershipx <= enemyx2 + 100) &&
					(playershipy + 150 >= enemyy2 && playershipy <= enemyy2 + 130))
				{
					if (explosionCount4 < 100)
					{
						explosions4[explosionCount4].x = playershipx;
						explosions4[explosionCount4].y = playershipy;
						explosions4[explosionCount4].explosionIdx = 0;
						explosions4[explosionCount4].active = true;
						explosions4[explosionCount4].timer = 0.0;
						explosionCount4++;
					}
					health -= 5;
					enemyy2 = 750;
					enemyx2 = 50 + rand() % 1300;
				}

				if ((playershipx + 150 >= enemyx3 && playershipx <= enemyx3 + 100) &&
					(playershipy + 150 >= enemyy3 && playershipy <= enemyy3 + 100))
				{
					if (explosionCount5 < 100)
					{
						explosions5[explosionCount5].x = playershipx;
						explosions5[explosionCount5].y = playershipy;
						explosions5[explosionCount5].explosionIdx = 0;
						explosions5[explosionCount5].active = true;
						explosions5[explosionCount5].timer = 0.0;
						explosionCount5++;
					}
					health -= 5;
					enemyy3 = 750;
					enemyx3 = 50 + rand() % 1300;
				}

				if ((playershipx + 150 >= meteorX2 && playershipx <= meteorX2 + 50) &&
					(playershipy + 150 >= meteorY2 && playershipy <= meteorY2 + 50))
				{
					if (meteorExpcount4 < 100)
					{
						meteordamage4[meteorExpcount4].x = playershipx;
						meteordamage4[meteorExpcount4].y = playershipy;
						meteordamage4[meteorExpcount4].explosionIdx = 0;
						meteordamage4[meteorExpcount4].active = true;
						meteordamage4[meteorExpcount4].timer = 0.0;
						meteorExpcount4++;
					}
					health -= 5;
					meteorY2 = 760;
					meteorX2 = 50 + rand() % 1300;
				}

				if ((playershipx + 150 >= meteorX3 && playershipx <= meteorX3 + 50) &&
					(playershipy + 150 >= meteorY3 && playershipy <= meteorY3 + 50))
				{
					if (meteorExpcount5 < 100)
					{
						meteordamage5[meteorExpcount5].x = playershipx;
						meteordamage5[meteorExpcount5].y = playershipy;
						meteordamage5[meteorExpcount5].explosionIdx = 0;
						meteordamage5[meteorExpcount5].active = true;
						meteordamage5[meteorExpcount5].timer = 0.0;
						meteorExpcount5++;
					}
					health -= 5;
					meteorY3 = 760;
					meteorX3 = 50 + rand() % 1300;
				}
			}
		}
	}
}

void bulletCollision()
{
	if (!hasShield)
	{
		if (!bossTime)
		{
			for (int i = 0; i < bulletCount; i++)
			{
				if ((bullets2[i].y >= playershipy + 30 && bullets2[i].y <= playershipy + 110) &&
					(bullets2[i].x >= playershipx + 30 && bullets2[i].x <= playershipx + 110))
				{
					if (explosionCount12 < 100)
					{
						explosions12[explosionCount12].x = playershipx + 12;
						explosions12[explosionCount12].y = playershipy + 40;
						explosions12[explosionCount12].explosionIdx = 0;
						explosions12[explosionCount12].active = true;
						explosions12[explosionCount12].timer = 0.0;
						explosionCount12++;
					}
					health -= 5;
					bullets2[i].x = enemyx1 + 89;
					bullets2[i].y = enemyy1 - 5;
					break;
				}

				if ((bullets3[i].y >= playershipy + 30 && bullets3[i].y <= playershipy + 110) &&
					(bullets3[i].x >= playershipx + 30 && bullets3[i].x <= playershipx + 110))
				{
					if (explosionCount13 < 100)
					{
						explosions13[explosionCount13].x = playershipx + 12;
						explosions13[explosionCount13].y = playershipy + 40;
						explosions13[explosionCount13].explosionIdx = 0;
						explosions13[explosionCount13].active = true;
						explosions13[explosionCount13].timer = 0.0;
						explosionCount13++;
					}
					health -= 5;
					bullets3[i].x = enemyx2 + 42;
					bullets3[i].y = enemyy2 - 20;
					break;
				}

				if ((bullets4[i].y >= playershipy + 30 && bullets4[i].y <= playershipy + 110) &&
					(bullets4[i].x >= playershipx + 30 && bullets4[i].x <= playershipx + 110))
				{
					if (explosionCount14 < 100)
					{
						explosions14[explosionCount14].x = playershipx + 12;
						explosions14[explosionCount14].y = playershipy + 40;
						explosions14[explosionCount14].explosionIdx = 0;
						explosions14[explosionCount14].active = true;
						explosions14[explosionCount14].timer = 0.0;
						explosionCount14++;
					}
					health -= 5;
					bullets4[i].x = enemyx3 + 42;
					bullets4[i].y = enemyy3 - 20;
					break;
				}
			}
		}
	}
}

void checkbossplayercollision()
{
	if (!hasShield)
	{
		for (int i = 0; i < bulletcount11; i++)
		{
			if ((bullets11[i].y >= playershipy + 30 && bullets11[i].y <= playershipy + 110) &&
				(bullets11[i].x >= playershipx + 30 && bullets11[i].x <= playershipx + 110))
			{
				if (explosionCount15 < 100)
				{
					explosions15[explosionCount15].x = playershipx + 12;
					explosions15[explosionCount15].y = playershipy + 40;
					explosions15[explosionCount15].explosionIdx = 0;
					explosions15[explosionCount15].active = true;
					explosions15[explosionCount15].timer = 0.0;
					explosionCount15++;
				}
				health -= 6;
				bullets11[i].x = bossX + 130;
				bullets11[i].y = bossY + 50;
			}

			for (int i = 0; i < bulletcount22; i++)
			{
				if ((bullets22[i].y >= playershipy + 30 && bullets22[i].y <= playershipy + 110) &&
					(bullets22[i].x >= playershipx + 30 && bullets22[i].x <= playershipx + 110))
				{
					if (explosionCount16 < 100)
					{
						explosions16[explosionCount16].x = playershipx + 12;
						explosions16[explosionCount16].y = playershipy + 40;
						explosions16[explosionCount16].explosionIdx = 0;
						explosions16[explosionCount16].active = true;
						explosions16[explosionCount16].timer = 0.0;
						explosionCount16++;
					}
					health -= 6;
					bullets22[i].x = bossX + 80;
					bullets22[i].y = bossY + 50;
				}
			}
			for (int i = 0; i < bulletcount33; i++)

			{
				if ((bullets33[i].y >= playershipy + 30 && bullets33[i].y <= playershipy + 110) &&
					(bullets33[i].x >= playershipx + 30 && bullets33[i].x <= playershipx + 110))
				{
					if (explosionCount17 < 100)
					{
						explosions17[explosionCount17].x = playershipx + 12;
						explosions17[explosionCount17].y = playershipy + 40;
						explosions17[explosionCount17].explosionIdx = 0;
						explosions17[explosionCount17].active = true;
						explosions17[explosionCount17].timer = 0.0;
						explosionCount17++;
					}
					health -= 6;
					bullets33[i].x = bossX + 160;
					bullets33[i].y = bossY + 80;
				}
			}
			for (int i = 0; i < bulletcount44; i++)

			{
				if ((bullets44[i].y >= playershipy + 30 && bullets44[i].y <= playershipy + 110) &&
					(bullets44[i].x >= playershipx + 30 && bullets44[i].x <= playershipx + 110))
				{
					if (explosionCount18 < 100)
					{
						explosions18[explosionCount18].x = playershipx + 12;
						explosions18[explosionCount18].y = playershipy + 40;
						explosions18[explosionCount18].explosionIdx = 0;
						explosions18[explosionCount18].active = true;
						explosions18[explosionCount18].timer = 0.0;
						explosionCount18++;
					}
					health -= 6;
					bullets44[i].x = bossX + 50;
					bullets44[i].y = bossY + 80;
				}
			}
			for (int i = 0; i < bulletcount55; i++)

			{
				if ((bullets55[i].y >= playershipy + 30 && bullets55[i].y <= playershipy + 110) &&
					(bullets55[i].x >= playershipx + 30 && bullets55[i].x <= playershipx + 110))
				{
					if (explosionCount19 < 100)
					{
						explosions19[explosionCount19].x = playershipx + 12;
						explosions19[explosionCount19].y = playershipy + 40;
						explosions19[explosionCount19].explosionIdx = 0;
						explosions19[explosionCount19].active = true;
						explosions19[explosionCount19].timer = 0.0;
						explosionCount19++;
					}
					health -= 6;
					bullets55[i].x = bossX + 90;
					bullets55[i].y = bossY + 30;
				}
			}
			for (int i = 0; i < bulletcount66; i++)

			{
				if ((bullets66[i].y >= playershipy + 30 && bullets66[i].y <= playershipy + 110) &&
					(bullets66[i].x >= playershipx + 30 && bullets66[i].x <= playershipx + 110))
				{
					if (explosionCount20 < 100)
					{
						explosions20[explosionCount20].x = playershipx + 12;
						explosions20[explosionCount20].y = playershipy + 40;
						explosions20[explosionCount20].explosionIdx = 0;
						explosions20[explosionCount20].active = true;
						explosions20[explosionCount20].timer = 0.0;
						explosionCount20++;
					}
					health -= 6;
					bullets66[i].x = bossX + 120;
					bullets66[i].y = bossY + 80;
				}
			}
		}
	}

}

void killingBoss()
{
	for (int i = 0; i < bulletCount; i++)
	{
		if (((bullets[i].y + 30) >= bossY && bullets[i].y <= bossY + 170 && bullets[i].x >= bossX - 30 && bullets[i].x <= bossX + 170) ||
			(bullets1[i].y >= bossY - 30 && bullets1[i].y <= bossY + 170 && bullets1[i].x >= bossX - 30 && bullets1[i].x <= bossX + 170))
		{
			if (bossHealth > 0)
			{
				bossHealth-=2;
				if (explosionCount21 < 700)
				{
					explosions21[explosionCount21].x = bossX + 20;
					explosions21[explosionCount21].y = bossY + 40;
					explosions21[explosionCount21].explosionIdx = 0;
					explosions21[explosionCount21].active = true;
					explosions21[explosionCount21].timer = 0.0;
					explosionCount21++;
				}
				gameScore += 50;
			}

			bullets[i].y = playershipy + 80;
			bullets[i].x = playershipx + 43;
			bullets1[i].x = playershipx + 95;
			bullets1[i].y = playershipy + 80;
			break;
		}
	}
	for (int i = 0; i <= bulletcount1; i++)
	{
		if ((bullets5[i].y >= bossY - 30 && bullets5[i].y <= bossY + 170) &&
			(bullets5[i].x >= bossX - 30 && bullets5[i].x <= bossX + 170))
		{
			if (bossHealth > 0)
			{
				bossHealth-=2;
				if (explosionCount22 < 700)
				{
					explosions22[explosionCount22].x = bossX + 20;
					explosions22[explosionCount22].y = bossY + 40;
					explosions22[explosionCount22].explosionIdx = 0;
					explosions22[explosionCount22].active = true;
					explosions22[explosionCount22].timer = 0.0;
					explosionCount22++;
				}
				gameScore += 50;
			}

			bullets5[i].y = playershipy + 80;
			bullets5[i].x = playershipx + 43;
			break;
		}


		if ((bullets6[i].y >= bossY - 30 && bullets6[i].y <= bossY + 170) &&
			(bullets6[i].x >= bossX - 30 && bullets6[i].x <= bossX + 170))
		{
			if (bossHealth > 0)
			{
				bossHealth-=2;
				if (explosionCount23 < 700)
				{
					explosions23[explosionCount23].x = bossX + 20;
					explosions23[explosionCount23].y = bossY + 40;
					explosions23[explosionCount23].explosionIdx = 0;
					explosions23[explosionCount23].active = true;
					explosions23[explosionCount23].timer = 0.0;
					explosionCount23++;
				}
				gameScore += 50;
			}
			bullets6[i].y = playershipy + 80;
			bullets6[i].x = playershipx + 43;
			break;
		}
	}
}

void drawHomePage()
{
	iShowBMP(0, 0, menupic[1]);
}

void drawaboutPage()
{
	iShowBMP(0, 0, menupic[0]);
	iShowBMP2(30, 690, menupic[3], 0);
}

void drawScorepage()
{
	iShowBMP(0, 0, menupic[2]);
	iShowBMP2(30, 690, menupic[3], 0);
	iSetColor(255,255,255);
	iLine(447,230,947,230);
	iLine(447,230,447,578);
	iLine(447,578,947,578);
	iLine(947,578,947,230);

	iLine(436,221,436,587);
	iLine(436,587,958,587);
	iLine(958,587,958,221);
	iLine(958,221,436,221);

	readScore();
}

void drawSettingpage()
{
	iShowBMP(0, 0, settings[0]);
	iShowBMP2(30, 690, menupic[3], 0);
}

void drawmusicpage()
{
	iShowBMP(0, 0, startmusic[0]);
	iShowBMP2(30, 690, menupic[3], 0);
}

void startButtonClick()
{
	homePage = 0;
	startpage = 1;
	aboutPage = 0;
	scorepage = 0;
	gameoverpage = 0;
	settingpage = 0;
	musicpage = 0;
	gamecompletepage = 0;
}

void aboutButtonClick()
{
	homePage = 0;
	startpage = 0;
	aboutPage = 1;
	scorepage = 0;
	gameoverpage = 0;
	settingpage = 0;
	musicpage = 0;
	gamecompletepage = 0;
}

void musicButtonClick()
{
	homePage = 0;
	startpage = 0;
	aboutPage = 0;
	scorepage = 0;
	gameoverpage = 0;
	settingpage = 0;
	musicpage = 1;
	gamecompletepage = 0;
}
void scoreButtonClick()
{
	homePage = 0;
	startpage = 0;
	aboutPage = 0;
	scorepage = 1;
	gameoverpage = 0;
	settingpage = 0;
	musicpage = 0;
	gamecompletepage = 0;
}

void backButtonClick()
{
	homePage = 1;
	startpage = 0;
	aboutPage = 0;
	scorepage = 0;
	gameoverpage = 0;
	musicpage = 0;
	gamecompletepage = 0;
}

void settingButtonClick()
{
	homePage = 0;
	startpage = 0;
	aboutPage = 0;
	scorepage = 0;
	gameoverpage = 0;
	settingpage = 1;
	musicpage = 0;
	gamecompletepage = 0;
}

void gamedonepage()
{
	iShowBMP(0,0,gamedone[0]);
}
void checkgamedone()
{
	if(bossHealth <= 0)
	{
		homePage = 0;
		startpage = 0;
		aboutPage = 0;
		scorepage = 0;
		gameoverpage = 0;
		settingpage = 0;
		musicpage = 0;
		gamecompletepage = 1;
		PlaySound(0, 0, 0);
		PlaySound("missionpass.wav", NULL, SND_LOOP | SND_ASYNC);
	}
}
void checkgameOver()
{
	if (health <= 0)
	{
		gameScore += 1000;
		homePage = 0;
		startpage = 0;
		musicpage = 0;
		aboutPage = 0;
		gamecompletepage = 0;
		scorepage = 0;
		settingpage = 0;
		gameoverpage = 1;
		PlaySound(0, 0, 0);
		PlaySound("music4.wav", NULL, SND_LOOP | SND_ASYNC);
	}
}

char point[10000];
char playerHealth[10000];
char bhealth[10000];

void drawTimer()
{
	if (startpage == 1)
	{

		iSetColor(255, 255, 255);
		sprintf(point, "%d", gameScore);
		iText(1157, 12, point, GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 255, 255);
		sprintf(playerHealth, "%d", health);
		iText(229, 12, playerHealth, GLUT_BITMAP_HELVETICA_18);

		if(bossTime)
		{
			iSetColor(255,0,0);
			iText(600,710,"BOSS ALERT!!!",GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(20,4,11);
			iFilledRectangle(31,701,230,36);
			iSetColor(255,255,255);
			iText(45,710,"BOSS HEALTH : ",GLUT_BITMAP_HELVETICA_18);
			iSetColor(255, 255, 255);
			sprintf(bhealth, "%d", bossHealth);
			iText(195, 710, bhealth, GLUT_BITMAP_HELVETICA_18);
		}
	}
}

int len = 0;
char str1[100];
bool newscore = true;

struct hscore
{
	char name[30];
	int Score = 0;
};
hscore highScore[5];

void readScore()
{
	FILE *fp;
	fp = fopen("Score.txt", "r");

	char showName[5][30], showScore[5][5];
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s %d\n", highScore[i].name, &highScore[i].Score);
	}

	fclose(fp);

	for (int i = 0; i < 5; i++)
	{
		sprintf(showName[i], "%s", highScore[i].name);
		sprintf(showScore[i], "%d", highScore[i].Score);
		iSetColor(255, 255, 254);
		iText(550, 500 - 50 * i, showName[i], GLUT_BITMAP_HELVETICA_18);
		iText(750, 500 - 50 * i, showScore[i], GLUT_BITMAP_HELVETICA_18);
	}
}

void newHighscore()
{
	newscore = true;
	FILE *fp;
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s %d\n", highScore[i].name, &highScore[i].Score);
	}
	fclose(fp);

	if (newscore)
	{
		printf("%d ", gameScore);
		if (gameScore > highScore[4].Score)
		{
			printf("score = %d", gameScore);
			highScore[4].Score = gameScore;
			strcpy(highScore[4].name, str1);

			for (int j = 0; j < 5; j++)
			{
				for (int k = 4; k > j; k--)
				{
					if (highScore[k].Score > highScore[k - 1].Score)
					{
						int tempScore = highScore[k - 1].Score;
						highScore[k - 1].Score = highScore[k].Score;
						highScore[k].Score = tempScore;

						char tempName[30];
						strcpy(tempName, highScore[k - 1].name);
						strcpy(highScore[k - 1].name, highScore[k].name);
						strcpy(highScore[k].name, tempName);
					}
				}
			}

			fp = fopen("Score.txt", "w");
			for (int i = 0; i < 5; i++)
			{
				fprintf(fp, "%s %d\n", highScore[i].name, highScore[i].Score);
			}
			fclose(fp);

			newscore = false;
		}
	}
}

void takeInput(unsigned key)
{
	if (gameoverpage == 1 || gamecompletepage == 1)
	{
		if (key == '\r')
		{
			newHighscore();
			gameReset();
			PlaySound(0, 0, 0);
			PlaySound("music3.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		else if (key == '\b')
		{
			if (len > 0)
				len--;
			str1[len] = '\0';
		}
		else
		{
			if (len < 29)
			{
				str1[len] = key;
				len++;
				str1[len] = '\0';
			}
		}
	}
}

void show_char()
{
	if(gameoverpage == 1)
	{
		iSetColor(255, 255, 255);
		iText(406, 60, str1, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	else if(gamecompletepage == 1)
	{
		iSetColor(0, 0, 0);
		iText(456, 108, str1, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

int prevBoss = 0;
void iDraw()
{
	iClear();
	if (startpage == 1)
	{
		int sum = 0;
		for (int i = 0; i < 30; i++)
		{
			iShowBMP(backgroundSky[i].x, backgroundSky[i].y, bgsky[i]);
		}
		iShowBMP2(playershipx, playershipy, playership[0], 0);

		changeBg();
		powerupWork();

		if (!bossTime)
		{
			iShowBMP2(enemyx1, enemyy1, enemySpaceship[1], 0);
			if (enemyy1 <= 0)
			{
				enemyy1 = 750;
				enemyx1 = 70 + rand() % 1260;
				enemyCount1++;
			}

			iShowBMP2(enemyx2, enemyy2, enemySpaceship[2], 0);
			if (enemyy2 <= 0)
			{
				enemyy2 = 750;
				enemyx2 = 50 + rand() % 1270;
				enemyCount2++;
			}

			iShowBMP2(enemyx3, enemyy3, enemySpaceship[2], 0);
			if (enemyy3 <= 0)
			{
				enemyy3 = 750;
				enemyx3 = 60 + rand() % 1230;
				enemyCount3++;
			}

			for (int i = 0; i < bulletCount; i++)
			{
				iShowBMP2(bullets2[i].x, bullets2[i].y, fireEffect[1], 0);
			}
			for (int i = 0; i < bulletCount; i++)
			{
				iShowBMP2(bullets3[i].x, bullets3[i].y, fireEffect[2], 0);
			}
			for (int i = 0; i < bulletCount; i++)
			{
				iShowBMP2(bullets4[i].x, bullets4[i].y, fireEffect[2], 0);
			}
		}

		iShowBMP2(meteorX2, meteorY2, meteor[1], 0);
		iShowBMP2(meteorX3, meteorY3, meteor[2], 0);

		if (meteorX2 <= 0 || meteorX2 >= screenwidth || meteorY2 <= 0)
		{
			meteorX2 = 50 + rand() % 1200;
			meteorY2 = 760;
		}

		if (meteorX3 <= 0 || meteorX3 >= screenwidth || meteorY3 <= 0)
		{
			meteorX3 = 50 + rand() % 1230;
			meteorY3 = 760;
		}

		for (int i = 0; i < explosionCount; i++)
		{
			if (explosions[i].active == true)
			{
				iShowBMP2(explosions[i].x, explosions[i].y, explosionEffect[explosions[i].explosionIdx], 0);
				explosions[i].timer++;

				if (explosions[i].timer > .5)
				{
					explosions[i].explosionIdx++;
					explosions[i].timer = 0;
				}
				if (explosions[i].explosionIdx >= 8)
					explosions[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount1; i++)
		{
			if (explosions1[i].active == true)
			{
				iShowBMP2(explosions1[i].x, explosions1[i].y, enemyExplosion[explosions1[i].explosionIdx], 0);
				explosions1[i].timer++;

				if (explosions1[i].timer > .5)
				{
					explosions1[i].explosionIdx++;
					explosions1[i].timer = 0;
				}
				if (explosions1[i].explosionIdx >= 6)
					explosions1[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount2; i++)
		{
			if (explosions2[i].active == true)
			{
				iShowBMP2(explosions2[i].x, explosions2[i].y, enemyExplosion[explosions2[i].explosionIdx], 0);
				explosions2[i].timer++;

				if (explosions2[i].timer > .5)
				{
					explosions2[i].explosionIdx++;
					explosions2[i].timer = 0;
				}
				if (explosions2[i].explosionIdx >= 6)
					explosions2[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount6; i++)
		{
			if (explosions6[i].active == true)
			{
				iShowBMP2(explosions6[i].x, explosions6[i].y, explosionEffect[explosions6[i].explosionIdx], 0);
				explosions6[i].timer++;

				if (explosions6[i].timer > .5)
				{
					explosions6[i].explosionIdx++;
					explosions6[i].timer = 0;
				}
				if (explosions6[i].explosionIdx >= 8)
					explosions6[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount7; i++)
		{
			if (explosions7[i].active == true)
			{
				iShowBMP2(explosions7[i].x, explosions7[i].y, enemyExplosion[explosions7[i].explosionIdx], 0);
				explosions7[i].timer++;

				if (explosions7[i].timer > .5)
				{
					explosions7[i].explosionIdx++;
					explosions7[i].timer = 0;
				}
				if (explosions7[i].explosionIdx >= 6)
					explosions7[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount8; i++)
		{
			if (explosions8[i].active == true)
			{
				iShowBMP2(explosions8[i].x, explosions8[i].y, enemyExplosion[explosions8[i].explosionIdx], 0);
				explosions8[i].timer++;

				if (explosions8[i].timer > .5)
				{
					explosions8[i].explosionIdx++;
					explosions8[i].timer = 0;
				}
				if (explosions8[i].explosionIdx >= 6)
					explosions8[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount9; i++)
		{
			if (explosions9[i].active == true)
			{
				iShowBMP2(explosions9[i].x, explosions9[i].y, explosionEffect[explosions9[i].explosionIdx], 0);
				explosions9[i].timer++;

				if (explosions9[i].timer > .5)
				{
					explosions9[i].explosionIdx++;
					explosions9[i].timer = 0;
				}
				if (explosions9[i].explosionIdx >= 8)
					explosions9[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount10; i++)
		{
			if (explosions10[i].active == true)
			{
				iShowBMP2(explosions10[i].x, explosions10[i].y, enemyExplosion[explosions10[i].explosionIdx], 0);
				explosions10[i].timer++;

				if (explosions10[i].timer > .5)
				{
					explosions10[i].explosionIdx++;
					explosions10[i].timer = 0;
				}
				if (explosions10[i].explosionIdx >= 6)
					explosions10[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount11; i++)
		{
			if (explosions11[i].active == true)
			{
				iShowBMP2(explosions11[i].x, explosions11[i].y, enemyExplosion[explosions11[i].explosionIdx], 0);
				explosions11[i].timer++;

				if (explosions11[i].timer > .5)
				{
					explosions11[i].explosionIdx++;
					explosions11[i].timer = 0;
				}
				if (explosions11[i].explosionIdx >= 6)
					explosions11[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount2; i++)
		{
			if (meteordamage2[i].active == true)
			{
				iShowBMP2(meteordamage2[i].x, meteordamage2[i].y, meteordamage[meteordamage2[i].explosionIdx], 0);
				meteordamage2[i].timer++;

				if (meteordamage2[i].timer > .5)
				{
					meteordamage2[i].explosionIdx++;
					meteordamage2[i].timer = 0;
				}
				if (meteordamage2[i].explosionIdx >= 3)
					meteordamage2[i].active = false;
			}
		}
		for (int i = 0; i < meteorExpcount3; i++)
		{
			if (meteordamage3[i].active == true)
			{
				iShowBMP2(meteordamage3[i].x, meteordamage3[i].y, meteordamage[meteordamage3[i].explosionIdx], 0);
				meteordamage3[i].timer++;

				if (meteordamage3[i].timer > .5)
				{
					meteordamage3[i].explosionIdx++;
					meteordamage3[i].timer = 0;
				}
				if (meteordamage3[i].explosionIdx >= 3)
					meteordamage3[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount4; i++)
		{
			if (meteordamage4[i].active == true)
			{
				iShowBMP2(meteordamage4[i].x, meteordamage4[i].y, meteordamage[meteordamage4[i].explosionIdx], 0);
				meteordamage4[i].timer++;

				if (meteordamage4[i].timer > .5)
				{
					meteordamage4[i].explosionIdx++;
					meteordamage4[i].timer = 0;
				}
				if (meteordamage4[i].explosionIdx >= 3)
					meteordamage4[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount5; i++)
		{
			if (meteordamage5[i].active == true)
			{
				iShowBMP2(meteordamage5[i].x, meteordamage5[i].y, meteordamage[meteordamage5[i].explosionIdx], 0);
				meteordamage5[i].timer++;

				if (meteordamage5[i].timer > .5)
				{
					meteordamage5[i].explosionIdx++;
					meteordamage5[i].timer = 0;
				}
				if (meteordamage5[i].explosionIdx >= 3)
					meteordamage5[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount6; i++)
		{
			if (meteordamage6[i].active == true)
			{
				iShowBMP2(meteordamage6[i].x, meteordamage6[i].y, meteordamage[meteordamage6[i].explosionIdx], 0);
				meteordamage6[i].timer++;

				if (meteordamage6[i].timer > .5)
				{
					meteordamage6[i].explosionIdx++;
					meteordamage6[i].timer = 0;
				}
				if (meteordamage6[i].explosionIdx >= 3)
					meteordamage6[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount7; i++)
		{
			if (meteordamage7[i].active == true)
			{
				iShowBMP2(meteordamage7[i].x, meteordamage7[i].y, meteordamage[meteordamage7[i].explosionIdx], 0);
				meteordamage7[i].timer++;

				if (meteordamage7[i].timer > .5)
				{
					meteordamage7[i].explosionIdx++;
					meteordamage7[i].timer = 0;
				}
				if (meteordamage7[i].explosionIdx >= 3)
					meteordamage7[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount8; i++)
		{
			if (meteordamage8[i].active == true)
			{
				iShowBMP2(meteordamage8[i].x, meteordamage8[i].y, meteordamage[meteordamage8[i].explosionIdx], 0);
				meteordamage8[i].timer++;

				if (meteordamage8[i].timer > .5)
				{
					meteordamage8[i].explosionIdx++;
					meteordamage8[i].timer = 0;
				}
				if (meteordamage8[i].explosionIdx >= 3)
					meteordamage8[i].active = false;
			}
		}

		for (int i = 0; i < meteorExpcount9; i++)
		{
			if (meteordamage9[i].active == true)
			{
				iShowBMP2(meteordamage9[i].x, meteordamage9[i].y, meteordamage[meteordamage9[i].explosionIdx], 0);
				meteordamage9[i].timer++;

				if (meteordamage9[i].timer > .5)
				{
					meteordamage9[i].explosionIdx++;
					meteordamage9[i].timer = 0;
				}
				if (meteordamage9[i].explosionIdx >= 3)
					meteordamage9[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount3; i++)
		{
			if (explosions3[i].active == true)
			{
				iShowBMP2(explosions3[i].x, explosions3[i].y, playershipDamage[explosions3[i].explosionIdx], 0);
				explosions3[i].timer++;

				if (explosions3[i].timer > .5)
				{
					explosions3[i].explosionIdx++;
					explosions3[i].timer = 0;
				}
				if (explosions3[i].explosionIdx >= 10)
					explosions3[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount4; i++)
		{
			if (explosions4[i].active == true)
			{
				iShowBMP2(explosions4[i].x, explosions4[i].y, playershipDamage[explosions4[i].explosionIdx], 0);
				explosions4[i].timer++;

				if (explosions4[i].timer > .5)
				{
					explosions4[i].explosionIdx++;
					explosions4[i].timer = 0;
				}
				if (explosions4[i].explosionIdx >= 10)
					explosions4[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount5; i++)
		{
			if (explosions5[i].active == true)
			{
				iShowBMP2(explosions5[i].x, explosions5[i].y, playershipDamage[explosions5[i].explosionIdx], 0);
				explosions5[i].timer++;

				if (explosions5[i].timer > .5)
				{
					explosions5[i].explosionIdx++;
					explosions5[i].timer = 0;
				}
				if (explosions5[i].explosionIdx >= 10)
					explosions5[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount12; i++)
		{
			if (explosions12[i].active == true)
			{
				iShowBMP2(explosions12[i].x, explosions12[i].y, playershipDamage[explosions12[i].explosionIdx], 0);
				explosions12[i].timer++;

				if (explosions12[i].timer > .5)
				{
					explosions12[i].explosionIdx++;
					explosions12[i].timer = 0;
				}
				if (explosions12[i].explosionIdx >= 10)
					explosions12[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount13; i++)
		{
			if (explosions13[i].active == true)
			{
				iShowBMP2(explosions13[i].x, explosions13[i].y, playershipDamage[explosions13[i].explosionIdx], 0);
				explosions13[i].timer++;

				if (explosions13[i].timer > .5)
				{
					explosions13[i].explosionIdx++;
					explosions13[i].timer = 0;
				}
				if (explosions13[i].explosionIdx >= 10)
					explosions13[i].active = false;
			}
		}

		for (int i = 0; i < explosionCount14; i++)
		{
			if (explosions14[i].active == true)
			{
				iShowBMP2(explosions14[i].x, explosions14[i].y, playershipDamage[explosions14[i].explosionIdx], 0);
				explosions14[i].timer++;

				if (explosions14[i].timer > .5)
				{
					explosions14[i].explosionIdx++;
					explosions14[i].timer = 0;
				}
				if (explosions14[i].explosionIdx >= 10)
					explosions14[i].active = false;
			}
		}

		for (int i = 0; i < bulletCount; i++)
		{
			iShowBMP2(bullets[i].x, bullets[i].y, fireEffect[0], 0);
		}

		for (int i = 0; i < bulletCount; i++)
		{
			iShowBMP2(bullets1[i].x, bullets1[i].y, fireEffect[0], 0);
		}
		if (hasBullet)
		{
			for (int i = 0; i < bulletCount; i++)
			{
				iShowBMP2(bullets5[i].x - 27, bullets5[i].y - 30, fireEffect[3], 0);
			}
			for (int i = 0; i < bulletCount; i++)
			{
				iShowBMP2(bullets6[i].x, bullets6[i].y - 30, fireEffect[4], 0);
			}
		}
		if (enemyCount1 + enemyCount2 + enemyCount3 >= 50)
		{
			bossTime = true;
		}

		if (bossTime == 1 && prevBoss == 0)
			iSetTimer(120, movebossbullets);

		if (bossTime)
		{
			shootbossbullets();
			checkbossplayercollision();
			killingBoss();

			iShowBMP2(bossX, bossY, bossShip[0], 0);

			for (int i = 0; i < bulletcount11; i++)
			{
				iShowBMP2(bullets11[i].x, bullets11[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < bulletcount22; i++)
			{
				iShowBMP2(bullets22[i].x, bullets22[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < bulletcount33; i++)
			{
				iShowBMP2(bullets33[i].x, bullets33[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < bulletcount44; i++)
			{
				iShowBMP2(bullets44[i].x, bullets44[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < bulletcount55; i++)
			{
				iShowBMP2(bullets55[i].x, bullets55[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < bulletcount66; i++)
			{
				iShowBMP2(bullets66[i].x, bullets66[i].y, bossbullet[0], 0);
			}

			for (int i = 0; i < explosionCount15; i++)
			{
				if (explosions15[i].active == true)
				{
					iShowBMP2(explosions15[i].x, explosions15[i].y, playershipDamage[explosions15[i].explosionIdx], 0);
					explosions15[i].timer++;

					if (explosions15[i].timer > .5)
					{
						explosions15[i].explosionIdx++;
						explosions15[i].timer = 0;
					}
					if (explosions15[i].explosionIdx >= 10)
						explosions15[i].active = false;
				}
			}

			for (int i = 0; i < explosionCount16; i++)
			{
				if (explosions16[i].active == true)
				{
					iShowBMP2(explosions16[i].x, explosions16[i].y, playershipDamage[explosions16[i].explosionIdx], 0);
					explosions16[i].timer++;

					if (explosions16[i].timer > .5)
					{
						explosions16[i].explosionIdx++;
						explosions16[i].timer = 0;
					}
					if (explosions16[i].explosionIdx >= 10)
						explosions16[i].active = false;
				}
			}

			for (int i = 0; i < explosionCount17; i++)
			{
				if (explosions17[i].active == true)
				{
					iShowBMP2(explosions17[i].x, explosions17[i].y, playershipDamage[explosions17[i].explosionIdx], 0);
					explosions17[i].timer++;

					if (explosions17[i].timer > .5)
					{
						explosions17[i].explosionIdx++;
						explosions17[i].timer = 0;
					}
					if (explosions17[i].explosionIdx >= 10)
						explosions17[i].active = false;
				}
			}

			for (int i = 0; i < explosionCount18; i++)
			{
				if (explosions18[i].active == true)
				{
					iShowBMP2(explosions18[i].x, explosions18[i].y, playershipDamage[explosions18[i].explosionIdx], 0);
					explosions18[i].timer++;

					if (explosions18[i].timer > .5)
					{
						explosions18[i].explosionIdx++;
						explosions18[i].timer = 0;
					}
					if (explosions18[i].explosionIdx >= 10)
						explosions18[i].active = false;
				}
			}

			for (int i = 0; i < explosionCount19; i++)
			{
				if (explosions19[i].active == true)
				{
					iShowBMP2(explosions19[i].x, explosions19[i].y, playershipDamage[explosions19[i].explosionIdx], 0);
					explosions19[i].timer++;

					if (explosions19[i].timer > .5)
					{
						explosions19[i].explosionIdx++;
						explosions19[i].timer = 0;
					}
					if (explosions19[i].explosionIdx >= 10)
						explosions19[i].active = false;
				}
			}

			for (int i = 0; i < explosionCount20; i++)
			{
				if (explosions20[i].active == true)
				{
					iShowBMP2(explosions20[i].x, explosions20[i].y, playershipDamage[explosions20[i].explosionIdx], 0);
					explosions20[i].timer++;

					if (explosions20[i].timer > .5)
					{
						explosions20[i].explosionIdx++;
						explosions20[i].timer = 0;
					}
					if (explosions20[i].explosionIdx >= 10)
						explosions20[i].active = false;
				}
			}

			// for (int i = 0; i < explosionCount21; i++)
			// {
			// 	if (explosions21[i].active == true)
			// 	{
			// 		iShowBMP2(explosions21[i].x, explosions21[i].y, bossExplosion[explosions21[i].explosionIdx], 0);
			// 		explosions21[i].timer++;

			// 		if (explosions21[i].timer > 3)
			// 		{
			// 			explosions21[i].explosionIdx++;
			// 			explosions21[i].timer = 0;
			// 		}
			// 		if (explosions21[i].explosionIdx >= 9)
			// 			explosions21[i].active = false;
			// 	}
			// }

			// for (int i = 0; i < explosionCount22; i++)
			// {
			// 	if (explosions22[i].active == true)
			// 	{
			// 		iShowBMP2(explosions22[i].x, explosions22[i].y, bossExplosion[explosions22[i].explosionIdx], 0);
			// 		explosions22[i].timer++;

			// 		if (explosions22[i].timer > 3)
			// 		{
			// 			explosions22[i].explosionIdx++;
			// 			explosions22[i].timer = 0;
			// 		}
			// 		if (explosions22[i].explosionIdx >= 9)
			// 			explosions22[i].active = false;
			// 	}
			// }

			// for (int i = 0; i < explosionCount23; i++)
			// {
			// 	if (explosions23[i].active == true)
			// 	{
			// 		iShowBMP2(explosions23[i].x, explosions23[i].y, bossExplosion[explosions23[i].explosionIdx], 0);
			// 		explosions23[i].timer++;

			// 		if (explosions23[i].timer > 3)
			// 		{
			// 			explosions23[i].explosionIdx++;
			// 			explosions23[i].timer = 0;
			// 		}
			// 		if (explosions23[i].explosionIdx >= 9)
			// 			explosions23[i].active = false;
			// 	}
			// }
		}

		iShowBMP(0, 0, scorecard[0]);
		iShowBMP2(1157, 680, startmusic[1], 0);
		iShowBMP2(1255, 680, startmusic[2], 0);
		iSetColor(255, 255, 255);
		iFilledRectangle(413, 8, 350, 23);
		iSetColor(20, 4, 11);
		iFilledRectangle(1140, 630, 204, 32);
		iSetColor(255, 255, 255);
		iSetColor(255, 255, 255);
		if (musicstate3 == 1)
		{
			iText(1142, 638, "MUSIC TURNED ON :)", GLUT_BITMAP_HELVETICA_18);
		}

		if (musicstate1 == 1)
		{
			musicstate3 = 0;
			iText(1142, 638, "MUSIC TURNED OFF :(", GLUT_BITMAP_HELVETICA_18);
		}

		if (musicstate2 == 1)
		{
			musicstate3 = 0;
			iText(1142, 638, "MUSIC TURNED ON :)", GLUT_BITMAP_HELVETICA_18);
		}
		if (hasBullet)
		{
			iSetColor(20, 4, 11);
			iText(470, 13, "EXTRA BULLET POWER !!!", GLUT_BITMAP_HELVETICA_18);
		}

		if (hasShield)
		{
			iSetColor(20, 4, 11);
			iText(470, 13, "EXTRA SHIELD POWER !!!", GLUT_BITMAP_HELVETICA_18);
		}

		prevBoss = bossTime;

		drawTimer();
		updatePowerUps();
		spawnPowerUp();
		powerupWork();
		renderShield();
		bulletCollision();
		checkgameOver();
		checkgamedone();
	}

	else if (gameoverpage == 1)
	{
		gameoverpic();
		show_char();
	}

	else if (homePage == 1)
	{
		drawHomePage();
	}

	else if(gamecompletepage == 1)
	{
		gamedonepage();
		show_char();
	}

	else if (aboutPage == 1)
		drawaboutPage();

	else if (scorepage == 1)
		drawScorepage();

	else if (settingpage == 1)
		drawSettingpage();

	else if (musicpage == 1)
		drawmusicpage();
}

void gameReset()
{
	homePage = 1;
	startpage = 0;
	aboutPage = 0;
	scorepage = 0;
	gameoverpage = 0;
	musicpage = 0;
	gamecompletepage = 0;
	playershipx = 755, playershipy = 35;
	enemyx1 = 200, enemyy1 = 750;
	enemyx2 = 550, enemyy2 = 750;
	enemyx3 = 700, enemyy3 = 750;
	enemyx4 = 1000, enemyy4 = 750;
	meteorX1 = 350, meteorY1 = 760;
	health = 200;
	gameScore = 0;
	meteorX2 = 790, meteorY2 = 760;
	meteorX3 = 1250, meteorY3 = 760;
	timer1 = 0;
	bulletTimer = 0;
	shieldTimer = 0;
	prevBoss = 0;
	hasShield = false;
	bossTime = false;
	hasBullet = false;
	powerUpCount = 0;
	enemyCount1 = 0,enemyCount2 = 0,enemyCount3 = 0;
	bossX = 640, bossY = 870,bossHealth = 200;
	powerUpTimer = 0;
	for (int i = 0; i < 6; i++)
	{
		bullets5[i].x = -1000;
		bullets5[i].y = -1000;
		bullets6[i].x = -1000;
		bullets6[i].y = -1000;
	}

	resetExplosions(explosions, explosionCount), resetExplosions(explosions1, explosionCount1), resetExplosions(explosions2, explosionCount2), resetExplosions(explosions21, explosionCount21), resetExplosions(explosions22, explosionCount22), resetExplosions(explosions23, explosionCount23), resetExplosions(explosions3, explosionCount3), resetExplosions(explosions4, explosionCount4), resetExplosions(explosions5, explosionCount5), resetExplosions(explosions6, explosionCount6), resetExplosions(explosions7, explosionCount7), resetExplosions(explosions8, explosionCount8), resetExplosions(explosions9, explosionCount9), resetExplosions(explosions10, explosionCount10), resetExplosions(explosions11, explosionCount11), resetExplosions(explosions12, explosionCount12), resetExplosions(explosions13, explosionCount13), resetExplosions(explosions14, explosionCount14), resetExplosions(explosions15, explosionCount15), resetExplosions(explosions16, explosionCount16), resetExplosions(explosions17, explosionCount17), resetExplosions(explosions18, explosionCount18), resetExplosions(explosions19, explosionCount19), resetExplosions(explosions20, explosionCount20);
	resetmeteorExplosions(meteordamage2, meteorExpcount2), resetmeteorExplosions(meteordamage3, meteorExpcount3), resetmeteorExplosions(meteordamage4, meteorExpcount4), resetmeteorExplosions(meteordamage5, meteorExpcount5), resetmeteorExplosions(meteordamage6, meteorExpcount6), resetmeteorExplosions(meteordamage7, meteorExpcount7), resetmeteorExplosions(meteordamage8, meteorExpcount8), resetmeteorExplosions(meteordamage9, meteorExpcount9);
	len = 0;
	memset(str1, '\0', sizeof(str1));
	newscore = false;
}

void resetExplosions(Explosion explosions[], int count)
{
	for (int i = 0; i < count; i++)
	{
		explosions[i].active = false;
		explosions[i].explosionIdx = 0;
		explosions[i].timer = 0;
	}
}

void resetmeteorExplosions(meteorDam explosions[], int explosionCount)
{
	for (int i = 0; i < explosionCount; i++)
	{
		explosions[i].active = false;
		explosions[i].explosionIdx = 0;
		explosions[i].timer = 0;
	}
}

void gameoverpic()
{
	iShowBMP(0, 0, gameover[0]);
}

void iMouseMove(int mx, int my)
{
}
void iMouse(int button, int state, int mx, int my)
{
	printf("%d %d\n",mx,my);
	if (homePage == 1 && (mx >= 517 && mx <= 791) && (my >= 544 && my <= 614))
	{
		gameReset();
		startButtonClick();
		PlaySound(0, 0, 0);
		PlaySound("music2.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	else if (homePage == 1 && (mx >= 491 && mx <= 818) && (my >= 429 && my <= 522))
	{
		gamecompletepage = 0;
		aboutButtonClick();
	}

	else if (homePage == 1 && (mx >= 502 && mx <= 802) && (my >= 207 && my <= 297))
	{
		gamecompletepage = 0;
		scoreButtonClick();
	}

	else if (homePage == 1 && (mx >= 517 && mx <= 793) && (my >= 331 && my <= 411))
	{
		gamecompletepage = 0;
		settingButtonClick();
	}

	else if (homePage == 1 && (mx >= 502 && mx <= 802) && (my >= 93 && my <= 182))
	{
		gamecompletepage = 0;
		musicButtonClick();
	}

	else if ((homePage == 1 | aboutPage == 1 | scorepage == 1 | settingpage == 1 | musicpage == 1) && (mx >= 34 && mx <= 76) && (my >= 696 && my <= 737))
	{
		gamecompletepage = 0;
		backButtonClick();
	}

	else if (gameoverpage == 1 && (mx >= 266 && mx <= 408) && (my >= 351 && my <= 410))
	{
		backButtonClick();
		PlaySound(0, 0, 0);
		PlaySound("music3.wav", NULL, SND_LOOP | SND_ASYNC);			
	}

	else if (startpage == 1 && (mx >= 1156 && mx <= 1219) && (my >= 687 && my <= 741))
	{
		PlaySound(0, 0, 0);
		musicstate1 = 1;
		musicstate2 = 0;
	}

	else if (startpage == 1 && (mx >= 1255 && mx <= 1320) && (my >= 687 && my <= 741))
	{
		PlaySound("music2.wav", NULL, SND_LOOP | SND_ASYNC);
		musicstate1 = 0;
		musicstate2 = 1;
	}

	else if (gameoverpage == 1 && (mx >= 932 && mx <= 1085) && (my >= 351 && my <= 410))
	{
		gameReset();
		startButtonClick();
		PlaySound(0, 0, 0);
		PlaySound("music2.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	else if (musicpage == 1 && (mx >= 726 && mx <= 893) && (my >= 367 && my <= 466))
	{
		PlaySound(0, 0, 0);
	}

	else if (musicpage == 1 && (mx >= 451 && mx <= 575) && (my >= 367 && my <= 465))
	{
		PlaySound("music3.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	else if(gamecompletepage == 1 && (mx >= 48 && mx <= 220) && (my >= 676 && my <= 727))
	{
		backButtonClick();
		PlaySound(0, 0, 0);
		PlaySound("music3.wav", NULL, SND_LOOP | SND_ASYNC);
	}
}

void iKeyboard(unsigned char key)
{
	if (gameoverpage == 1)
		takeInput(key);
	else if(gamecompletepage == 1)
		takeInput(key);
}

void iSpecialKeyboard(unsigned char key)
{
	if (startpage == 1)
	{
		if (key == GLUT_KEY_RIGHT)
			playershipx += 17;
		if (playershipx > screenwidth - 100)
			playershipx = screenwidth - 100;

		else if (key == GLUT_KEY_DOWN)
			playershipy -= 20;
		if (playershipy < 35)
			playershipy = 35;

		else if (key == GLUT_KEY_LEFT)
			playershipx -= 17;
		if (playershipx < 5)
			playershipx = 5;

		else if (key == GLUT_KEY_UP)
			playershipy += 20;
		if (playershipy > 710)
			playershipy = 710;
	}
}

void setBackgroud()
{
	int sum = 0;
	for (int i = 0; i < 30; i++)
	{
		backgroundSky[i].y = sum;
		backgroundSky[i].x = 0;
		sum += 30;
	}
}

void changeBg()
{
	if (startpage == 1)
	{
		for (int i = 0; i < 30; i++)
		{
			backgroundSky[i].y -= bgSkyspeed;

			if (backgroundSky[i].y <= 0)
				backgroundSky[i].y = screenheight;
		}
	}
}

void shootBullet()
{
	if (bulletCount < maxBullets)
	{
		bullets[bulletCount].x = playershipx + 43;
		bullets[bulletCount].y = playershipy + 130;
		bulletCount++;
	}

	if (bulletCount < maxBullets)
	{
		bullets1[bulletCount].x = playershipx + 95;
		bullets1[bulletCount].y = playershipy + 130;
		bulletCount++;
	}

	if (hasBullet == true)
	{
		if (bulletcount1 < maxBullets)
		{
			bullets5[bulletcount1].x = playershipx + 20;
			bullets5[bulletcount1].y = playershipy + 90;
			bulletcount1++;
		}

		if (bulletcount2 < maxBullets)
		{
			bullets6[bulletcount2].x = playershipx + 95;
			bullets6[bulletcount2].y = playershipy + 90;
			bulletcount2++;
		}
	}

	if (hasBullet == false)
	{
		for (int i = 0; i < 6; i++)
		{
			bullets5[i].x = -1000;
			bullets5[i].y = -1000;
			bullets6[i].x = -1000;
			bullets6[i].y = -1000;
		}
	}
}

void moveBullets()
{
	if (startpage == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			bullets[i].y += 100;

			if (bullets[i].y > screenheight)
			{
				bullets[i].x = playershipx + 43;
				bullets[i].y = playershipy + 110;
			}
		}

		for (int i = 0; i < 6; i++)
		{
			bullets1[i].y += 100;

			if (bullets1[i].y > screenheight)
			{
				bullets1[i].x = playershipx + 95;
				bullets1[i].y = playershipy + 110;
			}
		}

		if (hasBullet == true)
		{
			for (int i = 0; i < 6; i++)
			{
				bullets5[i].y += 100;
				bullets5[i].x -= 60;

				if (bullets5[i].y > screenheight)
				{
					bullets5[i].x = playershipx + 43;
					bullets5[i].y = playershipy + 110;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets6[i].y += 100;
				bullets6[i].x += 60;

				if (bullets6[i].y > screenheight)
				{
					bullets6[i].x = playershipx + 95;
					bullets6[i].y = playershipy + 110;
				}
			}
		}

		enemyy1 -= 6;
		enemyy2 -= 5;
		enemyy3 -= 3;
		meteorX2 -= rand() % 10;
		meteorX3 += rand() % 10;
		meteorY2 -= 8;
		meteorY3 -= 9;

		collision();
		detectPlayerCollision();
	}
}

void shootEnemybullets()
{
	if (bulletCount < 1)
	{
		bullets2[bulletCount].x = enemyx1 + 89;
		bullets2[bulletCount].y = enemyy1 - 5;
		bulletCount++;
	}
	if (bulletCount < 1)
	{
		bullets3[bulletCount].x = enemyx2 + 42;
		bullets3[bulletCount].y = enemyy2 - 20;
		bulletCount++;
	}
	if (bulletCount < 1)
	{
		bullets4[bulletCount].x = enemyx3 + 42;
		bullets4[bulletCount].y = enemyy3 - 20;
		bulletCount++;
	}
}

void moveEnenmybullets()
{
	if (startpage == 1)
	{
		for (int i = 0; i < 1; i++)
		{
			bullets2[i].y -= 100;

			if (bullets2[i].y < 0)
			{
				bullets2[i].x = enemyx1 + 89;
				bullets2[i].y = enemyy1 - 15;
			}
		}
		for (int i = 0; i < 1; i++)
		{
			bullets3[i].y -= 100;

			if (bullets3[i].y < 0)
			{
				bullets3[i].x = enemyx2 + 42;
				bullets3[i].y = enemyy2 - 20;
			}
		}
		for (int i = 0; i < 1; i++)
		{
			bullets4[i].y -= 100;

			if (bullets4[i].y < 0)
			{
				bullets4[i].x = enemyx3 + 42;
				bullets4[i].y = enemyy3 - 20;
			}
		}
	}
}

void shootbossbullets()
{
		if (bulletcount11 < maxBullets)
		{
			bullets11[bulletcount11].x = bossX + 130;
			bullets11[bulletcount11].y = bossY + 50;
			bulletcount11++;
		}
		if (bulletcount22 < maxBullets)
		{
			bullets22[bulletcount22].x = bossX + 80;
			bullets22[bulletcount22].y = bossY + 50;
			bulletcount22++;
		}
		if (bulletcount33 < maxBullets)
		{
			bullets33[bulletcount33].x = bossX + 160;
			bullets33[bulletcount33].y = bossY + 80;
			bulletcount33++;
		}
		if (bulletcount44 < maxBullets)
		{
			bullets44[bulletcount44].x = bossX + 50;
			bullets44[bulletcount44].y = bossY + 80;
			bulletcount44++;
		}
		if (bulletcount55 < maxBullets)
		{
			bullets55[bulletcount55].x = bossX + 90;
			bullets55[bulletcount55].y = bossY + 30;
			bulletcount55++;
		}
		if (bulletcount66 < maxBullets)
		{
			bullets66[bulletcount66].x = bossX + 120;
			bullets66[bulletcount66].y = bossY + 30;
			bulletcount66++;
		}

}

void bossMovement()
{
	static bool movingRight = true;

	bossY -= 5;
	if (bossY <= 550)
	{
		bossY = 550;
	}
	if (bossX >= 1250)
	{
		movingRight = false;
	}
	else if (bossX <= 30)
	{
		movingRight = true;
	}

	if (movingRight)
	{
		bossX += 5;
	}
	else
	{
		bossX -= 5;
	}
}

void movebossbullets()
{
	if (startpage == 1)
	{
		if (bossTime)
		{
			for (int i = 0; i < 6; i++)
			{
				bullets11[i].x += 80;
				bullets11[i].y -= 80;

				if (bullets11[i].y < 0)
				{
					bullets11[i].x = bossX + 130;
					bullets11[i].y = bossY + 50;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets22[i].x -= 80;
				bullets22[i].y -= 80;

				if (bullets22[i].y < 0)
				{
					bullets22[i].x = bossX + 80;
					bullets22[i].y = bossY + 50;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets33[i].x += 125;
				bullets33[i].y -= 80;

				if (bullets33[i].y < 0)
				{
					bullets33[i].x = bossX + 160;
					bullets33[i].y = bossY + 80;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets44[i].x -= 125;
				bullets44[i].y -= 80;

				if (bullets44[i].y < 0)
				{
					bullets44[i].x = bossX + 50;
					bullets44[i].y = bossY + 50;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets55[i].x -= 25;
				bullets55[i].y -= 70;

				if (bullets55[i].y < 0)
				{
					bullets55[i].x = bossX + 90;
					bullets55[i].y = bossY + 30;
				}
			}

			for (int i = 0; i < 6; i++)
			{
				bullets66[i].x += 25;
				bullets66[i].y -= 70;

				if (bullets66[i].y < 0)
				{
					bullets66[i].x = bossX + 120;
					bullets66[i].y = bossY + 30;
				}
			}
		}
	}
}

int main()
{
	PlaySound("music3.wav", NULL, SND_LOOP | SND_ASYNC);
	setBackgroud();
	shootEnemybullets();
	shootbossbullets();
	iSetTimer(35, moveBullets);
	iSetTimer(300, moveEnenmybullets);
	iSetTimer(35, bossMovement);
	iInitialize(screenwidth, screenheight, " SPACE SHOOTER ");
	return 0;
}
