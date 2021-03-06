// http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.3/exception-source.html

// Exception Handling support header for -*- C++ -*-

// Copyright (C) 1995, 1996, 1997, 1998, 2000, 2001, 2002
// Free Software Foundation
//
// This file is part of GNU CC.
//
// GNU CC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// GNU CC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU CC; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#ifndef __EXCEPTION__
#define __EXCEPTION__

extern "C++" {

namespace std 
{
  class exception 
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();
    virtual const char* what() const throw();
  };

  class bad_exception : public exception 
  {
  public:
    bad_exception() throw() { }
    // This declaration is not useless:
    // http://gcc.gnu.org/onlinedocs/gcc-3.0.2/gcc_6.html#SEC118
    virtual ~bad_exception() throw();
  };

  typedef void (*terminate_handler) ();
  typedef void (*unexpected_handler) ();

  terminate_handler set_terminate(terminate_handler) throw();
  void terminate() __attribute__ ((__noreturn__));

  unexpected_handler set_unexpected(unexpected_handler) throw();
  void unexpected() __attribute__ ((__noreturn__));

  bool uncaught_exception() throw();
} // namespace std

namespace __gnu_cxx
{
  void __verbose_terminate_handler ();
} // namespace __gnu_cxx
  
} // extern "C++"

#endif
