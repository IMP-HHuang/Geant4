	//PrimaryGeneratorAction.cc定义产生子

#include "PrimaryGeneratorAction.hh"
#include "Analysis.hh"

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
#include "G4IonTable.hh"

#include "vector"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  	fParticleGunAlpha(0)
{
  	G4int n_particle = 1;
	fParticleGunAlpha = new G4ParticleGun(n_particle);

  	// default particle kinematic
  	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* Particle;
    for(G4int i = 0; i < particleTable->entries(); i++)
    {
        Particle = particleTable->GetParticle(i);
        std::cout << "\033[31mG4ParticleTable  " << Particle->GetParticleName() << "\033[0m" << std::endl;
    }
    
    Particle = particleTable->FindParticle("alpha");
    fParticleGunAlpha = new G4ParticleGun(n_particle);
    if(Particle != 0)
        fParticleGunAlpha->SetParticleDefinition(Particle);
    else
    {
        std::cout << "\033[31m Cannot get alpha particle\033[0m" << std::endl;
    }
	fParticleGunGamma = new G4ParticleGun(n_particle);
	Particle = particleTable->FindParticle("gamma");
	if(Particle != 0)
		fParticleGunGamma->SetParticleDefinition(Particle);
	else
		std::cout << "\033[31m Cannot get gamma particle\033[0m" << std::endl;

	// 注意没有下面这句编译不报错执行会崩
	fParticleGunBeta = new G4ParticleGun(n_particle);
	// Beta 注意找不到编译不报错执行会崩
	Particle = particleTable->FindParticle("e-");

	if(Particle != 0)
		fParticleGunBeta->SetParticleDefinition(Particle);
	else
		std::cout << "\033[31m Cannot get e particle\033[0m" << std::endl;

    G4IonTable* ionTable = particleTable->GetIonTable();
    for(G4int i = 0; i< ionTable->Entries(); i++)
    {
        G4ParticleDefinition* ParticleDefOut = ionTable->GetParticle(i);
        std::cout << "\033[31mG4IonTable  " << ParticleDefOut->GetParticleName() << "\033[0m" << std::endl;
    }
    particleSource = new G4GeneralParticleSource();
    //Using GPS
   // G4ParticleDefinition* particleDef = ionTable->GetIon(11, 22, 0);  //11-Na-22
   /*
    G4ParticleDefinition* particleDef = ionTable->GetIon(27, 60, 0);    // 27-Co-60
    if(particleDef != 0)
        particleSource->GetCurrentSource()->SetParticleDefinition(particleDef);  
	else
		std::cout << "\033[31m Cannot get GPS source \033[0m" << std::endl;
    */

	nEvent = 0;
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGunAlpha;
	delete fParticleGunBeta;
	delete fParticleGunGamma;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
		
    //Using ParticleGun
    //粒子出射方向，各方向均匀分布
	G4double phi_max = 360.*deg;
    G4double sin_theta = G4UniformRand();
    G4double phi_angle = G4UniformRand() * phi_max;
	G4double cos_theta;
	if(G4UniformRand() > 0.5) cos_theta = sqrt(1 - sin_theta*sin_theta);
	else cos_theta = -sqrt(1 - sin_theta*sin_theta);
	G4double th = acos(1.0-2*G4UniformRand());
	G4double ph = G4UniformRand()*2.0*CLHEP::pi;

    fParticleGunGamma->SetParticleEnergy(0.511*MeV);
    fParticleGunGamma->SetParticlePosition(G4ThreeVector(0, 0, 70*mm));	
	fParticleGunGamma->SetParticleMomentumDirection(G4ThreeVector(sin(th)*cos(ph), sin(th)*sin(ph), cos(th)));

//	fParticleGunGamma->GeneratePrimaryVertex(anEvent);  //在每个事件中产生粒子，没这句不发射
    particleSource->GeneratePrimaryVertex(anEvent);

	nEvent++;
//    G4cout<<"**********ParticleGun   ok**************"<<G4endl;
}
