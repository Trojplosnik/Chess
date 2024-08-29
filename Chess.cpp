
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

constexpr auto Pawn_Black = -1;
constexpr auto Pawn_White = 1;
constexpr auto Rook_Black = -2;
constexpr auto Rook_White = 2;
constexpr auto Knight_Black = -3;
constexpr auto Knight_White = 3;
constexpr auto Bishop_Black = -4;
constexpr auto Bishop_White = 4;
constexpr auto Queen_Black = -5;
constexpr auto Queen_White = 5;
constexpr auto King_Black = -6;
constexpr auto King_White = 6;
constexpr auto Transform_Black = -7;
constexpr auto Transform_White = 7;
constexpr auto Fantom_Pawn = 10;


int board_size = 824, field_size = 103, x, y;
bool bFirstMoveKandR[6] = { 1, 1, 1, 1, 1, 1 };
bool bTurn = true, bTransformetion = false;
int I_figure_in_hand = 0;

int Board[8][8] =
{ -2,-3,-4,-5,-6,-4,-3,-2,
 -1,-1,-1,-1,-1,-1,-1,-1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  2, 3, 4, 5, 6, 4, 3, 2, };




bool check(int x, int y);

bool moveKing(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if ((abs(x - newX) == 1 || x - newX == 0) && (abs(y - newY) == 1 || y - newY == 0))
        return true;
    else if (y - newY == 0 && abs(x - newX) == 2 && ((bFirstMoveKandR[3] && bTurn) || (bFirstMoveKandR[0] && !bTurn)))
    {
        int row, Rcolour, Prow;
        if (bTurn)
        {
            Prow = 1, row = 7, Rcolour = 3;
        }
        else
        {
            Prow = -1, row = 0, Rcolour = 0;
        }
        if (check(4, row))
            return false;
        if (newX - x == 2)
        {
            if (bFirstMoveKandR[1 + Rcolour])
            {
                for (int i = 5; i < 7; i++)
                    if (Board[row][i] != 0 || check(i, row))
                        return false;
                for (int i = 6; i < 8; i++)
                    if (Board[row - Prow][i] == -Prow)
                        return false;
                Board[row][5] = Board[row][7];
                Board[row][7] = 0;
                bFirstMoveKandR[1 + Rcolour] = false;
                return true;
            }
            else
                return false;
        }
        else
        {
            if (bFirstMoveKandR[2 + Rcolour])
            {
                for (int i = 1; i < 4; i++)
                    if (Board[row][i] != 0 || check(i, row))
                        return false;
                for (int i = 1; i < 3; i++)
                    if (Board[row - Prow][i] == -Prow)
                        return false;
                Board[row][3] = Board[row][0];
                Board[row][0] = 0;
                bFirstMoveKandR[2 + Rcolour] = false;
                return true;
            }
            else
                return false;
        }
    }
    else
        return false;
}
bool moveQueen(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if (y - newY == 0)
    {
        if (abs(x - newX) == 1)
            return true;
        else if (x - newX > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y][x - i] != 0 && Board[y][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y][x + i] != 0 && Board[y][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
    }
    else if (x - newX == 0)
    {
        if (abs(y - newY) == 1)
            return true;
        else if (y - newY > 0)
        {
            for (int i = 1; i < abs(y - newY); i++)
                if (Board[y - i][x] != 0 && Board[y - i][x] != Fantom_Pawn)
                    return false;
            return true;
        }
        else
        {
            for (int i = 1; i < abs(y - newY); i++)
                if (Board[y + i][x] != 0 && Board[y + i][x] != Fantom_Pawn)
                    return false;
            return true;
        }
    }
    else if (abs(x - newX) == abs(y - newY))
    {
        if (abs(x - newX) == 1)
            return true;
        else if (x - newX > 0 && y - newY > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y - i][x - i] != 0 && Board[y - i][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX < 0 && y - newY > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y - i][x + i] != 0 && Board[y - i][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX > 0 && y - newY < 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y + i][x - i] != 0 && Board[y + i][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX < 0 && y - newY < 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y + i][x + i] != 0 && Board[y + i][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
        return false;
    }
    else
        return false;
}
bool moveBishop(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if (abs(x - newX) == abs(y - newY))
    {
        if (abs(x - newX) == 1)
            return true;
        else if (x - newX > 0 && y - newY > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y - i][x - i] != 0 && Board[y - i][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX < 0 && y - newY > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y - i][x + i] != 0 && Board[y - i][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX > 0 && y - newY < 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y + i][x - i] != 0 && Board[y + i][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else if (x - newX < 0 && y - newY < 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y + i][x + i] != 0 && Board[y + i][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
        return false;
    }
    else
        return false;
}
bool moveRook(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if (y - newY == 0)
    {
        if (abs(x - newX) == 1)
            return true;
        else if (x - newX > 0)
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y][x - i] != 0 && Board[y][x - i] != Fantom_Pawn)
                    return false;
            return true;
        }
        else
        {
            for (int i = 1; i < abs(x - newX); i++)
                if (Board[y][x + i] != 0 && Board[y][x + i] != Fantom_Pawn)
                    return false;
            return true;
        }
    }
    else if (x - newX == 0)
    {
        if (abs(y - newY) == 1)
            return true;
        else if (y - newY > 0)
        {
            for (int i = 1; i < abs(y - newY); i++)
                if (Board[y - i][x] != 0 && Board[y - i][x] != Fantom_Pawn)
                    return false;
            return true;
        }
        else
        {
            for (int i = 1; i < abs(y - newY); i++)
                if (Board[y + i][x] != 0 && Board[y + i][x] != Fantom_Pawn)
                    return false;
            return true;
        }
    }
    else
        return false;
}
bool moveKnight(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if ((abs(x - newX) == 2 && abs(y - newY) == 1) || (abs(x - newX) == 1 && abs(y - newY) == 2))
        return true;
    else
        return false;
}
bool movePawn(int x, int y, int newX, int newY)
{
    if (y - newY == 0 && x - newX == 0)
        return false;
    else if (x - newX == 0)
    {
        if (bTurn)
        {
            if (y - newY == 1)
            {
                if (Board[newY][newX] == 0)
                {
                    if (newY == 0)
                    {
                        I_figure_in_hand = Transform_White;
                        bTransformetion = true;
                    }
                    return true;
                }
                else
                    return false;
            }
            else if (y == 6 && y - newY == 2)
            {
                if (Board[y - 1][x] == 0 && Board[y - 2][x] == 0)
                {
                    Board[y - 1][x] = Fantom_Pawn;
                    return true;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
        {
            if (newY - y == 1)
            {
                if (Board[newY][newX] == 0)
                {
                    if (newY == 7)
                    {
                        I_figure_in_hand = Transform_Black;
                        bTransformetion = true;
                    }
                    return true;
                }
                else
                    return false;
            }
            else if (y == 1 && newY - y == 2)
            {
                if (Board[y + 1][x] == 0 && Board[y + 2][x] == 0)
                {
                    Board[y + 1][x] = Fantom_Pawn;
                    return true;
                }
                else
                    return false;
            }
            else
                return false;
        }
    }
    else if (abs(x - newX) == 1)
    {
        if (((I_figure_in_hand == Pawn_White || Board[y][x] == Pawn_White) && y - newY == 1) || ((I_figure_in_hand == Pawn_Black || Board[y][x] == Pawn_Black) && newY - y == 1))
        {
            if (Board[newY][newX] != 0)
            {
                if (Board[newY][newX] == Fantom_Pawn)
                    Board[y][newX] = 0;
                if (newY == 0 && Board[newY][newX] != King_Black)
                {
                    I_figure_in_hand = Transform_White;
                    bTransformetion = true;
                }
                else if (newY == 7 && Board[newY][newX] != King_White)
                {
                    I_figure_in_hand = Transform_Black;
                    bTransformetion = true;
                }
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool check(int x, int y)
{
    if (bTurn)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == 0 || Board[i][j] > 0)
                    continue;
                else
                {
                    switch (Board[i][j])
                    {
                    case King_Black:
                        if (moveKing(j, i, x, y))
                            return true;
                        break;
                    case Queen_Black:
                        if (moveQueen(j, i, x, y))
                            return true;
                        break;
                    case Bishop_Black:
                        if (moveBishop(j, i, x, y))
                            return true;
                        break;
                    case Knight_Black:
                        if (moveKnight(j, i, x, y))
                            return true;
                        break;
                    case Rook_Black:
                        if (moveRook(j, i, x, y))
                            return true;
                        break;
                    case Pawn_Black:
                        if (movePawn(j, i, x, y))
                            return true;
                        break;
                    }
                }
            }
    }
    else
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == 0 || Board[i][j] < 0 || Board[i][j] == Fantom_Pawn)
                    continue;
                else
                {
                    switch (Board[i][j])
                    {
                    case King_White:
                        if (moveKing(j, i, x, y))
                            return true;
                        break;
                    case Queen_White:
                        if (moveQueen(j, i, x, y))
                            return true;
                        break;
                    case Bishop_White:
                        if (moveBishop(j, i, x, y))
                            return true;
                        break;
                    case Knight_White:
                        if (moveKnight(j, i, x, y))
                            return true;
                        break;
                    case Rook_White:
                        if (moveRook(j, i, x, y))
                            return true;
                        break;
                    case Pawn_White:
                        if (movePawn(j, i, x, y))
                            return true;
                        break;
                    }
                }
            }
    }
    return false;
}

bool defence(int x, int y)
{
    if (!bTurn)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == 0 || Board[i][j] > 0)
                    continue;
                else
                {
                    switch (Board[i][j])
                    {
                    case Queen_Black:
                        if (moveQueen(j, i, x, y))
                            return true;
                        break;
                    case Bishop_Black:
                        if (moveBishop(j, i, x, y))
                            return true;
                        break;
                    case Knight_Black:
                        if (moveKnight(j, i, x, y))
                            return true;
                        break;
                    case Rook_Black:
                        if (moveRook(j, i, x, y))
                            return true;
                        break;
                    case Pawn_Black:
                        if (movePawn(j, i, x, y))
                            return true;
                        break;
                    }
                }
            }
    }
    else
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == 0 || Board[i][j] < 0 || Board[i][j] == Fantom_Pawn)
                    continue;
                else
                {
                    switch (Board[i][j])
                    {
                    case Queen_White:
                        if (moveQueen(j, i, x, y))
                            return true;
                        break;
                    case Bishop_White:
                        if (moveBishop(j, i, x, y))
                            return true;
                        break;
                    case Knight_White:
                        if (moveKnight(j, i, x, y))
                            return true;
                        break;
                    case Rook_White:
                        if (moveRook(j, i, x, y))
                            return true;
                        break;
                    case Pawn_White:
                        if (movePawn(j, i, x, y))
                            return true;
                        break;
                    }
                }
            }
    }
    return false;
}


