zmqpp_path=$(HOME)/src/zmqpp/install/usr/local
zmqpp_lib=$(zmqpp_path)/lib
CXXFLAGS=-std=c++11 -I$(zmqpp_path)/include
LDFLAGS=-L$(zmqpp_lib)
all: poller_zmq poller_system
poller_zmq: poller_zmq.o
	$(CXX) $^ -o $@ $(CXXFLAGS) -lzmqpp $(LDFLAGS) -Wl,-rpath=$(zmqpp_lib)
poller_system: poller_system.o
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	rm *.o poller_system poller_zmq
