#pragma once

#include <iostream>
#include <vector>
#include <memory>


class Menu {
public:
    virtual int execute() = 0;
    virtual ~Menu() = default;
};

class ListRequest : public Menu{
public:
    int execute() override;
private:
    int action(std::vector<std::string>&);
};

class ListUsers : public Menu{
public:
    int execute() override;
private:
    int action(std::vector<std::string>&);
};

class TurnOff : public Menu {
public:
    int execute() override;
};

class TurnOn : public Menu {
public:
    int execute() override;
};

class listInfoReq : public Menu {
public:
    int execute() override;
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
            case 4:
                return std::unique_ptr<Menu>(new listInfoReq());
            default:
                std::cout << "There is no such command, select an item from the suggested options" << std::endl;

        }
    }
};