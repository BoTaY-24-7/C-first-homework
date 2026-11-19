#pragma once
#include <string>
#include <ostream>
#include <utility>
#include "Errors.hpp"

struct ModelAbout {
  std::string fabricator;
  int maxSpeedKmH;
};

class InventoryItem {
protected:
  std::string id_;
  std::string name_;
public:
  InventoryItem(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {
    if (id_.empty() || name_.empty()) {
      throw ValidationError("ID и название не могут быть пустыми");
    }
  }

  bool operator<(const InventoryItem& other) const {
    return (id_ < other.id_);
  }
  virtual ~InventoryItem() = default;
  virtual void describe(std::ostream& os) const = 0;

  const std::string& getId() const { return id_; }
  const std::string& getName() const { return name_; }
};
inline std::ostream& operator<<(std::ostream& os, 
                                const InventoryItem& item) {
    item.describe(os);
    return os;
}

class EnergyConsumer : virtual public InventoryItem {
private:
  double dailyexp_;
public:
  EnergyConsumer(std::string id, std::string name, double energy) 
    : InventoryItem(std::move(id), std::move(name)), dailyexp_(energy) {
    if (energy < 0) {
      throw ValidationError("Потребление энергии не может быть отрицательным");
    }
  }
  virtual double dailyEnergy() const { return dailyexp_; }
};
