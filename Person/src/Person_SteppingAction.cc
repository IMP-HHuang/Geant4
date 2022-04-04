//  Person_SteppingAction.cc
// brief Implementation of the Person_SteppingAction class

#include "Person_SteppingAction.hh"
#include "Person_EventAction.hh"
#include "Person_DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
Person_SteppingAction::Person_SteppingAction(const Person_DetectorConstruction* detectorConstruction, Person_EventAction* eventAction): G4UserSteppingAction(),
fDetConstruction(detectorConstruction),
feventAction(eventAction)
{}

Person_SteppingAction::~Person_SteppingAction()
{}

void Person_SteppingAction::UserSteppingAction(const G4Step* step)
{
	auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
	auto point = step->GetPreStepPoint()->GetPosition();
	auto x = point.x();
	auto y = point.y();
	auto z = point.z();
	auto edep = step->GetTotalEnergyDeposit();
//	G4UIcommand * command;
	if ( volume == fDetConstruction->Getbody() ) 
	{
		feventAction->Add_body(edep, x, y, z);
	}
	if(sqrt(point.x()*point.x() + (point.y()-660*mm)*(point.y()-660*mm) + point.z()*point.z()) < 90*mm)
	{
		feventAction->Add_head(edep, x, y, z);
	}
}
