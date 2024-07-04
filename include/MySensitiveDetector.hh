#ifndef MYSENSITIVEDETECTOR_HH
#define MYSENSITIVEDETECTOR_HH
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"

class MySensitiveDetector : public G4VSensitiveDetector {

public:
    MySensitiveDetector(const G4String& name);
    ~MySensitiveDetector();

    void Initialize(G4HCofThisEvent* hce);
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

private:
    // Define any necessary member variables or methods
};
#endif // MYSENSITIVEDETECTOR_HH
