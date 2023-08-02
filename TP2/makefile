
servidor:
		g++ serverMain.cpp Resolver.cpp Socket.cpp Servidor.cpp Protocolo.cpp Juego.cpp Partida.cpp liberror.cpp Thread.cpp ThreadAceptador.cpp ThreadCliente.cpp JuegoProtected.cpp  -o servidor
		./servidor 7081
		rm servidor

cliente:
		g++ clienteMain.cpp Cliente.cpp Resolver.cpp Socket.cpp Protocolo.cpp liberror.cpp -o cliente
		./cliente "127.0.0.1" 7081
		rm cliente
