//    Person_SteppingAction.hh
//	  Definition of the Person_SteppingAction class

#ifndef Person_SteppingAction_h
#define Person_SteppingAction_h 1

#include "Person_DetectorConstruction.hh"
#include "Person_EventAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"

class Person_EventAction;

class G4LogicalVolume;

// Stepping action class

class Person_SteppingAction : public G4UserSteppingAction
{
  	public:
    	Person_SteppingAction(const Person_DetectorConstruction* detectorConstruction, Person_EventAction* eventAction);
    	virtual ~Person_SteppingAction();

    	virtual void UserSteppingAction(const G4Step*);   //模拟过程中，对每个step的操作

  	private:
		const Person_DetectorConstruction* fDetConstruction;
		Person_EventAction* feventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
