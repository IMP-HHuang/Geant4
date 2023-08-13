///  EventAction.hh  用于管理每一个模拟事件
//   brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"  //全局
#include <TTree.h>
#include <TFile.h>
#include <vector>

class RunAction;

class EventAction : public G4UserEventAction
{
	public:
    	EventAction();
    	virtual ~EventAction();

    	virtual void BeginOfEventAction(const G4Event* );
    	virtual void EndOfEventAction(const G4Event* );
		G4double Gaus(G4double x, G4double sigma, G4double offset);
		Double_t Energy;
        Int_t EventId;
		Double_t e[28];

		std::vector<Double_t> Voe;
		std::vector<Int_t> Void;

  	private:
		TFile *fout;
		TTree *tree;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

    
