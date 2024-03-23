//
// Sensor.h
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
#pragma once

#include "Base.h"

class CSensor : CBase
{

public:
   
   // Range: 0.00 - 1.00+
   virtual double Measure() = 0;
   
};

enum LoadClass
{
   LoadClassUnknown     = -1,
   
   // 0.00 - 0.20
   LoadClassEmpty       = 0,   
   
   // 0.20 - 0.40
   LoadClassBelowNormal = 1,
   
   // 0.40 - 0.60
   LoadClassNormal      = 2, 
   
   // 0.60 - 0.80
   LoadClassAboveNormal = 3,
   
   // 0.80 - 1.00
   LoadClassFull        = 4, 

   // > 1.00
   LoadClassOverload    = 5
};


#define CHECK_EMPTY(Current) (((Current) >= 0.00) && ((Current) <= 0.20))
#define CHECK_BELOWNORMAL(Current) (((Current) > 0.20) && ((Current) <= 0.40))
#define CHECK_NORMAL(Current) (((Current) > 0.40) && ((Current) <= 0.60))
#define CHECK_ABOVENORMAL(Current) (((Current) > 0.60) && ((Current) <= 0.80))
#define CHECK_FULL(Current) (((Current) > 0.80) && ((Current) <= 1.00))
#define CHECK_OVERLOAD(Current) ((Current) > 1.0)

class CLoadSensor : public CSensor
{
   
public:
   
   virtual double MaximumLoad() = 0;
   
   LoadClass Load();
   
};

const char *LoadClassToString( const LoadClass inLoadClass );
