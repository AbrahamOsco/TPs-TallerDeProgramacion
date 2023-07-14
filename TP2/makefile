
servidor:
		g++ serverMain.cpp Resolver.cpp Socket.cpp Servidor.cpp Protocolo.cpp Juego.cpp Partida.cpp  -o servidor
		./servidor 7081
		rm servidor

cliente:
		g++ clienteMain.cpp Cliente.cpp Resolver.cpp Socket.cpp Protocolo.cpp -o cliente
		./cliente "127.0.0.1" 7081
		rm cliente
