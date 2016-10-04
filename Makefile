build_model_bin = bin/build_model
humming_bin = bin/humming
model_dir = models
midi_list = bin/48plus2000_midilist.txt

test_all: run_build_model test_search

test_search:
	bin/humming models/QBH.Model models/QBHModel.info WAVqueries/00013.wav test.txt

run_build_model: 
	$(build_model_bin) $(midi_list) $(model_dir)
	
build_all: build_fuzzy_search build_humming build_build_model
	
build_fuzzy_search:
	g++ -m32 -g -w -fpermissive -c src/SDFuzzySearch/*.cpp;
	
build_build_model:
	g++ -m32 -g -w -fpermissive -c src/SDHBuildModel/*.cpp src/SDHBuildModel/*.c;\
	g++ -m32 *.o; mv *.o *.out bin; mv bin/a.out $(build_model_bin);

build_humming:
	g++ -g -m32 -w -fpermissive -c src/SDHumming/*.cpp; \
	g++ -m32 *.o; mv *.o *.out bin; mv bin/a.out $(humming_bin);

clean:
	rm bin/*.o

