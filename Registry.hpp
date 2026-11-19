#pragma once
#include <ostream>
#include <cstddef>
#include <vector>
#include "Errors.hpp"

template <typename T, std::size_t Cap>
class Registry {
private:
  std::vector<T> AllItems_;
public:
  Registry() {
    if (Cap == 0) {
      throw RegistrationError("Длина регистрационного листа не может быть нулевой");
    }
    AllItems_.reserve(Cap);
  }
  void add(const T& item) {
    if (AllItems_.size() < Cap) {
      AllItems_.push_back(item);
    } else {
      AllItems_.erase(AllItems_.begin());
      AllItems_.push_back(item);
    }
  }
  std::size_t size() const {
    return AllItems_.size();
  }

  void print(std::ostream& os) const {
    for (const auto& item : AllItems_) {
      os << item << "\n";
    }
  }
};
