#include "Global.h"

int main()
{
	Init(); 
	CircleShape shaforrobot(4, 6);
	shaforrobot.setOrigin(4, 4);
	shaforrobot.setFillColor(Color(255, 255, 255));
	shaforrobot.setOutlineThickness(2);
	shaforrobot.setOutlineColor(Color(0, 0, 0));
	CircleShape mousesh(5, 4);
	mousesh.setOrigin(5, 5);
	mousesh.setFillColor(Color(255, 200, 200));
	mousesh.setOutlineThickness(2);
	mousesh.setOutlineColor(Color(0, 0, 0));
	while (window.isOpen())
	{
		while (window.isOpen() && gamestate == GameState::ChooseMode)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			text.setCharacterSize(96);
			window.clear();
			text.setString(alltext[0][int(lang)]);
			text.setPosition(ScreenSize[0] / 4 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 - 48);
			if (text.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
			{
				text.setFillColor(Color(170, 170, 170));
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					gamestate = GameState::HumanGame;
					globaltime.restart();
				}
			}
			else text.setFillColor(Color(255, 255, 255));
			window.draw(text);
			text.setString(alltext[1][int(lang)]);
			text.setPosition((ScreenSize[0] / 4) * 3 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 - 48);
			if (text.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
			{
				text.setFillColor(Color(170, 170, 170));
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					gamestate = GameState::BotGame;
					globaltime.restart();
					timeforsolving.restart();
				}
			}
			else text.setFillColor(Color(255, 255, 255));
			window.draw(text);
			text.setFillColor(Color(255, 255, 255));
			text.setCharacterSize(24);
			text.setString(alltext[2][int(lang)]);
			text.setPosition(ScreenSize[0] / 2 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 - ScreenSize[1] / 5);
			window.draw(text);
			text.setCharacterSize(64);
			text.setString(alltext[3][int(lang)]);
			text.setPosition(ScreenSize[0] / 2 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 - ScreenSize[1] / 3);
			window.draw(text);

			text.setString("ENG");
			text.setPosition(ScreenSize[0] / 4 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 + 200);
			if (text.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
			{
				text.setFillColor(Color(170 - 30 * (lang == Language::Eng), 170 - 30 * (lang == Language::Eng), 170 - 30 * (lang == Language::Eng)));
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					lang = Language::Eng;
					globaltime.restart();
				}
			}
			else text.setFillColor(Color(255 - 30 * (lang == Language::Eng), 255 - 30 * (lang == Language::Eng), 255 - 30 * (lang == Language::Eng)));
			window.draw(text);
			text.setString(L"ÐÓÑ");
			text.setPosition((ScreenSize[0] / 4) * 3 - text.getGlobalBounds().width / 2, ScreenSize[1] / 2 + 200);
			if (text.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y))
			{
				text.setFillColor(Color(170 - 30 * (lang == Language::Eng), 170 - 30 * (lang == Language::Eng), 170 - 30 * (lang == Language::Eng)));
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					lang = Language::Rus;
					globaltime.restart();
				}
			}
			else text.setFillColor(Color(255 - 30 * (lang == Language::Eng), 255 - 30 * (lang == Language::Eng), 255 - 30 * (lang == Language::Eng)));
			window.draw(text);

			window.display();
		}
		while (window.isOpen() && gamestate == GameState::HumanGame)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			window.clear();
			for (int x = 0; x < 40; x++)
				for (int y = 0; y < 20; y++)
				{
					if (gamemap[y][x] == 2)
					{
						doorsprite.spr.setPosition(x * rc.getGlobalBounds().width,
							y * rc.getGlobalBounds().height + rc.getGlobalBounds().height * 3);
						window.draw(doorsprite.spr);
					}
					else
					{
						rc.setPosition(x * rc.getGlobalBounds().width, y * rc.getGlobalBounds().height + rc.getGlobalBounds().height * 3);
						if (gamemap[y][x] == 1) rc.setFillColor(Color(0, 0, 0));
						else  rc.setFillColor(Color(255, 255, 255));
						window.draw(rc);
					}
				}
			if (idti.x != -1)
			{
				if (pathclock.getElapsedTime().asSeconds() > 5)
				{
					if (pathclock.getElapsedTime().asMilliseconds() % 1000 > 500)
						window.draw(magictanglesprite[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
				}
				else
					window.draw(magictanglesprite[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
				HowToGet(idti, Vector2i(player.pos.x, player.pos.y), true);
				CircleShape sha(6, 6);
				sha.setOrigin(6, 6);
				sha.setPosition(
					(idti.x) * rc.getGlobalBounds().width + (rc.getGlobalBounds().width / 2),
					(idti.y) * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height + (rc.getGlobalBounds().width / 2));
				sha.setFillColor(Color(0, 0, 0));
				window.draw(sha);
			}
			window.draw(buddysprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			window.draw(foesprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			window.draw(treasuresprite.spr);
			playersprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr.setPosition(
				player.pos.x * rc.getGlobalBounds().width,
				player.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
			window.draw(playersprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			for (int i = 0; i < QofEnemies; i++)
			{
				if (enemies[i].died)
				{
					enemysprites[0].spr.setScale(2, 2);
					enemysprites[0].spr.setPosition(
						enemies[i].pos.x * rc.getGlobalBounds().width,
						enemies[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					enemysprites[0].spr.setColor(Color(167, 127, 127));
					window.draw(enemysprites[0].spr);
				}
				else
				{
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setScale(2, 2);
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setPosition(
						enemies[i].pos.x * rc.getGlobalBounds().width,
						enemies[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setColor(Color(255, 255, 255));
					window.draw(enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr);
				}
			}
			text.setFillColor(Color(255, 255, 255)); 
			text.setCharacterSize(rc.getGlobalBounds().height);
			text.setString(alltext[4][int(lang)]);
			text.setPosition(rc.getGlobalBounds().height / 2, rc.getGlobalBounds().height / 3);
			window.draw(text);
			wstringstream ss; ss << alltext[6][int(lang)] << (3 - finded);
			text.setString(ss.str());
			text.setPosition(
				ScreenSize[0] - rc.getGlobalBounds().height / 2 - text.getGlobalBounds().width,
				rc.getGlobalBounds().height + rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height / 3);
			window.draw(text);
			for (int i = 0; i < player.health; i++)
			{
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setPosition(
					rc.getGlobalBounds().height / 2 + (rc.getGlobalBounds().height + rc.getGlobalBounds().height / 3) * i,
					rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height);
				window.draw(heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr);
			}
			for (int i = bombs.size() - 1; i >= 0; i--)
			{
				if (bombs[i].timer.getElapsedTime().asSeconds() < 3)
				{
					boomsprites[0].spr.setPosition(
						bombs[i].pos.x * rc.getGlobalBounds().width,
						bombs[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					window.draw(boomsprites[0].spr);
				}
				else
					if (bombs[i].timer.getElapsedTime().asSeconds() < 4)
					{
						boomsprites[1].spr.setPosition(
							bombs[i].pos.x * rc.getGlobalBounds().width,
							bombs[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
						window.draw(boomsprites[1].spr);
						if (abs(bombs[i].pos.x - player.pos.x) <= 1 && abs(bombs[i].pos.y - player.pos.y) <= 1
							&& bombs[i].hittedplayer == false)
						{
							bombs[i].hittedplayer = true;
							player.health--; uronapol++;
						}
						for (int u = 0; u < QofEnemies; u++)
							if (abs(bombs[i].pos.x - enemies[u].pos.x) <= 1.5f && abs(bombs[i].pos.y - enemies[u].pos.y) <= 1.5f)
							{
								if (!enemies[u].died)
								{
									killed++;
									enemies[u].died = true;
								}
							}
					}
					else
					{
						bombs.erase(bombs.begin() + i);
					}
			}
			if ((abs(player.pos.x - buddy.pos.x) <= 1 && abs(player.pos.y - buddy.pos.y) <= 1) ||
				(abs(player.pos.x - foe.pos.x) <= 1 && abs(player.pos.y - foe.pos.y) <= 1))
			{
				text.setString(alltext[7][int(lang)]);
				text.setPosition(
					ScreenSize[0] - rc.getGlobalBounds().height / 2 - text.getGlobalBounds().width, 
					rc.getGlobalBounds().height / 3);
				window.draw(text);
				if (solvetimer.getElapsedTime().asMilliseconds() > 350)
				{
					if (Keyboard::isKeyPressed(Keyboard::F))
					{
						solvetimer.restart();
						if (abs(player.pos.x - buddy.pos.x) <= 1 && abs(player.pos.y - buddy.pos.y) <= 1)
						{
							bool talking = true;
							while (window.isOpen() && talking)
							{
								Event event;
								while (window.pollEvent(event))
								{
									if (event.type == Event::Closed) window.close();
								}
								if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
								window.clear(Color(255, 255, 255));
								if (player.health == 10) text.setString(alltext[19][int(lang)]);
								else
								{
									if (buddy.activated == false)
									{
										text.setString(alltext[20][int(lang)]);
									}
									else
									{
										text.setString(alltext[21][int(lang)]);
									}
								}
								text.setPosition(
									ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
									ScreenSize[1] / 2 - text.getGlobalBounds().height / 2);
								window.draw(text);
								if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 2000)
								{
									text.setString(alltext[18][int(lang)]);
									text.setPosition(
										ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
										ScreenSize[1] / 2 + ScreenSize[1] / 10);
									window.draw(text);
								}
								window.display();
								if (Keyboard::isKeyPressed(Keyboard::F) &&
									pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 2000)
								{
									talking = false; solvetimer.restart();
								}
							}
							if (player.health < 10)
							{
								if (buddy.activated == false)
								{
									help++;
									player.health = 10;
								}
								buddy.activated = true;
							}
						}
						else
						{
							bool talking = true;
							while (window.isOpen() && talking)
							{
								Event event;
								while (window.pollEvent(event))
								{
									if (event.type == Event::Closed) window.close();
								}
								if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
								window.clear(Color(255, 255, 255));
								if (foe.activated == false)
								{
									signaltimer.restart();
									for (int i = 0; i < QofEnemies; i++) enemies[i].signalized = true;
									text.setString(alltext[22][int(lang)]);
								}
								else
								{
									text.setString(alltext[23][int(lang)]);
								}
								text.setPosition(
									ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
									ScreenSize[1] / 2 - text.getGlobalBounds().height / 2);
								window.draw(text);
								if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 2000)
								{
									text.setString(alltext[18][int(lang)]);
									text.setPosition(
										ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
										ScreenSize[1] / 2 + ScreenSize[1] / 10);
									window.draw(text);
								}
								window.display();
								if (Keyboard::isKeyPressed(Keyboard::F) &&
									pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 2000)
								{
									talking = false; solvetimer.restart();
								}
							}
							if (!foe.activated)
							{
								foe.activated = true; vred++;
							}
						}
					}
				}
			}
			window.display();
			if (pathclock.getElapsedTime().asSeconds() > 10) idti = Vector2i(-1, -1);
			if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 250)
			{
				if (Keyboard::isKeyPressed(Keyboard::Key::K))
				{
					pathclock.restart();
					Vector2i mouse = Mouse::getPosition();
					if (mouse.y > rc.getGlobalBounds().height * 3)
					{
						mouse.y -= rc.getGlobalBounds().height * 3;
						mouse.x /= rc.getGlobalBounds().height;
						mouse.y /= rc.getGlobalBounds().height;
						if (gamemap[mouse.y][mouse.x] == 0) idti = mouse;
					}
				}
				pushbuttoncooldownclock.restart();
				postpos = player.pos;
				if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up)) player.pos.y--;
				if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down)) player.pos.y++;
				if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left)) player.pos.x--;
				if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right)) player.pos.x++;
				if (player.pos.y < 0 || player.pos.y > 19 || player.pos.x < 0 || player.pos.x > 39) player.pos = postpos;
				if (gamemap[int(player.pos.y)][int(player.pos.x)] == 1) player.pos = postpos;
				if (gamemap[int(player.pos.y)][int(player.pos.x)] == 2)
				{
					gamestate = GameState::DoorHack;
					for (int i = 0; i < 10; i++) pressed[i] = false;
					x = rand() % 10;
					a = rand() % 11 - 5;
					b = rand() % 11 - 5;
					c = -(a * x * x + b * x);
					window.clear();
					timeforsolving.restart();
					solve = false;
				}
				if (postpos != player.pos)
				{
					putlen++;
					for (int i = 0; i < QofEnemies; i++)
					{
						enemies[i].pos.x = int(enemies[i].pos.x);
						enemies[i].pos.y = int(enemies[i].pos.y);
						if (player.pos == enemies[i].pos) enemies[i].pos = postpos;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Space))
				{
					if (bombs.size() < 3)
					{
						bool mayi = true;
						for (int i = 0; i < bombs.size(); i++)
							if (bombs[i].pos == player.pos) mayi = false;
						if (mayi)
						{
							bombs.push_back(Bomb(player.pos)); bomb++;
						}
					}
				}
				if (player.pos == treasure.pos)
				{
					finded++;
					do treasure.pos = Vector2f(rand() % 40, rand() % 20); while (
						gamemap[int(treasure.pos.y)][int(treasure.pos.x)] != 0 ||
						(abs(treasure.pos.x - player.pos.x) + abs(treasure.pos.y - player.pos.y)) < 7);
					do buddy.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(buddy.pos.y)][int(buddy.pos.x)] != 0 || buddy.pos == treasure.pos);
					do foe.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(foe.pos.y)][int(foe.pos.x)] != 0 ||
						foe.pos == treasure.pos || foe.pos == buddy.pos);
					for (int i = 0; i < QofEnemies; i++)
					{
						do enemies[i].pos = Vector2f(rand() % 40, rand() % 18 + 2); while
							(gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x)] != 0);
						enemies[i].died = false;
					}
					buddy.activated = false;
					foe.activated = false;
					treasuresprite.spr.setPosition(treasure.pos.x* rc.getGlobalBounds().width, treasure.pos.y* rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					for (int i = 0; i < 2; i++)
					{
						buddysprites[i].spr.setPosition(buddy.pos.x * rc.getGlobalBounds().width, buddy.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
						foesprites[i].spr.setPosition(foe.pos.x * rc.getGlobalBounds().width, foe.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					}
					for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++)
						if (gamemap[y][x] == 2) gamemap[y][x] = 1;
					for (int x = 1; x < 39; x++) for (int y = 1; y < 19; y += 2)
						if (gamemap[y - 1][x] == 0 && gamemap[y][x] == 1 && gamemap[y][x - 1] == 1
							&& gamemap[y][x + 1] == 1 && gamemap[y + 1][x] == 0) if (rand() % 8 == 0) gamemap[y][x] = 2;
				}
			}
			if (moveenemiesclock.getElapsedTime().asMilliseconds() > 400)
			{
				moveenemiesclock.restart();
				for (int i = 0; i < QofEnemies; i++)
					if (!enemies[i].died)
					{
						if (enemies[i].signalized)
						{
							Vector3i wherego = HowToGet(
								Vector2i(player.pos.x, player.pos.y),
								Vector2i(enemies[i].pos.x, enemies[i].pos.y), false);
							bool mayi = true;
							for (int u = 0; u < QofEnemies; u++)
								if (abs(enemies[i].pos.x - enemies[u].pos.x + wherego.x) < 1 &&
									abs(enemies[i].pos.y - enemies[u].pos.y + wherego.y) < 1 && enemies[u].died == false) mayi = false;
							if (mayi)
							{
								enemies[i].pos.x += wherego.x;
								enemies[i].pos.y += wherego.y;
							}
						}
						else
						{
							bool moved = false;
							bool isseeplayer = false;
							//cout << enemies[i].pos.x << " " << enemies[i].pos.y << endl;
							if (abs(player.pos.x - enemies[i].pos.x) == 1.0f && abs(player.pos.y - enemies[i].pos.y) == 1.0f)
							{
								if (player.pos.x > enemies[i].pos.x && !moved) if (enemies[i].pos.x + 1 <= 39)
									if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x + 1)] == 0) enemies[i].pos.x += 1 + (moved++) * 0;
								if (player.pos.x < enemies[i].pos.x && !moved) if (enemies[i].pos.x - 1 >= 0)
									if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x - 1)] == 0) enemies[i].pos.x += -1 + (moved++) * 0;
								if (player.pos.y > enemies[i].pos.y && !moved) if (enemies[i].pos.y + 1 <= 19)
									if (gamemap[int(enemies[i].pos.y + 1)][int(enemies[i].pos.x)] == 0) enemies[i].pos.y += 1 + (moved++) * 0;
								if (player.pos.y < enemies[i].pos.y && !moved) if (enemies[i].pos.y - 1 >= 0)
									if (gamemap[int(enemies[i].pos.y - 1)][int(enemies[i].pos.x)] == 0) enemies[i].pos.y += -1 + (moved++) * 0;
							}
							if (!moved)
							{
								if (player.pos.x == enemies[i].pos.x && abs(player.pos.y - enemies[i].pos.y) >= 1.0f)
								{
									isseeplayer = true;
									for (int y = enemies[i].pos.y; y != player.pos.y; y += (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y))
										if (gamemap[y][int(enemies[i].pos.x)] != 0) isseeplayer = false;
									if (isseeplayer)
									{
										enemies[i].signalized = false;
										if (abs(player.pos.y - enemies[i].pos.y) <= 1)
										{
											if (enemies[i].pos.y + (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y) == player.pos.y)
												enemies[i].pos.y += ((player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y)) * 0.4f;
											if (rand() % 1 == 0) player.health--;
											uronapol++;
										}
										else
										{
											bool mayi = true;
											for (int u = 0; u < QofEnemies; u++)
												if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
													abs(enemies[i].pos.y - enemies[u].pos.y + (player.pos.y - enemies[i].pos.y)
														/ abs(player.pos.y - enemies[i].pos.y)) < 1 && enemies[u].died == false) mayi = false;
											if (mayi) enemies[i].pos.y += (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y);
										}
										moved = true;
									}
								}
								if (player.pos.y == enemies[i].pos.y && abs(player.pos.x - enemies[i].pos.x) >= 1.0f)
								{
									isseeplayer = true;
									for (int x = enemies[i].pos.x; x != player.pos.x; x += (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x))
										if (gamemap[int(enemies[i].pos.y)][x] != 0) isseeplayer = false;
									if (isseeplayer)
									{
										enemies[i].signalized = false;
										if (abs(player.pos.x - enemies[i].pos.x) <= 1)
										{
											if (enemies[i].pos.x + (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x) == player.pos.x)
												enemies[i].pos.x += ((player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x)) * 0.4f;
											if (rand() % 1 == 0) player.health--;
											uronapol++;
										}
										else
										{
											bool mayi = true;
											for (int u = 0; u < QofEnemies; u++)
												if (abs(enemies[i].pos.x - enemies[u].pos.x + (player.pos.x - enemies[i].pos.x) /
													abs(player.pos.x - enemies[i].pos.x)) < 1 &&
													abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
											if (mayi) enemies[i].pos.x += (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x);
										}
										moved = true;
									}
								}
							}
							if (!moved && !(abs(player.pos.x - enemies[i].pos.x) < 1.0f && abs(player.pos.y - enemies[i].pos.y) < 1.0f))
							{
								if (rand() % 2 == 0)
								{
									if (rand() % 2 == 0) {
										if (enemies[i].pos.x + 1 <= 39)
											if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x + 1)] == 0)
											{
												bool mayi = true;
												for (int u = 0; u < QofEnemies; u++)
													if (abs(enemies[i].pos.x - enemies[u].pos.x + 1) < 1 &&
														abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
												if (mayi) enemies[i].pos.x += 1;
											}
											else {
												if (enemies[i].pos.x - 1 >= 0) if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x - 1)] == 0)
												{
													bool mayi = true;
													for (int u = 0; u < QofEnemies; u++)
														if (abs(enemies[i].pos.x - enemies[u].pos.x - 1) < 1 &&
															abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
													if (mayi) enemies[i].pos.x -= 1;
												}
											}
									}
									else
									{
										if (rand() % 2 == 0) {
											if (enemies[i].pos.y + 1 <= 19)
												if (gamemap[int(enemies[i].pos.y + 1)][int(enemies[i].pos.x)] == 0)
												{
													bool mayi = true;
													for (int u = 0; u < QofEnemies; u++)
														if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
															abs(enemies[i].pos.y - enemies[u].pos.y + 1) < 1 && enemies[u].died == false) mayi = false;
													if (mayi) enemies[i].pos.y += 1;
												}
										}
										else {
											if (enemies[i].pos.y - 1 >= 0) if (gamemap[int(enemies[i].pos.y - 1)][int(enemies[i].pos.x)] == 0)
											{
												bool mayi = true;
												for (int u = 0; u < QofEnemies; u++)
													if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
														abs(enemies[i].pos.y - enemies[u].pos.y - 1) < 1 && enemies[u].died == false) mayi = false;
												if (mayi) enemies[i].pos.y -= 1;
											}
										}
									}
								}
							}
						}
					}
			}
			if (comebackenemiesclock.getElapsedTime().asMilliseconds() > 75)
			{
				comebackenemiesclock.restart();
				for (int i = 0; i < QofEnemies; i++)
				{
					if (int(enemies[i].pos.x * 10) % 10 > 0 && int(enemies[i].pos.x * 10) % 10 < 5) enemies[i].pos.x -= 0.1f;
					if (int(enemies[i].pos.x * 10) % 10 > 5 && int(enemies[i].pos.x * 10) % 10 <= 9) enemies[i].pos.x += 0.1f;
					if (int(enemies[i].pos.y * 10) % 10 > 0 && int(enemies[i].pos.y * 10) % 10 < 5) enemies[i].pos.y -= 0.1f;
					if (int(enemies[i].pos.y * 10) % 10 > 5 && int(enemies[i].pos.y * 10) % 10 <= 9) enemies[i].pos.y += 0.1f;
					enemies[i].pos.x = (int(enemies[i].pos.x * 100.0f) / 10) * 0.1f;
					enemies[i].pos.y = (int(enemies[i].pos.y * 100.0f) / 10) * 0.1f;
				}
			}
			if (signaltimer.getElapsedTime().asSeconds() > 15) for (int i = 0; i < QofEnemies; i++) enemies[i].signalized = false;
			if (finded == 3 || player.health <= 0)
			{
				gamestate = GameState::Conclusion;
				timeintheend = globaltime.getElapsedTime().asMilliseconds() * 0.001f;
			}
		}
		while (window.isOpen() && gamestate == GameState::BotGame)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			window.clear();
			for (int x = 0; x < 40; x++)
				for (int y = 0; y < 20; y++)
				{
					if (gamemap[y][x] == 5)
					{
						rc.setPosition(x* rc.getGlobalBounds().width, y* rc.getGlobalBounds().height + rc.getGlobalBounds().height * 3);
						rc.setFillColor(Color(127, 0, 0));
						window.draw(rc);
					}
					else
					if (gamemap[y][x] == 2)
					{
						doorsprite.spr.setPosition(x * rc.getGlobalBounds().width,
							y * rc.getGlobalBounds().height + rc.getGlobalBounds().height * 3);
						window.draw(doorsprite.spr);
					}
					else
					{
						rc.setPosition(x * rc.getGlobalBounds().width, y * rc.getGlobalBounds().height + rc.getGlobalBounds().height * 3);
						if (gamemap[y][x] == 1) rc.setFillColor(Color(0, 0, 0));
						else  rc.setFillColor(Color(255, 255, 255));
						window.draw(rc);
					}
				}
			window.draw(buddysprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			window.draw(foesprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			window.draw(treasuresprite.spr);
			playersprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr.setPosition(
				player.pos.x * rc.getGlobalBounds().width,
				player.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
			window.draw(playersprites[int(spriteanimclock.getElapsedTime().asSeconds()) % 2].spr);
			for (int i = 0; i < QofEnemies; i++)
			{
				if (enemies[i].died)
				{
					enemysprites[0].spr.setScale(2, 2);
					enemysprites[0].spr.setPosition(
						enemies[i].pos.x * rc.getGlobalBounds().width,
						enemies[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					enemysprites[0].spr.setColor(Color(167, 127, 127));
					window.draw(enemysprites[0].spr);
				}
				else
				{
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setScale(2, 2);
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setPosition(
						enemies[i].pos.x * rc.getGlobalBounds().width,
						enemies[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setColor(Color(255, 255, 255));
					window.draw(enemysprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr);
				}
			}
			text.setFillColor(Color(255, 255, 255));
			text.setCharacterSize(rc.getGlobalBounds().height);
			text.setString(alltext[5][int(lang)]);
			text.setPosition(rc.getGlobalBounds().height / 2, rc.getGlobalBounds().height / 3);
			window.draw(text);
			wstringstream ss; ss << alltext[6][int(lang)] << (3 - finded);
			text.setString(ss.str());
			text.setPosition(
				ScreenSize[0] - rc.getGlobalBounds().height / 2 - text.getGlobalBounds().width,
				rc.getGlobalBounds().height + rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height / 3);
			window.draw(text);
			for (int i = 0; i < player.health; i++)
			{
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setPosition(
					rc.getGlobalBounds().height / 2 + (rc.getGlobalBounds().height + rc.getGlobalBounds().height / 3) * i,
					rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height / 3 + rc.getGlobalBounds().height);
				window.draw(heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr);
			}
			for (int i = bombs.size() - 1; i >= 0; i--)
			{
				if (bombs[i].timer.getElapsedTime().asSeconds() < 3)
				{
					boomsprites[0].spr.setPosition(
						bombs[i].pos.x * rc.getGlobalBounds().width,
						bombs[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					window.draw(boomsprites[0].spr);
				}
				else
					if (bombs[i].timer.getElapsedTime().asSeconds() < 4)
					{
						boomsprites[1].spr.setPosition(
							bombs[i].pos.x * rc.getGlobalBounds().width,
							bombs[i].pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
						window.draw(boomsprites[1].spr);
						if (abs(bombs[i].pos.x - player.pos.x) <= 1 && abs(bombs[i].pos.y - player.pos.y) <= 1
							&& bombs[i].hittedplayer == false)
						{
							bombs[i].hittedplayer = true;
							player.health--; uronapol++;
						}
						for (int u = 0; u < QofEnemies; u++)
							if (abs(bombs[i].pos.x - enemies[u].pos.x) <= 1.5f && abs(bombs[i].pos.y - enemies[u].pos.y) <= 1.5f)
							{
								if (!enemies[u].died)
								{
									killed++;
									enemies[u].died = true;
								}
							}
					}
					else
					{
						bombs.erase(bombs.begin() + i);
					}
			}
			if (abs(player.pos.x - buddy.pos.x) <= 1 && abs(player.pos.y - buddy.pos.y) <= 1)
				if (player.health < 10 && buddy.activated == false)
				{
					player.health = 10;
					buddy.activated = true;
				}
			if (false)
			HowToGet1(
				Vector2i(treasure.pos.x, treasure.pos.y),
				Vector2i(player.pos.x, player.pos.y), true);
			for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++) if (gamemap[y][x] >= 10) gamemap[y][x] -= 10;
			if (true)
			{
				Vector2i need = Vector2i(player.pos.x, player.pos.y);
				while (!(need.x == treasure.pos.x && need.y == treasure.pos.y))
				{
					Vector3i res = HowToGet1(Vector2i(treasure.pos.x, treasure.pos.y), Vector2i(need.x, need.y), false);
					for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++) if (gamemap[y][x] >= 10) gamemap[y][x] -= 10;
					need.x += res.x;
					need.y += res.y;
					shaforrobot.setPosition(
						(need.x) * rc.getGlobalBounds().width + (rc.getGlobalBounds().width / 2),
						(need.y) * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height + (rc.getGlobalBounds().width / 2));
					window.draw(shaforrobot);
				}
			}
			if (true)
			{
				Vector2i mouse = Mouse::getPosition();
				if (mouse.y > rc.getGlobalBounds().height * 3)
				{
					mouse.y -= rc.getGlobalBounds().height * 3;
					mouse.x /= rc.getGlobalBounds().height;
					mouse.y /= rc.getGlobalBounds().height;
					mousesh.setPosition(
						(mouse.x) * rc.getGlobalBounds().width + (rc.getGlobalBounds().width / 2),
						(mouse.y) * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height + (rc.getGlobalBounds().width / 2));
					window.draw(mousesh);
				}
			}
			window.display();
			if (timeforsolving.getElapsedTime().asMilliseconds() > 150)
			{
				if (Mouse::isButtonPressed(Mouse::Button::Left) || Mouse::isButtonPressed(Mouse::Button::Right))
				{
					Vector2i mouse = Mouse::getPosition();
					if (mouse.y > rc.getGlobalBounds().height * 3)
					{
						timeforsolving.restart();
						mouse.y -= rc.getGlobalBounds().height * 3;
						mouse.x /= rc.getGlobalBounds().height;
						mouse.y /= rc.getGlobalBounds().height;
						if (Mouse::isButtonPressed(Mouse::Button::Left))
						{
							if (gamemap[mouse.y][mouse.x] == 0 || gamemap[mouse.y][mouse.x] == 2) gamemap[mouse.y][mouse.x] = 1;
							else if (gamemap[mouse.y][mouse.x] == 1) gamemap[mouse.y][mouse.x] = 2;
						}
						else gamemap[mouse.y][mouse.x] = 0;
					}
				}
			}
			if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 250)
			{
				pushbuttoncooldownclock.restart();
				Vector3i wheregobuddy = HowToGet1(
					Vector2i(buddy.pos.x, buddy.pos.y),
					Vector2i(player.pos.x, player.pos.y), true);
				for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++) if (gamemap[y][x] >= 10) gamemap[y][x] -= 10;
				Vector3i wherego = HowToGet1(
					Vector2i(treasure.pos.x, treasure.pos.y), 
					Vector2i(player.pos.x, player.pos.y), true);
				for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++) if (gamemap[y][x] >= 10) gamemap[y][x] -= 10;
				if (wheregobuddy.z < 10 && player.health < 9 && buddy.activated == false) wherego = wheregobuddy;
				if (wherego.x != -2 && rand() % 15 < 14)
				{
					if (gamemap[int(player.pos.y + wherego.y)][int(player.pos.x + wherego.x)] == 2)
					{
						if (rand() % 3 <= 1)
						{
							dvereio++;
							gamemap[int(player.pos.y + wherego.y)][int(player.pos.x + wherego.x)] = 0;
						}
						else
						{
							dvereiz++;
							gamemap[int(player.pos.y + wherego.y)][int(player.pos.x + wherego.x)] = 1;
						}
					}
					else
					{
						bool gogo = false;
						int lowest1 = 999, lowest2 = 999;
						for (int i = 0; i < bombs.size(); i++)
							if (abs(player.pos.x + wherego.x - bombs[i].pos.x) <= 1 && abs(player.pos.y + wherego.y - bombs[i].pos.y) <= 1)
								if (abs(player.pos.x + wherego.x - bombs[i].pos.x) + abs(player.pos.y + wherego.y - bombs[i].pos.y) < lowest1)
									lowest1 = abs(player.pos.x - bombs[i].pos.x + wherego.x) + abs(player.pos.y - bombs[i].pos.y + wherego.y);
						for (int i = 0; i < bombs.size(); i++)
							if (abs(player.pos.x - bombs[i].pos.x) <= 1 && abs(player.pos.y - bombs[i].pos.y) <= 1)
								if (abs(player.pos.x - bombs[i].pos.x) + abs(player.pos.y - bombs[i].pos.y) < lowest2)
									lowest2 = abs(player.pos.x - bombs[i].pos.x) + abs(player.pos.y - bombs[i].pos.y);
						if (lowest1 >= lowest2) gogo = true;
						if (!gogo && lowest2 < 2)
						{
							for (int u = 0; u < 8 && lowest1 < 2; u++)
							{
								wherego.x = 0; wherego.y = 0;
								if (rand() % 2)
								{
									if (rand() % 2) wherego.x = 1;
									else wherego.x = -1;
								}
								else
								{
									if (rand() % 2) wherego.y = 1;
									else wherego.y = -1;
								}
								for (int i = 0; i < bombs.size(); i++)
									if (abs(player.pos.x + wherego.x - bombs[i].pos.x) <= 1 && abs(player.pos.y + wherego.y - bombs[i].pos.y) <= 1)
										if (abs(player.pos.x + wherego.x - bombs[i].pos.x) + abs(player.pos.y + wherego.y - bombs[i].pos.y) < lowest1)
											lowest1 = abs(player.pos.x - bombs[i].pos.x + wherego.x) + abs(player.pos.y - bombs[i].pos.y + wherego.y);
								for (int i = 0; i < bombs.size(); i++)
									if (abs(player.pos.x - bombs[i].pos.x) <= 1 && abs(player.pos.y - bombs[i].pos.y) <= 1)
										if (abs(player.pos.x - bombs[i].pos.x) + abs(player.pos.y - bombs[i].pos.y) < lowest2)
											lowest2 = abs(player.pos.x - bombs[i].pos.x) + abs(player.pos.y - bombs[i].pos.y);
								if (lowest1 >= lowest2) gogo = true;
							}
						}
						else
						if (gogo)
						{
							putlen++;
							for (int i = 0; i < QofEnemies; i++)
							{
								enemies[i].pos.x = int(enemies[i].pos.x);
								enemies[i].pos.y = int(enemies[i].pos.y);
								if (enemies[i].pos.x == player.pos.x + wherego.x &&
									enemies[i].pos.y == player.pos.y + wherego.y) enemies[i].pos = player.pos;
							}
							player.pos.x += wherego.x;
							player.pos.y += wherego.y;
							//cout << wherego.z << endl;
							if (rand() % 6 == 0 && wherego.z > 10)
							{
								if (bombs.size() < 3)
								{
									bool mayi = true;
									for (int i = 0; i < bombs.size(); i++)
										if (bombs[i].pos == player.pos) mayi = false;
									if (mayi)
									{
										bombs.push_back(Bomb(player.pos)); bomb++;
									}
								}
							}
						}
					}
					if (player.pos == treasure.pos)
					{
						finded++;
						do treasure.pos = Vector2f(rand() % 40, rand() % 20); while (
							gamemap[int(treasure.pos.y)][int(treasure.pos.x)] != 0 ||
							(abs(treasure.pos.x - player.pos.x) + abs(treasure.pos.y - player.pos.y)) < 7);
						do buddy.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(buddy.pos.y)][int(buddy.pos.x)] != 0 || buddy.pos == treasure.pos);
						do foe.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(foe.pos.y)][int(foe.pos.x)] != 0 ||
							foe.pos == treasure.pos || foe.pos == buddy.pos);
						for (int i = 0; i < QofEnemies; i++)
						{
							do enemies[i].pos = Vector2f(rand() % 40, rand() % 18 + 2); while
								(gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x)] != 0);
							enemies[i].died = false;
						}
						buddy.activated = false;
						foe.activated = false;
						treasuresprite.spr.setPosition(treasure.pos.x * rc.getGlobalBounds().width, treasure.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
						for (int i = 0; i < 2; i++)
						{
							buddysprites[i].spr.setPosition(buddy.pos.x * rc.getGlobalBounds().width, buddy.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
							foesprites[i].spr.setPosition(foe.pos.x * rc.getGlobalBounds().width, foe.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
						}
						for (int x = 0; x < 40; x++) for (int y = 0; y < 20; y++)
							if (gamemap[y][x] == 2) gamemap[y][x] = 1;
						for (int x = 1; x < 39; x++) for (int y = 1; y < 19; y += 2)
							if (gamemap[y - 1][x] == 0 && gamemap[y][x] == 1 && gamemap[y][x - 1] == 1
								&& gamemap[y][x + 1] == 1 && gamemap[y + 1][x] == 0) if (rand() % 8 == 0) gamemap[y][x] = 2;
					}
				}
			}
			if (moveenemiesclock.getElapsedTime().asMilliseconds() > 400)
			{
				moveenemiesclock.restart();
				for (int i = 0; i < QofEnemies; i++)
					if (!enemies[i].died)
					{
						if (enemies[i].signalized)
						{
							Vector3i wherego = HowToGet(
								Vector2i(player.pos.x, player.pos.y),
								Vector2i(enemies[i].pos.x, enemies[i].pos.y), false);
							bool mayi = true;
							for (int u = 0; u < QofEnemies; u++)
								if (abs(enemies[i].pos.x - enemies[u].pos.x + wherego.x) < 1 &&
									abs(enemies[i].pos.y - enemies[u].pos.y + wherego.y) < 1 && enemies[u].died == false) mayi = false;
							if (mayi)
							{
								enemies[i].pos.x += wherego.x;
								enemies[i].pos.y += wherego.y;
							}
						}
						else
						{
							bool moved = false;
							bool isseeplayer = false;
							//cout << enemies[i].pos.x << " " << enemies[i].pos.y << endl;
							if (abs(player.pos.x - enemies[i].pos.x) == 1.0f && abs(player.pos.y - enemies[i].pos.y) == 1.0f)
							{
								if (player.pos.x > enemies[i].pos.x && !moved) if (enemies[i].pos.x + 1 <= 39)
									if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x + 1)] == 0) enemies[i].pos.x += 1 + (moved++) * 0;
								if (player.pos.x < enemies[i].pos.x && !moved) if (enemies[i].pos.x - 1 >= 0)
									if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x - 1)] == 0) enemies[i].pos.x += -1 + (moved++) * 0;
								if (player.pos.y > enemies[i].pos.y && !moved) if (enemies[i].pos.y + 1 <= 19)
									if (gamemap[int(enemies[i].pos.y + 1)][int(enemies[i].pos.x)] == 0) enemies[i].pos.y += 1 + (moved++) * 0;
								if (player.pos.y < enemies[i].pos.y && !moved) if (enemies[i].pos.y - 1 >= 0)
									if (gamemap[int(enemies[i].pos.y - 1)][int(enemies[i].pos.x)] == 0) enemies[i].pos.y += -1 + (moved++) * 0;
							}
							if (!moved)
							{
								if (player.pos.x == enemies[i].pos.x && abs(player.pos.y - enemies[i].pos.y) >= 1.0f)
								{
									isseeplayer = true;
									for (int y = enemies[i].pos.y; y != player.pos.y; y += (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y))
										if (gamemap[y][int(enemies[i].pos.x)] != 0) isseeplayer = false;
									if (isseeplayer)
									{
										enemies[i].signalized = false;
										if (abs(player.pos.y - enemies[i].pos.y) <= 1)
										{
											if (enemies[i].pos.y + (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y) == player.pos.y)
												enemies[i].pos.y += ((player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y)) * 0.4f;
											if (rand() % 1 == 0) player.health--;
											uronapol++;
										}
										else
										{
											bool mayi = true;
											for (int u = 0; u < QofEnemies; u++)
												if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
													abs(enemies[i].pos.y - enemies[u].pos.y + (player.pos.y - enemies[i].pos.y)
														/ abs(player.pos.y - enemies[i].pos.y)) < 1 && enemies[u].died == false) mayi = false;
											if (mayi) enemies[i].pos.y += (player.pos.y - enemies[i].pos.y) / abs(player.pos.y - enemies[i].pos.y);
										}
										moved = true;
									}
								}
								if (player.pos.y == enemies[i].pos.y && abs(player.pos.x - enemies[i].pos.x) >= 1.0f)
								{
									isseeplayer = true;
									for (int x = enemies[i].pos.x; x != player.pos.x; x += (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x))
										if (gamemap[int(enemies[i].pos.y)][x] != 0) isseeplayer = false;
									if (isseeplayer)
									{
										enemies[i].signalized = false;
										if (abs(player.pos.x - enemies[i].pos.x) <= 1)
										{
											if (enemies[i].pos.x + (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x) == player.pos.x)
												enemies[i].pos.x += ((player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x)) * 0.4f;
											if (rand() % 1 == 0) player.health--;
											uronapol++;
										}
										else
										{
											bool mayi = true;
											for (int u = 0; u < QofEnemies; u++)
												if (abs(enemies[i].pos.x - enemies[u].pos.x + (player.pos.x - enemies[i].pos.x) /
													abs(player.pos.x - enemies[i].pos.x)) < 1 &&
													abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
											if (mayi) enemies[i].pos.x += (player.pos.x - enemies[i].pos.x) / abs(player.pos.x - enemies[i].pos.x);
										}
										moved = true;
									}
								}
							}
							if (!moved && !(abs(player.pos.x - enemies[i].pos.x) < 1.0f && abs(player.pos.y - enemies[i].pos.y) < 1.0f))
							{
								if (rand() % 2 == 0)
								{
									if (rand() % 2 == 0) {
										if (enemies[i].pos.x + 1 <= 39)
											if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x + 1)] == 0)
											{
												bool mayi = true;
												for (int u = 0; u < QofEnemies; u++)
													if (abs(enemies[i].pos.x - enemies[u].pos.x + 1) < 1 &&
														abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
												if (mayi) enemies[i].pos.x += 1;
											}
											else {
												if (enemies[i].pos.x - 1 >= 0) if (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x - 1)] == 0)
												{
													bool mayi = true;
													for (int u = 0; u < QofEnemies; u++)
														if (abs(enemies[i].pos.x - enemies[u].pos.x - 1) < 1 &&
															abs(enemies[i].pos.y - enemies[u].pos.y) < 1 && enemies[u].died == false) mayi = false;
													if (mayi) enemies[i].pos.x -= 1;
												}
											}
									}
									else
									{
										if (rand() % 2 == 0) {
											if (enemies[i].pos.y + 1 <= 19)
												if (gamemap[int(enemies[i].pos.y + 1)][int(enemies[i].pos.x)] == 0)
												{
													bool mayi = true;
													for (int u = 0; u < QofEnemies; u++)
														if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
															abs(enemies[i].pos.y - enemies[u].pos.y + 1) < 1 && enemies[u].died == false) mayi = false;
													if (mayi) enemies[i].pos.y += 1;
												}
										}
										else {
											if (enemies[i].pos.y - 1 >= 0) if (gamemap[int(enemies[i].pos.y - 1)][int(enemies[i].pos.x)] == 0)
											{
												bool mayi = true;
												for (int u = 0; u < QofEnemies; u++)
													if (abs(enemies[i].pos.x - enemies[u].pos.x) < 1 &&
														abs(enemies[i].pos.y - enemies[u].pos.y - 1) < 1 && enemies[u].died == false) mayi = false;
												if (mayi) enemies[i].pos.y -= 1;
											}
										}
									}
								}
							}
						}
					}
			}
			if (comebackenemiesclock.getElapsedTime().asMilliseconds() > 75)
			{
				comebackenemiesclock.restart();
				for (int i = 0; i < QofEnemies; i++)
				{
					if (int(enemies[i].pos.x * 10) % 10 > 0 && int(enemies[i].pos.x * 10) % 10 < 5) enemies[i].pos.x -= 0.1f;
					if (int(enemies[i].pos.x * 10) % 10 > 5 && int(enemies[i].pos.x * 10) % 10 <= 9) enemies[i].pos.x += 0.1f;
					if (int(enemies[i].pos.y * 10) % 10 > 0 && int(enemies[i].pos.y * 10) % 10 < 5) enemies[i].pos.y -= 0.1f;
					if (int(enemies[i].pos.y * 10) % 10 > 5 && int(enemies[i].pos.y * 10) % 10 <= 9) enemies[i].pos.y += 0.1f;
					enemies[i].pos.x = (int(enemies[i].pos.x * 100.0f) / 10) * 0.1f;
					enemies[i].pos.y = (int(enemies[i].pos.y * 100.0f) / 10) * 0.1f;
				}
			}
			if (signaltimer.getElapsedTime().asSeconds() > 15) for (int i = 0; i < QofEnemies; i++) enemies[i].signalized = false;
			if (finded == 3 || player.health <= 0)
			{
				gamestate = GameState::Conclusion;
				timeintheend = globaltime.getElapsedTime().asMilliseconds() * 0.001f;
			}
		}
		while (window.isOpen() && gamestate == GameState::DoorHack)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			window.clear(Color(255, 255, 255));
			for (int i = 0; i < player.health; i++)
			{
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setScale(4, 4);
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setPosition(
					rc.getGlobalBounds().height + (rc.getGlobalBounds().height * 2 + rc.getGlobalBounds().height * 2 / 3) * i,
					rc.getGlobalBounds().height * 2 / 3 + rc.getGlobalBounds().height * 2 / 3 + rc.getGlobalBounds().height * 2);
				if (damage.getElapsedTime().asMilliseconds() < 500)
					heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setColor(Color(255, 0, 0));
				else
					heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setColor(Color(255, 255, 255));
				window.draw(heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr);
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setScale(2, 2);
				heartsprites[int(spriteanimclock.getElapsedTime().asSeconds() + i) % 2].spr.setColor(Color(255, 255, 255));
			}
			if (!solve)
				if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 400)
				{
					pushbuttoncooldownclock.restart();
					for (int i = 0; i < 10; i++)
					{
						pressed[i] = false;
						if (Keyboard::isKeyPressed(Keyboard::Key(26 + i)))
						{
							pressed[i] = true;
							if (i == x)
							{
								solvetimer.restart();
								solve = true;
							}
							else
							{
								player.health--; 
								uronapol++;
								damage.restart();
							}
						}
					}
				}
			if (solve && solvetimer.getElapsedTime().asSeconds() > 2)
			{
				gamestate = GameState::HumanGame;
				gamemap[int(player.pos.y)][int(player.pos.x)] = 0; dvereio++;
				player.pos = postpos;
			}
			for (int i = 0; i < 10; i++)
			{
				RectangleShape rc;
				rc.setSize(Vector2f(ScreenSize[0] / 10 - 6, ScreenSize[1] / 6 - 6));
				rc.setPosition((ScreenSize[0] / 10) * i + 3, (ScreenSize[1] / 6) * 5 + 3);
				rc.setFillColor(Color(0, 0, 0));
				if (pressed[i] && i == x) rc.setFillColor(Color(0, 255, 0));
				if (pressed[i] && i != x) rc.setFillColor(Color(255, 0, 0));
				window.draw(rc);
				text.setFillColor(Color(255, 255, 255));
				text.setCharacterSize(ScreenSize[1] / 8);
				stringstream ss1; ss1 << i;
				text.setString(ss1.str());
				text.setPosition(
					rc.getPosition().x + rc.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
					rc.getPosition().y + rc.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2
				);
				window.draw(text);
				if (pushbuttoncooldownclock.getElapsedTime().asMilliseconds() > 150)
					if (Mouse::isButtonPressed(Mouse::Button::Left) &&
						rc.getGlobalBounds().contains(Vector2f(Mouse::getPosition().x, Mouse::getPosition().y)))
					{
						pressed[i] = true;
						if (i == x)
						{
							solvetimer.restart();
							solve = true;
						}
						else
						{
							player.health--;
							uronapol++;
							damage.restart();
						}
					}

			}
			text.setFillColor(Color(0, 0, 0));
			text.setCharacterSize(rc.getGlobalBounds().height * 2);
			stringstream ss; 
			ss << a << "x^2 "; 
			if (b >= 0) ss << "+"; else ss << "-";
			ss << abs(b) << "x ";
			if (c >= 0) ss << "+"; else ss << "-";
			ss << abs(c) << " = 0";
			text.setString(ss.str());
			text.setPosition(
				ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
				ScreenSize[1] / 2 - text.getGlobalBounds().height / 2 - ScreenSize[1] / 12
			);
			window.draw(text);
			text.setString("x = ?");
			text.setPosition(
				ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
				ScreenSize[1] / 2 - text.getGlobalBounds().height / 2 + ScreenSize[1] / 12
			);
			window.draw(text);
			if (!solve)
			{
				stringstream ss1; ss1 << 20 - (timeforsolving.getElapsedTime().asMilliseconds() * 0.001);
				text.setString(ss1.str());
				text.setPosition(
					ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
					ScreenSize[1] / 2 - text.getGlobalBounds().height / 2 - (ScreenSize[1] / 10) * 2
				);
				window.draw(text);
			}
			window.display();
			if (timeforsolving.getElapsedTime().asSeconds() > 20)
			{
				gamestate = GameState::HumanGame;
				gamemap[int(player.pos.y)][int(player.pos.x)] = 1; dvereiz++;
				player.pos = postpos;
			}
		}
		while (window.isOpen() && gamestate == GameState::Conclusion)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			window.clear(Color(255, 255, 255));
			text.setCharacterSize(rc.getGlobalBounds().height * 1.5f);
			wstringstream ss; 
			ss		 << alltext[8][int(lang)] << timeintheend <<
				"\n" << alltext[9][int(lang)] << killed <<
				"\n" << alltext[10][int(lang)] << help <<
				"\n" << alltext[11][int(lang)] << vred <<
				"\n" << alltext[12][int(lang)] << bomb <<
				"\n" << alltext[13][int(lang)] << putlen <<
				"\n" << alltext[14][int(lang)] << dvereio <<
				"\n" << alltext[15][int(lang)] << dvereiz <<
				"\n" << alltext[16][int(lang)] << uronapol <<
				"\n" << alltext[17][int(lang)];
			text.setString(ss.str().substr(0, max(int(ss.str().size()), moveenemiesclock.getElapsedTime().asMilliseconds() / 100)));
			text.setPosition(
				ScreenSize[0] / 2 - text.getGlobalBounds().width / 2,
				ScreenSize[1] / 2 - text.getGlobalBounds().height / 2
			);
			window.draw(text);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				buddy.activated = false;
				foe.activated = false;
				player.health = 10;
				finded = 0;
				killed = 0;
				help = 0; 
				vred = 0;
				bomb = 0;
				putlen = 0;
				dvereio = 0;
				dvereiz = 0;
				uronapol = 0;
				gamestate = GameState::ChooseMode; 
				text.setFillColor(Color(255, 255, 255));
				text.setOutlineThickness(3);
				text.setOutlineColor(Color(50, 50, 50));
				text.setLineSpacing(1.2f);
				bool yes = true;
				do
				{
					labgen();
					for (int x = 0; x < 40; x++)
						for (int y = 1; y < 20; y++)
							if (gamemap[y][x] == 0)
								if (HowToGet(Vector2i(0, 0), Vector2i(x, y), false).z == 999)
									yes = false;
				} while (!yes);
				player.pos = Vector2f(0, 0);
				do treasure.pos = Vector2f(rand() % 40, 18); while (gamemap[int(treasure.pos.y)][int(treasure.pos.x)] != 0);
				do buddy.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(buddy.pos.y)][int(buddy.pos.x)] != 0 || buddy.pos == treasure.pos);
				do foe.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(foe.pos.y)][int(foe.pos.x)] != 0 ||
					foe.pos == treasure.pos || foe.pos == buddy.pos);
				for (int i = 0; i < QofEnemies; i++)
					do enemies[i].pos = Vector2f(rand() % 40, rand() % 18 + 2); while (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x)] != 0);
				for (int i = 0; i < 2; i++)
				{
					treasuresprite.spr.setPosition(treasure.pos.x * rc.getGlobalBounds().width, treasure.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					buddysprites[i].spr.setPosition(buddy.pos.x * rc.getGlobalBounds().width, buddy.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
					foesprites[i].spr.setPosition(foe.pos.x * rc.getGlobalBounds().width, foe.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
				}
				labgen();
			}
		}
	}
	return 0;
}