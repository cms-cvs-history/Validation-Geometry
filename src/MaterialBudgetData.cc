//#include "Utilities/UI/interface/SimpleConfigurable.h"

#include "Validation/Geometry/interface/MaterialBudgetData.h"
#include "G4Step.hh"
#include "G4Material.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"


MaterialBudgetData::MaterialBudgetData()
{

  //instantiate categorizer to assing an ID to volumes and materials
  myMaterialBudgetCategorizer = 0;
}

void MaterialBudgetData::SetAllStepsToTree()
{
  allStepsToTree = 1;
  MAXNUMBERSTEPS = 0;
  MAXNUMBERSTEPS = 5000; //!!!WARNING: this number is also hardcoded when booking the tree
  theDmb = new float[MAXNUMBERSTEPS];
  // rr
  theSupportDmb     = new float[MAXNUMBERSTEPS];
  theSensitiveDmb   = new float[MAXNUMBERSTEPS];
  theCablesDmb      = new float[MAXNUMBERSTEPS];
  theCoolingDmb     = new float[MAXNUMBERSTEPS];
  theElectronicsDmb = new float[MAXNUMBERSTEPS];
  theOtherDmb       = new float[MAXNUMBERSTEPS];
  theAirDmb         = new float[MAXNUMBERSTEPS];
  // rr
  theInitialX = new double[MAXNUMBERSTEPS];
  theInitialY = new double[MAXNUMBERSTEPS];
  theInitialZ = new double[MAXNUMBERSTEPS];
  theFinalX   = new double[MAXNUMBERSTEPS];
  theFinalY   = new double[MAXNUMBERSTEPS];
  theFinalZ   = new double[MAXNUMBERSTEPS];
  // rr
  theVolumeID     = new int[MAXNUMBERSTEPS];
  theVolumeName   = new std::string[MAXNUMBERSTEPS];
  theVolumeCopy   = new int[MAXNUMBERSTEPS];
  theVolumeX      = new float[MAXNUMBERSTEPS];
  theVolumeY      = new float[MAXNUMBERSTEPS];
  theVolumeZ      = new float[MAXNUMBERSTEPS];
  theVolumeXaxis1 = new float[MAXNUMBERSTEPS];
  theVolumeXaxis2 = new float[MAXNUMBERSTEPS];
  theVolumeXaxis3 = new float[MAXNUMBERSTEPS];
  theVolumeYaxis1 = new float[MAXNUMBERSTEPS];
  theVolumeYaxis2 = new float[MAXNUMBERSTEPS];
  theVolumeYaxis3 = new float[MAXNUMBERSTEPS];
  theVolumeZaxis1 = new float[MAXNUMBERSTEPS];
  theVolumeZaxis2 = new float[MAXNUMBERSTEPS];
  theVolumeZaxis3 = new float[MAXNUMBERSTEPS];
  theMaterialID   = new int[MAXNUMBERSTEPS];
  theMaterialName = new std::string[MAXNUMBERSTEPS];
  theMaterialX0   = new float[MAXNUMBERSTEPS];
  theStepID             = new int[MAXNUMBERSTEPS];
  theStepInitialPt      = new float[MAXNUMBERSTEPS];
  theStepInitialEta     = new float[MAXNUMBERSTEPS];
  theStepInitialPhi     = new float[MAXNUMBERSTEPS];
  theStepInitialEnergy  = new float[MAXNUMBERSTEPS];
  theStepInitialPx      = new float[MAXNUMBERSTEPS];
  theStepInitialPy      = new float[MAXNUMBERSTEPS];
  theStepInitialPz      = new float[MAXNUMBERSTEPS];
  theStepInitialBeta    = new float[MAXNUMBERSTEPS];
  theStepInitialGamma   = new float[MAXNUMBERSTEPS];
  theStepFinalPt        = new float[MAXNUMBERSTEPS];
  theStepFinalEta       = new float[MAXNUMBERSTEPS];
  theStepFinalPhi       = new float[MAXNUMBERSTEPS];
  theStepFinalEnergy    = new float[MAXNUMBERSTEPS];
  theStepFinalPx        = new float[MAXNUMBERSTEPS];
  theStepFinalPy        = new float[MAXNUMBERSTEPS];
  theStepFinalPz        = new float[MAXNUMBERSTEPS];
  theStepFinalBeta      = new float[MAXNUMBERSTEPS];
  theStepFinalGamma     = new float[MAXNUMBERSTEPS];
  theStepProcess        = new int[MAXNUMBERSTEPS];
  // rr
}


