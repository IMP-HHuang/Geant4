//DSSD_ActionInitialization.cc   用于实现对模拟的统一管理

#include "DSSD_ActionInitialization.hh"
#include "DSSD_PrimaryGeneratorAction.hh"
#include "DSSD_RunAction.hh"
#include "DSSD_EventAction.hh"
#include "DSSD_SteppingAction.hh"

DSSD_ActionInitialization::DSSD_ActionInitialization(DSSD_DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
fDetConstruction(detConstruction)  //给类内的成员变量传参
{
	std::cout << " DSSD_ActionInitialization::DSSD_ActionInitialization(DSSD_DetectorConstruction* detConstruction) " << std::endl;
}

DSSD_ActionInitialization::~DSSD_ActionInitialization()
{
	std::cout << " DSSD_ActionInitialization::~DSSD_ActionInitialization() " << std::endl;
//	delete EventAction;
}

void DSSD_ActionInitialization::Build() const
{
  	SetUserAction(new DSSD_PrimaryGeneratorAction());   //调用产生子
	SetUserAction(new DSSD_RunAction());  //构建并调用Run，准备开始一次模拟
	DSSD_EventAction *EventAction = new DSSD_EventAction();  //构建Event，准备开始一个事件的模拟
	SetUserAction(EventAction);  //调用Event
	SetUserAction(new DSSD_SteppingAction(fDetConstruction, EventAction));  //构建并调用Step，准备开始对一个step操作
}  
