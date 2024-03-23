//
// Console.cpp
//
// Author:
//       Hakan Emre Kartal <hek@nula.com.tr>
//
// Copyright (c) 2018 Hakan Emre Kartal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "Console.h"

void ClrScr( __int16 inColor )
{
   HANDLE l_hConsole;
   COORD l_varCoord;
   DWORD l_dwReturnLength, l_dwLength;
   CONSOLE_SCREEN_BUFFER_INFO l_varInfo;

   l_hConsole = ::GetStdHandle( STD_OUTPUT_HANDLE );
   ::GetConsoleScreenBufferInfo( l_hConsole, &l_varInfo );
   l_dwLength = (l_varInfo.dwSize.X * l_varInfo.dwSize.Y);

   l_varCoord.X = l_varCoord.Y = 0;
   
   ::FillConsoleOutputCharacter( l_hConsole, (CHAR)0, l_dwLength, l_varCoord, &l_dwReturnLength );
   ::FillConsoleOutputAttribute( l_hConsole, (WORD)inColor, l_dwLength, l_varCoord, &l_dwReturnLength );

   ::SetConsoleCursorPosition( l_hConsole, l_varCoord );
}

void GotoXY( __int16 inX, __int16 inY )
{
   COORD l_varCoord;

   l_varCoord.X = inX;
   l_varCoord.Y = inY;

   ::SetConsoleCursorPosition( ::GetStdHandle( STD_OUTPUT_HANDLE ), l_varCoord );
}
