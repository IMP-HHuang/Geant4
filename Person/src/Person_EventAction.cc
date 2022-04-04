// Person_EventAction.cc
// Implementation of the Person_EventAction class

#include "G4RunManager.hh"

#include "Person_EventAction.hh"
#include "Person_Analysis.hh"
#include "Person_PrimaryGeneratorAction.hh"

Person_EventAction::Person_EventAction()
: G4UserEventAction()
{} 
Person_EventAction::~Person_EventAction()
{}
//每一个事件模拟之前的操作，对提取信息的初始化
void Person_EventAction::BeginOfEventAction(const G4Event*)
{    
	head_energy = 0;
	head_x = 0;
	head_y = 0;
	head_z = 0;
	body_energy = 0;
	body_x = 0;
	body_y = 0;
	body_z = 0;
}
//每一个事件模拟之后的操作，对提取信息的操作和存储
void Person_EventAction::EndOfEventAction(const G4Event*)
{
	auto analysisManager = G4AnalysisManager::Instance();  //获取数据管理器的操作权限， auto --自动匹配数据类型
	if(!analysisManager)  G4cout<<"Cannot receive the AnalysisManager"<<G4endl; //判断当管理权限是否获取成功，如果没获取成功，执行会报错
    const G4Event* currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent();  // G4RunManager 获取模拟管理权限，并获取当前事件
    if(currentEvent)  //判断当前事件是否获取成功，如果没获取成功，执行会报错
    {   
        G4int ID = currentEvent->GetEventID(); //获取事件ID
        analysisManager->FillNtupleDColumn(0, ID);  //在tree中填ID数据
    }   
    const Person_PrimaryGeneratorAction* generatorAction = static_cast<const Person_PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());   //获取产生子，用于读取产生子信息
    if (generatorAction)	//判断产生子是否获取成功
    {   
        G4ThreeVector MomentumDirection = generatorAction->GetParticleGun()->GetParticleMomentumDirection();  //获取射线的出射方向
		//获取射线的出射方向对应在三个坐标轴上的方向，并填充到tree中
		analysisManager->FillNtupleDColumn(1, MomentumDirection.x());
        analysisManager->FillNtupleDColumn(2, MomentumDirection.y());
        analysisManager->FillNtupleDColumn(3, MomentumDirection.z());
    }
	//填充头部信息
	analysisManager->FillNtupleDColumn(4, head_energy);
	if(head_energy>0)  //有能量沉积，获取沉积中心
	{
		head_x = head_x/head_energy;
		head_y = head_y/head_energy;
		head_z = head_z/head_energy;	
	}
	else  //无能量沉积，获取沉积中心坐标用-1000代替
	{
		head_x = -1000;
		head_y = -1000;
		head_z = -1000;
	}
	analysisManager->FillNtupleDColumn(5, head_x);
	analysisManager->FillNtupleDColumn(6, head_y);
	analysisManager->FillNtupleDColumn(7, head_z);
	analysisManager->FillNtupleDColumn(8, body_energy);
	//填充身体信息，方法与头部相同
	if(body_energy>0)
	{
		body_x = body_x/body_energy;
		body_y = body_y/body_energy;
		body_z = body_z/body_energy;
	}
	else
	{
		body_x = -1000;
		body_y = -1000;
		body_z = -1000;
	}
	analysisManager->FillNtupleDColumn(9, body_x);
	analysisManager->FillNtupleDColumn(10, body_y);
	analysisManager->FillNtupleDColumn(11, body_z);  
    analysisManager->AddNtupleRow();   
}
