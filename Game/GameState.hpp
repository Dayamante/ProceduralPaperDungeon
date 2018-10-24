#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/EntityHandle.hpp"
#include "../Engine/Core/World.hpp"

#include "FloorData.hpp"
#include "RoomData.hpp"
#include "Room.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager, const std::string& seed);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

		const std::string& getSeed() const;

		oe::Window& getWindow();
		oe::View& getView();

	private:
		oe::World mWorld;
		oe::ImGuiDataViewer mDataViewer;
		//oe::ImGuiProfiler mProfiler;

		std::string mSeed;
		unsigned int mLevel;

		FloorData::Ptr mFloorData;

        Room::Ptr mCurrentRoom;
};

#endif // GAMESTATE_HPP
