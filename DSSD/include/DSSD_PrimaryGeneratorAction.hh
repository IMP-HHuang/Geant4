//DSSD_PrimaryGeneratorAction.hh  用于构造产生子 

#ifndef DSSD_PrimaryGeneratorAction_h
#define DSSD_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"   //全局，为了获取信息

class G4ParticleGun;

// The primary generator action class with particle gun.
// The default kinematic is a 0.662 MeV gamma, randomly distribued 

class DSSD_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  	public:
    	DSSD_PrimaryGeneratorAction();  //构造函数，模拟过程只执行一次，各事件的随机信息不能在这定义
    	virtual ~DSSD_PrimaryGeneratorAction();  

    	// method from the base class
    	virtual void GeneratePrimaries(G4Event*);  //每一个模拟事件执行一次，各事件的随机信息在这定义       
  
    	// method to access particle gun
    	const G4ParticleGun* GetParticleGunAlpha() const { return fParticleGunAlpha; }  //外部调用---要全局
    	const G4ParticleGun* GetParticleGunBeta() const { return fParticleGunBeta; }  //外部调用---要全局
  	private:
    	G4ParticleGun*  fParticleGunAlpha; // pointer to gun class  用于读取 ParticleGun  的信息
    	G4ParticleGun*  fParticleGunBeta; // pointer to gun class  用于读取 ParticleGun  的信息
		int nEvent;  //用于记事件数
};

#endif
