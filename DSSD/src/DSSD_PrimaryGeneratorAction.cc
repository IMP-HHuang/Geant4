	//DSSD_PrimaryGeneratorAction.cc定义产生子

#include "DSSD_PrimaryGeneratorAction.hh"
#include "DSSD_Analysis.hh"

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

DSSD_PrimaryGeneratorAction::DSSD_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  	fParticleGunAlpha(0)
{
  	G4int n_particle = 1;
	fParticleGunAlpha = new G4ParticleGun(n_particle);

  	// default particle kinematic
  	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

	G4String particleNameAlpha = "alpha";
	G4ParticleDefinition* ParticleAlpha = particleTable->FindParticle(particleNameAlpha);
	fParticleGunAlpha->SetParticleDefinition(ParticleAlpha);


	fParticleGunBeta = new G4ParticleGun(n_particle);
/*
	G4int i = 0;
	while(1)
	{
		std::cout << "\033[31m"<< particleTable->GetParticleName(i)<<"\033[0m" << std::endl;
		i++;
		if(i>500) break;
	}
	*/
	// Beta 注意找不到编译不报错执行会崩
	G4ParticleDefinition* ParticleBeta = particleTable->FindParticle("e-");
	if(ParticleBeta!=0)
		fParticleGunBeta->SetParticleDefinition(ParticleBeta);
	else
		std::cout << "\033[31m Cannot get e particle\033[0m" << std::endl;
	nEvent = 0;
}

DSSD_PrimaryGeneratorAction::~DSSD_PrimaryGeneratorAction()
{
	delete fParticleGunAlpha;
	delete fParticleGunBeta;
}

void DSSD_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //粒子出射方向，各方向均匀分布
//    G4double theta_max = 180.*deg; 
	G4double phi_max = 360.*deg;
//    G4double theta_angle = G4UniformRand() * theta_max;
    G4double sin_theta = G4UniformRand();
//    G4cout<<"************ sin_theta "<<sin_theta<<"*************"<<G4endl;
    G4double phi_angle = G4UniformRand() * phi_max;
	G4double cos_theta;
	if(G4UniformRand() > 0.5) cos_theta = sqrt(1 - sin_theta*sin_theta);
	else cos_theta = -sqrt(1 - sin_theta*sin_theta);

	//Alpha particle
	fParticleGunAlpha->SetParticleMomentumDirection(G4ThreeVector(sin_theta*cos(phi_angle), sin_theta*sin(phi_angle), cos_theta));
	G4double EnergyValue = G4UniformRand();
	if(EnergyValue < 0.1215)
		fParticleGunAlpha->SetParticleEnergy(4.069*MeV);
	else if(EnergyValue < 0.4669)
		fParticleGunAlpha->SetParticleEnergy(4.232*MeV);
	else if(EnergyValue < 0.6846)
		fParticleGunAlpha->SetParticleEnergy(4.522*MeV);
	else if(EnergyValue < 0.8363)
		fParticleGunAlpha->SetParticleEnergy(4.611*MeV);
	else if(EnergyValue < 0.9175)
		fParticleGunAlpha->SetParticleEnergy(4.804*MeV);
	else if(EnergyValue < 0.9333)
		fParticleGunAlpha->SetParticleEnergy(5.031*MeV);
	else if(EnergyValue < 0.9547)
		fParticleGunAlpha->SetParticleEnergy(5.103*MeV);
	else if(EnergyValue < 0.9706)
		fParticleGunAlpha->SetParticleEnergy(5.200*MeV);
	else if(EnergyValue < 0.9900)
		fParticleGunAlpha->SetParticleEnergy(5.331*MeV);
	else
		fParticleGunAlpha->SetParticleEnergy(5.565*MeV);

	G4double x = G4UniformRand() * 128.0 * mm - 64.0*mm;
	G4double y = G4UniformRand() * 48.0 * mm - 24.0*mm;
    fParticleGunAlpha->SetParticlePosition(G4ThreeVector(x, y, -147E-3*mm));	

	fParticleGunAlpha->GeneratePrimaryVertex(anEvent);  //在每个事件中产生粒子，没这句不发射

	// electron
	fParticleGunBeta->SetParticlePosition(G4ThreeVector(x, y, -147E-3*mm));
    phi_angle = G4UniformRand() * phi_max;
	if(G4UniformRand() > 0.5) cos_theta = sqrt(1 - sin_theta*sin_theta);
	else cos_theta = -sqrt(1 - sin_theta*sin_theta);
	fParticleGunBeta->SetParticleMomentumDirection(G4ThreeVector(sin_theta*cos(phi_angle), sin_theta*sin(phi_angle), cos_theta));
	fParticleGunBeta->SetParticleEnergy(150*keV);
	if(abs(fParticleGunAlpha->GetParticleEnergy() - 4.232*MeV) <0.005*MeV)
	{
		fParticleGunBeta->GeneratePrimaryVertex(anEvent);
	//	std::cout << nEvent <<"  beta " << fParticleGunAlpha->GetParticleEnergy()  << std::endl;
	}
	else
		fParticleGunBeta->SetParticleEnergy(0*keV);
	nEvent++;
//    G4cout<<"**********ParticleGun   ok**************"<<G4endl;
}
