// Example program
#include <iostream>
#include <string>


constexpr auto XSize = 10;
constexpr auto YSize = 10;

constexpr int towers[XSize][YSize] =
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 3, 3, 0, 0, 0, 0, 0},
    {0, 0, 3, 1, 3, 1, 1, 1, 0, 0},
    {0, 0, 3, 3, 3, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 2, 2, 2, 1, 1, 1, 0},
    {0, 0, 0, 2, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
};

enum CellType
{
    Empty,
    BlackHole,
    Wall
};

CellType slice[XSize][YSize];

void fill(int x, int y)
{
    if (x < 0 || x >= XSize || y < 0 || y >= YSize) return;

    if (slice[y][x] != CellType::Empty) return;

    slice[y][x] = CellType::BlackHole;

    fill(x - 1, y);
    fill(x + 1, y);
    fill(x, y - 1);
    fill(x, y + 1);
}

void processSlice(int layerNumber)
{
    // Initialize slice
    int x;
    int y;
    for (x = 0; x < XSize; ++x)
    {
        for (y = 0; y < YSize; ++y)
        {
            slice[y][x] = towers[y][x] > layerNumber ? Wall : Empty;
        }
    }

    // Apply fill algorithm with "BlackHole" color to each cell of perimeter
    for (y = 0; y < YSize; ++y)
    {
        fill(0, y);
        fill(XSize - 1, y);
    }

    for (x = 1; x < XSize - 1; ++x)
    {
        fill(x, 0);
        fill(x, YSize - 1);
    }

    // Display the result
    for (y = 0; y < YSize; ++y)
    {
        for (int i = 0; i < y; ++i) std::cout << " ";

        for (x = 0; x < XSize; ++x)
        {
            char c;
            switch (slice[y][x])
            {
            case CellType::Empty: c = '~'; break;
            case CellType::BlackHole: c = '.'; break;
            case CellType::Wall: c = '#'; break;
            }
            std::cout << c;
        }
        std::cout << "\n";
    }
}

int main()
{
    processSlice(0);
    processSlice(1);
    processSlice(2);
    processSlice(3);
}
