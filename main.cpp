#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <memory>
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

void printHelp() {
  std::cout << "Доступные команды:\n"
            << "  add bike <id> <name> <ease>\n"
            << "  add escooter <id> <name> <energy> <ease>\n"
            << "  add ebike <id> <name> <energy> <ease>\n"
            << "  add mcqueen <id> <name> <energy> <ease> <maxSpeed>\n"
            << "  add helmet <id> <name>\n"
            << "  add dockstation <id> <name> <energy>\n"
            << "  remove <id>\n"
            << "  list\n"
            << "  energy\n"
            << "  novice\n"
            << "  focus <id>\n"
            << "  show_focus\n"
            << "  log\n"
            << "  max_energy\n"
            << "  help\n"
            << "  quit\n";
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif

  ServiceCenter center;
  printHelp();

  std::string cmd;
  while (true) {
    std::cout << "> ";
    if (!(std::cin >> cmd) || cmd == "quit") {
      break;
    }

    try {
      if (cmd == "help") {
        printHelp();
      } else if (cmd == "add") {
        std::string type, id, name;
        std::cin >> type >> id >> name;

        if (type == "bike") {
          int ease = 0;
          std::cin >> ease;
          center.addItem(std::make_unique<Bike>(id, name, ease));
        } else if (type == "escooter") {
          double energy = 0.0;
          int ease = 0;
          std::cin >> energy >> ease;
          center.addItem(std::make_unique<EScooter>(id, name, energy, ease));
        } else if (type == "ebike") {
          double energy = 0.0;
          int ease = 0;
          std::cin >> energy >> ease;
          center.addItem(std::make_unique<EBike>(id, name, energy, ease));
        } else if (type == "mcqueen") {
          double energy = 0.0;
          int ease = 0, maxSpeed = 0;
          std::cin >> energy >> ease >> maxSpeed;
          center.addItem(std::make_unique<McQueen>(id, name, energy, ease, maxSpeed));
        } else if (type == "helmet") {
          center.addItem(std::make_unique<Helmet>(id, name));
        } else if (type == "dockstation") {
          double energy = 0.0;
          std::cin >> energy;
          center.addItem(std::make_unique<Dockstation>(id, name, energy));
        } else {
          throw ValidationError("Неизвестный тип объекта: " + type);
        }
        std::cout << "Объект успешно добавлен.\n";
      } else if (cmd == "remove") {
        std::string id;
        std::cin >> id;
        center.remove(id);
        std::cout << "Объект удалён.\n";
      } else if (cmd == "list") {
        center.list(std::cout);
      } else if (cmd == "energy") {
        std::cout << "Суммарное потребление энергии: " << center.totalEnergy() << "\n";
      } else if (cmd == "novice") {
        center.printNovice(std::cout);
      } else if (cmd == "focus") {
        std::string id;
        std::cin >> id;
        center.setFocus(id);
        std::cout << "Объект помещён на витрину.\n";
      } else if (cmd == "show_focus") {
        center.showFocus(std::cout);
      } else if (cmd == "log") {
        center.printReglist(std::cout);
      } else if (cmd == "max_energy") {
        center.printMaxEnergy(std::cout);
      } else {
        throw ValidationError("Неизвестная команда: " + cmd);
      }

    } catch (const FleetError& e) {
      std::cout << "Error: " << e.what() << "\n";
    } catch (const std::exception& e) {
      std::cout << "System error: " << e.what() << "\n";
    }
  }

  return 0;
}