//
// Base.h
//
// Author:
//       Hakan Emre Kartal <hek@nula.com.tr>
//
// Copyright (c) 2021 Hakan Emre Kartal
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

#include <vector>

#define __abs(x)((0>(x))?(-(x)):(x))

class CBase
{

public:

   CBase( void );
   virtual ~CBase( void );

   const char *Identifier() { return (const char *)0; }

};

class CSynchronizer : public CBase 
{
public:

   virtual void Acquire() = 0;
   virtual void Release() = 0;

};

template<typename TSubject> \
class CVector : public CBase 
{
private:

   CSynchronizer *m_objLock;
   std::vector<TSubject> *m_objV;

protected:

   virtual void DoFreeSubject( TSubject &ioSubject ) {}

public:

   CVector( CSynchronizer *inLock = NULL ) : \
      CBase(), \
      m_objLock(inLock), \
      m_objV(new std::vector<TSubject>())
   {}

   virtual ~CVector( void )
   { Empty(); }

   TSubject Get( int inIndex )
   { return m_objV->at( inIndex ); }

   int Count( void )
   { return m_objV->size(); }

   virtual void Empty( void )
   {
      TSubject _Subject;

      Lock();
      __try
      {
         while (Count() > 0)
         {
            _Subject = m_objV->back();
            m_objV->pop_back();

            DoFreeSubject( _Subject );
         }
      }
      __finally
      { Unlock(); }
   }

   void Add( TSubject inSubject )
   { 
      Lock();
      __try
      { m_objV->push_back( inSubject ); }
      __finally
      { Unlock(); }
   }

   void Lock()
   {
      if (m_objLock != NULL)
      { m_objLock->Acquire(); }
   }

   void Unlock()
   {
      if (m_objLock != NULL)
      { m_objLock->Release(); }
   }
};

