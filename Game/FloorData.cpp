#include "FloorData.hpp"

#include "../Engine/System/String.hpp"
#include "../Engine/Math/Random.hpp"

#include <functional>
#include <string>

#include "GameConfig.hpp"

FloorData::FloorData(const std::string& globalSeed, unsigned int level)
    : mSeedNum(0)
    , mSeed(globalSeed + oe::toString(level))
    , mLevel(level)
{
    std::hash<std::string> hasher;
    mSeedNum = hasher(mSeed);
    printf("%s : %d\n", mSeed.c_str(), mSeedNum);
    oe::Random::setSeed(mSeedNum);

    generateRoomGrid();
    generateDoors();
    generateRooms();
}

FloorData::~FloorData()
{
}

const std::string& FloorData::getSeed() const
{
    return mSeed;
}

unsigned int FloorData::getLevel() const
{
    return mLevel;
}

unsigned int FloorData::getRoomCount() const
{
    return mRoomData.size();
}

RoomData& FloorData::getRoomData(unsigned int index)
{
    return mRoomData[index];
}

void FloorData::generateRoomGrid()
{
    unsigned int roomNumber = mLevel + oe::Random::get<unsigned int>(6, 10);
    unsigned int currentIndex = 1;

    mRoomData.emplace_back(0, 0, 0);

    while (currentIndex <= roomNumber)
    {
        int currentAccessIndex = oe::Random::get<int>(0, mRoomData.size() - 1);
        RoomData& currentRoomData = mRoomData[currentAccessIndex];

        // Top
        bool alreadyCreatedTopDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() - 1);
        bool blockedBySquareOneTopDoor = isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY() - 1) && isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY());
        bool blockedBySquareTwoTopDoor = isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY() - 1) && isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY());
        bool canGenerateTopDoor = !alreadyCreatedTopDoor && !blockedBySquareOneTopDoor && !blockedBySquareTwoTopDoor;
        if (canGenerateTopDoor && 25.0f > oe::Random::get<float>(0.0f, 100.0f))
        {
            mRoomData.emplace_back(currentIndex, currentRoomData.getRoomX(), currentRoomData.getRoomY() - 1);
            currentIndex++;
        }

        // Right
        bool alreadyCreatedRightDoor = isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY());
        bool blockedBySquareOneRightDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() - 1) && isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY() - 1);
        bool blockedBySquareTwoRightDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() + 1) && isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY() + 1);
        bool canGenerateRightDoor = !alreadyCreatedRightDoor && !blockedBySquareOneRightDoor && !blockedBySquareTwoRightDoor;
        if (canGenerateRightDoor && 25.0f > oe::Random::get<float>(0.0f, 100.0f))
        {
            mRoomData.emplace_back(currentIndex, currentRoomData.getRoomX() + 1, currentRoomData.getRoomY());
            currentIndex++;
        }

        // Bottom
        bool alreadyCreatedBottomDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() + 1);
        bool blockedBySquareOneBottomDoor = isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY() + 1) && isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY());
        bool blockedBySquareTwoBottomDoor = isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY() + 1) && isRoomCreated(currentRoomData.getRoomX() + 1, currentRoomData.getRoomY());
        bool canGenerateBottomDoor = !alreadyCreatedBottomDoor && !blockedBySquareOneBottomDoor && !blockedBySquareTwoBottomDoor;
        if (canGenerateBottomDoor && 25.0f > oe::Random::get<float>(0.0f, 100.0f))
        {
            mRoomData.emplace_back(currentIndex, currentRoomData.getRoomX(), currentRoomData.getRoomY() + 1);
            currentIndex++;
        }

        // Left
        bool alreadyCreatedLeftDoor = isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY());
        bool blockedBySquareOneLeftDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() - 1) && isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY() - 1);
        bool blockedBySquareTwoLeftDoor = isRoomCreated(currentRoomData.getRoomX(), currentRoomData.getRoomY() + 1) && isRoomCreated(currentRoomData.getRoomX() - 1, currentRoomData.getRoomY() + 1);
        bool canGenerateLeftDoor = !alreadyCreatedLeftDoor && !blockedBySquareOneLeftDoor && !blockedBySquareTwoLeftDoor;
        if (canGenerateLeftDoor && 25.0f > oe::Random::get<float>(0.0f, 100.0f))
        {
            mRoomData.emplace_back(currentIndex, currentRoomData.getRoomX() - 1, currentRoomData.getRoomY());
            currentIndex++;
        }
    }
}

void FloorData::generateDoors()
{
    for (unsigned int i = 0; i < mRoomData.size(); i++)
    {
        RoomData& currentRoom = mRoomData[i];
        unsigned int roomIndex;
        if (isRoomCreated(currentRoom.getRoomX(), currentRoom.getRoomY() - 1, &roomIndex))
        {
            currentRoom.addConnection(RoomData::Top, roomIndex);
        }
        if (isRoomCreated(currentRoom.getRoomX() + 1, currentRoom.getRoomY(), &roomIndex))
        {
            currentRoom.addConnection(RoomData::Right, roomIndex);
        }
        if (isRoomCreated(currentRoom.getRoomX(), currentRoom.getRoomY() + 1, &roomIndex))
        {
            currentRoom.addConnection(RoomData::Bottom, roomIndex);
        }
        if (isRoomCreated(currentRoom.getRoomX() - 1, currentRoom.getRoomY(), &roomIndex))
        {
            currentRoom.addConnection(RoomData::Left, roomIndex);
        }
    }
}

void FloorData::generateRooms()
{
    for (unsigned int i = 0; i < mRoomData.size(); i++)
    {
        int numStains = oe::Random::get<int>(0, 2);
        for (int j = 0; j < numStains; j++)
        {
            int type = oe::Random::get<int>(0, 3);
            float x = oe::Random::get<float>(0.0f, WINSIZEX);
            float y = oe::Random::get<float>(0.0f, WINSIZEY);
            float scale = oe::Random::get<float>(0.5f, 1.8f);
            float angle = oe::Random::get<float>(0.0f, 360.0f);
            mRoomData[i].addStain(type, x, y, scale, angle);
        }
    }
}

bool FloorData::isRoomCreated(int x, int y, unsigned int* roomIndex) const
{
    for (unsigned int i = 0; i < mRoomData.size(); i++)
    {
        if (mRoomData[i].getRoomX() == x && mRoomData[i].getRoomY() == y)
        {
            if (roomIndex)
            {
                *roomIndex = mRoomData[i].getRoomIndex();
            }
            return true;
        }
    }
    return false;
}