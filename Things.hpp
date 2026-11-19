#pragma once
#include <ostream>
#include <string>
#include "Inventory.hpp"
#include <utility>

class Things : virtual public InventoryItem {
public:
  Things(std::string id, std::string name)
    : InventoryItem(std::move(id), std::move(name)) {}
};

class Helmet: public Things {
public:
  Helmet(std::string id, std::string name)
    : InventoryItem(std::move(id), std::move(name)),
      Things("g", "g") {}
    void describe(std::ostream& os) const override {
      os << "Helmet: " << getName() << " ID: " << getId();
    } 
};

class Dockstation: public Things, public EnergyConsumer {
public:
  Dockstation(std::string id, std::string name, double energy)
    : InventoryItem(std::move(id), std::move(name)),
      EnergyConsumer("g", "g", energy),
      Things("g", "g") {}
    void describe(std::ostream& os) const override {
      os << "Dockstation: " << getName() << " ID: " << getId() << ", Energy: " << dailyEnergy();
    } 
};