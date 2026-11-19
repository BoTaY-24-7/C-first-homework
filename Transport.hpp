#pragma once
#include <ostream>
#include <string>
#include "Inventory.hpp"
#include "Errors.hpp"
#include <utility>

class Transport : virtual public InventoryItem {
protected:
  int ease;
public:
  Transport(std::string id, std::string name, int ease)
      : InventoryItem(std::move(id), std::move(name)), ease(ease) {
    if (ease <= 0 || ease > 10) {
      throw ValidationError("простота должна быть в диапазоне от 1 до 10");
    }
  }
  int getEaseScore() const { return ease; }
  virtual bool NoviceFriendly() const { return ease >= 6; }
};

class Bike : public Transport {
public:
  Bike(std::string id, std::string name, int ease)
      : InventoryItem(std::move(id), std::move(name)), 
        Transport("g", "g", ease) {}
  void describe(std::ostream& os) const override {
    os << "Bike: " << getName()
       << " ID: " << getId()
       << ", Ease: " << ease;
  }
};

class EScooter : public Transport, public EnergyConsumer {
public:
  EScooter(std::string id, std::string name, double energy, int ease)
      : InventoryItem(std::move(id), std::move(name)),
        EnergyConsumer("g", "g", energy),
        Transport("g", "g", ease) {}
  void describe(std::ostream& os) const override {
    os << "EScooter: " << getName()
       << " ID: " << getId()
       << ", Energy: "<< dailyEnergy()
       << ", Ease: " << ease;
  }
};

class EBike : public Transport, public EnergyConsumer {
public:
  EBike(std::string id, std::string name, double energy, int ease)
      : InventoryItem(std::move(id), std::move(name)),
        EnergyConsumer("g", "g", energy),
        Transport("g", "g", ease) {}
  void describe(std::ostream& os) const override {
    os << "EBike: " << getName()
       << " ID: " << getId()
       << ", Energy: "<< dailyEnergy()
       << ", Ease: " << ease;
  }
};

class McQueen : public Transport, public EnergyConsumer {
private:
  int maxSpeed_;
public:
  McQueen(std::string id, std::string name, double energy, int ease, int maxSpeed)
      : InventoryItem(std::move(id), std::move(name)),
        EnergyConsumer("g", "g", energy),
        Transport("g", "g", ease),
        maxSpeed_(maxSpeed) {
    if (maxSpeed_ <= 0) {
      throw ValidationError("Максимальная скорость должна быть положительной");
    }
  }

  double dailyEnergy() const override {
    if (maxSpeed_ <= 25) {
      return EnergyConsumer::dailyEnergy();
    }
    return (EnergyConsumer::dailyEnergy() * 1.5);
  }

  bool NoviceFriendly() const override {
    if (ease * 5 < maxSpeed_) {
      return false;
    }
    return true;
  }
  
  void describe(std::ostream& os) const override {
    os << "McQueen: " << getName()
       << " ID: " << getId()
       <<", Energy: " << dailyEnergy()
       << ", Ease: " << ease
       << ", NoviceFriendly:" << (NoviceFriendly() ? "Yes" : "No");
  }
};