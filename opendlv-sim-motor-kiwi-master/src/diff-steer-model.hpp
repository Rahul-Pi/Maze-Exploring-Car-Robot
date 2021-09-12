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

#ifndef DIFF_STEER_MODEL
#define DIFF_STEER_MODEL

#include <mutex>

#include "opendlv-standard-message-set.hpp"

class DiffSteerModel {
 private:
  DiffSteerModel(DiffSteerModel const &) = delete;
  DiffSteerModel(DiffSteerModel &&) = delete;
  DiffSteerModel &operator=(DiffSteerModel const &) = delete;
  DiffSteerModel &operator=(DiffSteerModel &&) = delete;

 public:
  DiffSteerModel() noexcept;
  ~DiffSteerModel() = default;

 public:
  void setLeftWheelSpeed(opendlv::proxy::WheelSpeedRequest const &) noexcept;
  void setRightWheelSpeed(opendlv::proxy::WheelSpeedRequest const &) noexcept;
  opendlv::sim::KinematicState step(double) noexcept;

 private:
  std::mutex m_leftWheelSpeedMutex;
  std::mutex m_rightWheelSpeedMutex;
  double m_longitudinalSpeed;
  double m_lateralSpeed;
  double m_yawRate;
  float m_leftWheelSpeed;
  float m_rightWheelSpeed;
};

#endif
