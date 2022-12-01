#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <sstream>

using namespace sf;
using namespace std;

enum class GameState { ChooseMode, BotGame, HumanGame, Conclusion, DoorHack };

enum class Language { Rus, Eng };

class SPRITE
{
public:
    Image img;
    Texture txtr;
    Sprite spr;
    SPRITE() { }
    Vector2i GetSize()
    {
        return Vector2i(img.getSize().x, img.getSize().y);
    }
    void Reload()
    {
        txtr.loadFromImage(img);
        spr.setTexture(txtr);
    }
    void Create(Vector2i size, Color clr = Color(255, 255, 255, 255))
    {
        img.create(size.x, size.y, clr);
        this->Reload();
    }
    void Load(string file)
    {
        img.loadFromFile(file);
        this->Reload();
    }
};

struct Bomb
{
    Vector2f pos;
    Clock timer;
    bool hittedplayer = false;
    Bomb(Vector2f _pos) { pos = _pos; }
};

struct Treasure
{
    Vector2f pos;
    Treasure() { }
};

struct Player
{
    Vector2f pos;
    int health = 10;
    Player() { }
};

struct Buddy
{
    Vector2f pos;
    bool activated = false;
    Buddy() { }
};

struct Foe
{
    Vector2f pos;
    bool activated = false;
    Foe() { }
};

struct Enemy
{
    Vector2f pos;
    bool died = false, signalized = false;
    Enemy() { }
};

int ScreenSize[2];
int gamemap[20][40];
int a, b, c, x, finded = 0, killed = 0, help = 0, vred = 0, bomb = 0, putlen = 0, dvereio = 0, dvereiz = 0, uronapol = 0;
bool pressed[10], solve, signalized = false;
float timeintheend = 0;
const int QofEnemies = 10;
RenderWindow window;
GameState gamestate = GameState::ChooseMode;
Font font;
Text text("", font, 96);
Treasure treasure;
Player player;
Buddy buddy;
Foe foe;
Enemy enemies[QofEnemies];
SPRITE magictanglesprite[2];
SPRITE treasuresprite;
SPRITE boomsprites[2];
SPRITE doorsprite;
SPRITE playersprites[2];
SPRITE heartsprites[2];
SPRITE buddysprites[2];
SPRITE foesprites[2];
SPRITE enemysprites[2];
Clock pushbuttoncooldownclock;
Clock comebackenemiesclock;
Clock moveenemiesclock;
Clock spriteanimclock;
Clock timeforsolving;
Clock signaltimer;
Clock solvetimer;
Clock globaltime;
Clock damage;
Clock pathclock;
RectangleShape rc;
Vector2f postpos;
Vector2i idti(-1, -1);
vector<Bomb> bombs;
Language lang = Language::Eng;
wstring alltext[][2] = 
{
    {L"ЧЕЛОВЕК", L"HUMAN"},
    {L"РОБОТ", L"BOT"},
    {L"Управление: WASD/Стрелочки   Бомба: Пробел   Говорить: T   Выход: Esc   Волшебный клубок: K", L"Control: WASD/Arrows   Bomb: Space   Talk: T   Exit: Esc   Magic tangle: K"},
    {L"Лабиринт", L"Maze"},
    {L"РЕЖИМ ИГРЫ: ЧЕЛОВЕК", L"GAME MODE: HUMAN"},
    {L"РЕЖИМ ИГРЫ: РОБОТ", L"GAME MODE: BOT"},
    {L"ОСТАЛОСЬ НАЙТИ СОКРОВИЩ: ", L"TREASURES LEFT: "},
    {L"НАЖМИТЕ F ЧТОБЫ ПОГОВОРИТЬ", L"PRESS F FOR TALKING"},
    {L"Время прохождения: ", L"Time: "},
    {L"Убито врагов: ", L"Killed enemies: "},
    {L"Помощь друга использована раз: ", L"Buddies help: "},
    {L"Враг позвал монстров раз: ", L"Foes tricks: "},
    {L"Бомб взорвано: ", L"Dropped bombs: "},
    {L"Клеток пройдено: ", L"Passed path: "},
    {L"Дверей открыто: ", L"Doors opened: "},
    {L"Проваленных дверей: ", L"Doors failed: "},
    {L"Получено урона: ", L"Damage received: "},
    {L"Нажмите R для рестарта", L"Press R for restart"},

    {L"Нажмите F, чтобы продолжить", L"Press F for continue"},

    {L"-\"Салют, рад тебя видеть\"", L"-\"Hey, nice to see you\""},
    {L"-\"Салют, я смотрю, тебя ранили, я вылечу тебя\"", L"-\"Hey, I see you are damaged, let me help\""},
    {L"-\"Салют, прости, у меня кончились медикаменты\"", L"-\"Hey, sorry i am out of meds\""},

    {L"-\"Ррр, опять ты?! Эй вы, демонические твари, он тут!\"", L"-\"Argh, again you?! Hey, monsters, he is here!\""},
    {L"-\"Вали отсюда\"", L"-\"Go away\""}
};

