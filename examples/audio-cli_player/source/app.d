/*
								   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 Aurora Free Open Source Software.

This file is part of the Aurora Free Open Source Software. This
organization promote free and open source software that you can
redistribute and/or modify under the terms of the GNU General Public
License Version 3 as published by the Free Software Foundation or (at your
option) any later version approved by the Aurora Free Open Source Software
Organization. The license is available in the package root path as
'LICENSE' file. Please review the following information to ensure the GNU
General Public License requirements will be met:
https://www.gnu.org/licenses/gpl-3.0.html .

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

import std.stdio : writeln;
import std.conv : to, text;
import core.thread : Thread;
import core.time : Duration, dur;

import aurorafw.core.application : Application;
import aurorafw.core.logger;
import aurorafw.core.debugmanager;
import aurorafw.audio;
import aurorafw.audio.soundio;

string fileName, inputFileName;
float volume = 1;
int numLoops = -1;
bool noAudio, printInfo, audio3DCalcs, printAudioInfo, buffer, loop, getCpuLoad;
int inputTime;

void appMainFunction(Application app) {
	writeln("Inside AuroraFW app! \\o/");

	try {
		// Initializes AudioBackend
		log("Getting access to the AudioBackend...");
		AudioBackend audioBackend = AudioBackend.getInstance();
		log("AudioBackend initialized.");

		/* OLD CODE, 3D EFFECTS ARE IN REFACTORING PROCESS
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
		*/

		if(printInfo) {
			pragma(msg, debugMsgPrefix, "TODO: Implement printInfo()");

			// Default output device
			AudioDevice defaultDevice;

			// Prints all available devices
			immutable AudioDevice[] audioDevices = audioBackend.getDevices();
			writeln("Printing all available audio devices...");
			for(byte i = 0; i < audioDevices.length; i++) {
				writeln(text(i + 1), " - ", audioDevices[i].name,
				audioDevices[i].isDefaultOutputDevice ? " [Default Output Device]" : "",
				audioDevices[i].isDefaultInputDevice ? " [Default Input Device]" : "");
			}

			// Prints all available output devices
			immutable AudioDevice[] audioOutputDevices = audioBackend.getOutputDevices();
			writeln("Printing all available output audio devices...");
			for(byte i = 0; i < audioOutputDevices.length; i++) {
				writeln(text(i + 1), " - ", audioOutputDevices[i].name,
				audioOutputDevices[i].isDefaultOutputDevice ? " [Default Output Device]" : "");
			}

			// Prints all available input devices
			immutable AudioDevice[] audioInputDevices = audioBackend.getInputDevices();
			writeln("Printing all available input audio devices...");
			for(byte i = 0; i < audioInputDevices.length; i++) {
				writeln(text(i + 1), " - ", audioInputDevices[i].name,
				audioInputDevices[i].isDefaultInputDevice ? " [Default Input Device]" : "");
			}

			// Prints information about the default input/output device
			defaultDevice = new AudioDevice();
			writeln("Printing info for default output device. [", defaultDevice.name, "]");
			writeln("Name: ", defaultDevice.name);
			writeln("Maximum input channels: ", defaultDevice.maxInputChannels);
			writeln("Maximum output channels: ", defaultDevice.maxOutputChannels);
			writeln("Default low input latency: ", defaultDevice.inputLowLatency);
			writeln("Default low output latency: ", defaultDevice.outputLowLatency);
			writeln("Default high input latency: ", defaultDevice.inputHighLatency);
			writeln("Default high input latency: ", defaultDevice.outputHighLatency);
			writeln("Default sample rate: ", defaultDevice.sampleRate);

		}

		// If the input arg was used, input the audio
		if(inputTime != 0) {
			AudioInfo inputInfo = new AudioInfo();
			inputInfo.sampleRate = 44100;
			inputInfo.channels = 2;

			// inputInfo.format = (SF_FORMAT_OGG | SF_FORMAT_VORBIS);
			AudioIStream inputStream = new AudioIStream(inputFileName, inputInfo, 44100 * inputTime);
			writeln("The stream was now created. Audio will be recorded for ", inputTime, 
					" seconds and be save to \"", inputFileName, "\"");

			Thread.sleep(dur!("seconds")(3));
			writeln("Recording will begin in: ");
			Thread.sleep(dur!("seconds")(1));
			for(byte i = 3; i > 0; i--) {
				writeln(i);
				Thread.sleep(dur!("msecs")(600));
			}

			inputStream.record();
			writeln("Record has stared. Speak now...");
			while(inputStream.isRecording()) {}

			writeln("Recording has ended, attempting to save it to disk...");
			inputStream.save() ? writeln("Done! Saved to \"", inputFileName, "\"")
				: writeln("Error while saving: check if you have enough space.");

			return;
		}

		// If the noaudio arg was used, quits immediately
		if(noAudio)
			return;

		// Gets ready to output audio
		if(fileName == "") {
			AudioOStream debugStream = new AudioOStream();
			writeln("Created debug sound. This will make a loud noise, turn down your volume!");
			Thread.sleep(dur!("seconds")(3));

			for(int i = 5; i > 0; i--) {
				writeln(i);
				Thread.sleep(dur!("seconds")(1));
			}

			debugStream.play();
			writeln("Playing debug sound for 5 seconds.");
			Thread.sleep(dur!("seconds")(5));
			debugStream.stop();
			writeln("Closed stream.");

			return;
		}

		AudioOStream outputStream = new AudioOStream(fileName, buffer);

		if(printAudioInfo) {
			writeln("Printing now audio info...");
			writeln("Title       : ", outputStream.audioInfo.title);
			writeln("Copyright   : ", outputStream.audioInfo.copyright);
			writeln("Software    : ", outputStream.audioInfo.software);
			writeln("Artist      : ", outputStream.audioInfo.artist);
			writeln("Comment     : ", outputStream.audioInfo.comment);
			writeln("Date        : ", outputStream.audioInfo.date);
			writeln("Album       : ", outputStream.audioInfo.album);
			writeln("License     : ", outputStream.audioInfo.license);
			writeln("Track Nº    : ", outputStream.audioInfo.trackNumber);
			writeln("Genre       : ", outputStream.audioInfo.genre);
			writeln("-----------------------------------");
			writeln("Sample rate : ", outputStream.audioInfo.sampleRate);
			writeln("Frames      : ", outputStream.audioInfo.frames);
			writeln("Channels    : ", outputStream.audioInfo.channels);
			writeln("Format      : ", outputStream.audioInfo.format);
		}

		writeln("Playing now the \"", fileName, "\" file until the end... (Volume: ", volume, ")");
		audioBackend.globalVolume = volume;
		outputStream.audioPlayMode = loop ? AudioPlayMode.Loop : AudioPlayMode.Once;

		outputStream.play();

		// Waits until the song is over
		int angle = 0;
		int numCallsCpuLoad = 0;
		double totalCpuValues = 0;
		while(outputStream.isPlaying())
		{
			// If 3D audio was enabled, makes the sound "spin" around the center
			/*audioSource.setPosition(Math::Vector3D(Math::cos(Math::toRadians(angle)), 0, -Math::sin(Math::toRadians(angle))));
			angle++;
			Pa_Sleep(20);*/

			if(getCpuLoad) {
				numCallsCpuLoad++;
				totalCpuValues += outputStream.getCpuLoad();
			}

			if(loop && outputStream.getNumLoops() > numLoops - 1)
				outputStream.stop();
		}

		writeln("Sound is over, attempting to stop it...");
		writeln("Stopped stream.");

		if(getCpuLoad) {
			writeln("The medium CPU load was ", (totalCpuValues / numCallsCpuLoad) * 100, "%");
		}

		// Backend is garbage-collected
		return;
	} catch(AudioFileNotFoundException e) {
		writeln(e);
	}
}

