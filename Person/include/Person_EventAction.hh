///  Person_EventAction.hh  用于管理每一个模拟事件
//   brief Definition of the Person_EventAction class

#ifndef Person_EventAction_h
#define Person_EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"  //全局

class Person_RunAction;

class Person_EventAction : public G4UserEventAction
{
	public:
    	Person_EventAction();
    	virtual ~Person_EventAction();

    	virtual void BeginOfEventAction(const G4Event* );
    	virtual void EndOfEventAction(const G4Event* );
		void Add_head(G4double de, G4double x, G4double y, G4double z);   //操作头部的能量和位置信息
		void Add_body(G4double de, G4double x, G4double y, G4double z);   //操作身体的能量和位置信息
  	private:
		G4double head_energy, head_x, head_y, head_z;
		G4double body_energy, body_x, body_y, body_z;
};
  //重心：能量对位置的加权平均值
inline void Person_EventAction::Add_body(G4double de, G4double x, G4double y, G4double z) 
{
	body_energy += de;
	body_x += x*de;
	body_y += y*de;
	body_z += z*de;
}
inline void Person_EventAction::Add_head(G4double de, G4double x, G4double y, G4double z)
{
	head_energy += de;
	head_x += x*de;
	head_y += y*de;
	head_z += z*de;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
