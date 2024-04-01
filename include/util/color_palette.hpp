#pragma once
#include "color.hpp"

namespace colors {
using Color = RGB;
constexpr Color Black = RGB(0, 0, 0);
constexpr Color White = {0xFF, 0xFF, 0xFF};
constexpr Color DimWhite = {0x77, 0x77, 0x77};
constexpr Color Red = RGB(255, 0, 0);
constexpr Color Orange = RGB(255, 128, 0);
constexpr Color Yellow = RGB(255, 255, 0);
constexpr Color Lime = RGB(128, 255, 0);
constexpr Color Green = RGB(0, 255, 0);
constexpr Color Turquoise = RGB(0, 255, 128);
constexpr Color Cyan = RGB(0, 255, 255);
constexpr Color DarkBlue = RGB(0, 128, 255);
constexpr Color Blue = RGB(0, 0, 255);
constexpr Color Purple = RGB(128, 0, 255);
constexpr Color Magenta = RGB(255, 0, 255);
constexpr Color Pink = RGB(255, 128, 128);

constexpr Color Sky = RGB(34, 230, 239);

namespace kelly {
constexpr Color vivid_yellow = RGB(255, 179, 0);
constexpr Color strong_purple = RGB(128, 62, 117);
constexpr Color vivid_orange = RGB(255, 104, 0);
constexpr Color very_light_blue = RGB(166, 189, 215);
constexpr Color vivid_red = RGB(193, 0, 32);
constexpr Color grayish_yellow = RGB(206, 162, 98);
constexpr Color medium_gray = RGB(129, 112, 102);

// these aren't good for people with defective color vision:
constexpr Color vivid_green = RGB(0, 125, 52);
constexpr Color strong_purplish_pink = RGB(246, 118, 142);
constexpr Color strong_blue = RGB(0, 83, 138);
constexpr Color strong_yellowish_pink = RGB(255, 122, 92);
constexpr Color strong_violet = RGB(83, 55, 122);
constexpr Color vivid_orange_yellow = RGB(255, 142, 0);
constexpr Color strong_purplish_red = RGB(179, 40, 81);
constexpr Color vivid_greenish_yellow = RGB(244, 200, 0);
constexpr Color strong_reddish_brown = RGB(127, 24, 13);
constexpr Color vivid_yellowish_green = RGB(147, 170, 0);
constexpr Color deep_yellowish_brown = RGB(89, 51, 21);
constexpr Color vivid_reddish_orange = RGB(241, 58, 19);
constexpr Color dark_olive_green = RGB(35, 44, 22);
}  // namespace kelly

namespace wad {
constexpr Color Black = RGB(0, 0, 0);
constexpr Color Dark_Gray = RGB(87, 87, 87);
constexpr Color Red = RGB(173, 35, 35);
constexpr Color Blue = RGB(42, 75, 215);
constexpr Color Green = RGB(29, 105, 20);
constexpr Color Brown = RGB(129, 74, 25);
constexpr Color Purple = RGB(129, 38, 192);
constexpr Color Light_Gray = RGB(160, 160, 160);
constexpr Color Light_Green = RGB(129, 197, 122);
constexpr Color Light_Blue = RGB(157, 175, 255);
constexpr Color Cyan = RGB(41, 208, 208);
constexpr Color Orange = RGB(255, 146, 51);
constexpr Color Yellow = RGB(255, 238, 51);
constexpr Color Tan = RGB(233, 222, 187);
constexpr Color Pink = RGB(255, 205, 243);
constexpr Color White = RGB(255, 255, 255);

}  // namespace wad

namespace brand {
// Primaries
constexpr Color Blue = RGB(91, 206, 250);
constexpr Color Pink = RGB(245, 169, 184);

// Complementaries (Blue)
constexpr Color Red = RGB(242, 82, 113);       // Red
constexpr Color Yellow = RGB(245, 236, 73);    // Yellow
constexpr Color DarkBlue = RGB(99, 182, 214);  // Dark Blue
constexpr Color Green = RGB(64, 248, 98);      // Lime Green
}  // namespace brand
}  // namespace colors
