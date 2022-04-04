//  Person_ActionInitialization.hh
//  brief Definition of the Person_ActionInitialization class
//用于管理模拟过程

#ifndef Person_ActionInitialization_h
#define Person_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "Person_DetectorConstruction.hh"

/// Action initialization class.

class Person_ActionInitialization : public G4VUserActionInitialization
{
  	public:
    	Person_ActionInitialization(Person_DetectorConstruction*);   //构造函数，用于传参
    	virtual ~Person_ActionInitialization();
    	virtual void Build() const;  //管理模拟过程
  	private:
		Person_DetectorConstruction* fDetConstruction;   //用于获取探测器信息
};

#endif

    
