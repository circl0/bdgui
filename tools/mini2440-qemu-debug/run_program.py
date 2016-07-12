import paramiko
import os.path
import json
import getopt
import sys

file_path = ''
file_name = ''
target_path = ''
options = {}

# get the args
try:
    options, args = getopt.getopt(sys.argv[1:], "s:d:", ["src=", "dest="])
except getopt.GetoptError:
    exit()

for name, value in options:
    if name in ("-s", "--src"):
        print(value)
        file_path = value
        file_name = os.path.basename(file_path)
    if name in ("-d", "--dest"):
        target_path = value

# load the setting.json
setting = {}
with open('setting.json', 'r') as f:
    setting = json.load(f)

# push the program into mini2440-qemu
t = paramiko.Transport((setting["hostname"], setting["port"]))
t.connect(hostkey=None, username=setting["username"], password=setting["password"])
sftp = paramiko.SFTPClient.from_transport(t)
sftp.put(file_path, '%s' % target_path)
t.close()

# ssh into mini2440-qemu and run the program
# print stdout stream from the program
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(setting["hostname"], port=setting["port"], username=setting["username"], password=setting["password"])

try:
    stdin, stdout, stderr = client.exec_command("chmod +x %s" % target_path)
    stdin, stdout, stderr = client.exec_command(target_path)
    for line in stdout:
        sys.stdout.write(line)
        sys.stdout.flush()
except:
    pass
finally:
    client.close()

