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
```python
git clone http://github.com/cmusphinx/sphinxbase
cd 
```
