#pragma once
#include <iostream>
#include <memory>
#include <vector>

class Menu {
public:
    virtual int Choice() = 0;
    virtual ~Menu() = default;
};

class ListRequest : public Menu{
public:
    int Choice() override;
    int Desicion(std::vector<std::string>&);
};

class ListUsers : public Menu{
public:
    int Choice() override;
    int Desicion(std::vector<std::string>&);
};
class TurnOFF : public Menu {
public:
    int Choice() override;
};

class MenuFactory {
public:
    static auto ChoiceFact(int point) {
        switch (point) {
            case 0:
                return std::unique_ptr<Menu>(new TurnOFF());
            case 1:
                return std::unique_ptr<Menu>(new ListRequest());
            case 2:
                return std::unique_ptr<Menu>(new ListUsers());
            default:
                std::cout << "There is no such command, select an item from the suggested options" << std::endl;

        }
    }
};