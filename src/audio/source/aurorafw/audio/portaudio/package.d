module aurorafw.audio.portaudio;

private {
	extern(C) {
		struct PaVersionInfo {
			int versionMajor;
			int versionMinor;
			int versionSubMinor;
			const char* versionControlRevision;
			const char* versionText;
		}

		struct PaHostApiInfo {
			int structVersion;
			HostApiTypeId type;
			const char* name;
			int deviceCount;
			DeviceIndex defaultInputDevice;
			DeviceIndex defaultOutputDevice;
		}
	}
}

enum HostApiTypeId
{
	InDevelopment=0,
	DirectSound=1,
	MME=2,
	ASIO=3,
	SoundManager=4,
	CoreAudio=5,
	OSS=7,
	ALSA=8,
	AL=9,
	BeOS=10,
	WDMKS=11,
	JACK=12,
	WASAPI=13,
	AudioScienceHPI=14
}

alias DeviceIndex = int;

alias VersionInfo = PaVersionInfo;
alias HostApiInfo = PaHostApiInfo;