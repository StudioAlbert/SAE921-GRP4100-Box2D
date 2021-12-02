#include "contact_listener.h"

#include <iostream>

#include "game.h"
#include "userData.h"


MyContactListener::MyContactListener(Game& game) : game_(game)
{

}

void MyContactListener::BeginContact(b2Contact* contact)
{
    std::cout << "Contact Begin!" << std::endl;
    
    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    std::cout << "A Fixture : " << UserData::UserDataTypeToString(A_Data->getUserDataType()) << std::endl;
    std::cout << "B Fixture : " << UserData::UserDataTypeToString(B_Data->getUserDataType()) << std::endl;

    if(
        (A_Data->getUserDataType()==UserDataType::ASTEROID && B_Data->getUserDataType() == UserDataType::SHIP)
        || 
        (A_Data->getUserDataType() == UserDataType::SHIP && B_Data->getUserDataType() == UserDataType::ASTEROID))
    {
        game_.getShip().setDamages(5);

    }

}

void MyContactListener::EndContact(b2Contact* contact)
{
    std::cout << "Contact End!" << std::endl;

    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetUserData().pointer);

}
