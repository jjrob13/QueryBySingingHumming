mkdir Jang48plus2000noiseESSEN;
wget -O Jang48plus2000noiseESSEN/midi.zip https://github.com/EliosMolina/QueryBySingingHumming/blob/master/Jang48plus2000noiseESSEN/Jang48plus2000noiseESSEN.zip?raw=true;
cd Jang48plus2000noiseESSEN; unzip midi.zip; ls *.mid | xargs -L1 sh -c 'timidity $1 -Ow -s 8k -o $(basename $1 .mid).wav' dummy
cd Jang48plus2000noiseESSEN; mkdir wav; mv *.wav wav;
cd Jang48plus2000noiseESSEN; mkdir midi; mv *.mid midi;
