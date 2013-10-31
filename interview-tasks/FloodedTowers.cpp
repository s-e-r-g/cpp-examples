#include <iostream>
#include <vector>
#include <cstdlib>


class Area
{
public:
    Area(size_t width_) : width(width_), towers(width_), water(width_){}

    void generateRandomTowers(int maxHeight)
    {
        for (size_t i = 0; i < width; ++i) towers[i] = rand() % maxHeight;
    }

    void calculateWater()
    {
        size_t leftPos = 0;
        int rightPos = width - 1;

        int leftMax = towers[leftPos];
        int rightMax = towers[rightPos];

        enum {LeftToRight, RightToLeft} direction = leftMax < rightMax ? LeftToRight : RightToLeft;

        while (leftPos < rightPos)
        {
            if (direction == LeftToRight)
            {
                water[leftPos] = leftMax - towers[leftPos];
               ++leftPos;
               if (towers[leftPos] > leftMax)
               {
                   leftMax = towers[leftPos];
                   if (leftMax > rightMax)
                   {
                        direction = RightToLeft;
                   }
               }
            }
            else
            {
               water[rightPos] = rightMax - towers[rightPos];
               --rightPos;
               if (towers[rightPos] > rightMax)
               {
                   rightMax = towers[rightPos];
                   if (rightMax > leftMax)
                   {
                        direction = LeftToRight;
                   }
               }
            }
        }
    }

    void print() const
    {
        // get min & max
        int min = 0;
        int max = 0;
        for (size_t i = 0; i < width; ++i)
        {
           if (min > towers[i]) min = towers[i];

           if (max < (towers[i] + water[i])) max = (towers[i] + water[i]);
        }

        for (int y = max; y > min; y--)
        {
           for (size_t x = 0; x < width; ++x)
           {
              char symbol = (towers[x] >= y) ? '#' : ((water[x] + towers[x]) >= y ? '~' : ' ');
              std::cout << symbol;
           }
           std::cout << std::endl;
        }
    }

private:
   size_t width;
   std::vector<int> towers;
   std::vector<int> water;
};







int main(int argc, const char** argv)
{
    srand (time(NULL));

    Area area(60);
    area.generateRandomTowers(40);
    area.calculateWater();
    area.print();
}

