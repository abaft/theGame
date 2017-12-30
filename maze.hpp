#include <string>
#ifndef _MAZE__HPP
#define _MAZE__HPP

typedef struct
{
  int x,y;
  char freedir; // NESW  4 bit direction
  char wall; // NE 2 bit
  char type; // W - Wall, C - Space
  void* parent;
} cell;

/*class maze{
private:
  cell* m;
  int height; // MUST BE ODD ints
  int width; // MUST BE ODD ints
  int mallocCells();

public:
  maze(int width_, int height_);
  maze();
  ~maze();  
  std::string draw();
};*/

#endif
