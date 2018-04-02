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
 * File:   Graph.cpp
 * Author: disba1ancer
 * 
 * Created on 17 марта 2018 г., 19:59
 */

#include "Graph.h"

enum {
	ID_Text = 1
};

Graph::Graph(wxWindow* parent, wxWindowID id,
		const wxPoint& pos,
		const wxSize& size, long style,
		const wxValidator& validator,
		const wxString& name):
wxControl(parent, id, pos, size, style | wxFULL_REPAINT_ON_RESIZE, validator, name), 
xStart(0), yStart(0), xEnd(1.f), yEnd(1.f),
editMode(FIELD_NONE),
edit(new wxTextCtrl(this, ID_Text))
{
	SetBackgroundColour(*wxBLACK);
	
	edit->Hide();
	edit->SetWindowStyleFlag(edit->GetWindowStyleFlag() | wxTE_PROCESS_ENTER);
	
	Bind(wxEVT_PAINT, &onPaint, this);
	Bind(wxEVT_LEFT_DCLICK, &onMouseDblClick, this);
	Bind(wxEVT_TEXT_ENTER, &onEditEnter, this, ID_Text);
	edit->Bind(wxEVT_KEY_DOWN, &onEditKeyDown, this);
	edit->Bind(wxEVT_KILL_FOCUS, &onEditKillFocus, this);
}

void Graph::setYEnd(float yEnd) {
	this->yEnd = yEnd;
	Refresh();
}

float Graph::getYEnd() const {
	return yEnd;
}

void Graph::setYStart(float yStart) {
	this->yStart = yStart;
	Refresh();
}

float Graph::getYStart() const {
	return yStart;
}

void Graph::setXEnd(float xEnd) {
	this->xEnd = xEnd;
	Refresh();
}

float Graph::getXEnd() const {
	return xEnd;
}

void Graph::setXStart(float xStart) {
	this->xStart = xStart;
	Refresh();
}

float Graph::getXStart() const {
	return xStart;
}

void Graph::setFunction(const std::function<float(float)>& f) {
	this->f = f;
}

std::function<float(float) > Graph::getFunction() const {
	return f;
}

void Graph::onPaint(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	dc.SetPen(*(wxThePenList->FindOrCreatePen(0x0ff00)));
	if (f != nullptr) {
		auto clientSize = this->GetClientSize();
		float xStep = (xEnd - xStart) / clientSize.x;
		float yStep = (yEnd - yStart) / clientSize.y;
		float currentX = xStart;
		float prevY = f(currentX);
		for (int i = 1; i < clientSize.x; ++i) {
			currentX += xStep;
			float currentY = f(currentX);
			dc.DrawLine(i - 1, (yEnd - prevY) / yStep, i, (yEnd - currentY) / yStep);
			prevY = currentY;
		}
	}
	dc.SetTextForeground(0x00ff00);
	dc.SetBackgroundMode(wxSOLID);
	dc.DrawLabel(wxString() << xStart, GetClientRect(), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	dc.DrawLabel(wxString() << xEnd, GetClientRect(), wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
	dc.DrawLabel(wxString() << yStart, GetClientRect(), wxALIGN_BOTTOM | wxALIGN_CENTER_HORIZONTAL);
	dc.DrawLabel(wxString() << yEnd, GetClientRect(), wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL);
}

void Graph::onMouseDblClick(wxMouseEvent& evt) {
	int left, top, right, bottom;
	evt.GetPosition(&left, &top);
	GetClientSize(&right, &bottom);
	right -= left;
	bottom -= top;
	if (left < right && left < top && left < bottom) {
		changeEditingState(FIELD_XSTART);
	} else if (right < left && right < top && right < bottom) {
		changeEditingState(FIELD_XEND);
	} else if (top < left && top < right && top < bottom) {
		changeEditingState(FIELD_YEND);
	} else {
		changeEditingState(FIELD_YSTART);
	}
}

void Graph::changeEditingState(EditableField field) {
	if (field != FIELD_NONE) {
		wxBoxSizer* sizer = 0;
		switch (field) {
			case FIELD_XSTART:
				sizer = new wxBoxSizer(wxHORIZONTAL);
				edit->Clear();
				*edit << xStart;
				break;
			case FIELD_XEND:
				sizer = new wxBoxSizer(wxHORIZONTAL);
				sizer->Add(0, 0, 1, wxEXPAND);
				edit->Clear();
				*edit << xEnd;
				break;
			case FIELD_YSTART:
				sizer = new wxBoxSizer(wxVERTICAL);
				sizer->Add(0, 0, 1, wxEXPAND);
				edit->Clear();
				*edit << yStart;
				break;
			case FIELD_YEND:
				sizer = new wxBoxSizer(wxVERTICAL);
				edit->Clear();
				*edit << yEnd;
				break;
		}
		edit->Show();
		SetSizer(sizer);
		if (sizer)
			sizer->Add(edit, 0, wxALIGN_CENTER);
		sizer->SetDimension(wxPoint(0, 0), GetClientSize());
		sizer->Layout();
		edit->SetFocus();
	} else {
		this->SetFocus();
		SetSizer(0);
		edit->Hide();
		double value;
		if (!edit->IsEmpty() && edit->GetValue().ToDouble(&value)) {
			switch (editMode) {
				case FIELD_XSTART:
					xStart = value;
					break;
				case FIELD_XEND:
					xEnd = value;
					break;
				case FIELD_YSTART:
					yStart = value;
					break;
				case FIELD_YEND:
					yEnd = value;
					break;
			}
			Refresh();
		}
	}
	editMode = field;
}

void Graph::onEditEnter(wxCommandEvent& evt) {
	SetFocus();
}

void Graph::onEditKeyDown(wxKeyEvent& evt) {
	if (evt.GetKeyCode() == WXK_ESCAPE) {
		edit->Clear();
		changeEditingState(FIELD_NONE);
	} else {
		evt.Skip();
	}
}

void Graph::onEditKillFocus(wxFocusEvent& evt) {
	changeEditingState(FIELD_NONE);
	evt.Skip();
}

