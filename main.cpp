#include <fstream>
#include <time.h>
#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "MinersSon.h"
#include "MinersDaughter.h"
#include "MinersBrother.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create his son
  MinersSon* Evan = new MinersSon(ent_Evan);

  //create his daughter
  MinersDaughter* Emily = new MinersDaughter(ent_Emily);

  //create his brother
  MinersBrother* Kim = new MinersBrother(ent_Kim);
  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Evan);
  EntityMgr->RegisterEntity(Emily);
  EntityMgr->RegisterEntity(Kim);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i < 30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
    Evan->Update();
    Emily->Update();
    Kim->Update();
    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  // delete Evan;
  delete Emily;
  delete Kim;
  //wait for a keypress before exiting
  printf("\n2018182022 ??????\n");
  PressAnyKeyToContinue();


  return 0;
}






