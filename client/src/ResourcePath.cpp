//
// ResourcePath.cpp for  in /home/mo_r//r-type/client
// 
// Made by renxiao mo
// Login   <mo_r@epitech.net>
// 
// Started on  Sat Oct 26 18:13:51 2013 renxiao mo
// Last update Sat Oct 26 19:35:52 2013 renxiao mo
//

#include "ResourcePath.hpp"

#ifdef _WIN32
std::string resourcePath()
{
	return std::string("..\\..\\Resources\\");
}
#else
std::string resourcePath()
{
  return std::string("Resources/");
}
#endif