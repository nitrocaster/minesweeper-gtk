g++ -std=c++11 -c main.cc `pkg-config --cflags --libs gtkmm-2.4`
g++ -std=c++11 -c helloworld.cc `pkg-config --cflags --libs gtkmm-2.4`
g++ -std=c++11 main.o helloworld.o -o helloworld `pkg-config --cflags --libs gtkmm-2.4`