int main()
{
    RenderWindow window(VideoMode(board_size, board_size), "Chess");

    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

    t0.loadFromFile("images\\boardW.png");
    t1.loadFromFile("images\\boardB.png");
    t2.loadFromFile("images\\P_b.png");
    t3.loadFromFile("images\\P_w.png");
    t4.loadFromFile("images\\R_b.png");
    t5.loadFromFile("images\\R_w.png");
    t6.loadFromFile("images\\N_b.png");
    t7.loadFromFile("images\\N_w.png");
    t8.loadFromFile("images\\B_b.png");
    t9.loadFromFile("images\\B_w.png");
    t10.loadFromFile("images\\Q_b.png");
    t11.loadFromFile("images\\Q_w.png");
    t12.loadFromFile("images\\K_b.png");
    t13.loadFromFile("images\\K_w.png");
    t14.loadFromFile("images\\Transform_b.png");
    t15.loadFromFile("images\\Transform_w.png");

    Sprite FieldW(t0);
    Sprite FieldB(t1);
    Sprite Pawn_b(t2);
    Sprite Pawn_w(t3);
    Sprite Rook_b(t4);
    Sprite Rook_w(t5);
    Sprite Knight_b(t6);
    Sprite Knight_w(t7);
    Sprite Bishop_b(t8);
    Sprite Bishop_w(t9);
    Sprite Queen_b(t10);
    Sprite Queen_w(t11);
    Sprite King_b(t12);
    Sprite King_w(t13);
    Sprite Transform_b(t14);
    Sprite Transform_w(t15);



    Sprite WhitePiece[8] = { Pawn_w, Rook_w, Knight_w, Bishop_w, Queen_w, King_w, Transform_w };
    Sprite BlackPiece[8] = { Pawn_b, Rook_b, Knight_b, Bishop_b, Queen_b, King_b, Transform_b };
    Sprite* S_figure_in_hand = nullptr;



    bool bIsMove = false, bCanMove = false, bFantom = false, bMate = false, bDrow = false;
    float dx = 0, dy = 0;
    Vector2i oldXY, newXY;
    while (window.isOpen())
    {
        window.clear();
        window.draw(FieldW);
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (Board[i][j] == 0)
                    continue;
                else if (Board[i][j] > 0)
                {
                    if (Board[i][j] == Fantom_Pawn)
                    {
                        bFantom = true;
                        continue;
                    }
                    else
                        WhitePiece[Board[i][j] - 1].setPosition(j * field_size, i * field_size);
                    window.draw(WhitePiece[Board[i][j] - 1]);
                }
                else
                {
                    BlackPiece[-(Board[i][j] + 1)].setPosition(j * field_size, i * field_size);
                    window.draw(BlackPiece[-(Board[i][j] + 1)]);
                }
            }
        Vector2i pos = Mouse::getPosition(window);
        x = pos.x / field_size;
        y = pos.y / field_size;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left)
                {
                    if (bTransformetion)
                    {
                        if (Board[y][x] == Transform_White)
                        {
                            int xx = pos.x % field_size, yy = pos.y % field_size;
                            if (xx < field_size / 2 && yy < field_size / 2 && xx > 0 && yy > 0)
                            {
                                Board[y][x] = Rook_White;
                                std::cout << "Turning into Rook" << "\n";
                            }
                            else if (xx > field_size / 2 && xx < field_size && yy > field_size / 2 && yy < field_size)
                            {
                                Board[y][x] = Knight_White;
                                std::cout << "Turning into Knight" << "\n";
                            }
                            else if (xx < field_size / 2 && xx > 0 && yy > field_size / 2 && y < field_size)
                            {
                                Board[y][x] = Bishop_White;
                                std::cout << "Turning into Bishop" << "\n";
                            }
                            else
                            {
                                Board[y][x] = Queen_White;
                                std::cout << "Turning into Queen" << "\n";
                            }
                            bTurn = false;
                            bTransformetion = false;
                            break;
                        }
                        else if (Board[y][x] == Transform_Black)
                        {
                            int xx = pos.x % field_size, yy = pos.y % field_size;
                            if (xx < field_size / 2 && yy < field_size / 2 && xx > 0 && yy > 0)
                            {
                                Board[y][x] = Rook_Black;
                                std::cout << "Turning into Rook" << "\n";
                            }
                            else if (xx > field_size / 2 && xx < field_size && yy > field_size / 2 && yy < field_size)
                            {
                                Board[y][x] = Knight_Black;
                                std::cout << "Turning into Knight" << "\n";
                            }
                            else if (xx < field_size / 2 && xx > 0 && yy > field_size / 2 && y < field_size)
                            {
                                Board[y][x] = Bishop_Black;
                                std::cout << "Turning into Bishop" << "\n";
                            }
                            else
                            {
                                Board[y][x] = Queen_Black;
                                std::cout << "Turning into Queen" << "\n";
                            }
                            bTurn = true;
                            bTransformetion = false;
                            break;
                        }
                    }
                    else if (Board[y][x] != 0 && !bMate && !bDrow)
                    {
                        dx = pos.x - x * field_size;
                        dy = pos.y - y * field_size;
                        if (bTurn && Board[y][x] > 0)
                        {
                            I_figure_in_hand = Board[y][x];
                            S_figure_in_hand = &WhitePiece[I_figure_in_hand - 1];
                            Board[y][x] = 0;
                        }
                        else if (!bTurn && Board[y][x] < 0)
                        {
                            I_figure_in_hand = Board[y][x];
                            S_figure_in_hand = &BlackPiece[-(I_figure_in_hand + 1)];
                            Board[y][x] = 0;
                        }
                        if (Board[y][x] == 0)
                        {
                            bIsMove = true;
                            oldXY.x = x;
                            oldXY.y = y;
                        }
                    }
                }
            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    bIsMove = false;
                    newXY = Vector2i(x, y);
                    if (I_figure_in_hand != 0)
                    {
                        if (newXY != oldXY && newXY.x >= 0 && newXY.y >= 0 && newXY.x < 8 && newXY.y < 8)
                        {
                            if (bTurn)
                            {
                                if (Board[newXY.y][newXY.x] <= 0 || Board[newXY.y][newXY.x] == Fantom_Pawn)
                                {
                                    switch (I_figure_in_hand)
                                    {
                                    case Pawn_White:
                                        bCanMove = movePawn(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Rook_White:
                                        bCanMove = moveRook(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Knight_White:
                                        bCanMove = moveKnight(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Bishop_White:
                                        bCanMove = moveBishop(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Queen_White:
                                        bCanMove = moveQueen(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case King_White:
                                        bCanMove = moveKing(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    default:
                                        bCanMove = false;
                                        break;
                                    }
                                }
                                else
                                    bCanMove = false;
                            }
                            else
                                if (Board[newXY.y][newXY.x] >= 0)
                                {
                                    switch (I_figure_in_hand)
                                    {
                                    case Pawn_Black:
                                        bCanMove = movePawn(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Rook_Black:
                                        bCanMove = moveRook(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Knight_Black:
                                        bCanMove = moveKnight(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Bishop_Black:
                                        bCanMove = moveBishop(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case Queen_Black:
                                        bCanMove = moveQueen(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    case King_Black:
                                        bCanMove = moveKing(oldXY.x, oldXY.y, newXY.x, newXY.y);
                                        break;
                                    default:
                                        bCanMove = false;
                                        break;
                                    }
                                }
                                else
                                    bCanMove = false;

                            if (bCanMove)
                            {
                                int KingX, KingY, figure;
                                bTurn ? figure = King_White : figure = King_Black;
                                if (figure == I_figure_in_hand)
                                {
                                    KingX = x;
                                    KingY = y;
                                }
                                else
                                {
                                    if (bTurn)
                                    {
                                        KingX = WhitePiece[5].getPosition().x / field_size;
                                        KingY = WhitePiece[5].getPosition().y / field_size;
                                    }
                                    else
                                    {
                                        KingX = BlackPiece[5].getPosition().x / field_size;
                                        KingY = BlackPiece[5].getPosition().y / field_size;
                                    }
                                }
                                figure = Board[y][x];
                                Board[y][x] = I_figure_in_hand;
                                if (check(KingX, KingY))
                                {
                                    Board[oldXY.y][oldXY.x] = I_figure_in_hand;
                                    I_figure_in_hand = 0;
                                    Board[y][x] = figure;
                                    break;
                                }
                                std::cout << char(oldXY.x + 'a') << 8 - oldXY.y << char(newXY.x + 'a') << 8 - newXY.y << "\n";
                                if (bFantom)
                                {
                                    int row;
                                    bTurn ? row = 2 : row = 5;
                                    for (int i = 0; i < 8; i++)
                                    {
                                        if (Board[row][i] == Fantom_Pawn)
                                        {
                                            Board[row][i] = 0;
                                            break;
                                        }
                                    }
                                    bFantom = false;
                                }
                                if (oldXY == Vector2i(4, 0))
                                    bFirstMoveKandR[0] = false;
                                else if (oldXY == Vector2i(7, 0))
                                    bFirstMoveKandR[1] = false;
                                else if (oldXY == Vector2i(0, 0))
                                    bFirstMoveKandR[2] = false;
                                else if (oldXY == Vector2i(4, 7))
                                    bFirstMoveKandR[3] = false;
                                else if (oldXY == Vector2i(7, 7))
                                    bFirstMoveKandR[4] = false;
                                else if (oldXY == Vector2i(0, 7))
                                    bFirstMoveKandR[5] = false;
                                if (!bTransformetion)
                                    bTurn = !bTurn;
                                bCanMove = false;
                                if (bTurn)
                                {
                                    figure = King_White;
                                    KingX = WhitePiece[5].getPosition().x / field_size;
                                    KingY = WhitePiece[5].getPosition().y / field_size;
                                }
                                else
                                {
                                    figure = King_Black;
                                    KingX = BlackPiece[5].getPosition().x / field_size;
                                    KingY = BlackPiece[5].getPosition().y / field_size;
                                }
                                if (check(KingX, KingY))
                                {
                                    bMate = true;
                                    for (int i = KingX - 1; i <= KingX + 1; i++)
                                    {
                                        for (int j = KingY - 1; j <= KingY + 1; j++)
                                        {
                                            if ((i == KingX && j == KingY) || i < 0 || j < 0 || i >= 8 || j >= 8)
                                                continue;
                                            if (Board[j][i] * figure <= 0 && !check(i, j))
                                            {
                                                bMate = false;
                                                break;
                                            }
                                        }
                                        if (!bMate)
                                            break;
                                    }
                                    if (bMate)
                                        if (defence(newXY.x, newXY.y))
                                            bMate = false;
                                        else
                                            switch (abs(I_figure_in_hand))
                                            {
                                            case 2:
                                                if (KingX == newXY.x)
                                                {
                                                    if (KingY > newXY.y)
                                                        for (int i = newXY.y + 1; i < KingY; i++)
                                                            if (defence(KingX, i))
                                                            {
                                                                bMate = false;
                                                                break;
                                                            }
                                                            else
                                                                for (int i = KingY + 1; i < newXY.y; i++)
                                                                    if (defence(KingX, i))
                                                                    {
                                                                        bMate = false;
                                                                        break;
                                                                    }
                                                }
                                                else if (KingY == newXY.y)
                                                {
                                                    if (KingX > newXY.x)
                                                        for (int i = newXY.x + 1; i < KingX; i++)
                                                            if (defence(i, KingY))
                                                            {
                                                                bMate = false;
                                                                break;
                                                            }
                                                            else
                                                                for (int i = KingX + 1; i < newXY.x; i++)
                                                                    if (defence(i, KingY))
                                                                    {
                                                                        bMate = false;
                                                                        break;
                                                                    }
                                                }
                                                break;
                                            case 4:
                                                if (KingY > newXY.y && KingX > newXY.x)
                                                {
                                                    for (int i = newXY.y + 1, j = newXY.x + 1; i < KingY; i++, j++)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else if (KingY > newXY.y && KingX < newXY.x)
                                                {
                                                    for (int i = newXY.y + 1, j = newXY.x - 1; i < KingY; i++, j--)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else if (KingY < newXY.y && KingX > newXY.x)
                                                {
                                                    for (int i = newXY.y - 1, j = newXY.x + 1; i > KingY; i--, j++)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else
                                                {
                                                    for (int i = newXY.y - 1, j = newXY.x - 1; i > KingY; i--, j--)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                break;
                                            case 5:
                                                if (KingX == newXY.x)
                                                {
                                                    if (KingY > newXY.y)
                                                        for (int i = newXY.y + 1; i < KingY; i++)
                                                            if (defence(KingX, i))
                                                            {
                                                                bMate = false;
                                                                break;
                                                            }
                                                            else
                                                                for (int i = KingY + 1; i < newXY.y; i++)
                                                                    if (defence(KingX, i))
                                                                    {
                                                                        bMate = false;
                                                                        break;
                                                                    }
                                                }
                                                else if (KingY == newXY.y)
                                                {
                                                    if (KingX > newXY.x)
                                                        for (int i = newXY.x + 1; i < KingX; i++)
                                                            if (defence(i, KingY))
                                                            {
                                                                bMate = false;
                                                                break;
                                                            }
                                                            else
                                                                for (int i = KingX + 1; i < newXY.x; i++)
                                                                    if (defence(i, KingY))
                                                                    {
                                                                        bMate = false;
                                                                        break;
                                                                    }
                                                }
                                                else  if (KingY > newXY.y && KingX > newXY.x)
                                                {
                                                    for (int i = newXY.y + 1, j = newXY.x + 1; i < KingY; i++, j++)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else if (KingY > newXY.y && KingX < newXY.x)
                                                {
                                                    for (int i = newXY.y + 1, j = newXY.x - 1; i < KingY; i++, j--)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else if (KingY < newXY.y && KingX > newXY.x)
                                                {
                                                    for (int i = newXY.y - 1, j = newXY.x + 1; i > KingY; i--, j++)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                else
                                                {
                                                    for (int i = newXY.y - 1, j = newXY.x - 1; i > KingY; i--, j--)
                                                        if (defence(j, i))
                                                        {
                                                            bMate = false;
                                                            break;
                                                        }
                                                }
                                                break;
                                            default:
                                                break;
                                            }
                                }
                                if (bMate)
                                    if (bTurn)
                                        std::cout << "Black wins!" << "\n";
                                    else
                                        std::cout << "White wins!" << "\n";
                            }
                            else
                                Board[oldXY.y][oldXY.x] = I_figure_in_hand;
                        }
                        else
                            Board[oldXY.y][oldXY.x] = I_figure_in_hand;
                    }
                    I_figure_in_hand = 0;
                }
            }
        }
        if (bIsMove)
        {
            S_figure_in_hand->setPosition(pos.x - dx, pos.y - dy);
            window.draw(*S_figure_in_hand);
        }
        window.display();
    }
}