Vector3i HowToGet(Vector2i target, Vector2i pos, bool showpath, int inception = 0, Vector2i pastpos = Vector2i(-1, -1))
{
    if (target == pos || inception > 250 || gamemap[pos.y][pos.x] != 0) return Vector3i(-2, -2, 999);
    Vector3i finalresult(-2, -2, 999);
    if (target.y == pos.y && target.x == pos.x + 1) finalresult = Vector3i(1, 0, inception);
    if (target.y == pos.y && target.x == pos.x - 1) finalresult = Vector3i(-1, 0, inception);
    if (target.x == pos.x && target.y == pos.y + 1) finalresult = Vector3i(0, 1, inception);
    if (target.x == pos.x && target.y == pos.y - 1) finalresult = Vector3i(0, -1, inception);
    if (finalresult.x == -2)
    {
        if (!(pos.x + 1 == pastpos.x && pos.y == pastpos.y) && pos.x + 1 < 40 && gamemap[pos.y][pos.x + 1] == 0)
        {
            Vector3i result = HowToGet(target, Vector2i(pos.x + 1, pos.y), showpath, inception + 1, pos);
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(1, 0, inception + 1);
        }
        if (!(pos.x - 1 == pastpos.x && pos.y == pastpos.y) && pos.x - 1 >= 0 && gamemap[pos.y][pos.x - 1] == 0)
        {
            Vector3i result = HowToGet(target, Vector2i(pos.x - 1, pos.y), showpath, inception + 1, pos);
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(-1, 0, inception + 1);
        }
        if (!(pos.y + 1 == pastpos.y && pos.x == pastpos.x) && pos.y + 1 < 20 && gamemap[pos.y + 1][pos.x] == 0)
        {
            Vector3i result = HowToGet(target, Vector2i(pos.x, pos.y + 1), showpath, inception + 1, pos);
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(0, 1, inception + 1);
        }
        if (!(pos.y - 1 == pastpos.y && pos.x == pastpos.x) && pos.y - 1 >= 0 && gamemap[pos.y - 1][pos.x] == 0)
        {
            Vector3i result = HowToGet(target, Vector2i(pos.x, pos.y - 1), showpath, inception + 1, pos);
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(0, -1, inception + 1);
        }
    }
    if (finalresult.x != -2) 
        if (showpath)
        {
            CircleShape sha(6, 6);
            sha.setOrigin(6, 6);
            sha.setFillColor(Color(0, 0, 0));
            sha.setPosition(
                pos.x * rc.getGlobalBounds().width + (rc.getGlobalBounds().width / 2),
                pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height + (rc.getGlobalBounds().width / 2));
            window.draw(sha);
        }
    return finalresult;
}

