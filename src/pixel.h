#pragma once
#ifndef PIXEL_H
#define PIXEL_H

#include "std_libs.h"

// Ansi Color Codes
//FROM: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
namespace COLOR
{
    const std::string reset = "\u001b[0m";

    // Default Colors
    const std::string fg_default = "39";
    const std::string bg_default = "49";

    // Foreground Colors
    const std::string fg_black = "30";
    const std::string fg_red = "31";
    const std::string fg_green = "32";
    const std::string fg_yellow = "33";
    const std::string fg_blue = "34";
    const std::string fg_magenta = "35";
    const std::string fg_cyan = "36";
    const std::string fg_white = "37";

    const std::string fg_black_b = "90";
    const std::string fg_red_b = "91";
    const std::string fg_green_b = "92";
    const std::string fg_yellow_b = "93";
    const std::string fg_blue_b = "94";
    const std::string fg_magenta_b = "95";
    const std::string fg_cyan_b = "96";
    const std::string fg_white_b = "97";

    // Background Colors
    const std::string bg_black = "40";
    const std::string bg_red = "41";
    const std::string bg_green = "42";
    const std::string bg_yellow = "43";
    const std::string bg_blue = "44";
    const std::string bg_magenta = "45";
    const std::string bg_cyan = "46";
    const std::string bg_white = "47";

    const std::string bg_black_b = "100";
    const std::string bg_red_b = "101";
    const std::string bg_green_b = "102";
    const std::string bg_yellow_b = "103";
    const std::string bg_blue_b = "104";
    const std::string bg_magenta_b = "105";
    const std::string bg_cyan_b = "106";
    const std::string bg_white_b = "107";

    // Unicode Sequences
    const std::string unicode_escape = "\u001b[";
    const std::string separator = ";";
    const std::string unicode_end = "m";

    // Other Decorations
    const std::string reset_code = "0";
    const std::string bold_on = "1";
    const std::string faint_on = "2";
    const std::string italic_on = "3";
    const std::string underline_on = "4";
    const std::string blinking_on = "5";
    const std::string inverse_on = "7";
    const std::string hidden_on = "8";
    const std::string strikethrough_on = "9";
    const std::string bold_off = "22";
    const std::string faint_off = "22";
    const std::string italic_off = "23";
    const std::string underline_off = "24";
    const std::string blinking_off = "25";
    const std::string inverse_off = "27";
    const std::string hidden_off = "28";
    const std::string strikethrough_off = "29";

}

// Terminal Custom Pixel Definition
class PIXEL
{
private:
    int X = -1, Y = -1;

public:
    char holder = '\0';
		std::string ascii = "NULL";

    // Get X Coordinate
    [[nodiscard]] int get_X() const { return this->X; }

    // Get Y Coordinate
    [[nodiscard]] int get_Y() const { return this->Y; }

    // Set X and Y Coordinate
    void set_coordinate(int x, int y)
    {
        this->X = x;
        this->Y = y;
    }
};

#endif // PIXEL_H
