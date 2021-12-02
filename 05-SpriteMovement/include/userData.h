#pragma once

#include <string>

#include "box2d/box2d.h"

enum UserDataType : char
{
    SHIP = 's',
    LIMIT = 'l',
    ASTEROID = 'a',
    MISSILE = 'n',
    NONE

};

class UserData
{
public:
    UserData();
    UserData(UserDataType type_);

    static const std::string UserDataTypeToString(UserDataType type_);

    UserDataType getUserDataType();

private:
    UserDataType m_type;
};
