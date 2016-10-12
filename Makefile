GCC = g++ -m32 -g -w -fpermissive 
model_dir = models
build_model_bin = bin/build_model
humming_bin = bin/humming

prod_midi_list = bin/midi_paths.txt
prod_wav = data/processed/queries/test.wav
test_wav = WAVqueries/00013.wav
test_midi_list = bin/48plus2000_midilist.txt

test_all: run_build_model test_search

query_test_wav:
	bin/humming models/QBH.Model models/QBHModel.info $(test_wav) test.txt

query_prod_wav:
	bin/humming models/QBH.Model models/QBHModel.info $(prod_wav) test.txt

build_prod_model: 
	$(build_model_bin) $(prod_midi_list) $(model_dir)

build_test_model:
	$(build_model_bin) $(test_midi_list) $(model_dir)
	
build_all: build_fuzzy_search build_humming build_build_model
	
build_fuzzy_search:
	$(GCC) -c src/SDFuzzySearch/*.cpp;
	
build_build_model:
	$(GCC) -c src/SDHBuildModel/*.cpp src/SDHBuildModel/*.c;\
	$(GCC) *.o; mv *.o *.out bin; mv bin/a.out $(build_model_bin);

build_test_model:

build_humming:
	$(GCC) -c src/SDHumming/*.cpp; \
	$(GCC) *.o; mv *.o *.out bin; mv bin/a.out $(humming_bin);

clean:
	rm bin/*.o

