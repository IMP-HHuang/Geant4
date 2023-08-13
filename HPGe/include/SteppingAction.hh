//    SteppingAction.hh
//	  Definition of the SteppingAction class

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;

class G4LogicalVolume;

// Stepping action class

class SteppingAction : public G4UserSteppingAction
{
  	public:
    	SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction);
    	virtual ~SteppingAction();

    	virtual void UserSteppingAction(const G4Step*);   //模拟过程中，对每个step的操作

  	private:
		const DetectorConstruction* fDetConstruction;
		EventAction* feventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
