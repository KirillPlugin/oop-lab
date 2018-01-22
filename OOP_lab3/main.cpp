#include <iostream>
#include "headers\wav_core.h"
#include "headers\WavLib.h"


using namespace std;

int  main(int argc, char *argv[])
{
	cout << "************** | WavCore | **************" << endl;
	const char* input_fname =  "c:\\temp2\\0.wav";
	const char* output_fname = "c:\\temp2\\out.wav";
	wav_errors_e err;
	wav_header_s header;
	WavLib mWav;
	err=mWav.Init(input_fname);
	if (err != WAV_OK) {
		cerr << "read_header() error: " << (int)err << endl;
		//mWav.PrintInputFileInfo();
		return err;
	}
	mWav.PrintInputFileInfo();

	err = mWav.ExtractDataInt16(input_fname);
	if (err != WAV_OK) {
		cerr << "extract_data_int16() error: " << (int)err << endl;
		return err;
	}
	cout << endl << "********************" << endl;

	err = mWav.MakeToMono();
	if (err != WAV_OK) {
		cerr << "make_mono() error: " << (int)err << endl;
		return err;
	}

	mWav.MakeReverb();

	err = mWav.MakeWavFile(output_fname);
	if (err != WAV_OK) {
		cerr << "make_wav_file() error: " << (int)err << endl;
		print_info(&header);
		return err;
	}
	
	mWav.PrintFileInfo(output_fname);
 	system("pause");
}


/*
#include <stdio.h>
int main()
{
	int t, i = 2;
	printf("vvedite chislo\n");
	scanf("%d", &t);

	printf("%d = ", t);

	while (i <= t)
	{
		if (t%i == 0)
		{
			printf("%d", i);
			t = t / i;
			if (t>1)
				printf("*");
		}
		else
			i = i + 1;
	}
	system("pause");
	return 0;
}
*/