void MaterialBudgetData::dataStartTrack( const G4Track* aTrack )
{
  // rr
  std::cout << "MaterialBudget Analysis of Event #" << G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() << std::endl;
  // rr
  
  const G4ThreeVector& dir = aTrack->GetMomentum() ;
  
  if( myMaterialBudgetCategorizer == 0) myMaterialBudgetCategorizer = new MaterialBudgetCategorizer;
  
  theStepN=0;
  theTotalMB=0;
  theEta=0;
  thePhi=0;
  
  // rr
  theID=0;
  thePt=0;
  theEnergy=0;
  
  theSupportMB     = 0.;
  theSensitiveMB   = 0.;
  theCablesMB      = 0.;
  theCoolingMB     = 0.;
  theElectronicsMB = 0.;
  theOtherMB       = 0.;
  theAirMB         = 0.;
  theSupportFractionMB     = 0.;
  theSensitiveFractionMB   = 0.;
  theCablesFractionMB      = 0.;
  theCoolingFractionMB     = 0.;
  theElectronicsFractionMB = 0.;
  theOtherFractionMB       = 0.;
  theAirFractionMB         = 0.;
  // rr
  
  theID = (int)(aTrack->GetDefinition()->GetPDGEncoding());
  thePt = dir.perp();
  if( dir.theta() != 0 ) {
    theEta = dir.eta(); 
  } else {
    theEta = -99;
  }
  //  thePhi = dir.phi()/deg; // better not to store in deg
  thePhi = dir.phi();
  theEnergy = aTrack->GetTotalEnergy();
  
}


void MaterialBudgetData::dataEndTrack( const G4Track* aTrack )
{
  //-  std::cout << "[OVAL] MaterialBudget " << G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() << " " << theEta << " " << thePhi << " " << theTotalMB << std::endl;
  // rr
  std::cout << " MaterialBudget " << G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() << " eta " << theEta << " phi " << thePhi << " total MB " << theTotalMB << " SUP " << theSupportMB << " SEN " << theSensitiveMB << " CAB " << theCablesMB << " COL " << theCoolingMB << " ELE " << theElectronicsMB << " other " << theOtherMB << " Air " << theAirMB << std::endl;
  // rr
}


