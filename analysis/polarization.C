// Make polarization profile plots across the Cerenkov detector bars.
// Pass the tree that should be used and a tag to append to standard output file names (e.g. "_horizontal")
// Example:
// build/QweakSimRoot QwSim_0.root
//   .L analysis/polarization.C+
//   polarization(QweakSimG4_Tree,"_horizontal")
//
// Note that all plots are versus -Cerenkov.Detector.HitLocalPositionX because the local X axis for the
// main detector points from PMT+ to PMT-

#include "TCanvas.h"
#include "TTree.h"

void polarization (TTree* QweakSimG4_Tree, const char* tag)
{
  // Some aliases to make what follows more easy to follow
  QweakSimG4_Tree->SetAlias("ID","Cerenkov.Detector.DetectorID");
  QweakSimG4_Tree->SetAlias("PDG","Cerenkov.Detector.ParticleType");
  QweakSimG4_Tree->SetAlias("PolX","-Cerenkov.Detector.PolarizationX"); // intuitive X position when looking along Z direction
  QweakSimG4_Tree->SetAlias("PolY","Cerenkov.Detector.PolarizationY");
  QweakSimG4_Tree->SetAlias("PolZ","Cerenkov.Detector.PolarizationZ");
  QweakSimG4_Tree->SetAlias("PolL","Cerenkov.Detector.LongitudinalPolarization");
  QweakSimG4_Tree->SetAlias("PolT","Cerenkov.Detector.TransversePolarization");
  QweakSimG4_Tree->SetAlias("PolTX","-Cerenkov.Detector.TransversePolarizationX"); // intuitive X position when looking along Z direction
  QweakSimG4_Tree->SetAlias("PolTY","Cerenkov.Detector.TransversePolarizationY");
  QweakSimG4_Tree->SetAlias("PolTPhiAngle","Cerenkov.Detector.TransversePolarizationPhiAngle");
  QweakSimG4_Tree->SetAlias("Pol","sqrt(PolX**2+PolY**2+PolZ**2)");
  QweakSimG4_Tree->SetAlias("X","-Cerenkov.Detector.HitLocalPositionX"); // intuitive X position when looking along Z direction
  QweakSimG4_Tree->SetAlias("Y","Cerenkov.Detector.HitLocalPositionY");
  QweakSimG4_Tree->SetAlias("Z","Cerenkov.Detector.HitLocalPositionZ");
  // make sure phi wraps around nicely at 180 degrees
  QweakSimG4_Tree->SetAlias("Primary_OriginVertexPhiAngle","180.0-180.0/pi*asin(sin(pi/180.0*Primary.OriginVertexPhiAngle))");

  // Cuts:
  //  PDG == 11 -> electrons only
  //  Z > 0 -> avoid double counting entry and exit point of track
  //  ID == 1 -> require correct octant (varies from octant to octant, of course)
  //  Pol > 0.01 -> require non-zero polarization to get rid of many unpolarized shower(?) electrons  
  
  // Listing of spin components
  QweakSimG4_Tree->SetScanField(0); // do not page scan results
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","",500);
  QweakSimG4_Tree->Scan("ID:X:Y:PolX:PolY:PolZ:PolL:PolT:PolTX:PolTY","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","",500);

  // Longitudinal polarization (this is dot product of polarization vector and normalized momentum)
  TCanvas c0("c0","Phi distribution at Cerenkov detector plane",1280,1024);
  c0.Divide(3,3);
  c0.cd(4);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01");
  c0.cd(1);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01");
  c0.cd(2);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01");
  c0.cd(3);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01");
  c0.cd(6);
  QweakSimG4_Tree->Draw("Primary_OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01");
  c0.cd(9);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01");
  c0.cd(8);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01");
  c0.cd(7);
  QweakSimG4_Tree->Draw("Primary.OriginVertexPhiAngle:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01");
  c0.SaveAs(Form("images/origin_vertex_phi_distribution%s.png",tag));
  
  // Longitudinal polarization (this is dot product of polarization vector and normalized momentum)
  TCanvas c1("c1","Longitudinal polarization at Cerenkov detector plane",1280,1024);
  c1.Divide(3,3);
  c1.cd(4);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c1.cd(1);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c1.cd(2);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c1.cd(3);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c1.cd(6);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c1.cd(9);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c1.cd(8);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c1.cd(7);
  QweakSimG4_Tree->Draw("PolL:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c1.SaveAs(Form("images/longitudinal_polarization%s.png",tag));

  // Transverse polarization (this is the magnitude of the difference of the total polarization vector and the longitudinal polarization vector)
  TCanvas c2("c2","Transverse polarization at Cerenkov detector plane",1280,1024);
  c2.Divide(3,3);
  c2.cd(4);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c2.cd(1);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c2.cd(2);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c2.cd(3);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c2.cd(6);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c2.cd(9);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c2.cd(8);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c2.cd(7);
  QweakSimG4_Tree->Draw("PolT:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c2.SaveAs(Form("images/transverse_polarization%s.png",tag));

  // Transverse polarization vector when projected on Cerenkov detectors (angle spanned by the transverse X and Y components)
  TCanvas c3("c3","Transverse polarization direction at Cerenkov detector plane",1280,1024);
  c3.Divide(3,3);
  c3.cd(4);
  QweakSimG4_Tree->Draw("   0.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c3.cd(1);
  QweakSimG4_Tree->Draw(" -45.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c3.cd(2);
  QweakSimG4_Tree->Draw(" -90.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c3.cd(3);
  QweakSimG4_Tree->Draw("-135.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c3.cd(6);
  QweakSimG4_Tree->Draw("+180.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c3.cd(9);
  QweakSimG4_Tree->Draw("+135.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c3.cd(8);
  QweakSimG4_Tree->Draw(" +90.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c3.cd(7);
  QweakSimG4_Tree->Draw(" +45.0+PolTPhiAngle:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c3.SaveAs(Form("images/transverse_polarization_direction%s.png",tag));

  // Transverse polarization component along the Cerenkov detectors
  TCanvas c3x("c3x","Transverse polarization perpendicular to the bar at Cerenkov detector plane",1280,1024);
  c3x.Divide(3,3);
  c3x.cd(4);
  QweakSimG4_Tree->Draw("cos(+0.0*pi/4)*PolTX-sin(+0.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c3x.cd(1);
  QweakSimG4_Tree->Draw("cos(+1.0*pi/4)*PolTX-sin(+1.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c3x.cd(2);
  QweakSimG4_Tree->Draw("cos(+2.0*pi/4)*PolTX-sin(+2.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c3x.cd(3);
  QweakSimG4_Tree->Draw("cos(+3.0*pi/4)*PolTX-sin(+3.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c3x.cd(6);
  QweakSimG4_Tree->Draw("cos(+4.0*pi/4)*PolTX-sin(+4.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c3x.cd(9);
  QweakSimG4_Tree->Draw("cos(-3.0*pi/4)*PolTX-sin(-3.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c3x.cd(8);
  QweakSimG4_Tree->Draw("cos(-2.0*pi/4)*PolTX-sin(-2.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c3x.cd(7);
  QweakSimG4_Tree->Draw("cos(-1.0*pi/4)*PolTX-sin(-1.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c3x.SaveAs(Form("images/transverse_polarization_perpendicular_to_bar%s.png",tag));

  // Transverse polarization component along the Cerenkov detectors
  TCanvas c3y("c3y","Transverse polarization along the bar at Cerenkov detector plane",1280,1024);
  c3y.Divide(3,3);
  c3y.cd(4);
  QweakSimG4_Tree->Draw("sin(+0.0*pi/4)*PolTX+cos(+0.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c3y.cd(1);
  QweakSimG4_Tree->Draw("sin(+1.0*pi/4)*PolTX+cos(+1.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c3y.cd(2);
  QweakSimG4_Tree->Draw("sin(+2.0*pi/4)*PolTX+cos(+2.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c3y.cd(3);
  QweakSimG4_Tree->Draw("sin(+3.0*pi/4)*PolTX+cos(+3.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c3y.cd(6);
  QweakSimG4_Tree->Draw("sin(+4.0*pi/4)*PolTX+cos(+4.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c3y.cd(9);
  QweakSimG4_Tree->Draw("sin(-3.0*pi/4)*PolTX+cos(-3.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c3y.cd(8);
  QweakSimG4_Tree->Draw("sin(-2.0*pi/4)*PolTX+cos(-2.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c3y.cd(7);
  QweakSimG4_Tree->Draw("sin(-1.0*pi/4)*PolTX+cos(-1.0*pi/4)*PolTY:X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c3y.SaveAs(Form("images/transverse_polarization_along_bar%s.png",tag));

  // Spin precession angle (at least when assuming that events started from longitudinal polarization)
  TCanvas c4("c4","Polarization precession at Cerenkov detector plane",1280,1024);
  // TransversePolarization is always positive as a magnitude, LongitudinalPolarization can be positive or negative.
  // Since the precession angle will be between 0 and 90 degrees, take the absolute value of LongitudinalPolarization.
  // FIXME: This will have to be changed for 3.3 GeV beam since precession may be larger than 90 degrees there!
  c4.Divide(3,3);
  c4.cd(4);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 1 && Pol>0.01","prof");
  c4.cd(1);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 2 && Pol>0.01","prof");
  c4.cd(2);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 3 && Pol>0.01","prof");
  c4.cd(3);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 4 && Pol>0.01","prof");
  c4.cd(6);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 5 && Pol>0.01","prof");
  c4.cd(9);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 6 && Pol>0.01","prof");
  c4.cd(8);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 7 && Pol>0.01","prof");
  c4.cd(7);
  QweakSimG4_Tree->Draw("180.0/pi*atan2(PolT,abs(PolL)):X","PDG == 11 && Z>0 && ID == 8 && Pol>0.01","prof");
  c4.SaveAs(Form("images/polarization_precession%s.png",tag));
}
