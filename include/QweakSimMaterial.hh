//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimMaterial.hh
   $Revision: 1.2 $
   $Date: 2005/12/27 19:25:44 $
   \author Klaus Hans Grimm

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimMaterial

   \brief Definition of elements and materials

   Placeholder for a long explaination

 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:25:44 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
//
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMaterial_H
#define QweakSimMaterial_H 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4NistManager.hh"

// user includes
#include "QweakSimSystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMaterial
{
  private:

    // Private constructor
    QweakSimMaterial();

    // Prevent creation of automatic copy constructors
    QweakSimMaterial(QweakSimMaterial const& copy);
    QweakSimMaterial& operator=(QweakSimMaterial const& copy);

    // Destructor
    virtual ~QweakSimMaterial() { };

  public:
    // Get the instance of the Qweak materials manager
    static QweakSimMaterial* GetInstance() {
      static QweakSimMaterial material;
      return &material;
    };

    // Get the material
    G4Material* GetMaterial(G4String material) {
      // Search list of custom materials
      G4Material* ptrToMaterial = G4Material::GetMaterial(material);
      // Search list of NIST materials
      if (ptrToMaterial == 0) {
        ptrToMaterial = fNistManager->FindOrBuildMaterial(material);
      }
      return ptrToMaterial;
    }

  private:

    // NIST materials manager
    G4NistManager* fNistManager;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//      $Revisions$
//      $Log: QweakSimMaterial.hh,v $
//      Revision 1.2  2005/12/27 19:25:44  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//


