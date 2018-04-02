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
 * File:   AbstractDataModel.h
 * Author: disba1ancer
 *
 * Created on 11 марта 2018 г., 17:49
 */

#ifndef ABSTRACTDATAMODEL_H
#define ABSTRACTDATAMODEL_H

#include <vector>
#include <functional>

constexpr float PI = 3.141592653589793f;

class AbstractDataModel {
public:
	struct element_t {
		float freq;
		float ampl;
		float phase;
	};
	
	enum Action {
		ACT_ADD,
		ACT_REMOVE,
		ACT_CLEAR,
		ACT_CHANGE,
		ACT_DESTROY
	};

	AbstractDataModel() noexcept;
	virtual ~AbstractDataModel() noexcept;
	unsigned add(const element_t& value) noexcept;
	bool remove(unsigned index) noexcept;
	bool clear() noexcept;
	bool changeElement(unsigned index, const element_t& value) noexcept;
	const element_t& readElement(unsigned index) const noexcept;
	unsigned elementsCount() const noexcept;
	bool registerObserver(std::function<void(Action, unsigned)>&) noexcept;
	bool unregisterObserver(std::function<void(Action, unsigned)>&) noexcept;
	float calculateY(float x) noexcept;
private:
	void notifyObservers(Action action, unsigned elem) noexcept;
	std::vector<element_t> data;
	std::vector<std::function<void(Action, unsigned)>*> observers;
};

#endif /* ABSTRACTDATAMODEL_H */

