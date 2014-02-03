/*

   \file QweakSimLumiDetector.hh
   \author Wade Duvall

*/

#ifndef QweakSimLumiDetector_h
#define QweakSimLumiDetector_h 1

// geant4 includes
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SDManager.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"

// user classes
class QweakSimMaterial;

class QweakSimLumiDetector
{
    private:
        QweakSimMaterial* pMaterial;

        // Lumi positions and rotations
        G4RotationMatrix* USLumi_Rot;
        G4RotationMatrix* DSLumi_Rot;
        G4ThreeVector USLumi_XYZ;
        G4ThreeVector DSLumi_XYZ;

        G4double USLumi_Position_X;
        G4double USLumi_Position_Y;
        G4double USLumi_Position_Z;
        G4double DSLumi_Position_X;
        G4double DSLumi_Position_Y;
        G4double DSLumi_Position_Z;

        // Define Upsteam and Downstream lumis
        G4VSolid*          USLumi_Solid;
        G4LogicalVolume*   USLumi_Logical;
        G4VPhysicalVolume* USLumi_Physical;
        G4VSolid*          DSLumi_Solid;
        G4LogicalVolume*   DSLumi_Logical;
        G4VPhysicalVolume* DSLumi_Physical;

        /* USLumi geometries */
        G4double USLumi_Length_X;
        G4double USLumi_Length_Y;
        G4double USLumi_Length_Z;

        // DSLumi geometries
        G4double DSLumi_Length_X;
        G4double DSLumi_Length_Y;
        G4double DSLumi_Length_Z;

        // Quartz bar for lumis
        G4Material* QuartzBar;  

        // Sensitive detectors
        G4VSensitiveDetector* USLumiSD;
        G4VSensitiveDetector* DSLumiSD;

    public:
        // Constructor and destructor
        QweakSimLumiDetector();
        virtual ~QweakSimLumiDetector();

        void ConstructComponent(G4VPhysicalVolume*);

        // For the GDML crap
        G4VPhysicalVolume* getUSLumiPhysicalVolume() {
            return USLumi_Physical;
        }
        G4VPhysicalVolume* getDSLumiPhysicalVolume() {
            return DSLumi_Physical;
        }
};

#endif
