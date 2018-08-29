#include <iostream>

class SudokuSolver
{
public:
    SudokuSolver()
    { 
	clean();
    }
    
    bool solve()
    {
        clean();
        for (std::uint8_t v = 1; v <= 9; ++v)
        {
            if (bt(0, 0, v)) return true;
        }
        
        return false;
    }
    
    
    void print() const
    {
        for (int y = 0; y < 9; ++y)
        {
            for (int x = 0; x < 9; ++x)
            {
                std::cout << (int)_field[y][x];
            }
            std::cout << "\n";
        }
    }
    
    void clean()
    {
        for (int y = 0; y < 9; ++y)
            for (int x = 0; x < 9; ++x)
                _field[y][x] = 0;
    }
        
private:
    bool bt(int x, int y, std::uint8_t value)
    {
        if (!isStepPossible(x, y, value)) return false;
      
        _field[y][x] = value;
        
        if (x == 8 && y == 8) return true;
      
        const int nextX = (x + 1) % 9;
        const int nextY = y + (nextX == 0 ? 1 : 0);
        
        for (std::uint8_t v = 1; v <= 9; ++v)
        {
            if (bt(nextX, nextY, v)) return true;
        }
        
        _field[y][x] = 0;
        
        return false;
    }
    
    bool isStepPossible(int x, int y, std::uint8_t value)
    {
        const int squareX = (x / 3) * 3;
        const int squareY = (y / 3) * 3;

        for (int i = 0; i < 9; ++i)
        {
            if (i != x && _field[y][i] == value)
            {
                return false;
            }

            if (i != y && _field[i][x] == value)
            {
                return false;
            }

            const int xToCheck = squareX + i % 3;
            const int yToCheck = squareY + i / 3;

            if (xToCheck != x && yToCheck != y && _field[yToCheck][xToCheck] == value)
            {
                return false;
            }
        }

        return true;
    }
    
    std::uint8_t _field[9][9];
};

int main()
{
    SudokuSolver solver;
    
    if (solver.solve())
    {
        solver.print();
    }
    else
    {
        std::cout << "NO solution!\n";
    }
}
