#pragma once
#include <iostream>
#include <memory>

class Menu {
public:
    virtual void Choice() = 0;
    ~Menu() = default;
};

class ListRequest : public Menu{
public:
    void Choice() override;
    void Desicion();
};

class TurnOFF : public Menu {
public:
    void Choice() override;
};

class MenuFactory {
public:
    static auto ChoiceFact(int point) {
        switch (point) {
            case 0:
                return std::unique_ptr<Menu>(new TurnOFF());
            case 1:
                return std::unique_ptr<Menu>(new ListRequest());
            default:
                std::cout << "There is no such command, select an item from the suggested options" << std::endl;

        }
    }
};