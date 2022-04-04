//Person_PrimaryGeneratorAction.hh  用于构造产生子 

#ifndef Person_PrimaryGeneratorAction_h
#define Person_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"   //全局，为了获取信息

class G4ParticleGun;

// The primary generator action class with particle gun.
// The default kinematic is a 0.662 MeV gamma, randomly distribued 

class Person_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  	public:
    	Person_PrimaryGeneratorAction();  //构造函数，模拟过程只执行一次，各事件的随机信息不能在这定义
    	virtual ~Person_PrimaryGeneratorAction();  

    	// method from the base class
    	virtual void GeneratePrimaries(G4Event*);  //每一个模拟事件执行一次，各事件的随机信息在这定义       
  
    	// method to access particle gun
    	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }  //外部调用---要全局
  	private:
    	G4ParticleGun*  fParticleGun; // pointer to gun class  用于读取 ParticleGun  的信息
};

#endif