void MaterialBudgetData::dataPerStep( const G4Step* aStep )
{
  G4Material * theMaterialPre = aStep->GetPreStepPoint()->GetMaterial();
  //  G4Material * theMaterialPost = aStep->GetPostStepPoint()->GetMaterial();

  G4StepPoint* prePoint  = aStep->GetPreStepPoint();
  G4StepPoint* postPoint = aStep->GetPostStepPoint();
  
  Hep3Vector prePos  = prePoint->GetPosition();
  Hep3Vector postPos = postPoint->GetPosition();

  G4double steplen = aStep->GetStepLength();

  G4double radlen;

  radlen = theMaterialPre->GetRadlen();
  //t    radlen = theMaterialPre->GetNuclearInterLength();

  G4String name = theMaterialPre->GetName();
  //  std::cout << " steplen " << steplen << " radlen " << radlen << " mb " << steplen/radlen << " mate " << theMaterialPre->GetName() << std::endl;
     
  G4LogicalVolume* lv = aStep->GetTrack()->GetVolume()->GetLogicalVolume();
  
  // instantiate the categorizer
  int volumeID   = myMaterialBudgetCategorizer->volume( lv->GetName() );
  int materialID = myMaterialBudgetCategorizer->material( lv->GetMaterial()->GetName() );
  // rr
  std::string volumeName   = lv->GetName();
  std::string materialName = lv->GetMaterial()->GetName();
  // rr
  
  // rr
  /*
    std::cout << " Volume "   << lv->GetName()                << std::endl;
    std::cout << " Material " << lv->GetMaterial()->GetName() << std::endl;
  */    
  theSupportFractionMB     = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[0];
  theSensitiveFractionMB   = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[1];
  theCablesFractionMB      = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[2];
  theCoolingFractionMB     = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[3];
  theElectronicsFractionMB = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[4];
  theOtherFractionMB       = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[5];
  theAirFractionMB         = myMaterialBudgetCategorizer->x0fraction(lv->GetMaterial()->GetName())[6];
  if(theOtherFractionMB!=0) std::cout << " material found with no category " << lv->GetMaterial()->GetName() 
				 << " in volume " << lv->GetName() << std::endl;
  // rr  
  
  float dmb = steplen/radlen;
  
  G4VPhysicalVolume*       pv                = aStep->GetPreStepPoint()->GetPhysicalVolume();
  const G4VTouchable*      t                 = aStep->GetPreStepPoint()->GetTouchable();
  G4ThreeVector            objectTranslation = t->GetTranslation();
  const G4RotationMatrix*  objectRotation    = t->GetRotation();
  const G4VProcess*        interactionPre    = prePoint->GetProcessDefinedStep();
  const G4VProcess*        interactionPost   = postPoint->GetProcessDefinedStep();
  
  G4Track* track = aStep->GetTrack();
  if(theStepN==0) std::cout << " Simulated Particle " << theID
			    << "\tPt = " << thePt  << " MeV/c" << "\tEta = " << theEta << "\tPhi = " << thePhi 
			    << "\tEnergy = " << theEnergy << " MeV"
		    //			    << std::endl
		    //			    << "\tMagnetic Field at (0,0,0): (" << B000[0] << "," < B000[1] << "," << B000[2] << ")" 
			    << std::endl;
  
  //fill data per step
  if( allStepsToTree ){
    if( stepN > MAXNUMBERSTEPS ) stepN = MAXNUMBERSTEPS;
    theDmb[theStepN] = dmb; 
    theSupportDmb[theStepN]     = (dmb * theSupportFractionMB);
    theSensitiveDmb[theStepN]   = (dmb * theSensitiveFractionMB);
    theCablesDmb[theStepN]      = (dmb * theCablesFractionMB);
    theCoolingDmb[theStepN]     = (dmb * theCoolingFractionMB);
    theElectronicsDmb[theStepN] = (dmb * theElectronicsFractionMB);
    theOtherDmb[theStepN]       = (dmb * theOtherFractionMB);
    theAirDmb[theStepN]         = (dmb * theAirFractionMB);
    theInitialX[theStepN] = prePos.x();
    theInitialY[theStepN] = prePos.y();
    theInitialZ[theStepN] = prePos.z();
    theFinalX[theStepN]   = postPos.x();
    theFinalY[theStepN]   = postPos.y();
    theFinalZ[theStepN]   = postPos.z();
    theVolumeID[theStepN]   = volumeID;
    theVolumeName[theStepN] = volumeName;
    theVolumeCopy[theStepN] = pv->GetCopyNo();
    theVolumeX[theStepN]    = objectTranslation.x();
    theVolumeY[theStepN]    = objectTranslation.y();
    theVolumeZ[theStepN]    = objectTranslation.z();
    theVolumeXaxis1[theStepN] = objectRotation->xx();
    theVolumeXaxis2[theStepN] = objectRotation->xy();
    theVolumeXaxis3[theStepN] = objectRotation->xz();
    theVolumeYaxis1[theStepN] = objectRotation->yx();
    theVolumeYaxis2[theStepN] = objectRotation->yy();
    theVolumeYaxis3[theStepN] = objectRotation->yz();
    theVolumeZaxis1[theStepN] = objectRotation->zx();
    theVolumeZaxis2[theStepN] = objectRotation->zy();
    theVolumeZaxis3[theStepN] = objectRotation->zz();
    theMaterialID[theStepN]   = materialID;
    theMaterialName[theStepN] = materialName;
    theMaterialX0[theStepN]   = radlen;
    theStepID[theStepN]             = track->GetDefinition()->GetPDGEncoding();
    theStepInitialPt[theStepN]      = prePoint->GetMomentum().perp();
    theStepInitialEta[theStepN]     = prePoint->GetMomentum().eta();
    theStepInitialPhi[theStepN]     = prePoint->GetMomentum().phi();
    theStepInitialEnergy[theStepN]  = prePoint->GetTotalEnergy();
    theStepInitialPx[theStepN]      = prePoint->GetMomentum().x();
    theStepInitialPy[theStepN]      = prePoint->GetMomentum().y();
    theStepInitialPz[theStepN]      = prePoint->GetMomentum().z();
    theStepInitialBeta[theStepN]    = prePoint->GetBeta();
    theStepInitialGamma[theStepN]   = prePoint->GetGamma();
    theStepFinalPt[theStepN]        = postPoint->GetMomentum().perp();
    theStepFinalEta[theStepN]       = postPoint->GetMomentum().eta();
    theStepFinalPhi[theStepN]       = postPoint->GetMomentum().phi();
    theStepFinalEnergy[theStepN]    = postPoint->GetTotalEnergy();
    theStepFinalPx[theStepN]        = postPoint->GetMomentum().x();
    theStepFinalPy[theStepN]        = postPoint->GetMomentum().y();
    theStepFinalPz[theStepN]        = postPoint->GetMomentum().z();
    theStepFinalBeta[theStepN]      = postPoint->GetBeta();
    theStepFinalGamma[theStepN]     = postPoint->GetGamma();
    theStepProcess[theStepN] = interactionPre->GetProcessType();
    std::cout << " step " << theStepN
	      << "\tDelta MB = " << theDmb[theStepN]
	      << std::endl
	      << "\t\tSupport "  << theSupportDmb[theStepN]
	      << " Sensitive "   << theSensitiveDmb[theStepN]
	      << " Cables "      << theCablesDmb[theStepN]
	      << " Cooling "     << theCoolingDmb[theStepN]
	      << " Electronics " << theElectronicsDmb[theStepN]
	      << " Other "       << theOtherDmb[theStepN]
	      << " Air "         << theAirDmb[theStepN]
	      << std::endl
	      << "\tProcess Pre " << interactionPre->GetProcessName()
	      << " type " << theStepProcess[theStepN] << " " << interactionPre->GetProcessTypeName(G4ProcessType(theStepProcess[theStepN]))
	      << std::endl
	      << "\tProcess Post " << interactionPost->GetProcessName()
	      << " type " << interactionPost->GetProcessType() << " " << interactionPost->GetProcessTypeName(G4ProcessType(interactionPost->GetProcessType()))
	      << std::endl;
    std::cout << "\tPre x = " << theInitialX[theStepN]
	      << "\ty = "     << theInitialY[theStepN]
	      << "\tz = "     << theInitialZ[theStepN] 
	      << "\tPolar Radius = " << sqrt(prePos.x()*prePos.x()+prePos.y()*prePos.y())
	      << "\tPt = "     << theStepInitialPt[theStepN]
	      << "\tEnergy = " << theStepInitialEnergy[theStepN]
      //	      << std::endl
      //	      << "B-field(T) at Pre (cm): " << field->fieldInTesla(GlobalPoint(pos.x()/10.,pos.y()/10.,pos.z()/10.))
	      << std::endl;
    std::cout  << "\tPost x = " << theFinalX[theStepN]
	       << "\ty = "      << theFinalY[theStepN]
	       << "\tz = "      << theFinalZ[theStepN] 
	       << "\tPolar Radius = " << sqrt(postPos.x()*postPos.x()+postPos.y()*postPos.y())
	      << "\tPt = "     << theStepFinalPt[theStepN]
	       << "\tEnergy = " << theStepFinalEnergy[theStepN]
	       << std::endl;
    std::cout << "\tvolume " << volumeID << " " << theVolumeName[theStepN] 
	      << " copy number " << theVolumeCopy[theStepN]
	      << "\tmaterial " << theMaterialID[theStepN] << " " << theMaterialName[theStepN]
	      << "\tX0 = " << theMaterialX0[theStepN] << " mm"
	      << std::endl;
    std::cout << "\t\tParticle "  << theStepID[theStepN] 
	      << " Initial Pt = " << theStepInitialPt[theStepN]     << " MeV/c"
	      << " eta = "        << theStepInitialEta[theStepN]
	      << " phi = "        << theStepInitialPhi[theStepN]
	      << " Energy = "     << theStepInitialEnergy[theStepN] << " MeV"
	      << " Beta = "       << theStepInitialBeta[theStepN]
	      << " Gamma = "      << theStepInitialGamma[theStepN]
	      << std::endl
	      << "\t\tParticle "  << theStepID[theStepN]
	      << " Final Pt = "   << theStepFinalPt[theStepN]       << " MeV/c"
	      << " eta = "        << theStepFinalEta[theStepN]
	      << " phi = "        << theStepFinalPhi[theStepN]
	      << " Energy = "     << theStepFinalEnergy[theStepN]   << " MeV"
	      << " Beta = "       << theStepFinalBeta[theStepN]
	      << " Gamma = "      << theStepFinalGamma[theStepN]
	      << std::endl;
    std:: cout << "\tVolume Centre x = " << theVolumeX[theStepN]
	       << "\ty = "               << theVolumeY[theStepN]
	       << "\tz = "               << theVolumeZ[theStepN]
	       << "\tPolar Radius = "    << sqrt( theVolumeX[theStepN]*theVolumeX[theStepN] +
						  theVolumeY[theStepN]*theVolumeY[theStepN] )
	       << std::endl;
    std::cout << "\tx axis = (" 
	      << theVolumeXaxis1[theStepN] << "," 
	      << theVolumeXaxis2[theStepN] << "," 
	      << theVolumeXaxis3[theStepN] << ")"
	      << std::endl;
    std::cout << "\ty axis = (" 
	      << theVolumeYaxis1[theStepN] << "," 
	      << theVolumeYaxis2[theStepN] << "," 
	      << theVolumeYaxis3[theStepN] << ")"
	      << std::endl;
    std::cout << "\tz axis = (" 
	      << theVolumeZaxis1[theStepN] << "," 
	      << theVolumeZaxis2[theStepN] << "," 
	      << theVolumeZaxis3[theStepN] << ")"
	      << std::endl;
  }
  
  theTrkLen = aStep->GetTrack()->GetTrackLength();
  //-  std::cout << " theTrkLen " << theTrkLen << " theTrkLen2 " << theTrkLen2 << " postPos " << postPos.mag() << postPos << std::endl;
  thePVname = pv->GetName();
  thePVcopyNo = pv->GetCopyNo();
  theRadLen = radlen;
  theTotalMB += dmb;
  
  // rr
  theSupportMB     += (dmb * theSupportFractionMB);
  theSensitiveMB   += (dmb * theSensitiveFractionMB);
  theCablesMB      += (dmb * theCablesFractionMB);
  theCoolingMB     += (dmb * theCoolingFractionMB);
  theElectronicsMB += (dmb * theElectronicsFractionMB);
  theOtherMB       += (dmb * theOtherFractionMB);
  theAirMB         += (dmb * theAirFractionMB);
  // rr
  
  theStepN++;
  
}

