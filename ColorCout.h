#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>

class ColorOutput
{
  enum Color;

  static Color cur_back;
  static Color cur_fore;

  public:
    enum Color
    {
      Black = 0,
      Blue = 1,
      Green = 2,
      Cyan = 3,
      Red = 4,
      Magenta = 5,
      Brown = 6,
      LightGray = 7,
      DarkGray = 8,
      LightBlue = 9,
      LightGreen = 10,
      LightCyan = 11,
      LightRed = 12,
      LightMagenta = 13,
      Yellow = 14,
      White = 15
    };

    static void SetTextColor(Color color)
    {
      cur_fore = color;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hStdOut, (WORD)((cur_back << 4) | color));
    }

    static void SetBackColor(Color color)
    {
      cur_back = color;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hStdOut, (WORD)((color << 4) | cur_fore));
    }

    static void SetColor(Color text, Color background)
    {
      cur_fore = text;
      cur_back = background;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }

    static void ResetColor()
    {
      SetColor(White, Black);
    }

    static void SetFont(int num)
    {
      typedef UINT(CALLBACK* TImportFunc)(HANDLE, UINT);
      HINSTANCE hInst = GetModuleHandle("kernel32.dll");
      TImportFunc SetConsoleFont = (TImportFunc)GetProcAddress(hInst, "SetConsoleFont");

      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), num);
      return;    
    }
};

ColorOutput::Color ColorOutput::cur_back = Color::Black;
ColorOutput::Color ColorOutput::cur_fore = Color::White;

typedef ColorOutput CO;
typedef ColorOutput::Color COL;