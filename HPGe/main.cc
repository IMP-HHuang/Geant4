
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
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
#include "G4PhysListFactory.hh"

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
	DetectorConstruction* DetectorConstructionTmp = new DetectorConstruction();
  	runManager->SetUserInitialization(DetectorConstructionTmp);
  	// Physics list
  //	G4VModularPhysicsList* physicsList = new FTFP_BERT; //QBBC;  //打包好的一个Physics list
  //	physicsList->SetVerboseLevel(1);
  //	runManager->SetUserInitialization(physicsList);

    G4PhysListFactory factory;
    G4VModularPhysicsList* physlist = factory.GetReferencePhysList("QGSP_BIC_HP");  //include source 
    runManager->SetUserInitialization(physlist);

  	// User action initialization
	ActionInitialization* ActionInit = new ActionInitialization(DetectorConstructionTmp);
  	runManager->SetUserInitialization(ActionInit);
	runManager->Initialize();

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

  	// Get the pointer to the User Interface manager
  	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/control/execute init_vis.mac");
	UImanager->ApplyCommand("/control/execute Source.mac");
    ui->SessionStart();  // 开启会话模式
	delete ui;
  	delete runManager;
	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
