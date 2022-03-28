//
// Garbage.h
//
// Author:
//       Hakan E. Kartal <hek@nula.com.tr>
//
// Copyright (c) 2021 Hakan E. Kartal
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
#include <stdlib.h>

/*
   
   Base
    \
     \_ Garbage
         |\
         | \_ DomesticWaste : Ev atýðý
         |\
         | \_ MedicalWaste : Týbbi atýk
         |\
         | \_ RottenFruit : Çürümüþ meyve
         |\
         | \_ RottenVegetable : Çürümüþ sebze
         |\
         | \_ PlasticWaste : Plastik atýk
         |\
         | \_ PaperWaste : Kaðýt atýðý
         |\
         | \_ ChemicalWaste : Kimyevi atýk
          \
           \_ OtherWaste : Diðer tür atýklar.

*/

class CGarbage : public CBase
{
private:
   
   double m_fWeight;

public:
   
   CGarbage( double inWeight );

   double Weight() { return m_fWeight; }

   virtual char *Identifier( void ) { return NULL; }

};

class CDomesticWaste : public CGarbage 
{
public:

   CDomesticWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier() { return "Domestic Waste"; }

};

class CMedicalWaste : public CGarbage
{
public:

   CMedicalWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Medical Waste"; }

};

class CRottenFruit : public CGarbage 
{
public:

   CRottenFruit( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Rotten Fruit"; }
};

class CRottenVegetable : public CGarbage
{
public:

   CRottenVegetable( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Rotten Vegetable"; }
};

class CPlasticWaste : public CGarbage 
{
public:

   CPlasticWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Plastic Waste"; }
};

class CPaperWaste : public CGarbage 
{
public:

   CPaperWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Paper Waste"; }
};

class CChemicalWaste : public CGarbage
{
public:

   CChemicalWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Chemical Waste"; }
};

class COtherWaste : public CGarbage
{
public:

   COtherWaste( double inWeight ) : CGarbage( inWeight ) {}

   char *Identifier( void ) { return "Other Waste"; }

};

CGarbage *GarbageGenerator( double inMinimumWeight = 0.01, double inMaximumWeight = 5.0 );
