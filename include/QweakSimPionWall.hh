
//=============================================================================
//
//  File     QweakSimPionWall.hh
//  Revision 1.0
//  Date     07/05/2012
//  Author   James Dowd
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimPionWall_h
#define QweakSimPionWall_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//  geant4 includes
#include "G4LogicalVolume.hh"

//  user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimPionWallMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


//  user classes
class QweakSimPionWallMessenger;
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimPionWall
{

  private:

    QweakSimMaterial* pMaterial;

    G4LogicalVolume*   PionWall_Logical;
    G4VPhysicalVolume* PionWall_Physical;
    G4Box*             PionWall_Solid;
    G4Material*        PionWall_Material;
    G4VisAttributes*   PionWall_VisAtt;

    QweakSimPionWallMessenger* PionWall_Messenger;  //  pionter to the Messenger

    G4double PionWall_Length_X;
    G4double PionWall_Length_Y;
    G4double PionWall_Length_Z;

    G4double MD7_CenterYPosition;
    G4double MD7_CenterZPosition;

    G4double PionWall_CenterXPosition;
    G4double PionWall_CenterYPosition;
    G4double PionWall_CenterZPosition;

  public:

    //!Constructor
    QweakSimPionWall();

    //!Destructor
    ~QweakSimPionWall();

    void ConstructPionWall(G4VPhysicalVolume*);
	
    void DestroyComponent();
	
    void     SetPionWall_CenterPositionInX(G4double xPos);
    void     SetPionWall_CenterPositionInY(G4double yPos);
    void     SetPionWall_CenterPositionInZ(G4double zPos);

    G4double GetPionWall_CenterPositionInX()    {return PionWall_CenterXPosition;}
    G4double GetPionWall_CenterPositionInY()    {return PionWall_CenterYPosition;}
    G4double GetPionWall_CenterPositionInZ()    {return PionWall_CenterZPosition;}

    void SetPionWallMaterial(G4String);
 
    void SetPionWall_LengthInX(G4double dim)  {PionWall_Length_X = dim;}
    void SetPionWall_LengthInY(G4double dim)  {PionWall_Length_Y = dim;}
    void SetPionWall_LengthInZ(G4double dim);
    
    G4double GetPionWall_LengthInX()          {return PionWall_Length_X;}
    G4double GetPionWall_LengthInY()          {return PionWall_Length_Y;}
    G4double GetPionWall_LengthInZ()          {return PionWall_Length_Z;}
    
    G4LogicalVolume*   getPionWallLogicalVolume()  {return PionWall_Logical;}
    G4VPhysicalVolume* getPionWallPhysicalVolume() {return PionWall_Physical;}
    
    void SetEnabled();
    void SetDisabled();
    
    void SetPionWall_Material(G4String);
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

