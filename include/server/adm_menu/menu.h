#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <memory>

constexpr std::string kCmdTable {"commands_table"};


class Menu {
public:
    virtual int Execute() = 0;
    virtual ~Menu() = default;
};

class ListRequest : public Menu{
public:
    int Execute() override;
private:
    int Actions();
    int RequestChoice();
    int ActionChoise();
private:
    std::vector<std::string> list_requests_;
};

class ListUsers : public Menu{
public:
    int Execute() override;
private:
    void Preparing_the_list();
    void Output_the_list();
    int Actions();
    int UserChoice();
    int ActionChoise();
    int RequestChoice();
    std::string ReturnNameCmd (int id_cmd);
private:
    std::vector<std::string> list_users_;
    std::vector<std::string> list_names_columns_ {"ID command", "Name command"};
    std::map<std::string, std::string> list_types_columns {{"ID command", "INTEGER"}, {"Name command", "TEXT"}};
    int id_cmd_min_ {1};
    int id_cmd_max_ {2};
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