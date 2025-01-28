#pragma once
#include <iostream>
#include <memory>
#include <vector>

class Menu {
public:
    virtual int Choice() = 0;
<<<<<<< HEAD
    virtual ~Menu() = default;
=======
    ~Menu() = default;
>>>>>>> 4306261216db8717a19a9653225e0fabff35af45
};

class ListRequest : public Menu{
public:
    int Choice() override;
private:
    int Actions(std::vector<std::string>&);
};

class ListUsers : public Menu{
public:
    int Choice() override;
private:
    int Actions(std::vector<std::string>&);
};

class TurnOff : public Menu {
public:
    int Choice() override;
};


class TurnOn : public Menu {
public:
    int Choice() override;
};

class MenuFactory {
public:
    static auto ChoiceFact(int point) {
        switch (point) {
            case 0:
                return std::unique_ptr<Menu>(new TurnOff());
            case 1:
                return std::unique_ptr<Menu>(new TurnOn());
            case 2:
                return std::unique_ptr<Menu>(new ListRequest());
            case 3:
                return std::unique_ptr<Menu>(new ListUsers());
            default:
                std::cout << "There is no such command, select an item from the suggested options" << std::endl;

        }
    }
};