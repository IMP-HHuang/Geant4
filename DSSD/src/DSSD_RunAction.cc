// DSSD_RunAction.cc   RunAction的具体实现

#include "DSSD_RunAction.hh"
#include "DSSD_PrimaryGeneratorAction.hh"
#include "DSSD_DetectorConstruction.hh"
#include "DSSD_Analysis.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
//#include "G4UnitsTable.hh"   
#include "G4SystemOfUnits.hh" // G4单位定义程序包

DSSD_RunAction::DSSD_RunAction()
{}
DSSD_RunAction::~DSSD_RunAction()
{}
//The Begin Of Run 
void DSSD_RunAction::BeginOfRunAction(const G4Run*)
{
	auto analysisManager = G4AnalysisManager::Instance();   //获取AnalysisManager管理权限
	if(analysisManager)  //判断是否获取成功
	{
	}
	else G4cout<<" cannot receive AnalysisManager"<<G4endl;
}
//The End Of Run
void DSSD_RunAction::EndOfRunAction(const G4Run* )
{
	auto analysisManager = G4AnalysisManager::Instance();  //获取AnalysisManager管理权限
	if(analysisManager)
	{
	}
	else  G4cout<<" cannot receive AnalysisManager "<<G4endl;
}
