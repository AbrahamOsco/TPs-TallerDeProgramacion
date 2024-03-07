echo 'Read 2' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

echo 'Chat hello' >> __client_0_pipe__
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

echo 'Chat bye' >> __client_0_pipe__
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

echo 'Chat what?' >> __client_1_pipe__
echo 'Read 1' >> __client_0_pipe__
echo 'Read 1' >> __client_1_pipe__

sleep 1
echo 'Exit' >> __client_0_pipe__
sleep 1
echo 'Exit' >> __client_1_pipe__
