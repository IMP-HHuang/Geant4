// Person_RunAction.cc   RunAction的具体实现

#include "Person_RunAction.hh"
#include "Person_PrimaryGeneratorAction.hh"
#include "Person_DetectorConstruction.hh"
#include "Person_Analysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"   
#include "G4SystemOfUnits.hh" // G4单位定义程序包

Person_RunAction::Person_RunAction()
{}
Person_RunAction::~Person_RunAction()
{}
//The Begin Of Run 
void Person_RunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();   //获取AnalysisManager管理权限
	if(analysisManager)  //判断是否获取成功
	{
		G4String fileName = "Person";
		analysisManager->OpenFile(fileName); //建立root文件
		analysisManager->CreateNtuple("tree", "0.662 MeV Gamma Person");  //建立tree
		analysisManager->CreateNtupleDColumn("event_ID");  //建立branch，注：double类型的
		analysisManager->CreateNtupleDColumn("P_x");
		analysisManager->CreateNtupleDColumn("P_y");
		analysisManager->CreateNtupleDColumn("P_z");
		analysisManager->CreateNtupleDColumn("head_energy");
		analysisManager->CreateNtupleDColumn("head_x");
		analysisManager->CreateNtupleDColumn("head_y");
		analysisManager->CreateNtupleDColumn("head_z");
		analysisManager->CreateNtupleDColumn("body_energy");
		analysisManager->CreateNtupleDColumn("body_x");
		analysisManager->CreateNtupleDColumn("body_y");
		analysisManager->CreateNtupleDColumn("body_z");
		analysisManager->FinishNtuple();  //完成tree的建立
	}
	else G4cout<<" cannot receive AnalysisManager"<<G4endl;
}
//The End Of Run
void Person_RunAction::EndOfRunAction(const G4Run* )
{
	auto analysisManager = G4AnalysisManager::Instance();  //获取AnalysisManager管理权限
	if(analysisManager)
	{
		analysisManager->Write();
		analysisManager->CloseFile();
	}
	else  G4cout<<" cannot receive AnalysisManager"<<G4endl;
}
