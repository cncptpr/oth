#include <condition_variable>
#include <iostream>
#include <memory>
#include <string>
#include <sys/types.h>

enum gattung {
  Gliedertier = 1,
  Vogel,
  Saeugetier,
  Weichtier,
  Fisch,
  Kriechtier
};

class tier {
protected:
  std::string name;
  int anzahlBeine;
  bool carnivor;
  int flossen;
  enum gattung gattung;

public:
  tier(std::string name, enum gattung gattung)
      : tier(name, 4, gattung, true, 0) {};
  tier(std::string name, int beine, enum gattung gattung, bool carnivor)
      : tier(name, beine, gattung, carnivor, 0) {};
  tier(std::string name, int anzahlBeine, enum gattung gattung, bool carnivor,
       int flossen)
      : name(name), anzahlBeine(anzahlBeine), gattung(gattung),
        carnivor(carnivor), flossen(flossen) {};
  void beschreibungAusgeben() {
    std::cout << name << " hat " << anzahlBeine << " Beine.\n";
  }
  bool paarung(tier mit) {
    if (gattung == mit.gattung) {
      std::cout << "Paarung erfolg! " << name << " 💕  " << mit.name << "\n";
      return true;
    }
    return false;
  }
  bool jagen() {
    if (carnivor)
      std::cout << name << " geht auf die Jagd.\n";
    else
      std::cout << name << " will nicht jagen.\n";
    return carnivor;
  }
  bool schwimmen() {
    if (flossen)
      std::cout << name << " schwimmt.\n";
    else
      std::cout << name << " ertrinkt.\n";
    return flossen;
  }
};

class insekt : public tier {
protected:
  int fluegel;

public:
  using tier::tier;
  insekt(std::string name, int beine, int fluegel, bool carnivor)
      : tier(name, beine, Gliedertier, carnivor, 0), fluegel(fluegel) {};
  bool kannFliegen() { return fluegel > 1; }
  void beschreibungAusgeben() {
    std::cout << name << " hat " << anzahlBeine << " Beine und kann "
              << (kannFliegen() ? "" : "nicht ") << "Fliegen.\n";
  }
  void paarung(tier mit) {
    if (tier::paarung(mit) && name.starts_with("Spinne")) {
      std::cout << "Paarung und Nahrung!\n";
    }
  }
};

int main() {
  tier nemo("Fish Nemo", 0, Fisch, false, 5), cujo("Hund Cujo", Saeugetier);
  insekt tusnelda("Spinne Tusnelda", 8, 0, true),
      schnuck("Libelle Schnuck", 6, 4, true);
  nemo.beschreibungAusgeben();
  cujo.beschreibungAusgeben();
  tusnelda.beschreibungAusgeben();
  schnuck.beschreibungAusgeben();
  nemo.paarung(cujo);
  tusnelda.paarung(schnuck);
  nemo.schwimmen();
  tusnelda.schwimmen();
  cujo.jagen();
  nemo.jagen();
  std::cout << std::endl;
  return 0;
}
