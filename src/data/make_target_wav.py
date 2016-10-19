from dotenv import load_dotenv, find_dotenv
import os

load_dotenv(find_dotenv())

def midi_to_wav(source_path, target_path):
	template = 'timidity %s -Ow -o %s'
	command = template % (source_path, target_path)
	os.system(command)

if __name__ == '__main__':
	midi_dir = os.environ['MIDI_DIR']
	midi_wav_dir = os.environ['MIDI_WAV_DIR']
	for root, folders, files in os.walk(midi_dir):
		for filename in files:
			if filename.lower().endswith('.mid'):
				filepath = os.path.join(root, filename)
				target_path = os.path.join(midi_wav_dir,
					os.path.splitext(filename)[0] + '.wav')
				midi_to_wav(filepath, target_path)
