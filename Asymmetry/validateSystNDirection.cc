/*
 * This code validates whether passed systematics and directions (mostly by the command line) are within
 * the valid range or not
 *
 */

#include <iostream>
#include <sstream>
using namespace std;

bool validateSystNDirection(string systematics, string direction){
  cout << "Validating whether the syst and direction are as expected." << endl;
  cout << "You passed systematics : " << systematics << " and direction : " << direction << endl;

  const int NSystWJets(18);
  short wjSyst[NSystWJets]   = {0, 1, 1, 5, 5, 6, 6, 7, 7, 4, 4, 8, 9, 10, 11, 11};
  short wjDir[NSystWJets]    = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 1,  1,  1, -1};

  ///////syst///////
  stringstream strStreamSyst;
  strStreamSyst << systematics;
  int intSyst = -10;
  strStreamSyst >> intSyst;

  ///////dir///////
  stringstream strStreamDir;
  strStreamDir << direction;
  int intDirection = -10;
  strStreamDir >> intDirection;

  bool validSyst = false;
  bool validDirection = false;

  //chech if within expected list of values
  for(int kk=0; kk<NSystWJets; kk++){
    if(intSyst==wjSyst[kk] && intDirection==wjDir[kk]){
      validSyst = true;
      validDirection = true;
    }
    ////cout << validSyst << "  " << validDirection << endl;
  }

  bool validSystNDir = false;
  if(validSyst && validDirection){
    validSystNDir = true;
  }

  if(validSystNDir) cout << "Passed systematics and direction are within accepted values, proceeding..." << endl;

  return validSystNDir;
}
