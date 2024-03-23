//
// Garbage.cpp
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
#include "Garbage.h"

CGarbage::CGarbage( double inWeight ) : \
   CBase(),
   m_fWeight(inWeight)
{}


CGarbage *GarbageGenerator( double inMinimumWeight, double inMaximumWeight )
{
   double l_fWeight = (inMinimumWeight + (rand() / (RAND_MAX / (inMaximumWeight - inMinimumWeight))));

   switch (__abs(rand()) % (7 + 1))
   {
      case 0: return new CDomesticWaste( l_fWeight );
      case 1: return new CMedicalWaste( l_fWeight );
      case 2: return new CRottenFruit( l_fWeight );
      case 3: return new CRottenVegetable( l_fWeight );
      case 4: return new CPlasticWaste( l_fWeight );
      case 5: return new CPaperWaste( l_fWeight );
      case 6: return new CChemicalWaste( l_fWeight );
   }
         
   return new COtherWaste( l_fWeight );
}
