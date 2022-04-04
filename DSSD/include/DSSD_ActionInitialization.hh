//  DSSD_ActionInitialization.hh
//  brief Definition of the DSSD_ActionInitialization class
//用于管理模拟过程

#ifndef DSSD_ActionInitialization_h
#define DSSD_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "DSSD_DetectorConstruction.hh"
#include "DSSD_EventAction.hh"

/// Action initialization class.

class DSSD_ActionInitialization : public G4VUserActionInitialization
{
  	public:
    	DSSD_ActionInitialization(DSSD_DetectorConstruction*);   //构造函数，用于传参
    	virtual ~DSSD_ActionInitialization();
    	virtual void Build() const;  //管理模拟过程
  	private:
		DSSD_DetectorConstruction* fDetConstruction;   //用于获取探测器信息
//		DSSD_EventAction* EventAction;
};

#endif

    
