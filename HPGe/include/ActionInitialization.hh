//  ActionInitialization.hh
//  brief Definition of the ActionInitialization class
//用于管理模拟过程

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
  	public:
    	ActionInitialization(DetectorConstruction*);   //构造函数，用于传参
    	virtual ~ActionInitialization();
    	virtual void Build() const;  //管理模拟过程
  	private:
		DetectorConstruction* fDetConstruction;   //用于获取探测器信息
//		EventAction* EventAction;
};

#endif

    
