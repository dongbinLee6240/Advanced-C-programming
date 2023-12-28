#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// 매크로
#define BLACK 0
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15

#define HunterBottomY 10
#define TreeBottomY 15
#define TreeBottomX 45
#define BulletY 10

//구조체
struct Hunter
{
    int y;
    int damage;
    int hp = 3;
    bool isSliding = false;
};

struct Bullet
{
    int x;
    int y;
    int exist;
    bool active;
};

struct Tree
{
    float x;
    int hitcount=0;
};

struct Bird
{
    int x;
    int hitcount=0;
};

struct Map
{
    int y;
    int x;
};

//함수 prototype
void DrawBird(const Bird& bird);
void MoveBird(Bird& bird);
void SetConsoleView();
void GotoXY(int x, int y);
void textcolor(int fg_color, int bg_color);
void InitGame();
int GetKeyDown();
void DrawMap(const Map& map, int& score);
void MoveMap(Map& map);
void DrawHearts(const Hunter& hunter);
void DrawHunter(const Hunter& hunter);
void DrawTree(const Tree& tree);
void DrawBird(const Bird& bird);
void MoveBird(Bird& bird);
void GameOver(const int score);
bool isCollision(const Tree& tree, Hunter& hunter, const Bird& bird);
void CheckBulletCollision(Bullet bullets[], int& bulletCount, const Tree& tree, int& score);
void Attack(Bullet bullets[], int& bulletCount);

//콘솔 뷰
void SetConsoleView()
{
    system("mode con::cols=100 lines=25");
    system("title DevilHunter. By BlockDMask.");
}

void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

//시작화면
void InitGame()
{
    system("cls");

    GotoXY(12, 7);
    textcolor(YELLOW1, BLACK);
    printf("####                   #     ##    #   #                 #                 \n");
    GotoXY(12, 8);
    printf(" #  #                         #    #   #                 #                 \n");
    GotoXY(12, 9);
    printf(" #  #   ###   #   #   ##      #    #   #  #   #  # ##   ####    ###   # ## \n");
    GotoXY(12, 10);
    printf(" #  #  #   #  #   #    #      #    #####  #   #  ##  #   #     #   #  ##  #\n");
    GotoXY(12, 11);
    printf(" #  #  #####   # #     #      #    #   #  #   #  #   #   #     #####  #    \n");
    GotoXY(12, 12);
    printf(" #  #  #       # #     #      #    #   #  #  ##  #   #   #  #  #      #    \n");
    GotoXY(12, 13);
    printf("####    ###     #     ###    ###   #   #   ## #  #   #    ##    ###   #    \n");
    textcolor(WHITE, BLACK);
    GotoXY(22, 18);
    printf("Press any key to start...");

    // 사용자의 입력 대기
    while (!_kbhit())
    {
        // 대기
    }

    // 키 입력 버퍼 비우기
    _getch();
}

int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

//맵
void DrawMap(const Map& map, int& score)
{
    GotoXY(0, 20);
    textcolor(MAGENTA1, BLACK);
    printf("========================================================================================================");
    textcolor(MAGENTA1, BLACK);
    printf("*** *  ##       $$     ** # ***  ###  **  #@$#%    !#@$  _________+++---      *** ##   $$     __**      ");
    textcolor(MAGENTA1, BLACK);
    printf("                                                                                                        ");
    textcolor(MAGENTA1, BLACK);
    printf("*** *  ##       $$     ** # ***  #&&  **  ####    !#@$  _________+++---  ### *** ##   $$     __****     ");
    textcolor(MAGENTA1, BLACK);
    printf("        _____+++---      *** ##   $$     __**                                                           ");
    textcolor(MAGENTA1, BLACK);
    printf("                                                                                                        ");
    textcolor(MAGENTA1, BLACK);
    printf("                                   # ***  #&&  **  ####    !#@$  _________+++---  ##                    ");
    textcolor(MAGENTA1, BLACK);
    printf("                  __________________________                                                            ");
    textcolor(WHITE, BLACK);

    if (score > 500)
    {
        GotoXY(0, 20);
        textcolor(GREEN1, BLACK);
        printf("^^^^^^^^^^___^^^^^^^^^^^^^^^^^^^^^^^^^^^^^________^^^^__^^____^^^^^^^^^^^^^^__^^^^^^^^^^^^^^^^____^^^^^^");
        textcolor(GREEN1, BLACK);
        printf("<<<>  ##       $$     ** # ***  ###  **  #@$#%    !#@$  _________+++---      *** ##   $$     __**       ");
        textcolor(GREEN1, BLACK);
        printf("                                                                                                        ");
        textcolor(GREEN1, BLACK);
        printf("<*** *><  ##   <<<>:><    $$     ** # ***  #&&  **  ||||    !#@$  //\______+++---  ### *** ##   <<      ");
        textcolor(GREEN1, BLACK);
        printf("        _____+++---      *** ##   $$     __**                                                           ");
        textcolor(GREEN1, BLACK);
        printf("                        ||    >>   \\                //\\              >><<>                            ");
        textcolor(GREEN1, BLACK);
        printf("                                   # ***  #&&  **  ####    !#@$  _________+++---  ##                    ");
        textcolor(GREEN1, BLACK);
        printf("                  ____________//\\__________             ______\/\//\__                                 ");
        textcolor(WHITE, BLACK);
    }

}

