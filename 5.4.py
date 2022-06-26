from netmiko import ConnectHandler

myserver = {
    'device_type': 'linux',
    'host': '192.168.56.101', #Your Server IP
    'username': 'shauqi', #Your Server Username
    'password': 'shauqi', #Your server password
    'port': 22,
    'secret':'',
}

net_connect = ConnectHandler(**myserver)
output = net_connect.send_command('uname -a')
print(output)