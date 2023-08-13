
//DetectorConstruction.cc 探测器构建具体实现

#include "DetectorConstruction.hh"

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
#include "G4GDMLParser.hh"
#include "G4LogicalVolumeStore.hh"
#include "TString.h"


//构造函数继承定义
DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{}
//析够函数定义
DetectorConstruction::~DetectorConstruction()
{}

//探测器几何构建
G4VPhysicalVolume* DetectorConstruction::Construct()
{  
    // Get nist material manager to Get material
    G4NistManager* nist = G4NistManager::Instance();
    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = true;  //true;

    // World

    G4Material* Air_mat = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* Vacuum_mat = nist->FindOrBuildMaterial("G4_Galactic");	

  	G4double He_mat_Z = 2.0;
  	G4double He_mat_MassPreMole = 4.0026028*g/mole;
  	G4Material* He_Gas = new G4Material("GasHe", He_mat_Z, He_mat_MassPreMole, 1.1825E-6*g/cm3, 
				  						kStateGas, 293.15*kelvin, 60*pascal);

	G4double Be_mat_Density = 1.848*g/cm3;
	G4double Be_mat_MassPreMole = 9.012182*g/mole;
	G4Material* Be_mat = new G4Material("Be", 4.0, Be_mat_MassPreMole, Be_mat_Density);

  	G4double Pb_mat_Density = 11.34*g/cm3;
  	G4double Pb_mat_MassPreMole = 207.2*g/mole;
  	G4Material* Pb_mat = new G4Material("Pb", 82.0, Pb_mat_MassPreMole, Pb_mat_Density);

  	G4double Cu_mat_Density = 8.91*g/cm3;
  	G4double Cu_mat_MassPreMole = 63.546*g/mole;
  	G4Material* Cu_mat = new G4Material("Cu", 29.0, Cu_mat_MassPreMole, Cu_mat_Density);

  	G4double Al_mat_Density = 2.702*g/cm3;
  	G4double Al_mat_MassPreMole = 26.98154*g/mole;
  	G4Material* Al_mat = new G4Material("Cu", 29.0, Cu_mat_MassPreMole, Cu_mat_Density);

	//Ge material
  	G4double Ge_mat_Density = 5.323*g/cm3;
  	G4double Ge_mat_MassPreMole = 72.61*g/mole;
  	G4Material* Ge_mat = new G4Material("Ge", 32.0, Ge_mat_MassPreMole, Ge_mat_Density);
	//Silicon material
  	G4double Si_mat_Density = 2.33*g/cm3;
  	G4double Si_mat_MassPreMole = 28.0855*g/mole;
  	G4Material* Si_mat = new G4Material("Si", 14.0, Si_mat_MassPreMole, Si_mat_Density);

    G4double Zel, a;
    a = 1.01*g/mole;  //指定氢原子(氕)的摩尔质量
    G4Element* elH = new G4Element("Hydrogen", "H", Zel= 1.0, a); //创建氢原子(氕)
    a = 16.00*g/mole;  //指定氧16原子的摩尔质量
    G4Element* elO = new G4Element("Oxygen", "O", Zel= 8.0, a);  //创建O16原子
    a = 12.01*g/mole;  //指定C12原子的摩尔质量
    G4Element* elC = new G4Element("Carbon", "C", Zel= 6.0, a);  //创建C12原子

    //	Polystyrol  C8H8 Fiber
    G4double C8H8_density = 1.06*g/cm3; //指定材料的密度
    G4Material* C8H8_mat = new G4Material("C8H8", C8H8_density, 2);  //last parameter : The number of element
    C8H8_mat->AddElement(elH, 8);
    //加入第一种原子H，其在一个材料分子中有8个
    C8H8_mat->AddElement(elC, 8);
    //加入第二种原子C，其在一个材料分子中有8个

    //	Polystyrol  H8C5O2 PMMA
    G4double H8C5O2_density = 0.95*g/cm3; //指定材料的密度
    G4Material* H8C5O2_mat = new G4Material("H8C5O2", H8C5O2_density, 3);  //last parameter : The number of element
    H8C5O2_mat->AddElement(elH, 8);
    H8C5O2_mat->AddElement(elC, 5);
    H8C5O2_mat->AddElement(elO, 2);


    G4double world_sizeX = 300*mm, world_sizeY = 200*mm, world_sizeZ = 200*mm;    //size of world  
    G4Box* solidWorld = new G4Box("World",                       //its name
                        0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,          //its solid
                                  Air_mat,           //its material
                                  "World");            //its name

    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,                     //rotation
                                   G4ThreeVector(),       //at (0,0,0)
                                   logicWorld,            //its logical volume
                                   "World",               //its name
                                   0,                     //its mother  volume
                                   false,                 //no boolean operation
                                   0,                     //copy number
                                    checkOverlaps);        //overlaps checking
    //one body detector
    G4double xLength = 50*mm;
    G4double yLength = 50*mm;
    G4double zLength = 50*mm;
    G4Box* Detector_solid = new G4Box("Detector",                       //its name
                            0.5*xLength, 0.5*yLength, 0.5*zLength);     //its size

    G4LogicalVolume* Detector_logic = new G4LogicalVolume(Detector_solid, Ge_mat, "Detector");
    G4VisAttributes* Detector_vis = new G4VisAttributes(G4Colour(0., 1., 0.));  
    Detector_logic->SetVisAttributes(Detector_vis); // SetVisAttributes(G4VisAttributes::Invisible);  //隐藏
    G4ThreeVector Detector_pos = G4ThreeVector(0, 0*mm, 0*mm);
    phys_Detector = new G4PVPlacement(0, Detector_pos, Detector_logic, "Detector", logicWorld, false, 0, checkOverlaps);

    G4cout<<"*********Detector  ok***************"<<G4endl;
    return physWorld;
}
