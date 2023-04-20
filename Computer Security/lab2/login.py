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
KEY_SIZE = 32  # AES256
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


def login(location, hash_secret, username):  # must return new dictionary
    index = 0
    password = getpass.getpass(prompt="Password: ")
    if username in location:
        index = location[username][0]
    else:
        print("Username or password incorrect")
        return
    try:
        offset = BLOCK_SIZE * index
        read = open("data.bin", "rb")
        read.seek(offset)
        saved_salt = read.read(SALT_SIZE)
        saved_hash = read.read(HASH_SIZE)
        read.close()
        key = scrypt(hash_secret, saved_salt, KEY_SIZE, N=2 ** 14, r=8, p=1)
        h = HMAC.new(key, password.encode(), digestmod=SHA256)
        new_hash = h.digest()
        # print(f'Saved={saved_hash}\nNew={new_hash}')
        if location[username][1]:
            new_password = getpass.getpass(prompt="New password: ")
            new_password_repeat = getpass.getpass(prompt="Repeat new password: ")
            if new_password_repeat == new_password:
                info = location[username]
                info[1] = False
                location[username] = info
                hash_salt = get_random_bytes(SALT_SIZE)
                key = scrypt(hash_secret, hash_salt, KEY_SIZE, N=2 ** 14, r=8, p=1)
                h_new = HMAC.new(key, new_password.encode(), digestmod=SHA256)
                byte_line = hash_salt + h_new.digest()
                write = open("data.bin", "r+b")
                write.seek(offset)
                write.write(byte_line)
                write.close()
                print("Login successful.")
                return location
            else:
                print("Password change failed. Password mismatch.")
        elif new_hash == saved_hash:
            print("Login successful.")
        else:
            print("Username or password incorrect.")
    except(ValueError, KeyError):
        print(f'Failed to decrypt data')
    return None


init_data = read_init(MASTERPASSWORD)
if init_data is not None:
    login_data = login(init_data, HASH_SECRET, sys.argv[1])
    if login_data is not None:
        save_init(MASTERPASSWORD, login_data)


