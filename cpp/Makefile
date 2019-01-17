BIN = bin/main

HEADERS = \
LineSensingPipeline.h LineSensingPipelineRunner.h


OBJS = \
LineSensingPipeline.o LineSensingPipelineRunner.o Main.o


CXXFLAGS += -Wall
LDFLAGS += `pkg-config --cflags --libs opencv`

all: $(BIN)

%.o: %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)