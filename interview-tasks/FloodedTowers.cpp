/////////////////////////////////////////////////////////////////////////
// Copyright by Serg Ponomarenko 2013
//
// You have an array with walls heights.
// Calculate the amount of water left after rain between these walls.
// --------------------------------------------------
// Example:
//
//               #   
//               #   
//             #~#   
//     #~#~~~~~#~#   
//     #~##~~#~#~#   
//    ##~##~######~# 
//    ##~##~######~##
//    ############~##
//
//  Wall Array is : [3,5,1,5,4,1,3,4,3,6,3,8,0,3,2]
//
//  Amount of water is : 20
//
///////////////////////////////////////////////////



#include <iostream>
#include <vector>
#include <cstdlib>




class Area
{
public:
    Area(size_t width_) : width(width_), towers(width_), water(width_){}

    void generateRandomTowers(int maxHeight)
    {
        for (size_t i = 0; i < width; ++i) towers[i] = rand() % (maxHeight + 1);
    }

    size_t calculateWater()
    {
        if (width <= 2)
        {
              std::fill(water.begin(), water.end(), 0);
              return 0;
        }

        size_t leftPos = 0;
        size_t rightPos = width - 1;

        int leftMax = towers[leftPos];
        int rightMax = towers[rightPos];

        size_t waterVolume = 0;

        while (leftPos < rightPos)
        {
            if (leftMax < rightMax) // Walk LEFT -----> RIGHT
            {
                water[leftPos] = leftMax - towers[leftPos];

                waterVolume += water[leftPos]; 

               ++leftPos;

               if (towers[leftPos] > leftMax)
               {
                   leftMax = towers[leftPos];
               }
            }
            else // Walk LEFT <------ RIGHT
            {
               water[rightPos] = rightMax - towers[rightPos];

               waterVolume += water[rightPos];

               --rightPos;

               if (towers[rightPos] > rightMax)
               {
                   rightMax = towers[rightPos];
               }
            }
        }

        return waterVolume;
    }

    void print() const
    {
        // Get min & max to fit picture size
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
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <Towers> <Max Height>>" << std::endl;
        return 1;
    }

    int towers = atoi(argv[1]);
    int maxHeight = atoi(argv[2]);

    srand (time(NULL));

    Area area(towers);
    area.generateRandomTowers(maxHeight);
    size_t waterVolume = area.calculateWater();
    area.print();
    std::cout << "Water volume: " << waterVolume << std::endl;
}

