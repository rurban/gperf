/* This may look like C code, but it is really -*- C++ -*- */

/* Keyword list.

   Copyright (C) 2002 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>.

   This file is part of GNU GPERF.

   GNU GPERF is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GNU GPERF is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef keyword_list_h
#define keyword_list_h 1

#include "keyword.h"

/* List node of a linear list of Keyword.  */
class Keyword_List
{
public:
  /* Constructor.  */
                        Keyword_List (Keyword *car);

  /* Access to first element of list.  */
  Keyword *             first () { return _car; }
  /* Access to next element of list.  */
  Keyword_List *&       rest () { return _cdr; }

protected:
  Keyword_List *        _cdr;
  Keyword * const       _car;
};

/* List node of a linear list of KeywordExt.  */
class KeywordExt_List : public Keyword_List
{
public:
  /* Unused constructor.  */
                        KeywordExt_List (KeywordExt *car);

  /* Access to first element of list.  */
  KeywordExt *          first () { return static_cast<KeywordExt*>(_car); }
  /* Access to next element of list.  */
  KeywordExt_List *&    rest () { return static_cast<KeywordExt_List*>(_cdr); }
};

#endif