#include "RoomData.hpp"

RoomData::RoomData()
    : mRoomIndex(0)
    , mRoomX(0)
    , mRoomY(0)
    , mDoorFlags(DoorFlags::None)
    , mConnections()
    , mStains()
{
}

RoomData::RoomData(unsigned int roomIndex, int x, int y)
    : mRoomIndex(roomIndex)
    , mRoomX(x)
    , mRoomY(y)
    , mDoorFlags(DoorFlags::None)
    , mConnections()
    , mStains()
{
}

RoomData::~RoomData()
{
}

unsigned int RoomData::getRoomIndex() const
{
    return mRoomIndex;
}

int RoomData::getRoomX() const
{
    return mRoomX;
}

int RoomData::getRoomY() const
{
    return mRoomY;
}

void RoomData::addConnection(DoorFlags doorFlag, unsigned int destinationIndex)
{
    mDoorFlags = mDoorFlags | doorFlag;
    mConnections[doorFlag] = destinationIndex;
}

unsigned int RoomData::getConnectionIndex(DoorFlags doorFlag) const
{
    if (mConnections.find(doorFlag) == mConnections.end())
    {
        return 0;
    }
    return mConnections.at(doorFlag);
}

RoomData::DoorFlags RoomData::getDoorFlags() const
{
    return mDoorFlags;
}

unsigned int RoomData::getDoorAmount() const
{
    return mConnections.size();
}

void RoomData::addStain(int type, float x, float y, float scale, float angle)
{
    Stain stain;
    stain.type = type;
    stain.x = x;
    stain.y = y;
    stain.scale = scale;
    stain.angle = angle;
    mStains.push_back(stain);
}

const RoomData::Stain& RoomData::getStain(unsigned int index) const
{
    return mStains[index];
}

unsigned int RoomData::getStainCount() const
{
    return mStains.size();
}