Vector3i HowToGet1(Vector2i target, Vector2i pos, bool showpath, int inception = 0, Vector2i pastpos = Vector2i(-1, -1))
{
    if (target == pos || inception > 100 || gamemap[pos.y][pos.x] == 1 || gamemap[pos.y][pos.x] >= 10) return Vector3i(-2, -2, inception);
    gamemap[pos.y][pos.x] += 10;
    Vector3i finalresult(-2, -2, 999);
    if (target.y == pos.y && target.x == pos.x + 1) finalresult = Vector3i(1, 0, inception + 1);
    if (target.y == pos.y && target.x == pos.x - 1) finalresult = Vector3i(-1, 0, inception + 1);
    if (target.x == pos.x && target.y == pos.y + 1) finalresult = Vector3i(0, 1, inception + 1);
    if (target.x == pos.x && target.y == pos.y - 1) finalresult = Vector3i(0, -1, inception + 1);
    if (finalresult.x == -2)
    {
        if (!(pos.x + 1 == pastpos.x && pos.y == pastpos.y) && pos.x + 1 < 40 && gamemap[pos.y][pos.x + 1] != 1 && gamemap[pos.y][pos.x + 1] < 10)
        {
            Vector3i result = HowToGet1(target, Vector2i(pos.x + 1, pos.y), showpath, inception + 1, pos);
            //if (inception == 0) cout << result.x << " " << result.y << " " << result.z << endl;
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(1, 0, result.z);
        }
        if (!(pos.x - 1 == pastpos.x && pos.y == pastpos.y) && pos.x - 1 >= 0 && gamemap[pos.y][pos.x - 1] != 1 && gamemap[pos.y][pos.x - 1] < 10)
        {
            Vector3i result = HowToGet1(target, Vector2i(pos.x - 1, pos.y), showpath, inception + 1, pos);
            //if (inception == 0) cout << result.x << " " << result.y << " " << result.z << endl;
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(-1, 0, result.z);
        }
        if (!(pos.y + 1 == pastpos.y && pos.x == pastpos.x) && pos.y + 1 < 19 && gamemap[pos.y + 1][pos.x] != 1 && gamemap[pos.y + 1][pos.x] < 10)
        {
            Vector3i result = HowToGet1(target, Vector2i(pos.x, pos.y + 1), showpath, inception + 1, pos);
            //if (inception == 0) cout << result.x << " " << result.y << " " << result.z << endl;
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(0, 1, result.z);
        }
        if (!(pos.y - 1 == pastpos.y && pos.x == pastpos.x) && pos.y - 1 >= 0 && gamemap[pos.y - 1][pos.x] != 1 && gamemap[pos.y - 1][pos.x] < 10)
        {
            Vector3i result = HowToGet1(target, Vector2i(pos.x, pos.y - 1), showpath, inception + 1, pos);
            //if (inception == 0) cout << result.x << " " << result.y << " " << result.z << endl;
            if (result.x != -2) if (result.z < finalresult.z) finalresult = Vector3i(0, -1, result.z);
        }
        //if (inception == 0) cout << endl;
    }
    if (finalresult.x != -2)
        if (showpath)
        {
            CircleShape sha(3, 3);
            sha.setOrigin(3, 3);
            sha.setFillColor(Color(0, 0, 0));
            sha.setScale(1 - inception * 0.01f, 1 - inception * 0.01f);
            sha.setPosition(
                pos.x * rc.getGlobalBounds().width + (rc.getGlobalBounds().width / 2),
                pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height + (rc.getGlobalBounds().width / 2));
            window.draw(sha);
        }
    gamemap[pos.y][pos.x] -= 10;
    return finalresult;
}

