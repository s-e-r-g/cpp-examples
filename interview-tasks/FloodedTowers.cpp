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

    size_t calculateWater()
    {
        if (width <= 1) return 0;
        
        size_t leftPos = 0;
        size_t rightPos = width - 1;

        int leftMax = towers[leftPos];
        int rightMax = towers[rightPos];

        enum {LeftToRight, RightToLeft} direction = leftMax < rightMax ? LeftToRight : RightToLeft;

        size_t waterVolume = 0;
        
        while (leftPos < rightPos)
        {
            if (direction == LeftToRight)
            {
                water[leftPos] = leftMax - towers[leftPos];
                
                waterVolume += water[leftPos]; 
                
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
               
               waterVolume += water[rightPos]; 
               
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
        
        return waterVolume;
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

        //Display picture
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
    size_t waterVolume = area.calculateWater();
    area.print();
    std::cout << "Water volume: " << waterVolume << std::endl;
}

