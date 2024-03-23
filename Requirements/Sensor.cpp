//
// Sensor.cpp
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
#include "Sensor.h"

LoadClass CLoadSensor::Load()
{
   double l_fMeasure = Measure();

   if (CHECK_EMPTY( l_fMeasure ))
   { return LoadClassEmpty; }

   if (CHECK_BELOWNORMAL( l_fMeasure ))
   { return LoadClass::LoadClassBelowNormal; }

   if (CHECK_NORMAL( l_fMeasure ))
   { return LoadClass::LoadClassNormal; }

   if (CHECK_ABOVENORMAL( l_fMeasure ))
   { return LoadClass::LoadClassAboveNormal; }

   if (CHECK_FULL( l_fMeasure ))
   { return LoadClass::LoadClassFull; }

   if (CHECK_OVERLOAD( l_fMeasure ))
   { return LoadClass::LoadClassOverload; }
   else
   { return LoadClass::LoadClassUnknown; }
}

const char *LoadClassToString( const LoadClass inLoadClass )
{
   switch (inLoadClass)
   {
      case LoadClassEmpty:
         return "Empty";
      case LoadClassBelowNormal:
         return "Below Normal";
      case LoadClassNormal:
         return "Normal";
      case LoadClassAboveNormal:
         return "Above Normal";
      case LoadClassFull:
         return "Full";
      case LoadClassOverload:
         return "Overload";
   }

   return "Unknown";
}
   
