/*
 * Copyright (C) 2018 disba1ancer
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

/* 
 * File:   AbstractDataModel.cpp
 * Author: disba1ancer
 * 
 * Created on 11 марта 2018 г., 17:49
 */

#include <cmath>

#include "AbstractDataModel.h"

AbstractDataModel::AbstractDataModel() noexcept {
	
}

AbstractDataModel::~AbstractDataModel() noexcept {
	notifyObservers(ACT_DESTROY, ~0U);
}

unsigned AbstractDataModel::add(const element_t& value) noexcept {
	data.push_back(value);
	auto elemNum = data.size() - 1;
	notifyObservers(ACT_ADD, elemNum);
	return elemNum;
}

bool AbstractDataModel::remove(unsigned index) noexcept {
	data.erase(data.begin() + index);
	notifyObservers(ACT_REMOVE, ~0U);
	return true;
}

bool AbstractDataModel::clear() noexcept {
	data.clear();
	notifyObservers(ACT_CLEAR, ~0U);
	return true;
}

bool AbstractDataModel::changeElement(unsigned index, const element_t& value) noexcept {
	data.at(index) = value;
	notifyObservers(ACT_CHANGE, index);
	return true;
}

const AbstractDataModel::element_t& AbstractDataModel::readElement(unsigned index) const noexcept {
	return data.at(index);
}

unsigned AbstractDataModel::elementsCount() const noexcept {
	return data.size();
}

bool AbstractDataModel::registerObserver(std::function<void(Action, unsigned)>& observer) noexcept {
	observers.push_back(&observer);
	return true;
}

bool AbstractDataModel::unregisterObserver(std::function<void(Action, unsigned)>& in_observer) noexcept {
	auto iter = observers.begin();
	auto eiter = observers.end();
	for (auto observer = *iter; iter != eiter; ++iter) {
		if (observer == &in_observer) {
			observers.erase(iter);
			return true;
		}
	}
	return false;
}

void AbstractDataModel::notifyObservers(Action action, unsigned elem) noexcept {
	for (auto observer : observers) {
		(*observer)(action, elem);
	}
}

float AbstractDataModel::calculateY(float x) noexcept {
	auto rslt = 0.f;
	auto count = elementsCount();
	for (unsigned i = 0; i < count; ++i) {
		const auto& elem = readElement(i);
		rslt += sin(x * elem.freq * 2 * PI + PI * elem.phase / 180) * elem.ampl;
	}
	return rslt;
}

