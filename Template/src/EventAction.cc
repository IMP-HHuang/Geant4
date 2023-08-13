// EventAction.cc
// Implementation of the EventAction class

#include "G4RunManager.hh"

#include "EventAction.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include <math.h>  
#include <TTree.h>
#include <TFile.h>

EventAction::EventAction()
: G4UserEventAction()
{
	fout = new TFile("out.root", "RECREATE");
	tree = new TTree("tree", "tree");
	tree->Branch("Energy", &Energy, "Energy/D");
	tree->Branch("Eid", &EventId, "Eid/I");
	tree->Branch("e", &Voe);

} 
EventAction::~EventAction()
{
	Voe.clear();
	Energy = 0.0;
    tree->Fill();
	fout->cd();
	fout->Write();
	fout->Close();
}
//每一个事件模拟之前的操作，对提取信息的初始化
void EventAction::BeginOfEventAction(const G4Event*)
{   
	Voe.clear();

	Energy = 0.0;
	for(int i=0; i<28; i++)
		e[i] = 0.0;
}
//每一个事件模拟之后的操作，对提取信息的操作和存储
void EventAction::EndOfEventAction(const G4Event*)
{

	auto analysisManager = G4AnalysisManager::Instance();  //获取数据管理器的操作权限， auto --自动匹配数据类型
	if(!analysisManager)  G4cout<<"Cannot receive the AnalysisManager"<<G4endl; //判断当管理权限是否获取成功，如果没获取成功，执行会报错
	
    const G4Event* currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent();  // G4RunManager 获取模拟管理权限，并获取当前事件
    if(currentEvent)  //判断当前事件是否获取成功，如果没获取成功，执行会报错
    {   
        EventId = currentEvent->GetEventID() + 1; //获取事件ID
    	const PrimaryGeneratorAction* generatorAction = static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());   //获取产生子，用于读取产生子信息
    	if (generatorAction)	//判断产生子是否获取成功
    	{   
        	G4ThreeVector MomentumDirection = generatorAction->GetParticleGunAlpha()->GetParticleMomentumDirection();  //获取射线的出射方向
			Energy = generatorAction->GetParticleGunGamma()->GetParticleEnergy();
    	}

		for(int i=0; i<28; i++)
			if(e[i] > 0.0)
			{
				Voe.push_back(Gaus(e[i]*1.0E3, 1.5, 0.0));
			}
        if(Voe.size() > 0)
		    tree->Fill();
    }
 	
  //  analysisManager->AddNtupleRow();   
}

//Resoluation
//inline G4double EventAction::Gaus(G4double x, G4double sigma, G4double offset)
G4double EventAction::Gaus(G4double x, G4double sigma, G4double offset)
{
	G4double x1, x2, A, B, C;
	x1 = G4UniformRand();
	x2 = G4UniformRand();
	A = sqrt((-2.0)*log(x1));
	B = 2.0*3.14159*x2;
	C  = A * cos(B);
	return x + C*sigma + offset;
}
