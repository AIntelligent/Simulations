//
// Controller.cpp
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
#include "Controller.h"

CPeriodicController::CPeriodicController( int inMillisecond ) : \
   m_iMillisecond(inMillisecond),
   m_hSignal(::CreateEvent( NULL, TRUE, FALSE, NULL )),
   m_hRunner(::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)CPeriodicController::ThreadProc, (LPVOID)(this), 0, NULL ))
{}

CPeriodicController::~CPeriodicController( void )
{ Shutdown(); }

void CPeriodicController::Shutdown()
{
   SetEvent( m_hSignal );
   WaitForSingleObject( m_hRunner, INFINITE );

   CloseHandle( m_hSignal );
   CloseHandle( m_hRunner );
}

