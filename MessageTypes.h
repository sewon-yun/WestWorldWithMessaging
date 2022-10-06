#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_TimeToPlay,
  Msg_SoccerReady,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";
  case Msg_TimeToPlay:
      return "TimeToPlay";
  case Msg_SoccerReady:
      return "SoccerReady";
  default:
    return "Not recognized!";
  }
}

#endif