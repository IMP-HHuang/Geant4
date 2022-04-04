//Person_ActionInitialization.cc   用于实现对模拟的统一管理

#include "Person_ActionInitialization.hh"
#include "Person_PrimaryGeneratorAction.hh"
#include "Person_RunAction.hh"
#include "Person_EventAction.hh"
#include "Person_SteppingAction.hh"

Person_ActionInitialization::Person_ActionInitialization(Person_DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
fDetConstruction(detConstruction)  //给类内的成员变量传参
{}

Person_ActionInitialization::~Person_ActionInitialization()
{}

void Person_ActionInitialization::Build() const
{
  	SetUserAction(new Person_PrimaryGeneratorAction());   //调用产生子
	SetUserAction(new Person_RunAction());  //构建并调用Run，准备开始一次模拟
	Person_EventAction* EventAction = new Person_EventAction();  //构建Event，准备开始一个事件的模拟
	SetUserAction(EventAction);  //调用Event
	SetUserAction(new Person_SteppingAction(fDetConstruction, EventAction));  //构建并调用Step，准备开始对一个step操作
}  
