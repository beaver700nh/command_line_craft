#include <cstring>
#include <fstream>
#include <ncurses.h>
#include <random>
#include <string>

#include "misc.hpp"

#include "../data/constants.hpp"

void Coords::d_print(WINDOW *win, int row, int col) {
  char buf[100];

  sprintf(buf, "x: %6ld, y: %6ld", x, y);

  mvwaddstr(win, row,   col, "Coords::d_print():");
  mvwaddstr(win, row+1, col, buf);
}

void unicode_to_chtype(const char *bytes, chtype *decoded) {
  int i = 0;
  int j = 0;

  while (bytes[i] != '\0') {
    if (((const unsigned char *) bytes)[i] == 0xE2) {
      decoded[j] = decode_lookup(bytes[i+2]);
      i += 3;
    }
    else if (((const unsigned char *) bytes)[i] == 0xC2) {
      decoded[j] = decode_lookup(bytes[i+1]);
      i += 2;
    }
    else {
      decoded[j] = bytes[i];
      ++i;
    }

    ++j;
  }

  decoded[j] = '\0';
}

chtype decode_lookup(char b) {
  switch ((unsigned char) b) {
    case 0x8C: return ACS_ULCORNER;
    case 0x90: return ACS_URCORNER;
    case 0x94: return ACS_LLCORNER;
    case 0x98: return ACS_LRCORNER;
    case 0x80: return ACS_HLINE;
    case 0x82: return ACS_VLINE;
    case 0xAC: return ACS_TTEE;
    case 0xB4: return ACS_BTEE;
    case 0x9C: return ACS_LTEE;
    case 0xA4: return ACS_RTEE;
    case 0xB0: return ACS_DEGREE;
    case 0xB1: return ACS_PLMINUS;
    default:   return '?';
  }
}

int get_rand_num(int min, int outcomes, std::mt19937 rng) {
  std::uniform_int_distribution<> dist(min, min + outcomes - 1);

  return dist(rng);
}

int set_logo(char *dest, std::mt19937 rng) {
  int logo_easter = get_rand_num(0, 4, rng);

  if (logo_easter == 0) {
    strcpy(dest, CLC_APPDATA "asciiart/logo.txt");
  }
  else if (logo_easter == 1) {
    strcpy(dest, CLC_APPDATA "asciiart/logo_alt_a.txt");
  }
  else if (logo_easter == 2) {
    strcpy(dest, CLC_APPDATA "asciiart/logo_alt_b.txt");
  }
  else if (logo_easter == 3) {
    strcpy(dest, CLC_APPDATA "asciiart/logo_alt_c.txt");
  }
  else {
    return 1; // Illegal random logo
  }

  return 0;
}

int set_splash(char *dest, std::mt19937 rng) {
  std::ifstream ifs(CLC_APPDATA "splashes.txt");
  std::vector<std::string> splashes;

  for (std::string line; std::getline(ifs, line); /* no 3rd clause */) {
    if ((line.length() != 0) && (line.at(0) != '#')) {
      splashes.push_back(line);
    }
  }

  ifs.close();

  int splash_id = get_rand_num(0, splashes.size(), rng);
  strcpy(dest, splashes.at(splash_id).c_str());

  return 0;
}
