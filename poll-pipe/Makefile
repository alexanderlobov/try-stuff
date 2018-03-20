CXXFLAGS=-std=c++11
all: poller_zmq poller_system
poller_zmq: poller_zmq.o
	$(CXX) $^ -o $@ $(CXXFLAGS) -lzmqpp
poller_system: poller_system.o
	$(CC) $^ -o $@ $(CFLAGS)
