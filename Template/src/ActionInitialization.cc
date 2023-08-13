//ActionInitialization.cc   用于实现对模拟的统一管理

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
fDetConstruction(detConstruction)  //给类内的成员变量传参
{
	std::cout << " ActionInitialization::ActionInitialization(DetectorConstruction* detConstruction) " << std::endl;
}

ActionInitialization::~ActionInitialization()
{
	std::cout << " ActionInitialization::~ActionInitialization() " << std::endl;
//	delete EventAction;
}

void ActionInitialization::Build() const
{
  	SetUserAction(new PrimaryGeneratorAction());   //调用产生子
	SetUserAction(new RunAction());  //构建并调用Run，准备开始一次模拟
	EventAction *EventActionTmp = new EventAction();  //构建Event，准备开始一个事件的模拟
	SetUserAction(EventActionTmp);  //调用Event
	SetUserAction(new SteppingAction(fDetConstruction, EventActionTmp));  //构建并调用Step，准备开始对一个step操作
}  
