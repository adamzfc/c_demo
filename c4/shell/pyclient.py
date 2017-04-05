import socket;

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
sock.connect(('127.0.0.1', 5555));
sock.send('0');

szBuf = sock.recv(1024);
print 'recv' + szBuf;
sock.close();
print 'end of connect';
