#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Miner_Bob,

  ent_Elsa,

  ent_Evan,

  ent_Emily,

  ent_Kim
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Miner_Bob:

    return "Miner Bob";

  case ent_Elsa:
    
    return "Elsa"; 

  case ent_Evan:
    return "Evan";

  case ent_Emily:
      return "Emily";

  case ent_Kim:
      return "Kim";

  default:

    return "UNKNOWN!";
  }
}

#endif