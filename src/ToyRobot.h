#pragma once

#include "Transform.h"

class ToyRobot
{
public:
	/**
	 * @brief   Intentionally not using enum class here since this enum is used in bitwise
	 *          and would need to static_cast to int everywhere its used, which arguably becomes more 
	 *          difficult to write and read
	 *          
	 *          TRANSFORM example: 1,2,EAST
	 *          TABLE_VIEW example: 
	 *             . . . . .
	 *             . . . . .
	 *             . > . . .
	 *             . . . . .
	 *             . . . . .
	 *           VERBOSE additional logging
	*/
	enum ReportFlags
	{
		TRANSFORM = 0x1,
		TABLE_VIEW = 0x2,
		VERBOSE = 0x4
	};
	/**
	 * @brief Construct a new Toy Robot object that has not yet been placed
	 */
	ToyRobot();

	/**
	 * @brief Check if robot has been placed
	 * 
	 * @return true if robot has been placed
	 * @return false if robot has not been placed
	 */
	bool isPlaced() const;

	/**
	 * @brief Send to standard output the co-ordinates and heading of the robot.
	 *        Also outputs a top-down view of the table to standard output
	 */

	/**
	 * @brief 
	 * @param flags Optional information the report should generate. By default we show 
	 *              the transform output and a view of the table
	*/
	void report(int reportFlags = ReportFlags::TRANSFORM ) const;

	/**
	 * @brief
	 * @param flags Optional information the report should generate. By default we show
	 *              the transform output and a view of the table
	*/
	std::string generateReport(int reportFlags = ReportFlags::TRANSFORM ) const;

	/**
	 * @brief Place the robot on the table via a Transform (position and direction)
	 *        This will fail (return false) if attempting to place outside the bounds
	 *        of the table.
	 * 
	 * @param transform 
	 * @return true if place action was successful
	 * @return false if place action failed
	 */
	bool place(const Transform& transform);

	/**
	 * @brief Rotate the robot clockwise or counter-clockwise by 90 degrees
	 *        Rotation will have no effect if robot has not been placed
	 * 
	 * @param rotateDir enum LEFT (counter-clockwise) or RIGHT (clockwise)
	 * @return true on rotation success
	 * @return false on rotation failure (robot has not been placed)
	 */
	bool rotate(const enums::RotateDir& rotateDir);

	/**
	 * @brief Move the robot forward one position in the direction of its Transform's heading
	 *        Move will fail if the robot has not been placed.
	 *        Move will also fail if the move would result in the robot leaving the table space.
	 * @return true if move succeeded
	 * @return false if move failed
	 */
	bool move();

	// getters to facilitate unit tests.
	Position getPosition()
	{
		return m_transform.pos;
	}

	enums::Direction getDirection()
	{
		return m_transform.dir;
	}

	Transform getTransform()
	{
		return m_transform;
	}

private:

	// hold the position and heading (rotation) data
	Transform m_transform;
};

std::ostream& operator<<(std::ostream& os, const ToyRobot& tr_);