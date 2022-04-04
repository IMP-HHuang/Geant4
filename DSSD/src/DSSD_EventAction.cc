// DSSD_EventAction.cc
// Implementation of the DSSD_EventAction class

#include "G4RunManager.hh"

#include "DSSD_EventAction.hh"
#include "DSSD_Analysis.hh"
#include "DSSD_PrimaryGeneratorAction.hh"
#include <math.h>  
#include <TTree.h>
#include <TFile.h>

DSSD_EventAction::DSSD_EventAction()
: G4UserEventAction()
{
	fout = new TFile("out.root", "RECREATE");
	tree = new TTree("tree", "DSSD");
	tree->Branch("id", &id, "id/I");
	tree->Branch("AlphaEnergy", &AlphaEnergy, "AlphaEnergy/D");
	tree->Branch("ElectronEnergy", &ElectronEnergy, "ElectronEnergy/D");
	tree->Branch("xid", &xid);
	tree->Branch("xE", &xEnergyValue);
	tree->Branch("yid", &yid);
	tree->Branch("yE", &yEnergyValue);

	std::cout << " DSSD_EventAction::DSSD_EventAction()" << std::endl;
} 
DSSD_EventAction::~DSSD_EventAction()
{
	fout->cd();
	fout->Write();
	fout->Close();
	std::cout << " DSSD_EventAction::~DSSD_EventAction() " << std::endl;
}
//每一个事件模拟之前的操作，对提取信息的初始化
void DSSD_EventAction::BeginOfEventAction(const G4Event*)
{   
	xid.clear();
	yid.clear();
	xEnergyValue.clear();
	yEnergyValue.clear();
	AlphaEnergy = 0.0;
	ElectronEnergy = 0.0;
	for(int i=0; i<128; i++)
		xEnergy[i] = 0.0;
	for(int j=0; j<48; j++)
		yEnergy[j] = 0.0;
//	std::cout << " Event begin" << std::endl;
}
//每一个事件模拟之后的操作，对提取信息的操作和存储
void DSSD_EventAction::EndOfEventAction(const G4Event*)
{
//	Energy = Gaus(Energy, 31.0E-3, 0.0); //sigma = 13E-3 MeV offset = 0.0

	auto analysisManager = G4AnalysisManager::Instance();  //获取数据管理器的操作权限， auto --自动匹配数据类型
	if(!analysisManager)  G4cout<<"Cannot receive the AnalysisManager"<<G4endl; //判断当管理权限是否获取成功，如果没获取成功，执行会报错
    const G4Event* currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent();  // G4RunManager 获取模拟管理权限，并获取当前事件
    if(currentEvent)  //判断当前事件是否获取成功，如果没获取成功，执行会报错
    {   
        G4int ID = currentEvent->GetEventID(); //获取事件ID
		id = ID;
    	const DSSD_PrimaryGeneratorAction* generatorAction = static_cast<const DSSD_PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());   //获取产生子，用于读取产生子信息
    	if (generatorAction)	//判断产生子是否获取成功
    	{   
        	G4ThreeVector MomentumDirection = generatorAction->GetParticleGunAlpha()->GetParticleMomentumDirection();  //获取射线的出射方向
			AlphaEnergy = generatorAction->GetParticleGunAlpha()->GetParticleEnergy();
			ElectronEnergy = generatorAction->GetParticleGunBeta()->GetParticleEnergy();
    	}/*
		if (ID % 1000 == 0)
		{
			std::cout << ID;
			std::cout << std::flush;

		}
		*/
//	std::cout << "\033[31m Energy :  " << ID <<"\033[0m"<< std::endl;
		for(int i=0; i<128; i++)
		{
			if(xEnergy[i] > 0)
			{
				xid.push_back(i);
				xEnergyValue.push_back(Gaus(xEnergy[i], 31.0E-3, 0.0));
			}
		}

		for(int j=0; j<48; j++)
		{
			if(yEnergy[j] > 0)
			{
				yEnergyValue.push_back(Gaus(yEnergy[j], 31.0E-3, 0.0));
				yid.push_back(j);
//					std::cout << "\033[31m Energy :  " << EnergyValue <<"\033[0m"<< std::endl;	
			}
		}
		tree->Fill();
    }   
  //  analysisManager->AddNtupleRow();   
}

//Resoluation
//inline G4double DSSD_EventAction::Gaus(G4double x, G4double sigma, G4double offset)
G4double DSSD_EventAction::Gaus(G4double x, G4double sigma, G4double offset)
{
	G4double x1, x2, A, B, C;
	x1 = G4UniformRand();
	x2 = G4UniformRand();
	A = sqrt((-2.0)*log(x1));
	B = 2.0*3.14159*x2;
	C  = A * cos(B);
	return x + C*sigma + offset;
}
