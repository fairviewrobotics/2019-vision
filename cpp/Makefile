BIN = bin/main

HEADERS = \
LineSensingPipeline.h LineSensingPipelineRunner.h


OBJS = \
LineSensingPipeline.o LineSensingPipelineRunner.o Main.o

#CXXFLAGS += -DDISPLAY_DEBUG

CXXFLAGS += -Wall -g
LDFLAGS += `pkg-config --cflags --libs opencv` -g

all: $(BIN)

%.o: %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)