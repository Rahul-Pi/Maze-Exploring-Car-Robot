/*
 * Copyright (C) 2018 Ola Benderius
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "behavior.hpp"


Behavior::Behavior() noexcept:
  m_frontUltrasonicReading{},
  m_rearUltrasonicReading{},
  m_leftIrReading{},
  m_rightIrReading{},
  m_leftWheelSpeedRequest{},
  m_rightWheelSpeedRequest{},
  m_frontUltrasonicReadingMutex{},
  m_rearUltrasonicReadingMutex{},
  m_leftIrReadingMutex{},
  m_rightIrReadingMutex{},
  m_leftWheelSpeedRequestMutex{},
  m_rightWheelSpeedRequestMutex{}
{
}

opendlv::proxy::WheelSpeedRequest Behavior::getLeftWheelSpeed() noexcept
{
  std::lock_guard<std::mutex> lock(m_leftWheelSpeedRequestMutex);
  return m_leftWheelSpeedRequest;
}

opendlv::proxy::WheelSpeedRequest Behavior::getRightWheelSpeed() noexcept
{
  std::lock_guard<std::mutex> lock(m_rightWheelSpeedRequestMutex);
  return m_rightWheelSpeedRequest;
}

void Behavior::setFrontUltrasonic(opendlv::proxy::DistanceReading const &frontUltrasonicReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_frontUltrasonicReadingMutex);
  m_frontUltrasonicReading = frontUltrasonicReading;
}

void Behavior::setRearUltrasonic(opendlv::proxy::DistanceReading const &rearUltrasonicReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_rearUltrasonicReadingMutex);
  m_rearUltrasonicReading = rearUltrasonicReading;
}

void Behavior::setLeftIr(opendlv::proxy::VoltageReading const &leftIrReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_leftIrReadingMutex);
  m_leftIrReading = leftIrReading;
}

void Behavior::setRightIr(opendlv::proxy::VoltageReading const &rightIrReading) noexcept
{
  std::lock_guard<std::mutex> lock(m_rightIrReadingMutex);
  m_rightIrReading = rightIrReading;
}


void Behavior::step() noexcept
{
  opendlv::proxy::DistanceReading frontUltrasonicReading;
  opendlv::proxy::DistanceReading rearUltrasonicReading;
  opendlv::proxy::VoltageReading leftIrReading;
  opendlv::proxy::VoltageReading rightIrReading;
  {
    std::lock_guard<std::mutex> lock1(m_frontUltrasonicReadingMutex);
    std::lock_guard<std::mutex> lock2(m_rearUltrasonicReadingMutex);
    std::lock_guard<std::mutex> lock3(m_leftIrReadingMutex);
    std::lock_guard<std::mutex> lock4(m_rightIrReadingMutex);

    frontUltrasonicReading = m_frontUltrasonicReading;
    rearUltrasonicReading = m_rearUltrasonicReading;
    leftIrReading = m_leftIrReading;
    rightIrReading = m_rightIrReading;
  }

  float frontDistance = frontUltrasonicReading.distance();
  //float rearDistance = rearUltrasonicReading.distance();
  double leftDistance = convertIrVoltageToDistance(leftIrReading.voltage());
  double rightDistance = convertIrVoltageToDistance(rightIrReading.voltage());
  
  
  float leftWheelSpeed=0.2f;
  float rightWheelSpeed=0.2f;
  
  if (0.11f<frontDistance) {
    leftWheelSpeed = 1.25f;
    rightWheelSpeed = 1.25f;
  }
  else if (0.2f < leftDistance) {
    leftWheelSpeed = -2.5f;
    rightWheelSpeed = 2.5f;
     
  }
  else if (0.2f < rightDistance) {
    leftWheelSpeed = 2.5f;
    rightWheelSpeed = -2.5f;
       
  }
  
  {
    std::lock_guard<std::mutex> lock1(m_leftWheelSpeedRequestMutex);
    std::lock_guard<std::mutex> lock2(m_rightWheelSpeedRequestMutex);

    opendlv::proxy::WheelSpeedRequest leftWheelSpeedRequest;
    leftWheelSpeedRequest.wheelSpeed(leftWheelSpeed);
    m_leftWheelSpeedRequest = leftWheelSpeedRequest;

    opendlv::proxy::WheelSpeedRequest rightWheelSpeedRequest;
    rightWheelSpeedRequest.wheelSpeed(rightWheelSpeed);
    m_rightWheelSpeedRequest = rightWheelSpeedRequest;
  }
}

// TODO: This is a rough estimate, improve by looking into the sensor specifications.
double Behavior::convertIrVoltageToDistance(float voltage) const noexcept
{
  double voltageDividerR1 = 1000.0;
  double voltageDividerR2 = 1000.0;

  double sensorVoltage = (voltageDividerR1 + voltageDividerR2) / voltageDividerR2 * voltage;
  //double sensorVoltage = voltage *5/1024;
  //double distance = 13/sensorVoltage;
  double distance = (2.5 - sensorVoltage) / 0.07;
  return distance;
}
