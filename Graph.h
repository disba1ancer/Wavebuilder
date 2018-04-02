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
 * File:   Graph.h
 * Author: disba1ancer
 *
 * Created on 17 марта 2018 г., 19:59
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <functional>

class Graph : public wxControl {
public:
	Graph(wxWindow* parent, wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxControlNameStr);
	void setYEnd(float yEnd);
	float getYEnd() const;
	void setYStart(float yStart);
	float getYStart() const;
	void setXEnd(float xEnd);
	float getXEnd() const;
	void setXStart(float xStart);
	float getXStart() const;
    void setFunction(const std::function<float(float)>& f);
    std::function<float(float)> getFunction() const;
private:
	enum EditableField {
		FIELD_NONE,
		FIELD_XSTART,
		FIELD_XEND,
		FIELD_YSTART,
		FIELD_YEND
	};
	
	void changeEditingState(EditableField field);
	
	void onPaint(wxPaintEvent& evt);
	void onMouseDblClick(wxMouseEvent& evt);
	void onEditEnter(wxCommandEvent& evt);
	void onEditKeyDown(wxKeyEvent& evt);
	void onEditKillFocus(wxFocusEvent& evt);
	
	float xStart, xEnd, yStart, yEnd;
	std::function<float(float)> f;
	EditableField editMode;
	wxTextCtrl* edit;
};

#endif /* GRAPH_H */

