#include "iostream"
#include "string"
#include "sstream"
#include "fstream"
#include "stdio.h"
#include "stdlib.h"
#include "thread"
#include "unistd.h"
#include "stdlib.h"
#include "signal.h"
#include "stdio.h"
#include "sys/stat.h"

// checks if file exists and returns "true" if it does exist
inline bool exists(const std::string& name) 
{ 
	struct stat buffer; 
	return (stat (name.c_str(), &buffer) == 0); 
}

// reads in both char array and string array, then append both to char pointer
void getPathsEX(char* (&finalpath), const char* prefix, const int prefixlen, const std::string appendarray[], const int appendarraysize)
{
	// processing appendarray
	int size(0);

	// add appendarraysize
	for (int count(0); count < appendarraysize; ++count)
	{
		size += appendarray[count].length();
	}
	finalpath = new char[size + prefixlen + 1];

	// keep count of all added char
	int arraycount(0);

	// add prefix
	for (int count(0); count < prefixlen; ++count)
	{
		finalpath[arraycount] = prefix[count];
		++arraycount;
	}

	// append arguments
	for (int counting(0); counting < appendarraysize; ++counting)
	{
		for (int count(0); count < appendarray[counting].length(); ++count)
		{
			finalpath[arraycount] = appendarray[counting][count];
			++arraycount;
		}
	}

	// append terminating character null
	finalpath[arraycount] = '\0';
}

FILE *fpipe = nullptr;
FILE *fpipesec = nullptr;

// path to pocketsphinx parameters must be adjusted
char command[] = "pocketsphinx_continuous -inmic yes -adcdev plughw:1,0 -samprate 16000 -logfn /dev/null -hmm /home/pi/Desktop/spanish/cmusphinx-es-5.2/model_parameters/voxforge_es_sphinx.cd_ptm_4000 -lm /home/pi/Desktop/spanish/es-20k.lm.bin -dict /home/pi/Desktop/spanish/es.dict > foo.txt";

// enter api-key 
char sendcurl[] = "curl --user apikey:Viqc9hPH10U8aIe_WX7iEmEsudzgYu6Z69_RLYthEQAt --request POST --header \"Content-Type: application/json\" --data \"{\\\"text\\\"\:";

// url must be adjusted
char endtext[] = "\\\"\model_id\\\"\:\\\"es-en\\\"\}\"\ \"\https://gateway.watsonplatform.net/language-translator/api/v3/translate?version=2018-05-01\"";

char spanishstart[] = "[\\\"";
char spanishend[] = "\\\"\],";
char flitetoappend[] = "flite \"";

// path to output wav file must be the same as path used for wav file input
char flitetoend[] = "\" /home/pi/Desktop/hear.wav";

char endofspeech[] = " end of speech";

// runs pocketsphinx on device (command). pocketsphinx will keep appending to file "foo.txt" while the rest of the program reads it
void startbranch()
{
	fpipe = (FILE*)popen(command, "r");
}

// returning true keeps the program in a loop. this is used for storing the translation returned from IBM's web API
bool alphabet(char value)
{
	switch (value)
	{
		case 'a':
			return true;
			break;
		case 'b':
			return true;
			break;
		case 'c':
			return true;
			break;
		case 'd':
			return true;
			break;
		case 'e':
			return true;
			break;
		case 'f':
			return true;
			break;
		case 'g':
			return true;
			break;
		case 'h':
			return true;
			break;
		case 'i':
			return true;
			break;
		case 'j':
			return true;
			break;
		case 'k':
			return true;
			break;
		case 'l':
			return true;
			break;
		case 'm':
			return true;
			break;
		case 'n':
			return true;
			break;
		case 'o':
			return true;
			break;
		case 'p':
			return true;
			break;
		case 'q':
			return true;
			break;
		case 'r':
			return true;
			break;
		case 's':
			return true;
			break;
		case 't':
			return true;
			break;
		case 'u':
			return true;
			break;
		case 'v':
			return true;
			break;
		case 'w':
			return true;
			break;
		case 'x':
			return true;
			break;
		case 'y':
			return true;
			break;
		case 'z':
			return true;
			break;
    case ' ':
      return true;
      break;
	}
	return false;
}

int main()
{
	remove("/home/pi/Desktop/foo.txt");
	std::thread recording(startbranch);                                       // starts pocketsphinx in a thread
	sleep(5);                                                                 // sleep for 5 seconds on Linux/Unix systems for "foo.txt" to be created
  system("pacmd set-card-profile bluez_card.70_26_05_AE_65_DD a2dp_sink");  // bluetooth address must be adjusted
  system("pacmd set-default-sink bluez_sink.70_26_05_AE_65_DD.a2dp_sink");  // bluetooth address must be adjusted
	
  std::ifstream myfile("/home/pi/Desktop/foo.txt");                         // reads file pocketsphinx outputs to
	std::string templine;
  
	while(1)
	{
		myfile.clear();                                                         // ignore lines that are already read
		while(getline(myfile, templine))
		{
			char* sendspanish = nullptr;
			char* sendcommand = nullptr;
			char *flitecommand = nullptr;
      
			std::string spanishstr[]{ templine, spanishend };
			getPathsEX(sendspanish, spanishstart, 3, spanishstr, 2);              // stores syntax for word/words into "sendspanish"
			
      std::string commandstr[]{ sendspanish, endtext };
			getPathsEX(sendcommand, sendcurl, 139, commandstr, 2);                // stores command for requesting translation from IBM into "sendcommand"
			
      fpipesec = (FILE*)popen(sendcommand, "r");
			char* a = new char[200];
			char* b = nullptr;
			int countingwords(0);
			fread(a, 200, 1, fpipesec);                                           // stores terminal output into "a"
      
			for (int count(46); count < 200; ++count)
			{
				++countingwords;                                                    // countingwords store the number of characters the word/words being translated contain
				if (alphabet(a[count+1]))                                           // if the next character is an alphabet or "space", keep looping. if it isn't an alphabet or "space", then we have finished calculating "countingwords", so end the loop
				{
				}
				else
				{
					break;
				}
			}
      
			b = new char[countingwords + 15];                                     // add 15 so we would have additional space to signify end of speech through the char array "endofspeech"
      
			for (int count(0); count < countingwords; ++count)
			{
				b[count] = a[46 + count];                                           // store the translated word/words into "b"
			}
      
      for (int count(0); count < 14; ++count)
      {
        b[countingwords + count] = endofspeech[count];                      // append "end of speech" to "b"
      }
      
			b[countingwords + 14] = '\0';
                        
			std::string flitestr[]{ b, flitetoend };
			getPathsEX(flitecommand, flitetoappend, 7, flitestr, 2);              // stores command for synthesizing speech to "flitecommand"

			remove("/home/pi/Desktop/hear.wav");
			system(flitecommand);                                                 // creates wav file that contains the speech for the translated word/words
      
			while (!(exists("/home/pi/Desktop/hear.wav")))	                      // if the wav file is not created yet, sleep until it is created
      {
        sleep(1);
      }
                        
			system("omxplayer -o alsa /home/pi/Desktop/hear.wav");		            // sound player must be changed depending on system (omxplayer for linux)	

			pclose(fpipesec);
			delete[] a;
			delete[] b;
			delete[] sendcommand;
			delete[] sendspanish;
			delete[] flitecommand;
		}
		sleep(1);                                                               // reduces burden on CPU due to while(1) statements
	}
	pclose(fpipe);
	recording.join();
	return 0;
}
