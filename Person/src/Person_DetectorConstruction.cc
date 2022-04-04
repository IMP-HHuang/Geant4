	//Person_DetectorConstruction.cc 探测器构建具体实现

#include "Person_DetectorConstruction.hh"

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

Person_DetectorConstruction::Person_DetectorConstruction()
: G4VUserDetectorConstruction()
{}
Person_DetectorConstruction::~Person_DetectorConstruction()
{}
//探测器构建
G4VPhysicalVolume* Person_DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;  //true;
 
  // World
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4double world_sizeX = 600*mm, world_sizeY = 1800*mm, world_sizeZ = 180*cm;    //size of world  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
	//head
	G4double d_head = 180*mm;
	G4Orb* head_solid = new G4Orb("head", 0.5*d_head);
	//neck
	G4double r_min = 0.*mm, d_neck = 100.*mm, l_neck = 90.*mm;
	G4double startAngle = 0.*deg, spanningAngle = 360.*deg;
	G4Tubs* neck_solid = new G4Tubs("neck", r_min, 0.5*d_neck, 0.5*l_neck, startAngle, spanningAngle);
	G4RotationMatrix* neck_rot = new G4RotationMatrix;
	neck_rot->rotateX(M_PI/2.*rad);
	//head and neck
	G4ThreeVector neck_head_dpos = G4ThreeVector(0, -120*mm, 0);	
	G4UnionSolid* head_neck_solid = new G4UnionSolid("head+neck", head_solid, neck_solid, neck_rot, neck_head_dpos);
	G4Material* head_neck_mat = nist->FindOrBuildMaterial("G4_WATER");
	G4LogicalVolume* head_neck_logic = new G4LogicalVolume(head_neck_solid, head_neck_mat, "head and neak");
	G4VisAttributes* head_neck_vis = new G4VisAttributes(G4Colour(1., 1., 0.));
	head_neck_logic->SetVisAttributes(head_neck_vis);
	G4ThreeVector head_neck_pos = G4ThreeVector(0, 660*mm, 0); //此位置应为头部所放位置，而非布尔几何中心位置
	new G4PVPlacement(0, head_neck_pos, head_neck_logic, "head and neak", logicWorld, false, 0, checkOverlaps);

	//body
	G4double body_sizeX = 120*mm, body_sizeY = 500*mm, body_sizeZ = 260*mm;    //size of body 
    G4Box* body_solid =
    new G4Box("body",                       //its name
        	0.5*body_sizeX, 0.5*body_sizeY, 0.5*body_sizeZ);     //its size
	G4Material* body_mat = nist->FindOrBuildMaterial("G4_WATER");
	G4LogicalVolume* body_logic = new G4LogicalVolume(body_solid, body_mat, "body");
//	body_logic->SetVisAttributes(G4VisAttributes::Invisible);  //隐藏身体
	G4VisAttributes* body_vis = new G4VisAttributes(G4Colour(0., 1., 0.));
	body_logic->SetVisAttributes(body_vis);
	G4ThreeVector body_pos = G4ThreeVector(0, 245*mm, 0);
	phys_body = new G4PVPlacement(0, body_pos, body_logic, "body", logicWorld, false, 0, checkOverlaps);

	//leg
	G4double d_leg = 110.*mm, l_leg = 820.*mm;
	G4Tubs* leg_solid = new G4Tubs("leg", 0, 0.5*d_leg, 0.5*l_leg, startAngle, spanningAngle);
	G4Material* leg_mat = nist->FindOrBuildMaterial("G4_WATER");
	G4LogicalVolume* leg_logic = new G4LogicalVolume(leg_solid, leg_mat, "leg");
	G4VisAttributes* leg_vis = new G4VisAttributes(G4Colour(0., 0., 1.));
	leg_logic->SetVisAttributes(leg_vis);
	G4RotationMatrix* leg_rot = new G4RotationMatrix;
	leg_rot->rotateX(M_PI/2.*rad);
	G4ThreeVector legl_pos = G4ThreeVector(0, -415*mm, -75*mm);
	new G4PVPlacement(leg_rot, legl_pos, leg_logic, "left leg", logicWorld, false, 0, checkOverlaps);
	G4ThreeVector legr_pos = G4ThreeVector(0, -415*mm, 75*mm);
	new G4PVPlacement(leg_rot, legr_pos, leg_logic, "left leg", logicWorld, false, 0, checkOverlaps);
	G4cout<<"*********Detector  ok***************"<<G4endl;
  	return physWorld;
}
