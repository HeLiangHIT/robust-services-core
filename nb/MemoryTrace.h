//==============================================================================
//
//  MemoryTrace.h
//
//  Copyright (C) 2017  Greg Utas
//
//  This file is part of the Robust Services Core (RSC).
//
//  RSC is free software: you can redistribute it and/or modify it under the
//  terms of the GNU General Public License as published by the Free Software
//  Foundation, either version 3 of the License, or (at your option) any later
//  version.
//
//  RSC is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
//  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
//  details.
//
//  You should have received a copy of the GNU General Public License along
//  with RSC.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef MEMORYTRACE_H_INCLUDED
#define MEMORYTRACE_H_INCLUDED

#include "TimedRecord.h"
#include <cstddef>
#include "SysTypes.h"

//------------------------------------------------------------------------------

namespace NodeBase
{
//  Records memory allocations and deallocations.
//
class MemoryTrace : public TimedRecord
{
public:
   //  Types of memory trace records.
   //
   static const Id Alloc = 1;  // allocation
   static const Id Free  = 2;  // deallocation

   //  Sets addr_, type_, and size_.  RID specifies allocation or deallocation.
   //
   MemoryTrace(Id rid, const void* addr, MemoryType type, size_t size);

   //  Overridden to display the trace record.
   //
   bool Display(std::ostream& stream, bool diff) override;
private:
   //  Overridden to return a string for displaying this type of record.
   //
   const char* EventString() const override;

   //  Returns a string for displaying TYPE.
   //
   static const char* TypeString(MemoryType type);

   //  The address where memory was allocated or freed.
   //
   const void* const addr_;

   //  The type of memory that was allocated or freed.
   //
   const MemoryType type_;

   //  The amount of memory that was allocated or freed.
   //
   const size_t size_;
};
}
#endif
