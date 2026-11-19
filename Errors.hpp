#pragma once
#include <exception>
#include <string>

class FleetError : public std::exception {
private:
  std::string message_;
public:
  explicit FleetError(const std::string& message)
    : message_(message) {}
  const char* what() const noexcept override {
    return message_.c_str();
  }
};
class RegistrationError : public FleetError {
public:
  explicit RegistrationError(const std::string& message)
    : FleetError("Ошибка при регистрации: " + message) {}
};

class ValidationError : public FleetError {
public:
  explicit ValidationError(const std::string& message)
    : FleetError("Ошибка при вводе данных: " + message) {}
};

class SkillMissMatchError : public FleetError {
public:
  explicit SkillMissMatchError(const std::string& message)
    : FleetError("Недостаточно умений: " + message) {}
};

class InspectionError : public FleetError {
public:
  explicit InspectionError(const std::string& message)
    : FleetError("Отказ при техосмотре: " + message) {}
};