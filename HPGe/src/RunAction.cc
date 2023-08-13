// RunAction.cc   RunAction的具体实现

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"   
#include "G4SystemOfUnits.hh" // G4单位定义程序包

RunAction::RunAction()
{}
RunAction::~RunAction()
{}
//The Begin Of Run 
void RunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();   //获取AnalysisManager管理权限
	if(analysisManager)  //判断是否获取成功
	{
	}
	else G4cout<<" cannot receive AnalysisManager"<<G4endl;
}
//The End Of Run
void RunAction::EndOfRunAction(const G4Run* )
{
	auto analysisManager = G4AnalysisManager::Instance();  //获取AnalysisManager管理权限
	if(analysisManager)
	{
	}
	else  G4cout<<" cannot receive AnalysisManager "<<G4endl;
}
