model_dir = models
build_model_bin = bin/build_model
humming_bin = bin/humming

prod_midi_list = bin/midi_paths.txt
prod_wav = data/processed/queries/test.wav
test_wav = query.wav
test_midi_list = bin/48plus2000_midilist.txt
single_track_list = bin/single_midi_paths.txt

test_all: run_build_model test_search

query_test_wav:
	bin/humming models/QBH.Model models/QBHModel.info $(test_wav) test.txt

query_prod_wav:
	bin/humming models/QBH.Model models/QBHModel.info $(prod_wav) test.txt

build_prod_model: 
	$(build_model_bin) $(prod_midi_list) $(model_dir)

build_test_model:
	$(build_model_bin) $(test_midi_list) $(model_dir)

build_single_track_model:
	$(build_model_bin) $(single_track_list) $(model_dir)
	
build_all: build_fuzzy_search build_humming build_build_model
	
build_fuzzy_search:
	g++ -m32 -g -w -fpermissive -c src/SDFuzzySearch/*.cpp;
	
build_build_model:
	g++ -m32 -g -w -fpermissive -c src/SDHBuildModel/*.cpp src/SDHBuildModel/*.c;\
	g++ -m32 *.o; mv *.o *.out bin; mv bin/a.out $(build_model_bin);

build_test_model:

build_humming:
	g++ -g -m32 -w -fpermissive -c src/SDHumming/*.cpp; \
	g++ -m32 *.o; mv *.o *.out bin; mv bin/a.out $(humming_bin);

install:
	pip install numpy; pip install -r requirements.txt
	sudo apt-get install $$(python -c "import sys; print ' '.join(map(str.strip, open('requirements.sys').readlines()))")
	bash get_data.sh
	find . -name *.mid > $(build_prod_model)
	mkdir -p $(model_dir)
	make build_prod_model clean

clean:
	rm bin/*.o

