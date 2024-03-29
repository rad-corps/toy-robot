#include "unitTests.h"
#include "unitTestFramework.h"
#include "ToyRobot.h"
#include "CommandParser.h"

namespace unit_tests
{
	void run()
	{
		INIT_TEST_FRAMEWORK();

		ADD_TEST("Command Parser",
		{
			app::CommandParser cp;
			IS_EQUAL( 
				cp.parseCommand("PLACE 1,1,EAST"), 
				enums::Command::PLACE, 
				"Place command matched expected" 
			);

			// PLACE command without parameters still evaluates to a place command
			// this is ok, as the next step to parse the parameters will fail
			IS_EQUAL( 
				cp.parseCommand("PLACE"),
				enums::Command::PLACE, 
				"Place command matched expected" 
			);

			IS_EQUAL( 
				cp.parseCommand("gdsjfkg4e9g489j 4g3. vsd, wrf w,fw 23"),
				enums::Command::INVALID_COMMAND, 
				"Invalid command" 
			);

			IS_EQUAL( 
				cp.parseCommand("LEFT"),
				enums::Command::LEFT, 
				"LEFT command" 
			);

			IS_EQUAL( 
				cp.parseCommand("RIGHT"),
				enums::Command::RIGHT, 
				"RIGHT command" 
			);

			IS_EQUAL( 
				cp.parseCommand("MOVE"),
				enums::Command::MOVE, 
				"MOVE command" 
			);

			IS_EQUAL( 
				cp.parseCommand("QUIT"),
				enums::Command::QUIT, 
				"QUIT command" 
			);

			{
				Transform t;
				IS_FALSE(cp.parsePlaceCommand("PLACE", t), "PLACE Command with no parameters");
				IS_FALSE(cp.parsePlaceCommand("PLACE 1", t), "PLACE Command with incorrect parameters");
				IS_FALSE(cp.parsePlaceCommand("PLACE 1,1", t), "PLACE Command with incorrect parameters");
				IS_FALSE(cp.parsePlaceCommand("PLACE 1,1,ASDJH", t), "PLACE Command with incorrect parameters");
				IS_FALSE(cp.parsePlaceCommand("PLACE das .d, 2,sd.", t), "PLACE Command with incorrect parameters");
				IS_TRUE(cp.parsePlaceCommand("PLACE 1,1,EAST", t), "PLACE Command with correct parameters");
				// even though this test case is out of bounds, it is still a parse-able command
				IS_TRUE(cp.parsePlaceCommand("PLACE 6,6,EAST", t), "PLACE Command with correct parameters");
			}
		});

		ADD_TEST("Place Robot Out Of Bounds",
		{
			ToyRobot tr;
			IS_FALSE(tr.isPlaced(), "Robot was not placed on construction");

			// test out of bounds placements
			tr.place(Transform{ Position{ -1, 0 }, enums::Direction::EAST });
			tr.place(Transform{ Position{ 0, -1 }, enums::Direction::EAST });
			tr.place(Transform{ Position{ 5, 0 }, enums::Direction::EAST });
			tr.place(Transform{ Position{ 0, 5 }, enums::Direction::EAST });
			IS_FALSE(tr.isPlaced(), "Robot was not placed in out of bounds positions");

			// test correct placement
			tr.place(Transform{ Position{ 0, 0 }, enums::Direction::EAST });
			IS_TRUE(tr.isPlaced(), "Robot was placed in 0,0 coordinates");
		});

		ADD_TEST("Move Robot Out Of Bounds 1",
		{
			// move off SOUTH bound
			{
				ToyRobot tr;
				Transform expected(Position(0, 0), enums::Direction::SOUTH);
				tr.place(expected);
				IS_FALSE(tr.move(), "Robot did not move off SOUTH table edge");
				IS_EQUAL(
					tr.getTransform(),
					expected,
					"Matched expected position after attempting to move out of SOUTH bounds"
				);
			}

			// move off WEST bound
			{
				ToyRobot tr;
				Transform expected(Position(0, 0), enums::Direction::WEST);
				tr.place(expected);
				IS_FALSE(tr.move(), "Robot did not move off WEST table edge");
				IS_EQUAL(
					tr.getTransform(),
					expected,
					"Matched expected position after attempting to move out of WEST bounds"
				);
			}

			// move off EAST bound
			{
				ToyRobot tr;
				Transform expected(Position(4, 4), enums::Direction::EAST);
				tr.place(expected);
				IS_FALSE(tr.move(), "Robot did not move off EAST table edge");
				IS_EQUAL(
					tr.getTransform(),
					expected,
					"Matched expected position after attempting to move out of WEST bounds"
				);
			}

			// move off NORTH bound
			{
				ToyRobot tr;
				Transform expected(Position(4, 4), enums::Direction::NORTH);
				tr.place(expected);
				IS_FALSE(tr.move(), "Robot did not move off NORTH table edge");
				IS_EQUAL(
					tr.getTransform(),
					expected,
					"Matched expected position after attempting to move out of NORTH bounds"
				);
			}
		});

		ADD_TEST("Rotate Robot Before Placement",
		{
			ToyRobot tr;
			Transform expected = tr.getTransform();
			for (int i = 0; i < 4; ++i)
			{
				IS_FALSE(tr.rotate(enums::RotateDir::RIGHT), "Robot did not rotate RIGHT as it has not been placed");
				IS_EQUAL(expected, tr.getTransform(), "Robot transform unchanged after " + std::to_string(i) + " RIGHT rotations");
			}

			for (int i = 0; i < 4; ++i)
			{
				IS_FALSE(tr.rotate(enums::RotateDir::LEFT), "Robot did not rotate LEFT as it has not been placed");
				IS_EQUAL(expected, tr.getTransform(), "Robot transform unchanged after " + std::to_string(i) + " LEFT rotations");
			}
		});

		// below test to get a cross section of primary flow.
		ADD_TEST("Move Around Table Primary Flow",
		{
			ToyRobot tr;
			// facing up ^
			tr.place(Transform(Position(0, 0), enums::Direction::NORTH));
			IS_TRUE(tr.move(), "Move should not fail to available table space");
			IS_EQUAL(Position(0,1), tr.getPosition(), "Check position 0,0");
			IS_EQUAL(enums::Direction::NORTH, tr.getDirection(), "Check direction NORTH");
			tr.move();
			tr.move();
			tr.move();
			IS_EQUAL(Position(0,4), tr.getPosition(), "Check position 0,4");
			// facing right > 
			tr.rotate(enums::RotateDir::RIGHT);
			IS_EQUAL(enums::Direction::EAST, tr.getDirection(), "Check direction EAST");
			tr.move();
			tr.move();
			tr.move();
			tr.move();
			IS_EQUAL(Position(4,4), tr.getPosition(), "Check position 4,4");
			// facing down via left rotation V
			tr.rotate(enums::RotateDir::LEFT);
			tr.rotate(enums::RotateDir::LEFT);
			tr.rotate(enums::RotateDir::LEFT);
			IS_EQUAL(enums::Direction::SOUTH, tr.getDirection(), "Check direction SOUTH");
			tr.move();
			tr.move();
			tr.move();
			tr.move();
			IS_EQUAL(Position(4,0), tr.getPosition(), "Check position 4,0");
			tr.rotate(enums::RotateDir::RIGHT);
			IS_EQUAL(enums::Direction::WEST, tr.getDirection(), "Check direction WEST");
			tr.rotate(enums::RotateDir::RIGHT);
			IS_EQUAL(enums::Direction::NORTH, tr.getDirection(), "Check direction NORTH");
		});

		RUN_TESTS();
	}
}
