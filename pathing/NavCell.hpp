#ifndef NAVCELL_H_INCLUDED
#define NAVCELL_H_INCLUDED

#include "../math/V2.hpp"

#define CELL_W 16
#define CELL_H 32
#define CELL_Z 12
#define CELL_WALL_H 20

class NavCell
{
  //! FRIENDS
friend class NavGrid;
friend class NavGridView;
friend class SearchState;

  //! NESTING
public:
  enum type_t
  {
    STAIRS, LANDING, CORRIDOR, WINDOW, WALL
  };
  struct neighbourhood_t
  {
    bool n, s, e, w, ne, se, nw, sw;
  };


  //! CONSTANTS
public:
  static const fV2 SIZE;
  static const float floor_z;
  static const float wall_h;


  //! ATTRIBUTES
public:
  type_t type;
  bool obstacle;
  const uV2 grid_position;
  const fV2 vertex_position;


  //! METHODS
public:
  NavCell(uV2 grid_position_);
  virtual ~NavCell();

  // mutators
  void setType(neighbourhood_t neighbour_obstacle);
};

#endif // NAVCELL_H_INCLUDED
