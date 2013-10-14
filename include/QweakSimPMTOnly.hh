// QweakSimPMTOnly.hh
// Marty McHugh
// 2013-06-11

/////// --------------------------------------------------------------------

#ifndef QweakSimPMTOnly_hh
#define QweakSimPMTOnly_hh 1

/////// --------------------------------------------------------------------

//--- geant4 includes
#include "G4LogicalVolume.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimPMTOnlyMessenger.hh"
#include "QweakSimUserInformation.hh"

/////// --------------------------------------------------------------------

//--- user classes
class QweakSimMaterial;
class QweakSimPMTOnlyMessenger;

/////// --------------------------------------------------------------------

class QweakSimPMTOnly
{
	
public:
	
    QweakSimPMTOnly(QweakSimUserInformation*);
    ~QweakSimPMTOnly();
	
    void ConstructComponent(G4VPhysicalVolume* MotherVolume);
    void DestroyComponent();
	
    void SetPMTOnly_Material(G4String);
	
    void SetPMTOnly_CenterPositionInX(G4double xPos);
    void SetPMTOnly_CenterPositionInY(G4double yPos);
    void SetPMTOnly_CenterPositionInZ(G4double zPos);
    
    G4double GetPMTOnly_CenterPositionInX()    {return PMTOnly_CenterPosition_X+Mother_CenterPosition_X;}
    G4double GetPMTOnly_CenterPositionInY()    {return PMTOnly_CenterPosition_Y+Mother_CenterPosition_Y;}
    G4double GetPMTOnly_CenterPositionInZ()    {return PMTOnly_CenterPosition_Z+Mother_CenterPosition_Z;}
	
    void SetPMTOnly_FullLengthInX(G4double dim)  {PMTOnly_FullLength_X = dim;}
    void SetPMTOnly_FullLengthInY(G4double dim)  {PMTOnly_FullLength_Y = dim;}
    void SetPMTOnly_FullLengthInZ(G4double dim)  {PMTOnly_FullLength_Z = dim;}
    
    G4double GetPMTOnly_FullLengthInX()          {return PMTOnly_FullLength_X;}
    G4double GetPMTOnly_FullLengthInY()          {return PMTOnly_FullLength_Y;}
    G4double GetPMTOnly_FullLengthInZ()          {return PMTOnly_FullLength_Z;}
    
    void SetPMTOnly_TiltAngleInX(G4double xTiltAngle);
    void SetPMTOnly_TiltAngleInY(G4double yTiltAngle);
    void SetPMTOnly_TiltAngleInZ(G4double zTiltAngle);
    
    G4double GetPMTOnly_TiltAngleInX()           {return Mother_TiltAngle_X;}
    G4double GetPMTOnly_TiltAngleInY()           {return Mother_TiltAngle_Y;}
    G4double GetPMTOnly_TiltAngleInZ()           {return Mother_TiltAngle_Z;}
	
    void SetPMTOnly_Enabled();
    void SetPMTOnly_Disabled();
	
    G4LogicalVolume*   GetPMTOnly_LogicalVolume()  {return PMTOnly_Logical;}
    G4VPhysicalVolume* GetPMTOnly_PhysicalVolume() {return PMTOnly_Physical;}
	
private:
	
    QweakSimPMTOnlyMessenger* PMTOnlyMessenger;
	
    QweakSimMaterial* pMaterial;

    G4Box* 		Mother_Solid;
    G4LogicalVolume*	Mother_Logical;
    G4VPhysicalVolume*	Mother_Physical;
    G4Material*		Mother_Material;	
    G4VisAttributes*   	Mother_VisAtt;

    G4Box*             	PMTOnly_Solid;
    G4LogicalVolume*   	PMTOnly_Logical;
    G4VPhysicalVolume* 	PMTOnly_Physical;
    G4Material*        	PMTOnly_Material;
    G4VisAttributes*   	PMTOnly_VisAtt;
    
    G4Tubs*		PMTQuartzOpticalFilm_Solid;
    G4LogicalVolume*   	PMTQuartzOpticalFilm_Logical;
    G4VPhysicalVolume* 	PMTQuartzOpticalFilm_Physical;
    G4Material*        	PMTQuartzOpticalFilm_Material;
    
    G4Tubs*		PMTEntranceWindow_Solid;
    G4LogicalVolume*   	PMTEntranceWindow_Logical; 
    G4VPhysicalVolume* 	PMTEntranceWindow_Physical; 
    G4Material*        	PMTEntranceWindow_Material;
    
    G4Tubs* 		Cathode_Solid;
    G4LogicalVolume*   	Cathode_Logical; 
    G4VPhysicalVolume* 	Cathode_Physical; 
    G4Material*        	Cathode_Material;
    
    //--- Mother sizes
    G4double Mother_FullLength_X;
    G4double Mother_FullLength_Y;
    G4double Mother_FullLength_Z;
    
    //--- Mother position
    G4double Mother_CenterPosition_X;
    G4double Mother_CenterPosition_Y;
    G4double Mother_CenterPosition_Z;
    G4ThreeVector Mother_CenterPosition;
	
    //--- PMTOnly sizes
    G4double PMTOnly_FullLength_X;
    G4double PMTOnly_FullLength_Y;
    G4double PMTOnly_FullLength_Z;
	
    //--- PMTOnly position
    G4double PMTOnly_CenterPosition_X;
    G4double PMTOnly_CenterPosition_Y;
    G4double PMTOnly_CenterPosition_Z;
    G4ThreeVector PMTOnly_CenterPosition;
	
    //--- Mother rotation
    G4double Mother_TiltAngle_X;
    G4double Mother_TiltAngle_Y;
    G4double Mother_TiltAngle_Z;
    G4RotationMatrix* Mother_RotationMatrix;

    //--- MD5 position
    G4double MD5_CenterPosition_X;
    G4double MD5_CenterPosition_Y;
    G4double MD5_CenterPosition_Z;

    //--- PMT Stuff
    G4double PMTQuartzOpticalFilm_Diameter;
    G4double PMTQuartzOpticalFilm_Thickness;

    G4double PMTEntranceWindow_Diameter;
    G4double PMTEntranceWindow_Thickness;

    G4double Cathode_Diameter;
    G4double Cathode_Thickness;

    //--- PMTOnly sensitive detector
    G4VSensitiveDetector* PMTOnlySD;
    
    G4VSensitiveDetector* PMTOnly_PMTSD;
    
    //--- QweakSimUserInformation
    QweakSimUserInformation* myUserInfo;
    
};


/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
