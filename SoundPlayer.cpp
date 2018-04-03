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
 * File:   SoundPlayer.cpp
 * Author: disba1ancer
 * 
 * Created on 31 марта 2018 г., 21:40
 */

#include <iostream>

#include "SoundPlayer.h"

// Bytes per sample
constexpr size_t bps = sizeof(SoundPlayer::Sample);

// Samples per second
constexpr size_t sps = 44100;

constexpr uint32_t RIFF_RIFF = 0x46464952;
constexpr uint32_t RIFF_WAVE = 0x45564157;
constexpr uint32_t RIFF_WAVE_FMT = 0x20746d66;
constexpr uint32_t RIFF_WAVE_DATA = 0x61746164;

// RIFF container chunk header
struct riff_chunk_header {
	uint32_t id;
	uint32_t size;
};

// RIFF chunk, only for use as pointer type
struct riff_chunk {
	riff_chunk_header hdr;
	unsigned char data[1];
	
	operator riff_chunk_header&() {
		return hdr;
	}
};

// RIFF chunk data header
struct riff_data_header {
	uint32_t id;
};

// RIFF chunk data, only for use as pointer type
struct riff_data {
	riff_data_header hdr;
	unsigned char data[1];
	
	operator riff_data_header&() {
		return hdr;
	}
};

struct WaveFmt {
    uint16_t format;
    uint16_t channelCount;
    uint32_t samplesPerSec;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

constexpr size_t bufferSize = 3 * sizeof(riff_chunk_header) + sizeof(riff_data_header) +
		sizeof(WaveFmt) + bps * sps;

template <typename Dst, typename Src>
constexpr Dst ptr_cast(Src src) {
	return static_cast<Dst>(static_cast<void*>(src));
}

SoundPlayer::SoundPlayer(const std::function<float(float)>& func) noexcept : data(new unsigned char[bufferSize]),
		sndData(0),
		sndPlayer(0),
		f(func),
		isPlay(false),
		amplMult(16384.f),
		freqMult(1.f)
{
	void* data = this->data.get();
	auto mainRiffChunk = static_cast<riff_chunk_header*>(data);
	auto mainRiffChunkData = ptr_cast<riff_data_header*>(mainRiffChunk + 1);
	auto formatChunk = ptr_cast<riff_chunk_header*>(mainRiffChunkData + 1);
	auto formatChunkData = ptr_cast<WaveFmt*>(formatChunk + 1);
	auto dataChunk = ptr_cast<riff_chunk_header*>(formatChunkData + 1);
	sndData = ptr_cast<Sample*>(dataChunk + 1);
	
	mainRiffChunk->id = RIFF_RIFF;
	mainRiffChunk->size = bufferSize - sizeof(riff_chunk_header);
	mainRiffChunkData->id = RIFF_WAVE;
	formatChunk->id = RIFF_WAVE_FMT;
	formatChunk->size = sizeof(WaveFmt);
	
	formatChunkData->format = 1;
	formatChunkData->channelCount = 1;
	formatChunkData->samplesPerSec = sps;
	formatChunkData->bytesPerSec = sps * bps;
	formatChunkData->blockAlign = bps;
	formatChunkData->bitsPerSample = bps * 8;
	
	dataChunk->id = RIFF_WAVE_DATA;
	dataChunk->size = mainRiffChunk->size - sizeof(riff_data_header) -
			2 * sizeof(riff_chunk_header) - sizeof(WaveFmt);
	
	for (size_t i = 0; i < sps; ++i) {
		sndData[i] = 0;
	}
	
	sndPlayer.reset(new wxSound(bufferSize, data));
}

void SoundPlayer::play() noexcept {
	isPlay = true;
	sndPlayer->Play(wxSOUND_ASYNC | wxSOUND_LOOP);
}

void SoundPlayer::stop() noexcept {
	isPlay = false;
	sndPlayer->Stop();
}

void SoundPlayer::update() noexcept {
	if (f) {
		for (size_t i = 0; i < sps; ++i) {
			sndData[i] = amplMult * f(float(i) * freqMult / float(sps));
		}
		sndPlayer.reset(new wxSound(bufferSize, this->data.get()));
		if (isPlay)
			sndPlayer->Play(wxSOUND_ASYNC | wxSOUND_LOOP);
	}
}

void SoundPlayer::changeAmplitudeMultiplier(float multiplier) noexcept {
	amplMult = multiplier;
	update();
}

float SoundPlayer::getAmplitudeMultiplier() noexcept {
	return amplMult;
}

void SoundPlayer::changeFrequencyMultiplier(float multiplier) noexcept {
	freqMult = multiplier;
	update();
}

float SoundPlayer::getFrequencyMultiplier() noexcept {
	return freqMult;
}

bool SoundPlayer::isPlaying() noexcept {
	return isPlay;
}

void SoundPlayer::setFunction(const std::function<float(float)>& func) noexcept {
	f = func;
	update();
}

std::function<float(float)> SoundPlayer::getFunction() noexcept {
	return f;
}

