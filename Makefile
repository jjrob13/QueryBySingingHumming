build_all: build_fuzzy_search build_humming build_build_model
	

build_fuzzy_search:
	g++ -w -fpermissive -c src/SDFuzzySearch/*.cpp;
	
build_build_model:
	g++ -w -fpermissive -c src/SDHBuildModel/*.cpp src/SDHBuildModel/*.c;\
	g++ *.o; mv *.o *.out bin; mv bin/a.out bin/build_model

build_humming:
	g++ -w -fpermissive -c src/SDHumming/*.cpp; \
	g++ *.o; mv *.o *.out bin; mv bin/a.out bin/humming

clean:
	rm bin/*.o *.o

