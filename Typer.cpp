/* Author: Brendon Kofink
 *         Wesley Goyette
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Epicer Puzzle
 * Assignment Description: A Puzzle game where the user can
 *   solve a puzzle by moving and snapping pieces into place.
 * Due Date: 5/4/2023
 * Date Created: 4/20/2023
 * Date Last Modified: 4/20/2023
 */

#include "Typer.h"

Typer::Typer()
{
  ImportLetters();
  ImportNumbers();
  ImportSymbols();
}

void Typer::ImportLetters()
{
  ifstream file("A.txt");
  char c;
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        file.get(c);
        if (c == '1')
        {
          characters[i][j][k] = true;
        }
        else
        {
          characters[i][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

void Typer::ImportNumbers()
{
  ifstream file("num.txt");
  char c;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        file.get(c);
        if (c == '1')
        {
          characters[i + 26][j][k] = true;
        }
        else
        {
          characters[i + 26][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

void Typer::ImportSymbols()
{
  ifstream file("special.txt");
  char c;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        file.get(c);
        if (c == '1')
        {
          characters[i + 36][j][k] = true;
        }
        else
        {
          characters[i + 36][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

bool Typer::TryLetter(char c, int &index)
{
  bool found = false;
  if (c == '!')
  {
    index = 36;
    found = true;
  }
  else if (c == ':')
  {
    index = 37;
    found = true;
  }
  else if (c == '.')
  {
    index = 38;
    found = true;
  }
  else if (c == '-')
  {
    index = 39;
    found = true;
  }
  else if (c == '+')
  {
    index = 40;
    found = true;
  }
  return found;
}

void Typer::DrawBox(SDL_Plotter &g, int x, int y, int size, color c)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (x+i >= 0 && x+i < g.getCol() && y+j >= 0 && y+j < g.getRow())
      {
        g.plotPixel(x + i, y + j, c.R, c.G, c.B);
      }
    }
  }
}

void Typer::Write(string word, SDL_Plotter &g, Vec2 pos, color c, int size, bool back)
{
  int character;
  for (int i = 0; i < word.length(); i++)
  {
    if (isalpha(word[i]))
    {
      character = toupper(word[i]) - 'A';
    }
    else if (isdigit(word[i]))
    {
      character = word[i] - '0' + 26;
    }
    else if (!TryLetter(word[i], character))
    {
      character = 0;
    }
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (characters[character][j][k] && word[i] != ' ')
        {
          DrawBox(g, pos.x + i * 5 * size + i * size + k * size, pos.y + j * size, size, c);
        }
        else if (back)
        {
          DrawBox(g, pos.x + i * 5 * size + i * size + k * size, pos.y + j * size, size, color(255,255,255));
        }
      }
    }
  }
}
