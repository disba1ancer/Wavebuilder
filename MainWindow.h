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
 * File:   MainWindow.h
 * Author: disba1ancer
 *
 * Created on 10 марта 2018 г., 17:54
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/dataview.h>
#include <wx/splitter.h>
#include <wx/statline.h>
#include <memory>

#include "HarmonicModel.h"
#include "Graph.h"
#include "SoundPlayer.h"

class MainWindow : public wxFrame {
public:
	MainWindow();
private:
	void onAddButtonClick(wxCommandEvent& event);
	void onRemoveButtonClick(wxCommandEvent& event);
	void onClearButtonClick(wxCommandEvent& event);
	void onPlayButtonClick(wxCommandEvent& event);
	void onAmplMultTextChange(wxCommandEvent& event);
	void onFreqMultTextChange(wxCommandEvent& event);
	
	wxSplitterWindow* split;
	Graph* graph;
	wxPanel* leftPanel;
	wxBoxSizer* leftPanelSizer;
    wxDataViewCtrl* dataView;
	wxBoxSizer* dataViewEditorSizer;
	wxButton* addButton;
	wxButton* removeButton;
	wxButton* clearButton;
	wxStaticLine* soundPlayerDevider;
	wxGridSizer* soundPlayerSizer;
	wxStaticText* amplMTitle;
	wxTextCtrl* amplMText;
	wxStaticText* freqMTitle;
	wxTextCtrl* freqMText;
	wxButton* playButton;
	
	std::unique_ptr<AbstractDataModel> model;
	std::function<void(AbstractDataModel::Action, unsigned)> dataModelGraphUpdater;
	std::unique_ptr<SoundPlayer> sndPlayer;
};

#endif /* MAINWINDOW_H */

