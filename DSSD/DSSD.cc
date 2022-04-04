
#include "DSSD_DetectorConstruction.hh"
#include "DSSD_PrimaryGeneratorAction.hh"
#include "DSSD_ActionInitialization.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{

	G4UIExecutive* ui = 0;
  	if ( argc == 1 ) 
	{
    	ui = new G4UIExecutive(argc, argv);
  	}

	//run Manager
  	G4RunManager* runManager = new G4RunManager;
  	// Detector construction
	DSSD_DetectorConstruction* DetectorConstruction = new DSSD_DetectorConstruction();
  	runManager->SetUserInitialization(DetectorConstruction);
  	// Physics list
  	G4VModularPhysicsList* physicsList = new FTFP_BERT; //QBBC;  //打包好的一个Physics list
  	physicsList->SetVerboseLevel(1);
  	runManager->SetUserInitialization(physicsList);

  	// User action initialization
	DSSD_ActionInitialization* ActionInit = new DSSD_ActionInitialization(DetectorConstruction);
  	runManager->SetUserInitialization(ActionInit);
	runManager->Initialize();

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

  	// Get the pointer to the User Interface manager
  	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/control/execute init_vis.mac");
	ui->SessionStart();
	delete ui;
  	delete runManager;
	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
