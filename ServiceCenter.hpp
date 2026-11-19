#pragma once
#include <ostream>
#include <string>
#include <vector>
#include <cctype>
#include <memory>
#include <utility>
#include <algorithm>

#include "Registry.hpp"
#include "Errors.hpp"
#include "Inventory.hpp"
#include "Transport.hpp"
#include "Things.hpp"


class ServiceCenter {
private:
  std::vector<std::shared_ptr<InventoryItem>> Park_;
  std::weak_ptr<InventoryItem> focusItem_;
  Registry<std::string, 10> Reglist_;
  void inspectBroken(const InventoryItem& item) const {
    std::string lowerName = item.getName();
    if (item.getName().size() >= 6) {
      for (char& ch : lowerName) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
      }
      for (int i = 0; i < item.getName().size() - 5; ++i) {
        if (lowerName.substr(i, 6) == "broken") {
          throw InspectionError("Предмет сломан");
        }
      }
    } 
  }

  void exist(const std::string& id) const {
    for (std::size_t i = 0; i < Park_.size(); ++i) {
      if ((Park_[i])->getId() == id) {
        throw RegistrationError("Элемент с таким Id уже существует");
      }
    }
  }
public:
  ServiceCenter() = default;
  void addItem(std::unique_ptr<InventoryItem> item) {
    if (item == nullptr) {
      throw ValidationError("Пустой предмет");
    }
    exist(item->getId());
    inspectBroken(*item);
    Park_.push_back(std::shared_ptr<InventoryItem>(std::move(item)));
    Reglist_.add("Добавлен: " + Park_.back()->getId());
  }

  void remove(const std::string& id) {
    for (auto iter = Park_.begin(); iter != Park_.end(); ++iter) {
      if ((*iter)->getId() == id) {
        Park_.erase(iter);
        Reglist_.add("Удалён: " + id);
        return;
      }
    }
    throw ValidationError("Элемент с таким Id не найден");
  }

  void list(std::ostream& os) const {
    std::vector<std::shared_ptr<InventoryItem>> sortedPark = Park_;
    std::sort(sortedPark.begin(), sortedPark.end(),
             [](const std::shared_ptr<InventoryItem> a,
                const std::shared_ptr<InventoryItem> b) { return *a < *b; });
    os << "Инвентарный лист:\n";
    for (int i = 0; i < sortedPark.size(); ++i) {
      os << *(sortedPark[i]) << ", \n";
    }
  }
  double totalEnergy() const {
    double sum = 0.0;
    for (const auto& item : Park_) {
      if (auto* itemSee = dynamic_cast<EnergyConsumer*>(item.get())) {
        sum += itemSee->dailyEnergy();
      }
    }
    return sum;
  }
  void printNovice(std::ostream& os) const {
    os << "Транспорт для новичков:\n";
    for (const auto& item : Park_) {
      if (auto* itemSee = dynamic_cast<Transport*>(item.get())) {
        if (itemSee->NoviceFriendly()) {
          os << *item << ", \n";
        }
      }
    }
  }
  void setFocus(const std::string& id) {
    for (const auto& item : Park_) {
      if (item->getId() == id) {
        focusItem_ = item;
        Reglist_.add("В фокусе: " + id);
        return;
      }
    }
    throw ValidationError("Элемент с таким Id нет");
  }

  void showFocus(std::ostream& os) const {
    auto ptr = focusItem_.lock();
    if (ptr) {
      os << "Витрина: " << *ptr << "\n";
    } else {
      os << "Витрина пуста или объект уже удалён\n";
    }
  }

  void printReglist(std::ostream& os) const {
    os << "Журнал операций:\n";
    Reglist_.print(os);
  }

  void printMaxEnergy(std::ostream& os) const {
    std::shared_ptr<InventoryItem> maxItem = nullptr;
    double maxVal = -1.0;

    for (const auto& item : Park_) {
      if (auto* consumer = dynamic_cast<EnergyConsumer*>(item.get())) {
        double energy = consumer->dailyEnergy();
        if (energy > maxVal) {
          maxVal = energy;
          maxItem = item;
        }
      }
    }

    if (maxItem) {
      os << "Максимальное потребление энергии (" << maxVal
         << "): " << *maxItem << "\n";
    } else {
      os << "В парке нет энергопотребляющих объектов\n";
    }
  }
};