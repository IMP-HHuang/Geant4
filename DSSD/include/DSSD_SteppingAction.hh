//    DSSD_SteppingAction.hh
//	  Definition of the DSSD_SteppingAction class

#ifndef DSSD_SteppingAction_h
#define DSSD_SteppingAction_h 1

#include "DSSD_DetectorConstruction.hh"
#include "DSSD_EventAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DSSD_EventAction;

class G4LogicalVolume;

// Stepping action class

class DSSD_SteppingAction : public G4UserSteppingAction
{
  	public:
    	DSSD_SteppingAction(const DSSD_DetectorConstruction* detectorConstruction, DSSD_EventAction* eventAction);
    	virtual ~DSSD_SteppingAction();

    	virtual void UserSteppingAction(const G4Step*);   //模拟过程中，对每个step的操作

  	private:
		const DSSD_DetectorConstruction* fDetConstruction;
		DSSD_EventAction* feventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
