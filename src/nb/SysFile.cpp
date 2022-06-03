//==============================================================================
//
//  SysFile.cpp
//
//  Copyright (C) 2013-2022  Greg Utas
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
#include "SysFile.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <ios>
#include <new>
#include <system_error>
#include "Debug.h"

using std::string;

//------------------------------------------------------------------------------

namespace NodeBase
{
istreamPtr SysFile::CreateIstream(c_string name)
{
   Debug::ft("SysFile.CreateIstream");

   istreamPtr stream(new std::ifstream(name));

   if((stream != nullptr) && (stream->peek() == EOF))
   {
      stream.reset();
      return nullptr;
   }

   return stream;
}

//------------------------------------------------------------------------------

ostreamPtr SysFile::CreateOstream(c_string name, bool trunc)
{
   Debug::ftnt("SysFile.CreateOstream");

   auto mode = (trunc ? std::ios::trunc : std::ios::app);
   ostreamPtr stream(new (std::nothrow) std::ofstream(name, mode));
   if(stream == nullptr) return nullptr;
   *stream << std::boolalpha << std::nouppercase;
   return stream;
}

//------------------------------------------------------------------------------

size_t SysFile::FindExt(const string& name, const string& ext)
{
   auto pos = name.rfind(ext);

   if((pos != string::npos) && (pos + ext.size() == name.size()))
   {
      return pos;
   }

   return string::npos;
}

//------------------------------------------------------------------------------

void SysFile::GetLine(std::istream& stream, std::string& str)
{
   std::getline(stream, str);
   if(!str.empty() && (str.back() == '\r')) str.pop_back();
}

//------------------------------------------------------------------------------

bool SysFile::ListFiles(const string& dir, std::set<string>& names)
{
   Debug::ft("SysFile.ListFiles");

   std::filesystem::path dirpath(dir);
   std::error_code err;
   std::filesystem::directory_iterator fit(dirpath, err);

   if(err.value() != 0) return false;

   for(NO_OP; fit != std::filesystem::end(fit); ++fit)
   {
      auto& filepath = fit->path();

      if(!std::filesystem::is_directory(filepath, err))
      {
         auto name = filepath.filename().string();
         names.insert(name);
      }
   }

   return true;
}
}
