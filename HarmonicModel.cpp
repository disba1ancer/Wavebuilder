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
 * File:   HarmonicModel.cpp
 * Author: disba1ancer
 * 
 * Created on 11 марта 2018 г., 14:27
 */

#include "HarmonicModel.h"

HarmonicModel::HarmonicModel(AbstractDataModel* dataModel) : dataModel(dataModel)
{
	dataModelHandler = [this](AbstractDataModel::Action action, unsigned index) {
		switch (action) {
			case AbstractDataModel::ACT_DESTROY:
				this->dataModel = 0;
				break;
			case AbstractDataModel::ACT_CHANGE:
				this->ItemChanged(wxDataViewItem(reinterpret_cast<void*>(index + 1)));
				break;
			case AbstractDataModel::ACT_ADD:
				this->ItemAdded(wxDataViewItem(0), wxDataViewItem(reinterpret_cast<void*>(index + 1)));
				break;
			default:
				this->Cleared();
		}
	};
	dataModel->registerObserver(dataModelHandler);
}

HarmonicModel::~HarmonicModel() {
	if (dataModel) {
		dataModel->unregisterObserver(dataModelHandler);
		dataModel = 0;
	}
}

bool HarmonicModel::IsContainer(const wxDataViewItem& item) const {
	if (dataModel)
		return !item.IsOk();
	return false;
}

wxDataViewItem HarmonicModel::GetParent(const wxDataViewItem& item) const {
	return wxDataViewItem();
}

unsigned int HarmonicModel::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const {
	if (dataModel) {
		auto count = dataModel->elementsCount();
		for (unsigned i = 0; i < count; ++i) {
			children.push_back(wxDataViewItem(reinterpret_cast<void*>(i + 1)));
		}
		return count;
	}
	return 0;
}

unsigned int HarmonicModel::GetColumnCount() const {
	return COL_CNT;
}

wxString HarmonicModel::GetColumnType(unsigned int col) const {
	return "double";
}

void HarmonicModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const {
	if (item.IsOk()) {
		auto val = dataModel->readElement(reinterpret_cast<unsigned>(item.GetID()) - 1);
		switch (col) {
			case COL_FREQ:
				variant = val.freq;
				break;
			case COL_AMPL:
				variant = val.ampl;
				break;
			case COL_PHAS:
				variant = val.phase;
				break;
		}
	}
}

bool HarmonicModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) {
	if (col < COL_CNT && item.IsOk()) {
		auto elemNum = reinterpret_cast<unsigned>(item.GetID()) - 1;
		auto elem = dataModel->readElement(elemNum);
		switch (col) {
			case COL_FREQ:
				elem.freq = static_cast<double>(variant);
				break;
			case COL_PHAS:
				elem.phase = static_cast<double>(variant);
				break;
			case COL_AMPL:
				elem.ampl = static_cast<double>(variant);
				break;
		}
		dataModel->changeElement(elemNum, elem);
		return true;
	}
	return false;
}

