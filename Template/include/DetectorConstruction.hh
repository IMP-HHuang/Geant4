//   DetectorConstruction.hh    用于构造探测器

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"   //全局--用于提取信息

class G4VPhysicalVolume;
class G4LogicalVolume;

// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  	public:
    	DetectorConstruction();
    	virtual ~DetectorConstruction();

    	virtual G4VPhysicalVolume* Construct();  //必须要有的函数，构建探测器时执行，只能修改函数的功能，不能重命名
  protected:
		G4VPhysicalVolume* phys_Detector;

};
/*
inline const G4VPhysicalVolume* DetectorConstruction::Getbody() const
{
	return phys_body;
}
*/

#endif

