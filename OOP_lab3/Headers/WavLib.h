#pragma once
#include <iostream>
#include "wav_header.h"
#include "wav_core.h"

using namespace std;


 class WavLib{
private:
	wav_header_s header;

	vector< vector<short> > chans_data;
	vector< vector<short> > edited_data;
	
	void printInfo(const wav_header_s *header_ptr)
	{
		printf("-------------------------\n");
		printf(" audioFormat   %u\n", header_ptr->audioFormat);
		printf(" numChannels   %u\n", header_ptr->numChannels);
		printf(" sampleRate    %u\n", header_ptr->sampleRate);
		printf(" bitsPerSample %u\n", header_ptr->bitsPerSample);
		printf(" byteRate      %u\n", header_ptr->byteRate);
		printf(" blockAlign    %u\n", header_ptr->blockAlign);
		printf(" chunkSize     %u\n", header_ptr->chunkSize);
		printf(" subchunk1Size %u\n", header_ptr->subchunk1Size);
		printf(" subchunk2Size %u\n", header_ptr->subchunk2Size);
		printf("-------------------------\n");
	}

public:
	wav_errors_e Init(const char* fname);
	void PrintInputFileInfo();
	wav_errors_e ExtractDataInt16(const char* fname);
	wav_errors_e MakeToMono();
	void MakeReverb();
	wav_errors_e MakeWavFile(const char* fname);
	wav_errors_e PrintFileInfo(const char* fname);

};

wav_errors_e WavLib::Init(const char* fname) {
	FILE* f = fopen(fname, "rb");
	if (f == NULL) {
		cerr << "error creaet file " << endl;
		system("pause");
		return IO_ERROR;
	}
	fclose(f);
	wav_errors_e res= read_header(fname, &header);
	return res;
};

void WavLib::PrintInputFileInfo() 
{
	printInfo(&header);
};

wav_errors_e WavLib::ExtractDataInt16(const char* fname) {
	return extract_data_int16(fname, chans_data);
};


wav_errors_e WavLib::MakeToMono() {
	return make_mono(chans_data, edited_data);
};

void WavLib::MakeReverb() {
	make_reverb(edited_data, header.sampleRate, 0.5, 0.6f);
};

wav_errors_e WavLib::MakeWavFile(const char* fname) {
	return make_wav_file(fname,header.sampleRate, edited_data);
}

wav_errors_e WavLib::PrintFileInfo(const char* fname) {
	wav_header_s header;
	wav_errors_e err;
	err = read_header(fname, &header);
	if (err != WAV_OK) {
		cerr << "read_header() error: " << (int)err << endl;
		print_info(&header);
		return err;
	}
	print_info(&header);
	return err;
};