void MoveMap(Map& map)
{
    map.x -= 2;

    if (map.x <= -30)
    {
        map.x = 0;
    }
}

//심장
void DrawHearts(const Hunter& hunter)
{
    for (int i = 0; i < hunter.hp; ++i)
    {
        GotoXY(30 + i * 4, 0);
        textcolor(RED1, BLACK);
        printf(" *  * ");
        GotoXY(30 + i * 4, 1);
        textcolor(RED1, BLACK);
        printf("******");
        GotoXY(30 + i * 4, 2);
        textcolor(RED1, BLACK);
        printf(" **** ");
        GotoXY(30 + i * 4, 3);
        textcolor(RED1, BLACK);
        printf("  **  ");
        textcolor(WHITE, BLACK);
    }
}

//Player
void DrawHunter(const Hunter& hunter)
{
    if (hunter.isSliding)
    {
        GotoXY(0, hunter.y + 5);
        printf(" $$$$$$\n");
        printf("  $$$$   \n");
        printf("    $$ $  $$$ $$$$$  \n");
        printf("     $$$  $$ \n");
        printf("      $$$  $$$    \n");
        printf("     $$$       $$    \n");

    }
    else {

        GotoXY(0, hunter.y);
        static bool LegFlag = true;
        printf("     $$$$$$$ \n");
        printf("    $$$$$$$$$\n");
        printf("      $$$$$$\n");
        printf("       $$$      $$\n");
        printf("  $$$$ $ $$$$$$$$$  \n");
        printf("    $$ $  $$$   \n");
        printf("     $$$  $$ \n");
        printf("     $$$  $$$    \n");
        printf("     $$$  $$    \n");

        if (LegFlag)
        {
            printf("     $    $$$    \n");
            printf("     $$          ");
            LegFlag = false;
        }

        else
        {
            printf("     $$$  $     \n");
            printf("          $$    ");
            LegFlag = true;
        }
    }
}

//나무
void DrawTree(const Tree& tree)
{
    GotoXY(tree.x, TreeBottomY);
    printf("$$$$");
    GotoXY(tree.x, TreeBottomY + 1);
    printf(" $$ ");
    GotoXY(tree.x, TreeBottomY + 2);
    printf(" $$ ");
    GotoXY(tree.x, TreeBottomY + 3);
    printf(" $$ ");
    GotoXY(tree.x, TreeBottomY + 4);
    printf(" $$ ");
    GotoXY(tree.x, TreeBottomY + 5);
    printf(" $$ ");
}

//새
void DrawBird(const Bird& bird)
{
    GotoXY(bird.x, TreeBottomY - 7);
    printf("      v   ");
    GotoXY(bird.x, TreeBottomY - 6);
    printf("     vvv     ");
    GotoXY(bird.x, TreeBottomY - 5);
    printf("AAA vvvvv AAA");
    GotoXY(bird.x, TreeBottomY - 4);
    printf("     vvv  ");
    GotoXY(bird.x, TreeBottomY - 3);
    printf("      v   ");
}

void MoveBird(Bird& bird)
{
    bird.x -= 2;
    if (bird.x <= 0)
    {
        bird.x = TreeBottomX;
    }
}

//게임오버
void GameOver(const int score)
{
    system("cls");

    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE:%d", score);

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");

    //아에 나가기
    exit(0);
}

//BirdCollision
bool isCollision(const Tree& tree, Hunter& hunter, const Bird& bird)
{
    GotoXY(0, 0);
    printf("birdx: %d", bird.x);
    if (tree.x <= 8 && tree.x >= 4 && hunter.y > 5)
    {
        hunter.hp -= 1;;
    }
    
    else if (bird.x <= 6&& bird.x >= 3 && hunter.y < (TreeBottomY - 5))
    {
        hunter.hp -= 1;
    }

    if (hunter.hp == 0)
    {
        return true;
    }
    return false; //기본적으로 false값
}

