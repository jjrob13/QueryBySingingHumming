import subprocess
import os, re
import music21
from dotenv import load_dotenv, find_dotenv
import pandas

load_dotenv(find_dotenv())
project_root = os.path.join(os.path.dirname(__file__), os.pardir)

def get_music21_obj(wav_file):
	"""Converts a wav_file to a list of notes and
		subsequently to a music21 stream object"""
	command = 'aubionotes -v %s 2>&1' % wav_file
	output = subprocess.check_output(command, shell=True)
	lines = output.split('\n')
	patt = r'(\d+\.\d+).*(\d+\.\d+).*(\d+\.\d+).*'

	note_pairs = [(re.search(patt, o).group(1),
				re.search(patt, o).group(2),
				re.search(patt, o).group(3))
				for o in lines\
				if re.search(patt, o)]

	str_pitches, str_on_t, str_off_t = zip(*note_pairs)
	pitches = map(float, str_pitches)
	on_ts = map(float, str_on_t)
	off_ts = map(float, str_off_t)

	stream = music21.stream.Stream()
	for p, t_on, t_off in zip(pitches, on_ts, off_ts):
		pitch = music21.pitch.Pitch()
		pitch.ps = p
		stream.append(music21.note.Note(pitch))

	return stream

def stream_to_midi_wav(song_obj):
	"""Converts the song object to a midi file, then converts the midi file to wav"""
	tmp_midi_path = '.tmp.mid'
	mf = music21.midi.translate.streamToMidiFile(song_obj)
	mf.open(tmp_midi_path, 'wb')
	mf.write()
	mf.close()

	midi_to_wav(tmp_midi_path, os.environ['QUERY_MIDI_WAV_PATH'])
	os.remove(tmp_midi_path)
	return os.environ['QUERY_MIDI_WAV_PATH']


def midi_to_wav(source_path, target_path):
	template = 'timidity %s -Ow -o %s'
	command = template % (source_path, target_path)
	os.system(command)

def get_prediction_df(query_path):

	abs_query_path = os.path.abspath(query_path)
	command = 'cd %s; bin/humming models/QBH.Model models/QBHModel.info %s test.txt' % (
		project_root, abs_query_path)

	output = subprocess.check_output(command, shell=True)
	song_results = output.split('\n')[:-2]
	id_filename_error = [re.sub('[^0-9\. ]+', '', s).split() for s in song_results]

	ids, filenames, errors = zip(*id_filename_error)
	wav_filenames = [f + '.wav' for f in filenames]
	midi_filenames = [f + '.mid' for f in filenames]
	wav_paths = [os.path.join(project_root,
			os.environ['MIDI_WAV_DIR'], wav_f) for wav_f in wav_filenames]
	
	midi_paths = [os.path.join(project_root,
			os.environ['MIDI_DIR'], midi_f) for midi_f in midi_filenames]
	
	df_map = {'id' : ids,
		'wav_paths' : wav_paths,
		'midi_paths' : midi_paths,
		'error' : errors,
		'rank' : range(1, len(filenames) + 1)}
	
	col_order = ['id', 'midi_paths', 'error', 'rank', 'wav_paths']
	res_df = pandas.DataFrame(df_map)[col_order]
	return res_df
	
