#pragma once

#include <iostream>
#include <vector>
#include <memory>


class Menu {
public:
    virtual int Execute() = 0;
    virtual ~Menu() = default;
};

class ListRequest : public Menu{
public:
    int Execute() override;
private:
    int Actions(std::vector<std::string>&);
};

class ListUsers : public Menu{
public:
    int Execute() override;
private:
    int Actions(std::vector<std::string>&);
    int UserChoice(std::vector<std::string> &list_user);
    int ActionChoise();
};

class TurnOff : public Menu {
public:
    int Execute() override;
};

class TurnOn : public Menu {
public:
    int Execute() override;
};


class MenuAction {
public:
    static auto CreateAct(int cmd) {
        switch (cmd) {
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