int main(string[] args) {
	for(byte opt; opt < args.length; opt++) {
		// Help argument
		if(args[opt] == "--help") {
			writeln(
				"audio - play a music file\n" ~
				"\n" ~
				"usage: audio | --afw-debug | -p | [-o fileName]\n" ~
				"\n" ~
				"\n" ~
				"Options:\n" ~
				"  -input [time=3] [output=out.ogg]	Captures input for the time specified and saves it\n" ~
				"  --afw-debug				(Derived from AuroraFW) Activates AuroraFW debug mode \n" ~
				"  -p					Prints input/output devices' info\n" ~
				"  -o [filename]				Open the \"fileName\" music file\n" ~
				"  -v [volume=1]				Sets the volume for playback. It ranges from 0 to 1 (bigger values distort sound)\n" ~
				"  -noaudio				Plays no audio (used for debugging)\n" ~
				"  -audio3d				Simulates 3D audio (the audio source spins at the center)\n" ~
				"  -audioinfo				Print information about the audio file\n" ~
				"  -loop [value=-1]			Loops the audio the num of times requested (-1 loops infinitely)\n" ~
				"  -cpuLoad				Gets the medium CPU load"
			);

			return 0;
		}
		// Print device info argument
		if(args[opt] == "-p") {
			printInfo = true;
		}
		// Open a file argument
		if(args[opt] == "-o") {
			fileName = args[opt + 1];
		}
		// Input audio argument
		if(args[opt] == "-input") {
			inputTime = to!int(args[opt + 1]);
			inputFileName = args[opt + 2];
		}
		// No output argument
		if(args[opt] == "-noaudio") {
			noAudio = true;
		}
		// Change volume argument
		if(args[opt] == "-v") {
			volume = to!float(args[opt + 1]);
		}
		// Run Audio3D calcs argument
		if(args[opt] == "-audio3d") {
			audio3DCalcs = true;
		}
		// Print audio info argument
		if(args[opt] == "-audioinfo") {
			printAudioInfo = true;
		}
		// Buffer sound file audio
		if(args[opt] == "-buffer") {
			buffer = true;
		}
		// Loop audio argument
		if(args[opt] == "-loop") {
			loop = true;
			numLoops = to!int(args[opt + 1]);
		}
		// Get CPU load argument
		if(args[opt] == "-cpuLoad") {
			getCpuLoad = true;
		}
	}

	Application app = Application(args.dup, &appMainFunction);
	return 0;
}