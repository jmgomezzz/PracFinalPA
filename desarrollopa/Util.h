#ifndef UTIL_H 
#define UTIL_H
#include <string> 
#include <algorithm> 
#include <cctype>
#include <vector>
//Para poder usar las funciones trim y 
// split en el ámbito de los materiales,
// se ha creado un namespace que contienen una réplica de estos métodos

namespace Util
{
	std::string trim(const std::string& s);
	std::vector<std::string> split(const std::string& s, char delimiter);
};

#endif