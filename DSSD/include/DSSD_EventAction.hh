///  DSSD_EventAction.hh  用于管理每一个模拟事件
//   brief Definition of the DSSD_EventAction class

#ifndef DSSD_EventAction_h
#define DSSD_EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"  //全局
#include <TTree.h>
#include <TFile.h>
#include <vector>

class DSSD_RunAction;

class DSSD_EventAction : public G4UserEventAction
{
	public:
    	DSSD_EventAction();
    	virtual ~DSSD_EventAction();

    	virtual void BeginOfEventAction(const G4Event* );
    	virtual void EndOfEventAction(const G4Event* );
//		void Add_DSSD(G4double de);   //DSSD的能量
		G4double Gaus(G4double x, G4double sigma, G4double offset);
		G4double xEnergy[128];
		G4double yEnergy[48];
		Int_t id;
		Double_t AlphaEnergy;
		Double_t ElectronEnergy;
		std::vector<Int_t> xid;
		std::vector<Int_t> yid;
		std::vector<Double_t> xEnergyValue;
		std::vector<Double_t> yEnergyValue;
  	private:
		TFile *fout;
		TTree *tree;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
//累加每一步的能量沉积获得总能量
inline void DSSD_EventAction::Add_DSSD(G4double de) 
{
    Energy += de; 
}
//Resoluation
inline G4double DSSD_EventAction::Gaus(G4double x, G4double sigma, G4double offset)
{
    G4double x1, x2, A, B, C;
    x1 = G4UniformRand();
    x2 = G4UniformRand();
    A = sqrt((-2.0)*log(x1));
    B = 2.0*3.14159*x2;
    C  = A * cos(B);
    return x + C*sigma + offset;
}


*/
#endif

    
