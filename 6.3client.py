import socket
import math
ClientSocket = socket.socket()
host = '192.168.56.101'
port = 8888

print('Waiting for connection')
try:
    ClientSocket.connect((host, port))
except socket.error as e:
    print(str(e))

Response = ClientSocket.recv(1024)
print(Response)
while True:
    print("Choose Number:")
    print("1-Logarithmic(Log)")
    print("2-Square Root")
    print("3-Exponential")    
    print("4-Exit\n")
    
    num = input('Enter Your Option: ')
    ClientSocket.send(str.encode(num))
    number = input('Enter number: ')
    ClientSocket.send(str.encode(number))
    if (num == '1'):
      print("Log Operation")
    elif (num == '2'):
      print("Square Root Operation")
    elif (num == '3'):
      print("Exponential Operation")
    elif (num == '4'):
      print("Bye!")
      ClientSocket.close()
    else:
      print("Invalid option. Try again!")
    result = ClientSocket.recv(1024)
    print("Result:",result.decode('utf-8'))
    print("\n")
ClientSocket.close()
