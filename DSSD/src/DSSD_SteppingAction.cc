//  DSSD_SteppingAction.cc
// brief Implementation of the DSSD_SteppingAction class

#include "DSSD_SteppingAction.hh"
#include "DSSD_EventAction.hh"
#include "DSSD_DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
DSSD_SteppingAction::DSSD_SteppingAction(const DSSD_DetectorConstruction* detectorConstruction, DSSD_EventAction* eventAction): G4UserSteppingAction(),
fDetConstruction(detectorConstruction),
feventAction(eventAction)
{
}

DSSD_SteppingAction::~DSSD_SteppingAction()
{}

void DSSD_SteppingAction::UserSteppingAction(const G4Step* step)
{
	auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
//	auto point = step->GetPreStepPoint()->GetPosition();
//	auto x = point.x();
//	auto y = point.y();
//	auto z = point.z();
	auto edep = step->GetTotalEnergyDeposit();
//	G4UIcommand * command;
//	G4cout << " Length " << step->GetStepLength() << G4endl;
//	G4cout << " Energy edep " << edep  << " x y z   "<<x <<"  "  << y << "  " <<z <<G4endl;
	// 获取特定探测器的能量沉积：靠位置定或靠探测器材料定、探测器名称
//	if (abs(point.x() - 0.0*mm) < 64.0*mm && abs(point.y()- 0.0*mm) < 24.0*mm && abs(point.z()-0.0*mm) < 150E-3*mm)//150.0E-3*mm)
//	if (step->GetTrack()->GetMaterial()->GetName() == "Si")
	if (step->GetTrack()->GetVolume()->GetName() == "DSSD")
	{
//		feventAction->Add_DSSD(edep);
		int xid = step->GetTrack()->GetVolume()->GetCopyNo()/100;
	   	int yid = step->GetTrack()->GetVolume()->GetCopyNo() - xid*100;
		feventAction->xEnergy[xid] += edep;
		feventAction->yEnergy[yid] += edep;
//		std::cout << step->GetTrack()->GetVolume()->GetCopyNo() <<"  xid : yid " << xid <<"  " << yid << std::endl;
	}
//	std::cout << "Volume CopyNo: " << step->GetTrack()->GetVolume()->GetCopyNo()<< std::endl;
//	std::cout << "Material : " << step->GetTrack()->GetMaterial()->GetName() << std::endl;
//	std::cout << "track id : " << step->GetTrack()->GetTrackID() << std::endl;
//	std::cout << "Volume : " << step->GetTrack()->GetVolume()->GetName()<< std::endl;
//	std::cout << "Step Number : " << step->GetTrack()->GetCurrentStepNumber()<< std::endl;
//	std::cout << " Energy of edep " << edep  << " x y z   "<<x <<"  "  << y << "  " <<z <<std::endl;

}
