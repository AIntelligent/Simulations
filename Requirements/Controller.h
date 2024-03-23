//
// Controller.h
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

#include <Windows.h>
#include "Base.h"

class CController : public CBase
{

public:

   virtual void Run() = 0;

};

class CPeriodicController : public CController
{
private:

   int      m_iMillisecond;

   HANDLE   m_hSignal;

   HANDLE   m_hRunner;

private:

   static LRESULT WINAPI ThreadProc( LPVOID inContext )
   {
      CPeriodicController *l_objCtl = (CPeriodicController *)(inContext);

      while (WaitForSingleObject( l_objCtl->m_hSignal, l_objCtl->m_iMillisecond ) == WAIT_TIMEOUT)
      { l_objCtl->Run(); }

      return ERROR_SUCCESS;
   }

public:

   CPeriodicController( int inMillisecond );
   virtual ~CPeriodicController( void );

   void Shutdown();

   int Millisecond() const { return m_iMillisecond; }

};
