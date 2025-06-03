#include <iostream>
#include <string>

class employe {
  protected:
    std::string name;
  public:
    employe(std::string name) {
      this->name = name;
    }
};

class secretary : public employe {
  public:
    using employe::employe;
    void call(secretary calle) {
      std::cout << "Hi, " << calle.name << "\n It's " << name << "." << std::endl;
    }
};

int main() {
  secretary mark { "Mark" }, lee { "Lee" };
  lee.call(mark);
  return 0;
}
