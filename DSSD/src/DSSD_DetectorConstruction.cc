	//DSSD_DetectorConstruction.cc 探测器构建具体实现

#include "DSSD_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


//构造函数继承定义
DSSD_DetectorConstruction::DSSD_DetectorConstruction()
: G4VUserDetectorConstruction()
{}
//析够函数定义
DSSD_DetectorConstruction::~DSSD_DetectorConstruction()
{}

//探测器几何构建
G4VPhysicalVolume* DSSD_DetectorConstruction::Construct()
{  
  // Get nist material manager to Get material
//  G4NistManager* nist = G4NistManager::Instance();
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;  //true;
 
  // World
//  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4double World_mat_Z = 2.0;
  G4double World_mat_MassPreMole = 4.0026028*g/mole;
  G4Material* world_mat = new G4Material("GasHe", World_mat_Z, World_mat_MassPreMole, 1.1825E-6*g/cm3, 
				  						kStateGas, 293.15*kelvin, 60*pascal);
  G4double world_sizeX = 300*mm, world_sizeY = 200*mm, world_sizeZ = 200*mm;    //size of world  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  	//DSSD one body
	G4double xLength = 128*mm;
	G4double yLength = 48*mm;
	G4double DSSDThickness = 300E-3*mm;
    G4Box* DSSD_solid =
    new G4Box("DSSD",                       //its name
        	0.5*xLength, 0.5*yLength, 0.5*DSSDThickness);     //its size
	//Silicon material
  	G4double Si_mat_Density = 2.33*g/cm3;
  	G4double Si_mat_MassPreMole = 4.0026028*g/mole;
  	G4Material* Si_mat = new G4Material("Si", 14.0, Si_mat_MassPreMole, Si_mat_Density);

	G4LogicalVolume* DSSD_logic = new G4LogicalVolume(DSSD_solid, Si_mat, "DSSD");
//	body_logic->SetVisAttributes(G4VisAttributes::Invisible);  //隐藏身体
	G4VisAttributes* DSSD_vis = new G4VisAttributes(G4Colour(0., 1., 0.));
	DSSD_logic->SetVisAttributes(DSSD_vis);
//	G4ThreeVector DSSD_pos = G4ThreeVector(0, 0*mm, 0*mm);
//	phys_DSSD = new G4PVPlacement(0, DSSD_pos, DSSD_logic, "DSSD", logicWorld, false, 0, checkOverlaps);

	G4Box *DSSD_solid_pixel[128][48];
	G4LogicalVolume *DSSD_logic_pixel[128][48];
	for(int i =0; i<128; i++)
	{
		for(int j=0; j<48; j++)
		{
			DSSD_solid_pixel[i][j] = new G4Box("DSSD", 0.5*xLength/128.0, 0.5*yLength/48.0, 0.5*DSSDThickness);
			DSSD_logic_pixel[i][j] = new G4LogicalVolume(DSSD_solid_pixel[i][j], Si_mat, "DSSD");
			DSSD_logic_pixel[i][j]->SetVisAttributes(DSSD_vis);
			G4ThreeVector DSSD_pos = G4ThreeVector(-64*mm + double(i+1)*mm + 0.5*mm, -24*mm + 0.5*mm + double(j+1)*mm, 0*mm);
//			std::cout << i <<"  "<<j <<"  : "<< DSSD_pos.getX() << "  " << DSSD_pos.getY() << "  "<< DSSD_pos.getZ() << std::endl;
			phys_DSSD_pixel[i][j] = new G4PVPlacement(0, DSSD_pos, DSSD_logic_pixel[i][j], "DSSD", logicWorld, false, 0, checkOverlaps);
			phys_DSSD_pixel[i][j]->SetCopyNo(i*100+j);
		}
	}

	G4cout<<"*********Detector  ok***************"<<G4endl;
  	return physWorld;
}