void CheckBulletCollision(Bullet bullets[], int& bulletCount, Tree& tree, Bird&bird, int& score)
{
    for (int i = 0; i < bulletCount; i++)
    {
        int score1 = 0;
        int score2 = 0;
        if (bullets[i].active && bullets[i].x >= tree.x && bullets[i].x <= tree.x + 3 && bullets[i].y == TreeBottomY)
        {
            bullets[i].active = false;
            score1 += 100;
            tree.hitcount++;
            if (tree.hitcount >= 2)
            {
                tree.x = TreeBottomX; 
                tree.hitcount = 0;    
            }
        }
        else if (bullets[i].active && bullets[i].x >= bird.x && bullets[i].x <= bird.x + 3 && bullets[i].y == TreeBottomY-5)
        {
            bullets[i].active = false;
            score2 += 100;
            bird.hitcount++;
            if (bird.hitcount >= 3)
            {
                bird.x = TreeBottomX + 15; // Reset the bird's position
                bird.hitcount = 0;          // Reset hit count
            }
        }
    }
}

void Attack(Bullet bullets[], int& bulletCount)
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (bullets[i].active)
        {
            GotoXY(bullets[i].x, bullets[i].y);
            printf("  "); // 이전 위치 지우기

            // x 좌표 업데이트
            bullets[i].x++;

            GotoXY(bullets[i].x, bullets[i].y);
            printf(">>"); // 새 위치에 총알 출력

            if (bullets[i].x > 50)
            {
                bullets[i].active = false;
            }
        }
    }
}

int main() {

    SetConsoleView();

    Map map;
    Hunter hunter = { HunterBottomY };
    Tree tree = { TreeBottomX };
    Bird bird = { TreeBottomX + 15 };

    bool isAttack = false;
    bool isJumping = false;
    bool isBottom = false;
    bool isSlidingKeyDown = false;

    const int gravity = 3;
    const int MaxBullet = 20;
    Bullet* bullets = new Bullet[MaxBullet];
    int damage = 0;
    int score = 0;
    int attackcnt = 0;
    int bulletCount = 0;

    clock_t start, curr;
    start = clock();

    clock_t slidingStartTime = 0;
    const int slidingDuration = 1000;

    InitGame();

    while (true)
    {
        int key = GetKeyDown();
        clock_t startslidetime = clock();

        if (key == 224)
        {
            key = GetKeyDown();
            if (key == 80)
            {
                isSlidingKeyDown = true;
                slidingStartTime = startslidetime;
            }
        }

        else
        {
            isSlidingKeyDown = false;
        }

        if (key == 'z' && isBottom) {
            isJumping = true;
            isBottom = false;
        }

        else if (key == 'c') {

            bullets[bulletCount].x = 15;
            bullets[bulletCount].y = BulletY;
            bullets[bulletCount].active = true;
            bulletCount++;
            attackcnt++;
        }

        else if (key == 'x') {

            bullets[bulletCount].x = 15;
            bullets[bulletCount].y = BulletY + 5;
            bullets[bulletCount].active = true;
            bulletCount++;
            attackcnt++;
        }

        if (isSlidingKeyDown && (startslidetime - slidingStartTime) >= slidingDuration) {
            isSlidingKeyDown = false;
        }

        hunter.isSliding = isSlidingKeyDown;

        if (isJumping) {
            hunter.y -= gravity;
        }
        else {
            hunter.y += gravity;
        }

        if (hunter.y >= HunterBottomY) {
            hunter.y = HunterBottomY;
            isBottom = true;
        }

        if (hunter.y <= 3) {
            isJumping = false;
        }

        tree.x -= 2;
        if (tree.x <= 0) {
            tree.x = TreeBottomX;
        }

        curr = clock();
        if (((curr - start / CLOCKS_PER_SEC)) >= 1);
        {
            score++;
            start = clock();
        }

        Attack(bullets, bulletCount);  //true일경우 bulletCount만큼 발사 근데 x를 누르면 true가 되니깐 계속 발사할것으로 예상됨(이게 왜 됨?)
        DrawHearts(hunter);
        DrawMap(map, score);
        MoveMap(map);
        DrawBird(bird);
        MoveBird(bird);
        DrawHunter(hunter);
        DrawTree(tree);
        Sleep(80);
        system("cls");
        CheckBulletCollision(bullets, bulletCount, tree,bird, score);
        GotoXY(22, 0);
        printf("Score: %d ", score);

        if (isCollision(tree, hunter, bird))
        {
            GameOver(score);
        }
    }

    delete[] bullets;

    system("pause");
    return 0;
}