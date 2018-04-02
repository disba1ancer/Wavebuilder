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
 * File:   MainWindow.cpp
 * Author: disba1ancer
 * 
 * Created on 10 марта 2018 г., 17:54
 */

#include "MainWindow.h"
#include "HarmonicModel.h"
#include "Graph.h"
	
enum {
	ID_START,
	ID_AddButton,
	ID_RemoveButton,
	ID_DataView,
	ID_Graph,
	ID_Split,
	ID_LeftPanel,
	ID_ClearButton,
	ID_AmplMultTitle,
	ID_AmplMultText,
	ID_FreqMultTitle,
	ID_FreqMultText,
	ID_PlayButton,
};

MainWindow::MainWindow() : wxFrame(NULL, wxID_ANY, "Wavebuilder", wxDefaultPosition, {640, 480}),
		split(new wxSplitterWindow(this, ID_Split)),
		graph(new Graph(split, ID_Graph)),
		leftPanel(new wxPanel(split, ID_LeftPanel)),
		leftPanelSizer(new wxBoxSizer(wxVERTICAL)),
		dataView(new wxDataViewCtrl(leftPanel, ID_DataView)),
		dataViewEditorSizer(new wxBoxSizer(wxHORIZONTAL)),
		addButton(new wxButton(leftPanel, ID_AddButton, "&Add")),
		removeButton(new wxButton(leftPanel, ID_RemoveButton, "&Remove")),
		clearButton(new wxButton(leftPanel, ID_ClearButton, "&Clear")),
		soundPlayerDevider(new wxStaticLine(leftPanel)),
		soundPlayerSizer(new wxGridSizer(2, 0, 0)),
		amplMTitle(new wxStaticText(leftPanel, ID_AmplMultTitle, "Amplitude multiplier")),
		amplMText(new wxTextCtrl(leftPanel, ID_AmplMultText)),
		freqMTitle(new wxStaticText(leftPanel, ID_FreqMultTitle, "Frequency multiplier")),
		freqMText(new wxTextCtrl(leftPanel, ID_FreqMultText)),
		playButton(new wxButton(leftPanel, ID_PlayButton, "&Play/Stop")),
		model(new AbstractDataModel),
		sndPlayer(new SoundPlayer(model.get()))
{
	split->SetSashGravity(1.);
	split->SetMinimumPaneSize(150);
	split->SetWindowStyleFlag(split->GetWindowStyleFlag() | wxSP_LIVE_UPDATE);
	split->SplitVertically(graph, leftPanel, -300);
	
	graph->SetWindowStyleFlag(graph->GetWindowStyleFlag() & ~wxBORDER_MASK | wxBORDER_NONE);
	graph->setYStart(-1.f);
	graph->setYEnd(1.f);
	graph->setXStart(-1.f);
	graph->setXEnd(1.f);
	graph->setFunction([this](float val) -> float {
		return model->calculateY(val);
	});
	
	leftPanel->SetSizer(leftPanelSizer);
	
	leftPanelSizer->Add(dataView, 1, wxEXPAND);
	leftPanelSizer->Add(dataViewEditorSizer, 0, wxALIGN_RIGHT | wxALL, 2);
	leftPanelSizer->Add(soundPlayerDevider, 0, wxEXPAND | wxLEFT | wxRIGHT, 4);
	leftPanelSizer->Add(soundPlayerSizer, 0, wxALIGN_RIGHT | wxALL, 2);
	
	model->registerObserver(dataModelGraphUpdater = [this] (AbstractDataModel::Action action, unsigned index) {
		if (action != AbstractDataModel::ACT_DESTROY) {
			graph->Refresh();
		}
	});
	
	model->add({1.f, 1.f, 0.f});
	
	wxObjectDataPtr<HarmonicModel> model;
	model = new HarmonicModel(this->model.get());
	
	//dataView->SetWindowStyleFlag(dataView->GetWindowStyleFlag() & ~wxBORDER_MASK | wxBORDER_NONE);
	dataView->AssociateModel(model.get());
	dataView->AppendTextColumn("", UINT_MAX, wxDATAVIEW_CELL_INERT, 0, wxALIGN_LEFT, wxDATAVIEW_COL_HIDDEN);
	dataView->AppendTextColumn("Frequency", HarmonicModel::COL_FREQ, wxDATAVIEW_CELL_EDITABLE, -1, wxALIGN_LEFT);
	dataView->AppendTextColumn("Amplitude", HarmonicModel::COL_AMPL, wxDATAVIEW_CELL_EDITABLE, -1, wxALIGN_LEFT);
	dataView->AppendTextColumn("Phase", HarmonicModel::COL_PHAS, wxDATAVIEW_CELL_EDITABLE, -1, wxALIGN_LEFT);
	
	dataViewEditorSizer->Add(addButton, 0, wxALIGN_RIGHT | wxALL, 2);
	dataViewEditorSizer->Add(removeButton, 0, wxALIGN_RIGHT | wxALL, 2);
	dataViewEditorSizer->Add(clearButton, 0, wxALIGN_RIGHT | wxALL, 2);
	
	soundPlayerSizer->Add(amplMTitle, 1, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
	soundPlayerSizer->Add(amplMText, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
	soundPlayerSizer->Add(freqMTitle, 1, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
	soundPlayerSizer->Add(freqMText, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
	soundPlayerSizer->Add(1,1);
	soundPlayerSizer->Add(playButton, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 2);
	
	SoundPlayer* sndPlayer = this->sndPlayer.get();
	
	*amplMText << sndPlayer->getAmplitudeMultiplier();
	*freqMText << sndPlayer->getFrequencyMultiplier();
	
	Bind(wxEVT_BUTTON, &onAddButtonClick, this, ID_AddButton);
	Bind(wxEVT_BUTTON, &onRemoveButtonClick, this, ID_RemoveButton);
	Bind(wxEVT_BUTTON, &onClearButtonClick, this, ID_ClearButton);
	Bind(wxEVT_TEXT, &onAmplMultTextChange, this, ID_AmplMultText);
	Bind(wxEVT_TEXT, &onFreqMultTextChange, this, ID_FreqMultText);
	Bind(wxEVT_BUTTON, &onPlayButtonClick, this, ID_PlayButton);
}

void MainWindow::onAddButtonClick(wxCommandEvent& event) {
	model->add({.0, .0, .0});
}

void MainWindow::onRemoveButtonClick(wxCommandEvent& event) {
	auto item = dataView->GetSelection();
	if (item.IsOk()) {
		model->remove(reinterpret_cast<unsigned>(item.GetID()) - 1);
	}
}

void MainWindow::onClearButtonClick(wxCommandEvent& event) {
	model->clear();
}

void MainWindow::onPlayButtonClick(wxCommandEvent& event) {
	if (sndPlayer->isPlaying())
		sndPlayer->stop();
	else
		sndPlayer->play();
}

void MainWindow::onAmplMultTextChange(wxCommandEvent& event) {
	SoundPlayer* sndPlayer = this->sndPlayer.get();
	double value;
	if (amplMText->GetValue().ToDouble(&value))
		sndPlayer->changeAmplitudeMultiplier(value);
}

void MainWindow::onFreqMultTextChange(wxCommandEvent& event) {
	SoundPlayer* sndPlayer = this->sndPlayer.get();
	double value;
	if (freqMText->GetValue().ToDouble(&value))
		sndPlayer->changeFrequencyMultiplier(value);
}

