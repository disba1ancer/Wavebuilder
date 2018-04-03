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
 * File:   SoundPlayer.h
 * Author: disba1ancer
 *
 * Created on 31 марта 2018 г., 21:40
 */

#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <memory>
#include <wx/sound.h>

#include "AbstractDataModel.h"

class SoundPlayer {
public:
	typedef int16_t Sample;
	
	SoundPlayer(const std::function<float(float)>& func = nullptr) noexcept;
	/*SoundPlayer(const SoundPlayer& orig);
	SoundPlayer(SoundPlayer&& orig);
	const SoundPlayer& operator=(const SoundPlayer& orig);
	const SoundPlayer& operator=(SoundPlayer&& orig);
	~SoundPlayer() noexcept;*/
	void play() noexcept;
	void stop() noexcept;
	void update() noexcept;
	void changeAmplitudeMultiplier(float multiplier) noexcept;
	void changeFrequencyMultiplier(float multiplier) noexcept;
	float getAmplitudeMultiplier() noexcept;
	float getFrequencyMultiplier() noexcept;
	bool isPlaying() noexcept;
	void setFunction(const std::function<float(float)>& func) noexcept;
	std::function<float(float)> getFunction() noexcept;
private:
	std::unique_ptr<unsigned char[]> data;
	Sample* sndData;
	wxScopedPtr<wxSound> sndPlayer;
	std::function<float(float)> f;
	bool isPlay;
	float amplMult, freqMult;
};

#endif /* SOUNDPLAYER_H */

