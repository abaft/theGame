#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <string>
#include "maze.hpp"

class maze{
private:
  cell* m;
  cell* walls;
  int height; // MUST BE ODD ints
  int width; // MUST BE ODD ints
  int mallocCells()
  {
    srand(time(nullptr));
    m = new cell[width * height];
    if (m == nullptr)
      return 1;

    cell* d;
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        d = m + j + i * width;
        d->x = j;
        d->y = i;
        d->wall = 3; // 1111

        //ensure border cannot be broken
        if (i == 0)
          d->freedir = 7; // 0111
        else if (i == height - 1)
          d->freedir = 13; // 1101
        else
          d->freedir = 15; // 1111

        if (j == 0)
          d->freedir &= 14; // 1110
        else if (j == width - 1)
          d->freedir &= 11; // 1011
      }
    }
    return 0;
  }

  cell* cellByCood(int x, int y)
  {
    return m + x + y * width;
  }
  
  cell* link(cell* d)
  {
    if ( d == nullptr ) return nullptr;


    int x, y;
    x = d->x;
    y = d->y;
    cell* rtn;

    while (d->freedir){
      char randDir = 1 << rand()%4; //Selects a random direction
      if (!(d->freedir & randDir))
        continue;

      d->freedir &= ~randDir;

      switch (randDir)
      {
        case 8: //NORTH
          if (cellByCood(x, y-1)->parent == nullptr)
          {
            rtn = cellByCood(x, y-1);
            d->wall &= 1; //01
            rtn->parent = d;
            return rtn;
          }
          else
            continue;
        case 4: //EAST
          if (cellByCood(x+1, y)->parent == nullptr)
          {
            rtn = cellByCood(x+1, y);
            d->wall &= 2; // 10
            rtn->parent = d;
            return rtn;
          }
          else
            continue;
        case 2: //SOUTH
          if (cellByCood(x, y+1)->parent == nullptr)
          {
            rtn = cellByCood(x, y+1);
            rtn->wall &= 1; //01
            rtn->parent = d;
            return rtn;
          }
          else
            continue;
        case 1: //WEST
          if (cellByCood(x-1, y)->parent == nullptr)
          {
            rtn = cellByCood(x-1, y);
            rtn->wall &= 2; //10
            rtn->parent = d;
            return rtn;
          }
          else
            continue;
      }
    }

    return d->parent;
  }

public:
  maze(int width_, int height_)
  {
    width = width_;
    height = height_;
  
    if (mallocCells())
    {
      exit(1);
    }
    cell* start = m;
    cell* end;
    start->parent = start;
    do
    {
      start = link(start);
    }while(start->parent != start);
  }
  
  maze()
  {
    width = 11;
    height = 11;
  
    if (mallocCells())
    {
      exit(1);
    }
    cell* start = m;
    cell* end;
    start->parent = start;
    do
    {
      start = link(start);
    }while(start->parent != start);
  }
  
  ~maze()
  {
    free(m);
  }
  
  std::string draw()
  {
    std::string rtn;
  
    cell* d;
    char tmp[(width * 4)];
    for (int z = 0; z < width * 4; ++z) tmp[z]= '#';
    for (int i = 0; i < height; ++i)
    {
      for(int j = 0; j < width; ++j)
      {
        d = m + j + i * width;
        if (!(d->wall & 2)) //NORT
        {
          tmp[0 + j*2] = ' ';
        }
        
        if (!(d->wall & 1)) //EAST
        {
          tmp[(width*2) + (j*2) + 1] = ' ';
        }
        tmp[(width*2) + (j*2)] = ' ';
      }
      rtn.append("#");
      rtn.append(tmp, width*2);
      rtn.append("\n#");
      rtn.append(tmp + width*2, width*2); 
      for (int z = 0; z < width * 4; ++z) tmp[z]= '#';
      rtn.append("\n");
    }
    rtn.append(2*width +1, '#');
    rtn.append("\n");
    return rtn;
  }
  int getHeight() {return height;}
  int getWidth() {return width;}

  
};

int main(int argc, char** argv)
{
  maze* Maze;
  if (argc == 3)
    Maze = new maze(atoi(argv[1]) ,atoi(argv[2]));
  else
    Maze = new maze;
  int i = Maze->getHeight();
  std::cout << i << "\n";
  std::cout << Maze->draw();
}
