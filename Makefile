main: src/main.cpp
	g++ -Iinclude src/main.cpp src/cpu.cpp src/utils.cpp src/system.cpp src/gpu.cpp src/ram.cpp -o main \
  	-lftxui-component -lftxui-dom -lftxui-screen

clean:
	rm main