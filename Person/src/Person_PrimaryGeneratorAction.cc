	//Person_PrimaryGeneratorAction.cc定义产生子

#include "Person_PrimaryGeneratorAction.hh"
#include "Person_Analysis.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UIcommand.hh"

Person_PrimaryGeneratorAction::Person_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  	fParticleGun(0)
{
  	G4int n_particle = 1;
  	fParticleGun  = new G4ParticleGun(n_particle);

  	// default particle kinematic
  	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  	G4String particleName = "gamma";
  	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  	fParticleGun->SetParticleDefinition(particle);  //设置粒子种类
}

Person_PrimaryGeneratorAction::~Person_PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void Person_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //粒子出射方向，各方向均匀分布
//    G4double theta_max = 180.*deg; 
	G4double phi_max = 360.*deg;
//    G4double theta_angle = G4UniformRand() * theta_max;
    G4double sin_theta = G4UniformRand();
//    G4cout<<"************ sin_theta "<<sin_theta<<"*************"<<G4endl;
    G4double phi_angle = G4UniformRand() * phi_max;
//    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(theta_angle)*cos(phi_angle), sin(theta_angle)*sin(phi_angle), cos(theta_angle)));
	G4double cos_theta;
	if(G4UniformRand() > 0.5) cos_theta = sqrt(1 - sin_theta*sin_theta);
	else cos_theta = -sqrt(1 - sin_theta*sin_theta);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin_theta*cos(phi_angle), sin_theta*sin(phi_angle), cos_theta));
    fParticleGun->SetParticleEnergy(0.662*MeV);  //粒子能量  0.662
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 245*mm, -50*cm));
    G4cout<<"**********ParticleGun   ok**************"<<G4endl;
	fParticleGun->GeneratePrimaryVertex(anEvent);

/*
	G4ThreeVector mo = fParticleGun->GetParticleMomentumDirection();
	G4double mox = mo.x();
	G4cout<<"*********The MomentumDirectionx  of particle is  "<<mox<<" *****"<<G4endl;
	G4UIcommand * command;
	G4String cv;
	cv = command->ConvertToString(mo);
	G4cout<<"*********The MomentumDirection  of particle is  "<<cv<<" *****"<<G4endl;
	G4cout<<"*********the particle is "<<fParticleGun->GetParticleDefinition()->GetParticleName()<<" ***"<<G4endl;
	G4double particleEnergy = fParticleGun->GetParticleEnergy();
	G4cout<<"*********The energy of particle is "<<particleEnergy<<"**************"<<G4endl;	
//	G4cout<<"*********The ID of current event is "<<eventID<<"**************"<<G4endl;
	G4TrajectoryContainer* trajectoryContainer = anEvent->GetTrajectoryContainer();
	G4int n_trajectories = 0;
	if (trajectoryContainer)  n_trajectories = trajectoryContainer->entries();  //不能操作空指针
	G4cout << "*****" << n_trajectories<< " trajectories stored in this event.****" << G4endl;
	G4cout<<"*********ParticleGun generate a event**************"<<G4endl;
*/
}
