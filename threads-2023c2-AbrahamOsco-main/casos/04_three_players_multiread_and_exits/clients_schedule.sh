# Nota: los clientes son lanzados en orden por el sercom con unos segundos
# de diferencia. Asi, para cuando el Cliente 1 se conecta, el Cliente 0
# ya deberia estar conectado y el server deberia haber enviado el mensaje
# "Jugadores 1..." a *solo* el Cliente 0 por que para ese momento Client 0
# era el unico que estaba conectado. En otras palabras, el Cliente 1
# *no* ve el mensaje "Jugadores 1..." por que se lo perdio, "llego tarde".

# Entonces se espera estos reads den:
# - para el Cliente 0, "Juagadores 1..."
# - para el Cliente 1, "Juagadores 2..."
# - para el Cliente 2, "Juagadores 3..."
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__
echo 'Read 1' >> __client_2_pipe__

# Podemos pedir mas mensajes:
# - para el Cliente 0, "Juagadores 2..."
# - para el Cliente 1, "Juagadores 3..."
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

# Podemos pedir mas mensajes:
# - para el Cliente 0, "Juagadores 3..."
echo 'Read 1' >> __client_0_pipe__

sleep 1
echo 'Exit' >> __client_2_pipe__

# Esperamos en ambos "Jugadores 2..."
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

sleep 1
echo 'Exit' >> __client_1_pipe__

# Esperamos "Jugadores 1..."
echo 'Read 1' >> __client_0_pipe__

sleep 1
echo 'Exit' >> __client_0_pipe__
