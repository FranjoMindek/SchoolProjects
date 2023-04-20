from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Hash import HMAC, SHA256
import json
import sys
import getpass
import os

# CONFIGURABLE
MASTERPASSWORD = "Ovo_bi_se_spremilo_negdje_gdje_se_ne_moze_tako_lako_procitati"
HASH_SECRET = 'Test123321Test'
KEY_SIZE = 32  # AES256 requires key of this size
HASH_SIZE = 32 # SHA256
TAG_SIZE = 16
SALT_SIZE = 16
# NOT CONFIGURABLE
NONCE_SIZE = 16  # always 16 bytes long for AES
BLOCK_SIZE = HASH_SIZE + SALT_SIZE



def save_init(master_pass, init_dict):
    dict_salt = get_random_bytes(SALT_SIZE)
    init_dict_encoded = json.dumps(init_dict).encode()
    key = scrypt(master_pass, dict_salt, KEY_SIZE, N=2 ** 14, r=8, p=1)
    cipher_encode = AES.new(key, AES.MODE_EAX, mac_len=TAG_SIZE)
    nonce = cipher_encode.nonce
    ciphertext, tag = cipher_encode.encrypt_and_digest(init_dict_encoded)
    f = open("init.bin", "wb")
    f.write(dict_salt)
    f.write(nonce)
    f.write(tag)
    f.write(ciphertext)
    f.close()
    return


def read_init(master_pass):
    if os.stat("init.bin").st_size == 0:
        return {}
    else:
        try:
            read = open("init.bin", "rb")
            init_salt = read.read(SALT_SIZE)
            init_nonce = read.read(NONCE_SIZE)
            init_tag = read.read(TAG_SIZE)
            init_ciphertext = read.read()
            read.close()
            key = scrypt(master_pass, init_salt, KEY_SIZE, N=2 ** 14, r=8, p=1)
            cipher_decode = AES.new(key, AES.MODE_EAX, nonce=init_nonce, mac_len=TAG_SIZE)
            init_text_byte = cipher_decode.decrypt_and_verify(init_ciphertext, init_tag)
            init_dict = json.loads(init_text_byte.decode())
            return init_dict
        except(ValueError, KeyError):
            print("Failed to read init data")
            return None


def save_user(location, hash_secret, username, change):  # must return new dictionary
    index = 0
    password = getpass.getpass(prompt="Password: ")
    password_repeat = getpass.getpass(prompt="Repeat password: ")
    if username in location and change:
        index = location[username][0]
        if password != password_repeat:
            print("Password change failed. Password mismatch")
            return None
    elif username not in location and not change:
        location[username] = [len(location), False]
        if password != password_repeat:
            print("User add failed. Password mismatch.")
            return None
    elif change:
        print("Attempting to change password of non-existing user")
        return None
    else:
        print("Attempting to create a new user with already existing username")
        return None
    hash_salt = get_random_bytes(SALT_SIZE)
    key = scrypt(hash_secret, hash_salt, KEY_SIZE, N=2 ** 14, r=8, p=1)
    h = HMAC.new(key, password.encode(), digestmod=SHA256)
    byte_line = hash_salt + h.digest() 
    if not change:
        write = open("data.bin", "ab")
        write.write(byte_line)
        write.close()
        print(f'User add successfully added.')
        return location
    else:
        offset = index * BLOCK_SIZE
        write = open("data.bin", "r+b")
        write.seek(offset)
        write.write(byte_line)
        write.close()
        print('Password change successful.')
        return None


def delete_user(location, username):
    if username in location:
        index = location[username][0]
        del location[username]
        for k, v in location.items():
            if v[0] > index:
                location[k] = [v[0] - 1, v[1]]
        with open("data.bin", "r+b") as data:
            byte_data = data.read()
            new_byte_data = byte_data[: index*BLOCK_SIZE] + byte_data[(1+index)*BLOCK_SIZE :]
            data.seek(0)
            data.truncate()
            data.write(new_byte_data)
            # print(f'Old data = {byte_data}\nNew data = {new_byte_data}')
            print("User successfuly removed.")
        return location
    else:
        print("Attempting to delete a non-existing username")
        return None


def force_change(location, username):
    if username in location:
        info = location[username]
        info[1] = True
        location[username] = info
        print("User will be requested to change password on next login.")
        return location
    else:
        print("Attempting to force password change on non-existing username")
        return


if sys.argv[1] == 'add':
    if len(sys.argv) != 3:
        print('Invalid number of arguments')
    else:
        init_data = read_init(MASTERPASSWORD)
        if init_data is not None:
            return_data = save_user(init_data, HASH_SECRET, sys.argv[2], False)
            if return_data is not None:
                save_init(MASTERPASSWORD, return_data)
elif sys.argv[1] == 'passwd':
    if len(sys.argv) != 3:
        print('Invalid number of arguments')
    else:
        init_data = read_init(MASTERPASSWORD)
        if init_data is not None:
            return_data = save_user(init_data, HASH_SECRET, sys.argv[2], True)
            if return_data is not None:
                save_init(MASTERPASSWORD, return_data)
elif sys.argv[1] == 'del':
    if len(sys.argv) != 3:
        print('Invalid number of arguments')
    else:
        init_data = read_init(MASTERPASSWORD)
        if init_data is not None:
            return_data = delete_user(init_data, sys.argv[2])
            if return_data is not None:
                save_init(MASTERPASSWORD, return_data)
elif sys.argv[1] == 'forcepass':
    if len(sys.argv) != 3:
        print('Invalid number of arguments')
    else:
        init_data = read_init(MASTERPASSWORD)
        if init_data is not None:
            return_data = force_change(init_data, sys.argv[2])
            if return_data is not None:
                save_init(MASTERPASSWORD, return_data)
elif sys.argv[1] == 'clear':
    open('data.bin', 'w').close()
    open('init.bin', 'w').close()
else:
    print(f'Invalid command {sys.argv[1]}')