void labgen()
{
    for (int x = 0; x < 40; x++)
        for (int y = 0; y < 20; y++) gamemap[y][x] = 1;
    int x = 0, y = 0, xx = 0, yy = 0;
    int longvall = 40, reallongvall;
    xx = longvall;
    for (; x < xx; x++) { gamemap[y][x] = 0; } 
    yy += 2;
    while (yy < 19)
    {
        x = 0; y = yy;
        do
        {
            longvall = (rand() % 8) + 2;
            reallongvall = 0;
            for (int gg = 0; gg < longvall; gg++)
            {
                if (x < xx)
                {
                    gamemap[y][x] = 0;
                    x++; reallongvall++;
                }
            }
            if (x == 39)
            {
                gamemap[y][x] = 0; //reallongvall++; 
                x++;
            }
            //Сам коридор
            int nutipo = rand() % reallongvall;
            while (gamemap[y - 2][x - nutipo - 1] != 0) nutipo = rand() % reallongvall;
            gamemap[y - 1][x - nutipo - 1] = 0;
            if (reallongvall > 4 && rand() % 2 == 0 && yy > 2)
            {
                int well = 0;
                nutipo = rand() % reallongvall;
                while (!(gamemap[y - 2][x - nutipo - 1] == 0 &&
                    gamemap[y - 1][x - nutipo - 1] == 1 &&
                    (x - nutipo - 1 == 0 || gamemap[y - 1][x - nutipo - 1 - 1] == 1) &&
                    gamemap[y - 1][x - nutipo - 1 + 1] == 1) && well < 10)
                {
                    nutipo = rand() % reallongvall; well++;
                }
                if (well < 10) gamemap[y - 1][x - nutipo - 1] = 2;
            }
            if (x + 1 < 40) {
                gamemap[y][x] = 1; x++;
            }
            //if (reallongvall < 2) cout << "я идиот" << endl;
            //Закрытие коридора
        } while (x < xx);
        yy += 2;
    }
}

void GetDesktopResolution()
{
	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	ScreenSize[0] = GetSystemMetrics(SM_CXSCREEN);
	ScreenSize[1] = GetSystemMetrics(SM_CYSCREEN);
}

