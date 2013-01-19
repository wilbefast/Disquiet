#ifndef NAVCELL_H_INCLUDED
#define NAVCELL_H_INCLUDED

#include "../math/V2.hpp"

class NavCell
{
  //! FRIENDS
friend class NavGrid;
friend class NavGridView;
friend class SearchState;

  //! CONSTANTS
public:
  static const fV2 SIZE;

  //! ATTRIBUTES
public:
  bool obstacle;
  uV2 grid_position;
  unsigned int cost;
  float height;


  //! METHODS
public:
  NavCell(uV2 grid_position_, bool obstacle_ = false);
  virtual ~NavCell();
};

#endif // NAVCELL_H_INCLUDED
