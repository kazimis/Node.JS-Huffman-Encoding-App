import hashlib
import uuid

import sys

# adapted from https://www.pythoncentral.io/hashing-strings-with-python/
def check_password(hashed_password, user_password):
    password, salt = hashed_password.split(':')
    return password == hashlib.sha256(salt.encode() + user_password.encode()).hexdigest()

def main():
    if (sys.argv[1] =="hash"):
        salt = uuid.uuid4().hex
        print(hashlib.sha256(salt.encode() + sys.argv[2].encode()).hexdigest() + ':' + salt)
    elif (sys.argv[1] == "check"):
        print(check_password(sys.argv[2], sys.argv[3]));

if __name__ == '__main__':
    print(sys.version)
    main()
