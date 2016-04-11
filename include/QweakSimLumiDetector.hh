/*

   \file QweakSimLumiDetector.hh
   \author Wade Duvall

*/

#ifndef QweakSimLumiDetector_h
#define QweakSimLumiDetector_h 1

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"

// user classes
class QweakSimMaterial;
class QweakSimLumiMessenger;

class QweakSimLumiDetector {
    private:
        QweakSimLumiMessenger* LumiMessenger;
        QweakSimMaterial* pMaterial;
        G4VisAttributes*   Lumi_VisAtt;

        // Lumi positions and rotations
        G4RotationMatrix* Lumi_Rot;
        G4ThreeVector Lumi_XYZ;

        G4double Lumi_Position_X;
        G4double Lumi_Position_Y;
        G4double Lumi_Position_Z;

        // Lumi tag
        G4String Lumi_Tag;

        // Define Upsteam and Downstream lumis
        G4VSolid*          Lumi_Solid;
        G4LogicalVolume*   Lumi_Logical;
        G4VPhysicalVolume* Lumi_Physical;

        /* Lumi geometries */
        G4double Lumi_Length_X;
        G4double Lumi_Length_Y;
        G4double Lumi_Length_Z;

        // Quartz bar for lumis
        G4Material* QuartzBar;  

        // Sensitive detectors
        G4VSensitiveDetector* LumiSD;

    public:
        // Constructor and destructor
        QweakSimLumiDetector(G4String);
        virtual ~QweakSimLumiDetector();

        // fuctions for the messanger class
        void SetLumi_PositionInX(G4double);
        void SetLumi_PositionInY(G4double);
        void SetLumi_PositionInZ(G4double);

        void SetLumi_Material(G4String);

        void SetLumi_Enabled();
        void SetLumi_Disabled();

        void ConstructComponent(G4VPhysicalVolume*, G4double, G4double,
                                G4double, G4double, G4double, G4double);

        // For the GDML crap
        G4VPhysicalVolume* getLumiPhysicalVolume() {
            return Lumi_Physical;
        }
};

#endif
