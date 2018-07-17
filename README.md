# speech-to-speech-translator
This is a translator that compilate softwares and APIs to enable speech-to-speech translation.

Note that this is a compilation of softwares and APIs. By no means is this a standalone speech recognizor, translator, or speech synthesizer.

There are hardware prerequisites in addition to a computer. A microphone is needed for audio input and some form of audio output is needed.

Also, this STS translator is tested on linux with the "Raspberry Pi 2" but should work with other systems. Instructions for other systems are provided as well but might need some modifications.

Dependencies:

[pocketsphinx](https://github.com/cmusphinx/pocketsphinx) for speech recognition

[sphinxbase](https://github.com/cmusphinx/sphinxbase) for speech recognition

[flite](https://github.com/festvox/flite) for speech synthesizing

[ibm language-translator](https://www.ibm.com/watson/services/language-translator/) for translation

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
To use IBM's translator, you must first create an account [here](https://www.ibm.com/watson/services/language-translator/). IBM allows an account to have a certain number of characters translated free for each month and does not require a credit card during sign up. We need the URL and API key provided after sign up. 

URL:

On line 68 of translate.cpp, replace (your URL) with the URL IBM provided (e.g.). 

API:

On line 65 of translate.cpp, replace (your key) with the API key IBM provided (e.g.).

Other ajustments:

For lines 75, 239, and 244, (wav file) must be replaced with a path for the creation, deletion, and input of a wav file (e.g.).

For lines 177, 183, and 62, (text file) must be replaced with a path for the creation, deletion, and input of a text file (e.g.).