void Init()
{
    std::cout << "Init" << endl;
    for (int i = 0; i < 10; i++) pressed[i] = false;
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    font.loadFromFile("data/font.ttf");
    text.setFillColor(Color(255, 255, 255));
    text.setStyle(sf::Text::Bold);
    text.setOutlineThickness(3);
    text.setOutlineColor(Color(50, 50, 50));
    text.setLineSpacing(1.2f);
    GetDesktopResolution();
    rc.setSize(Vector2f(ScreenSize[0] / 40, ScreenSize[0] / 40));
    std::cout << "Step 1" << endl;
    bool yes = true;
    do
    {
        labgen(); cout << "Generating" << endl;
        for (int x = 0; x < 40; x++)
            for (int y = 1; y < 20; y++)
                if (gamemap[y][x] == 0)
                    if (HowToGet(Vector2i(0, 0), Vector2i(x, y), false).z == 999)
                        yes = false;
    } while (!yes);
    std::cout << "Step 2" << endl;
    player.pos = Vector2f(0, 0);
    do treasure.pos = Vector2f(rand() % 40, 18); while (gamemap[int(treasure.pos.y)][int(treasure.pos.x)] != 0);
    do buddy.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(buddy.pos.y)][int(buddy.pos.x)] != 0 || buddy.pos == treasure.pos);
    do foe.pos = Vector2f(rand() % 40, rand() % 17 + 2); while (gamemap[int(foe.pos.y)][int(foe.pos.x)] != 0 ||
        foe.pos == treasure.pos || foe.pos == buddy.pos);
    for (int i = 0; i < QofEnemies; i++)
        do enemies[i].pos = Vector2f(rand() % 40, rand() % 18 + 2); while (gamemap[int(enemies[i].pos.y)][int(enemies[i].pos.x)] != 0);
    std::cout << "Step 3" << endl;
    magictanglesprite[0].Load("data/images/magic tangle.png");
    magictanglesprite[1].Load("data/images/magic tangle1.png");
    magictanglesprite[0].img.createMaskFromColor(Color(255, 0, 0)); magictanglesprite[0].Reload();
    magictanglesprite[1].img.createMaskFromColor(Color(255, 0, 0)); magictanglesprite[1].Reload();
    treasuresprite.Load("data/images/treasure.png");
    treasuresprite.img.createMaskFromColor(Color(255, 0, 0)); treasuresprite.Reload();
    boomsprites[0].Load("data/images/bomb.png"); boomsprites[1].Load("data/images/boom.png");
    boomsprites[0].img.createMaskFromColor(Color(255, 0, 0)); boomsprites[0].Reload();
    boomsprites[1].img.createMaskFromColor(Color(255, 0, 0)); boomsprites[1].Reload();
    doorsprite.Load("data/images/door.png");
    playersprites[0].Load("data/images/player.png");   playersprites[1].Load("data/images/player1.png");
    playersprites[0].img.createMaskFromColor(Color(255, 0, 0)); playersprites[0].Reload();
    playersprites[1].img.createMaskFromColor(Color(255, 0, 0)); playersprites[1].Reload();
    heartsprites[0].Load("data/images/heart.png");     heartsprites[1].Load("data/images/heart1.png");
    heartsprites[0].img.createMaskFromColor(Color(255, 0, 0)); heartsprites[0].Reload();
    heartsprites[1].img.createMaskFromColor(Color(255, 0, 0)); heartsprites[1].Reload();
    buddysprites[0].Load("data/images/buddy.png");     buddysprites[1].Load("data/images/buddy1.png");
    buddysprites[0].img.createMaskFromColor(Color(255, 0, 0)); buddysprites[0].Reload();
    buddysprites[1].img.createMaskFromColor(Color(255, 0, 0)); buddysprites[1].Reload();
    foesprites[0].Load("data/images/foe.png");         foesprites[1].Load("data/images/foe1.png");
    foesprites[0].img.createMaskFromColor(Color(255, 0, 0)); foesprites[0].Reload();
    foesprites[1].img.createMaskFromColor(Color(255, 0, 0)); foesprites[1].Reload();
    enemysprites[0].Load("data/images/enemy.png");     enemysprites[1].Load("data/images/enemy1.png");
    enemysprites[0].img.createMaskFromColor(Color(255, 0, 0)); enemysprites[0].Reload();
    enemysprites[1].img.createMaskFromColor(Color(255, 0, 0)); enemysprites[1].Reload();
    std::cout << "Step 4" << endl;
    for (int i = 0; i < 2; i++)
    {
        magictanglesprite[i].spr.setScale(4.66, 4.66);
        magictanglesprite[i].spr.setPosition(ScreenSize[0] / 2 - 192, (rc.getGlobalBounds().width / 3));
        treasuresprite.spr.setScale(2, 2);
        doorsprite.spr.setScale(2, 2);
        boomsprites[i].spr.setScale(2, 2);
        playersprites[i].spr.setScale(2, 2);
        heartsprites[i].spr.setScale(2, 2);
        buddysprites[i].spr.setScale(2, 2);
        foesprites[i].spr.setScale(2, 2);
        treasuresprite.spr.setPosition(treasure.pos.x * rc.getGlobalBounds().width, treasure.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
        buddysprites[i].spr.setPosition(buddy.pos.x * rc.getGlobalBounds().width, buddy.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
        foesprites[i].spr.setPosition(foe.pos.x * rc.getGlobalBounds().width, foe.pos.y * rc.getGlobalBounds().height + 3 * rc.getGlobalBounds().height);
    }
    std::cout << "Step 5" << endl;
	window.create(VideoMode(ScreenSize[0], ScreenSize[1]), "Programm", Style::Fullscreen, ContextSettings(0, 0, 8));
    std::cout << "Init complete" << endl;
}