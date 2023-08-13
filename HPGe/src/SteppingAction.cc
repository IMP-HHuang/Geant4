//  SteppingAction.cc
// brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
SteppingAction::SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction): G4UserSteppingAction(),
fDetConstruction(detectorConstruction),
feventAction(eventAction)
{
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
	auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
//	auto point = step->GetPreStepPoint()->GetPosition();
//	auto x = point.x();
//	auto y = point.y();
//	auto z = point.z();
	auto edep = step->GetTotalEnergyDeposit();
	// 获取特定探测器的能量沉积：靠位置定或靠探测器材料定、探测器名称
	if(step->GetTrack()->GetVolume()->GetName() == "Detector")
    //&&   step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma")
	    feventAction->e[0] += edep;

}
