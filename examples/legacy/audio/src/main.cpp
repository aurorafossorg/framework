/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU General Public License version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3 requirements will be
** met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Aurora.h>

#include <string>
#include <iostream>

using namespace AuroraFW;
using namespace AudioManager;

std::string fileName("");
float volume = 1;
int numLoops = -1;
bool noAudio;
bool printInfo = false;
bool audio3DCalcs = false;
bool printAudioInfo = false;
bool buffer = false;
bool loop = false;
bool getCpuLoad = false;
float inputTime = 0;
std::string inputFilename("");

using namespace std;

void appMainFunction(Application* )
{
	try {
		// Initializes AudioBackend
		AuroraFW::DebugManager::Log("Getting access to the AudioBackend");
		AudioBackend::start();
		AuroraFW::DebugManager::Log("AudioBackend initialized.");
		float sourceX, sourceY, sourceZ, listenerX, listenerY, listenerZ;
		AudioSource audioSource;

		if(audio3DCalcs) {
			CLI::Output << "Audio3D calculations:\n\n";

			// Asks for listener's coordinates
			CLI::Output << "Listener:\n\n";
			CLI::Output << "x: ";
			CLI::Input >> listenerX;
			CLI::Output << "y: ";
			CLI::Input >> listenerY;
			CLI::Output << "z: ";
			CLI::Input >> listenerZ;

			// Updates locations of listener and source
			AudioListener::getInstance().position = Math::Vector3D(listenerX, listenerY, listenerZ);
			audioSource.setPosition(Math::Vector3D(sourceX, sourceY, sourceZ));

			// Gets the panning to output value
			float pan = audioSource.getPanning();

			CLI::Output << "Using AudioSource method: " << '\n';
			CLI::Output << "Pan between -1 and 1: " << pan << std::endl;

			// Calculates percentages
			float leftPercent = -(100 * pan)/2 + 50;
			float rightPercent = (100 * pan)/2 + 50;

			CLI::Output << "Percentage in left ear: " << leftPercent << '\n';
			CLI::Output << "Percentage in right ear: " << rightPercent << '\n';
		}

		if(printInfo) {
			// Default output device.
			AudioDevice *defaultDevice;

			AudioBackend audioBackend = AudioBackend::getInstance();

			// Prints all available devices
			const AudioDevice *audioDevices = audioBackend.getAllDevices();
			CLI::Log(CLI::Notice, "Printing all available audio devices...");
			for(int i = 0; i < audioBackend.getNumDevices(); i++) {
				CLI::Log(CLI::Information, i + 1, " - ", audioDevices[i].getName(),
				audioDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "",
				audioDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
			}

			// Prints all available output devices
			const AudioDevice *audioOutputDevices = audioBackend.getOutputDevices();
			CLI::Log(CLI::Notice, "Printing all available output audio devices...");
			for(int i = 0; i < audioBackend.getNumOutputDevices(); i++) {
				CLI::Log(CLI::Information, i + 1, " - ", audioOutputDevices[i].getName(),
				audioOutputDevices[i].isDefaultOutputDevice() ? " [Default Output Device]" : "");
			}

			// Prints all available input devices
			const AudioDevice *audioInputDevices = audioBackend.getInputDevices();
			CLI::Log(CLI::Notice, "Printing all available input audio devices...");
			for(int i = 0; i < audioBackend.getNumInputDevices(); i++) {
				CLI::Log(CLI::Information, i + 1, " - ", audioInputDevices[i].getName(),
				audioInputDevices[i].isDefaultInputDevice() ? " [Default Input Device]" : "");
			}

			// Prints information about the default input/output device
			defaultDevice = AFW_NEW AudioDevice();
			CLI::Log(CLI::Notice, "Printing info for default output device. [", defaultDevice->getName(), "]");
			CLI::Log(CLI::Notice, "Name: ", defaultDevice->getName());
			CLI::Log(CLI::Notice, "Maximum input channels: ", defaultDevice->getMaxInputChannels());
			CLI::Log(CLI::Notice, "Maximum output channels: ", defaultDevice->getMaxOutputChannels());
			CLI::Log(CLI::Notice, "Default low input latency: ", defaultDevice->getDefaultLowInputLatency());
			CLI::Log(CLI::Notice, "Default low output latency: ", defaultDevice->getDefaultLowOutputLatency());
			CLI::Log(CLI::Notice, "Default high input latency: ", defaultDevice->getDefaultHighInputLatency());
			CLI::Log(CLI::Notice, "Default high input latency: ", defaultDevice->getDefaultHighOutputLatency());
			CLI::Log(CLI::Notice, "Default sample rate: ", defaultDevice->getDefaultSampleRate());

			// Cleans declared pointers
			delete defaultDevice;
			delete[] audioDevices;
			delete[] audioInputDevices;
			delete[] audioOutputDevices;
		}

		// If the input arg was used, input the audio
		if(inputTime != 0) {
			AudioInfo* inputInfo = AFW_NEW AudioInfo();
			inputInfo->setSampleRate(44100);
			inputInfo->setChannels(2);

			inputInfo->setFormat(SF_FORMAT_OGG | SF_FORMAT_VORBIS);
			DebugManager::Log(&inputInfo, "\t" , sizeof(inputInfo));
			AudioIStream inputStream(inputFilename.c_str(), inputInfo, 44100 * inputTime);
			CLI::Log(CLI::Notice, "The stream was now created. Audio will be recorded for ", inputTime,
					" seconds and be saved to \"", inputFilename, "\"");
			Pa_Sleep(3000);
			CLI::Log(CLI::Notice, "Recording will begin in: ");
			Pa_Sleep(1000);
			for(int i = 3; i > 0; i--) {
				CLI::Log(CLI::Notice, i);
				Pa_Sleep(600);
			}
			inputStream.record();
			CLI::Log(CLI::Notice, "Record has started. Speak now...");
			while(inputStream.isRecording()) {}

			CLI::Log(CLI::Notice, "Recording has ended, attempting to close stream...");
			//inputStream.stop();
			CLI::Log(CLI::Notice, "Stream stopped. Now recording into disk...");
			inputStream.save() ? CLI::Log(CLI::Notice, "Done! Saved to \"", inputFilename, "\"")
				: CLI::Log(CLI::Warning, "Error while saving: check if you have enough space.");
			return;
		}

		// If the noaudio arg was used, quits immediately
		if(noAudio) {
			AudioBackend::terminate();
			return;
		}

		// Gets ready to output audio
		if(fileName == "") {
			AudioOStream debugSound;
			CLI::Log(CLI::Notice, "Created debug sound. This will make a loud noise, turn down your volume!");
			Pa_Sleep(3000);
			for(int i = 5; i > 0; i--) {
				CLI::Log(CLI::Notice, i);
				Pa_Sleep(1000);
			}

			debugSound.play();
			CLI::Log(CLI::Notice, "Playing debug sound for 5 seconds.");
			Pa_Sleep(5000);
			debugSound.stop();
			CLI::Log(CLI::Notice, "Closed stream.");

			AudioBackend::terminate();
			return;
		}

		AudioOStream audioOStream(fileName.c_str(), audio3DCalcs ? &audioSource : nullptr, buffer);

		if(printAudioInfo) {
			CLI::Log(CLI::Notice, "Printing now audio info...");
			CLI::Log(CLI::Notice, "Title       : ", audioOStream.audioInfo.getTitle());
			CLI::Log(CLI::Notice, "Copyright   : ", audioOStream.audioInfo.getCopyright());
			CLI::Log(CLI::Notice, "Software    : ", audioOStream.audioInfo.getSoftware());
			CLI::Log(CLI::Notice, "Artist      : ", audioOStream.audioInfo.getArtist());
			CLI::Log(CLI::Notice, "Comment     : ", audioOStream.audioInfo.getComment());
			CLI::Log(CLI::Notice, "Date        : ", audioOStream.audioInfo.getDate());
			CLI::Log(CLI::Notice, "Album       : ", audioOStream.audioInfo.getAlbum());
			CLI::Log(CLI::Notice, "License     : ", audioOStream.audioInfo.getLicense());
			CLI::Log(CLI::Notice, "Track Nº    : ", audioOStream.audioInfo.getTrackNumber());
			CLI::Log(CLI::Notice, "Genre       : ", audioOStream.audioInfo.getGenre());
			CLI::Log(CLI::Notice, "-----------------------------------");
			CLI::Log(CLI::Notice, "Sample rate : ", audioOStream.audioInfo.getSampleRate());
			CLI::Log(CLI::Notice, "Frames      : ", audioOStream.audioInfo.getFrames());
			CLI::Log(CLI::Notice, "Channels    : ", audioOStream.audioInfo.getChannels());
			CLI::Log(CLI::Notice, "Format      : ", audioOStream.audioInfo.getFormat());
		}

		CLI::Log(CLI::Notice, "Playing now the \"", fileName, "\" file until the end... (Volume: ", volume, ")");
		AudioBackend::getInstance().globalVolume = volume;
		audioOStream.audioPlayMode = loop ? AudioPlayMode::Loop : AudioPlayMode::Once;
		audioOStream.play();

		// DEBUG: Prints size of audioOStream
		CLI::Log(CLI::Notice, "AudioOStream size: " , sizeof(audioOStream));
		CLI::Log(CLI::Notice, "AudioSource size: " , sizeof(audioSource));

		// Waits until the song is over
		int angle = 0;
		int numCallsCpuLoad = 0;
		double totalCpuValues = 0;
		while(audioOStream.isPlaying())
		{
			// If 3D audio was enabled, makes the sound "spin" around the center
			audioSource.setPosition(Math::Vector3D(Math::cos(Math::toRadians(angle)), 0, -Math::sin(Math::toRadians(angle))));
			angle++;
			Pa_Sleep(20);

			if(getCpuLoad) {
				numCallsCpuLoad++;
				totalCpuValues += audioOStream.getCpuLoad();
			}

			if(loop && audioOStream.getNumLoops() > numLoops - 1)
				audioOStream.stop();
		}

		CLI::Log(CLI::Notice, "Sound is over, attempting to stop it...");
		CLI::Log(CLI::Notice, "Stopped stream.");

		if(getCpuLoad) {
			CLI::Log(CLI::Notice, "The medium CPU load was ", (totalCpuValues / numCallsCpuLoad) * 100, "%");
		}

		// Terminates AudioBackend (and therefore PortAudio)
		AudioBackend::terminate();
		return;
	} catch(AudioFileNotFound e1) {
		CLI::Log(CLI::Warning, e1.what());
	} catch(PAErrorException e2) {
		CLI::Log(CLI::Warning, e2.what());
	}
}

int main(int argc, char *argv[])
{
	for(int i = 0; i < argc; i++) {
		// Help argument
		if(std::string(argv[i]) == "--help") {
			cout <<
			"audio - play a music file\n"
			"\n"
			"usage: audio | --afw-debug | -p | [-o fileName]\n"
			"\n"
			"\n"
			"Options:\n"
			"  -input [time=3] [output=out.ogg]	Captures input for the time specified and saves it\n"
			"  --afw-debug				(Derived from AuroraFW) Activates AuroraFW debug mode \n"
			"  -p					Prints input/output devices' info\n"
			"  -o [filename]				pen the \"fileName\" music file\n"
			"  -v [volume=1]				Sets the volume for playback. It ranges from 0 to 1 (bigger values distort sound)\n"
			"  -noaudio				Plays no audio (used for debugging)\n"
			"  -audio3d				Simulates 3D audio (the audio source spins at the center)\n"
			"  -audioinfo				Print information about the audio file\n"
			"  -loop [value=-1]			Loops the audio the num of times requested (-1 loops infinitely)\n"
			"  -cpuLoad				Gets the medium CPU load"
			<< endl;
			return 0;
		}
		// Argument to print device info
		if(std::string(argv[i]) == "-p") {
			printInfo = true;
		}
		// Argument to open a file
		if(std::string(argv[i]) == "-o") {
			fileName = std::string(argv[i+1]);
		}
		// Argument to input audio
		if(std::string(argv[i]) == "-input") {
			inputTime = std::stof(std::string(argv[i+1]));
			inputFilename = std::string(argv[i+2]);
		}
		// Argument to not output any audio
		if(std::string(argv[i]) == "-noaudio") {
			noAudio = true;
		}
		// Argument to change volume
		if(std::string(argv[i]) == "-v") {
			volume = std::stof(std::string(argv[i+1]));
		}
		// Argument to run special Audio3D calculations
		if(std::string(argv[i]) == "-audio3d") {
			audio3DCalcs = true;
		}
		// Argument to print audio info
		if(std::string(argv[i]) == "-audioinfo") {
			printAudioInfo = true;
		}
		// Argument to buffer the sound file
		if(std::string(argv[i]) == "-buffer") {
			buffer = true;
		}
		// Argument to loop infinitely the audio
		if(std::string(argv[i]) == "-loop") {
			loop = true;
			numLoops = std::stof(std::string(argv[i+1]));
		}
		// Argument to get CPU load
		if(std::string(argv[i]) == "-cpuLoad") {
			getCpuLoad = true;
		}
	}

	Application app(argc, argv, appMainFunction);

	return EXIT_SUCCESS;
}
