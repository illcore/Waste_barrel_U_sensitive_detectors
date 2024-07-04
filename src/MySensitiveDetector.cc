//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "math.h"
#include <iostream>
#include <fstream>
#include "MySensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
using namespace std;


MySensitiveDetector::MySensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name) {
}

MySensitiveDetector::~MySensitiveDetector() {
}

void MySensitiveDetector::Initialize(G4HCofThisEvent* hce) {
    // Initialize anything you need when a new event begins
}

G4bool MySensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
G4VPhysicalVolume* Volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
G4LogicalVolume* LogicalVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
G4Track* track = step->GetTrack();
const G4DynamicParticle* dynpar = track->GetDynamicParticle();
G4ParticleDefinition* particle = dynpar->GetDefinition();
G4double KineticEnergy = dynpar->GetKineticEnergy();
G4ThreeVector Momentum = dynpar->GetMomentum();
G4double MomenX = dynpar->GetMomentum().x();
G4double MomenY = dynpar->GetMomentum().y();
G4double MomenZ = dynpar->GetMomentum().z();
G4double MomentumMagnitude = sqrt(pow(MomenX,2)+pow(MomenY,2)+pow(MomenZ,2)); 
G4StepPoint* PostPoint = step->GetPostStepPoint();
G4ThreeVector Position = PostPoint->GetPosition();
G4double PosX = PostPoint->GetPosition().x()/cm;
G4double PosY = PostPoint->GetPosition().y()/cm;
G4double PosZ = PostPoint->GetPosition().z()/cm;
G4int TrackID = track->GetTrackID();
G4double TotalEnerDepo=step->GetTotalEnergyDeposit();
G4String ProcessName = PostPoint->GetProcessDefinedStep()->GetProcessName();
G4String ParticleName = particle->GetParticleName();
if (ParticleName == "mu+" || ParticleName == "mu-") {
if (ProcessName == "Transportation"){
std::ofstream CheckFile;
CheckFile.open("Hodoscopes.dat", std::ios::app);
CheckFile << TrackID << " " << PosX << " " << PosY << " " << PosZ << " " << KineticEnergy << " " << TotalEnerDepo << " " << Volume->GetName() << " " << ProcessName <<  G4endl;
CheckFile.close();
}
}
return true;
}
//....oooOO0OOooo......

