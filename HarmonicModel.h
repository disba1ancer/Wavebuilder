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
 * File:   HarmonicModel.h
 * Author: disba1ancer
 *
 * Created on 11 марта 2018 г., 14:27
 */

#ifndef HARMONICMODEL_H
#define HARMONICMODEL_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/dataview.h>

#include "AbstractDataModel.h"

class HarmonicModel : public wxDataViewModel {
public:
	enum {
		COL_FREQ,
		COL_AMPL,
		COL_PHAS,
		COL_CNT
	};
	
	HarmonicModel(AbstractDataModel* dataModel);
	~HarmonicModel() override;
	bool IsContainer(const wxDataViewItem& item) const override;
	wxDataViewItem GetParent(const wxDataViewItem& item) const override;
	unsigned int GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;
	unsigned int GetColumnCount() const override;
	wxString GetColumnType(unsigned int col) const override;
	void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;
	bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;

private:
	AbstractDataModel* dataModel;
	std::function<void(AbstractDataModel::Action, unsigned)> dataModelHandler;
};

#endif /* HARMONICMODEL_H */

