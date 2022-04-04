//Person_RunAction.hh  Run即每次模拟的的操作

#ifndef Person_RunAction_h
#define Person_RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"   //全局

class G4Run;

/// Run action class
class Person_RunAction : public G4UserRunAction
{
  	public:
    	Person_RunAction();
    	virtual ~Person_RunAction();

    	virtual void   BeginOfRunAction(const G4Run*);
    	virtual void   EndOfRunAction(const G4Run*);
  	private:
//    G4Accumulable<G4double> fEdep;
//    G4Accumulable<G4double> fEdep2;
};

#endif

