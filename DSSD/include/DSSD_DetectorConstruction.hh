//   DSSD_DetectorConstruction.hh    用于构造探测器

#ifndef DSSD_DetectorConstruction_h
#define DSSD_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"   //全局--用于提取信息

class G4VPhysicalVolume;
class G4LogicalVolume;

// Detector construction class to define materials and geometry.

class DSSD_DetectorConstruction : public G4VUserDetectorConstruction
{
  	public:
    	DSSD_DetectorConstruction();
    	virtual ~DSSD_DetectorConstruction();

    	virtual G4VPhysicalVolume* Construct();  //必须要有的函数，构建探测器时执行，只能修改函数的功能，不能重命名
//		inline const G4VPhysicalVolume* Getbody() const {return phys_body;};  //用于外部获取探测器的所在的位置信息
//		inline const G4VPhysicalVolume* Getbody() const;
  protected:
		G4VPhysicalVolume* phys_DSSD;
		G4VPhysicalVolume*phys_DSSD_pixel[128][48];
};
/*
inline const G4VPhysicalVolume* DSSD_DetectorConstruction::Getbody() const
{
	return phys_body;
}
*/

#endif

