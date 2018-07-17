# speech-to-speech-translator
This is a translator that compilate softwares and APIs to enable speech-to-speech translation.

Note that this is a compilation of softwares and APIs. By no means is this a standalone speech recognizor, translator, or speech synthesizer.

There are hardware prerequisites in addition to a computer. A microphone is needed for audio input and some form of audio output is needed.

Also, this STS translator is tested on linux with the "Raspberry Pi 2" but should work with other systems. Although instructions for other systems are not provided, the translator is coded so as to be compatible on most systems. So, setup on other systems would be similar but may need some slight modifications.


**Dependencies:**

[pocketsphinx](https://github.com/cmusphinx/pocketsphinx) for speech recognition

[sphinxbase](https://github.com/cmusphinx/sphinxbase) for speech recognition

[flite](https://github.com/festvox/flite) for speech synthesizing

[ibm-language-translator](https://www.ibm.com/watson/services/language-translator/) for translation

# Prerequisites 

1. curl must be installed
2. c++ complier

# Linux/Unix installation
Begin with installing sphinxbase:
```python
git clone http://github.com/cmusphinx/sphinxbase
cd sphinxbase
./autogen.sh
./configure
make
sudo make install
```
Then, install pocketsphinx:
```python
git clone http://github.com/cmusphinx/pocketsphinx
cd pocketsphinx
./autogen.sh
./configure
make
sudo make install
```
To install flite:
```python
git clone http://github.com/festvox/flite
cd flite
./configure
make
make get_voices
sudo make install
```
To use IBM's translator, you must first create an account [here](https://www.ibm.com/watson/services/language-translator/). IBM allows an account to have a certain number of characters translated free for each month and does not require a credit card during sign up. We need the API and URL key provided after sign up. 

**API:**

On line 65 of translate.cpp, replace (your key) with the API key IBM provided (e.g. Uuqc9hPH99U8aIe_SD7iDqEeudzgYu7Q69_RLYthEQBq).

**URL:**

On line 68 of translate.cpp, replace (your URL) with the URL IBM provided (e.g. https://gateway.watsonplatform.net/language-translator/api/v3/translate?version=2018-05-01). 

**Other ajustments:**

For lines 75, 236, 239, and 244, (wav file) must be replaced with a path for the creation, deletion, and input of a wav file (e.g. /home/pi/Desktop/hear.wav).

For lines 62, 177, and 183, (text file) must be replaced with a path for the creation, deletion, and input of a text file (e.g. /home/pi/Desktop/foo.txt).

# Changing language
To setup the language model used by pocketsphinx, first download the desired language model at https://sourceforge.net/projects/cmusphinx/files acoustic and language Models section. In this example, we will use the Spanish language model but steps should be similar for other language models.

Open the folder containing the language model and note the following files: filename.dict (e.g. es.dict), filename.lm.bin or filename.lm (e.g. es-20k.lm.bin), and a folder containing the files feat.params, mdef, means, mixture_weights... (e.g. /home/pi/Desktop/spanish/cmusphinx-es-5.2/model_parameters/voxforge_es_sphinx.cd_ptm_4000)

On line 62 of translate.cpp, replace (lm path) with the path to filename.lm.bin (e.g. /home/pi/Desktop/spanish/es-20k.lm.bin). Replace (hmm path) with the folder containing the various files (e.g. /home/pi/Desktop/spanish/cmusphinx-es-5.2/model_parameters/voxforge_es_sphinx.cd_ptm_4000). Replace (dict path) with the path to filename.dict (e.g. /home/pi/Desktop/spanish/es.dict).

On line 68, "es-en" directs IBM translator to translate from Spanish to English. You must set this yourself for your desired language (e.g. en-es to translate from English to Spanish). Note that the language to be translated must match the language model you chose for pocketsphinx. 

# Speech output
Because Flite is used for speech synthesizing, the language in which speech outputs is limited by the selections Flute provide. Right now, the options are available [here](https://github.com/festvox/flite/tree/master/config). Flite speaks in English by default. Note that whatever the option, it must match the language chosen to be translated to at IBM settings.

To direct Flite to use a specify voice package, choose a file that ends with "lv" in the folder at /flite/config and configure flite with the command
```
./configure --with-langvox="lv filename"
(e.g. ./configure --with-langvox=transtac)
```

# Audio output
Depending on your system, line 244 of translate.cpp would be different. The purpose here is to play the wav file created by Flite. On the Raspberry Pi, omxplayer is used. If you are using other systems, other audio players can be used. 

Regarding the parameter "-o alsa", it should be used if the headphone/earphone you are using outputs with alsa mixer. If not, remove the parameter from the command on line 244. Raspberry Pi can be configured to use alsa when paired with Bluetooth headphone/earphone (see below). Other systems might be different, so it is up to you to figure out what audio player and parameters you should use. 

# Bluetooth
translate.cpp assumes that you use Bluetooth headphone/earphone to receive audio output. If that is not the case, then comment out lines 180 and 181. Then, see below's section "No Bluetooth". 

If you are using Bluetooth earphone for audio output on Linux computers, you might also want to comment out the two lines. To test whether you need to, install [Pulse audio](https://www.freedesktop.org/wiki/Software/PulseAudio/?) then enter the command 

`flite - t "testing testing one two three" `. 

If you can hear the audio output through your Bluetooth earphone, then you should comment out the two lines. If however, there is no audio output, then you must keep the two lines and replace (Bluetooth address) with the Bluetooth address of your earphone (e.g. 74_26_05_AE_65_DE).

Additionally, if you are setting this up on a Raspberry Pi, you might need to run a script avaliable [here](https://github.com/BaReinhard/a2dp_bluetooth). It will configure your Raspberry Pi to be used with Bluetooth headphones/earphones. 

# No bluetooth
If you are using wired connection, simply comment out line 180 and 181.

# Compiling on Linux/Unix
When all adjustments and setups are complete, you can compile translate.cpp and begin using the speech-to-speech-translator. To compile, you must link the "include" and "lib" directory the "make install" commands made in. By default, linux has an "include" folder at /usr/local/include and a "lib" folder at /usr/local/lib. Moreover, depending on the c++ compiler, the include folder for c applications might be available at /usr/include/c++. The command to compile is as follow:
```
g++ -Wall -I (path to c's include folder) -I (path to user's include folder) -L (path to user's lib folder) -lpthread translate.cpp -o translate
```
where "translate.cpp" is the path to the cpp file. This command will generate a file named "translate".

For example on the Raspberry Pi, you can run the below command in terminal:
```
g++ -Wall -I /usr/include/c++/6 -I /usr/local/include -L /usr/local/lib -lpthread translate.cpp -o translate
```

After translate.cpp is compiled, you can run the translator by navigating to the directory containing the "translate" file and entering:
```
./translate
```
This will start a loop that keeps detecting speech input and output the translated speech through voice.
