#ifndef PLANE_HPP
#define PLANE_HPP

#include <ncurses.h>

template <typename Type>
class Plane {
  public:
    Plane();
    Plane(Type fill, long xr, long yr);

    void set_data(long x, long y, Type data);
    Type get_data(long x, long y);

    void d_print(WINDOW *win, int row, int col);

  private:
    std::vector<std::vector<Type>> internal_data;
};

template <typename Type>
Plane<Type>::Plane() {
  /* default ctor does nothing */;
}

template <typename Type>
Plane<Type>::Plane(Type fill, long xr, long yr) {
  std::vector<Type> each_row(xr, fill);
  internal_data.assign(yr, each_row);
}

template <typename Type>
void Plane<Type>::set_data(long x, long y, Type data) {
  internal_data.at(
    (y < 0 ? y * -2 - 1 : y * 2)
  ).at(
    (x < 0 ? x * -2 - 1 : x * 2)
  ) = data;
}

template <typename Type>
Type Plane<Type>::get_data(long x, long y) {
  return internal_data.at(
    (y < 0 ? y * -2 - 1 : y * 2)
  ).at(
    (x < 0 ? x * -2 - 1 : x * 2)
  );
}

template <typename Type>
void Plane<Type>::d_print(WINDOW *win, int row, int col) {
  char buf[100];
  sprintf(buf, "xr: %ld, yr: %ld", internal_data.at(0).size(), internal_data.size());

  mvwaddstr(win, row,   col, "Plane::d_print():");
  mvwaddstr(win, row+1, col, buf);
}

#endif
