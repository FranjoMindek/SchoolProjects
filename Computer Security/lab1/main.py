from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import json
import sys

# CONFIGURABLE
keysize = 32   # AES256
paddingSize = 256
tagSize = 16
saltSize = 16
# NOT CONFIGURABLE
nonceSize = 16  # always 16 bytes long for AES
# TOTAL
blockSize = paddingSize+tagSize+saltSize+nonceSize


def saveInit(masterPass, initDict):
    if not initDict:
        open('data.bin', 'w').close()
        print('Password manager initialized')
    dictSalt = get_random_bytes(saltSize)
    initDictEncoded = json.dumps(initDict).encode()
    key = scrypt(masterPass, dictSalt, keysize, N=2**14, r=8, p=1)
    cipherEncode = AES.new(key, AES.MODE_EAX, mac_len=tagSize)
    nonce = cipherEncode.nonce
    ciphertext, tag = cipherEncode.encrypt_and_digest(initDictEncoded)
    f = open("init.bin", "wb")
    f.write(dictSalt)
    f.write(nonce)
    f.write(tag)
    f.write(ciphertext)
    f.close()
    return


def readInit(masterPass):
    try:
        read = open("init.bin", "rb")
        initSalt = read.read(saltSize)
        initNonce = read.read(nonceSize)
        initTag = read.read(tagSize)
        initCiphertext = read.read()
        read.close()
        key = scrypt(masterPass, initSalt, keysize, N=2**14, r=8, p=1)
        cipherDecode = AES.new(key, AES.MODE_EAX, nonce=initNonce, mac_len=tagSize)
        initTextByte = cipherDecode.decrypt_and_verify(initCiphertext, initTag)
        initText = json.loads(initTextByte.decode())
        return initText
    except(ValueError, KeyError):
        print("Failed to decrypt init data")
        return None


def savePassword(location, masterPass, addressPass, address): # must return new dictionary
    if address in location:
        append = False
        index = location[address]
    else:
        append = True
        location[address] = len(location)
    passwordSalt = get_random_bytes(saltSize)
    addressPassEncoded = addressPass.encode()
    key = scrypt(masterPass, passwordSalt, keysize, N=2**14, r=8, p=1)
    cipherEncode = AES.new(key, AES.MODE_EAX, mac_len=tagSize)
    nonce = cipherEncode.nonce
    ciphertext, tag = cipherEncode.encrypt_and_digest(pad(addressPassEncoded, paddingSize))
    byteLine = passwordSalt + nonce + tag + ciphertext
    if append:
        write = open("data.bin", "ab")
        write.write(byteLine)
        write.close()
        print(f'Stored password for {address}')
    else:
        offset = index * blockSize
        write = open("data.bin", "r+b")
        write.seek(offset)
        write.write(byteLine)
        write.close()
        print(f'Updated password for {address}')
    return location


def loadPassword(location, masterPass, address):
    if address in location:
        index = location[address]
    else:
        print(f'There is no password saved under {address}')
        return
    try:
        offset = blockSize * index
        read = open("data.bin", "rb")
        read.seek(offset)
        addressSalt = read.read(saltSize)
        addressNonce = read.read(nonceSize)
        addressTag = read.read(tagSize)
        addressCiphertext = read.read(paddingSize)
        read.close()
        key = scrypt(masterPass, addressSalt, keysize, N=2**14, r=8, p=1)
        cipherDecode = AES.new(key, AES.MODE_EAX, nonce=addressNonce, mac_len=tagSize)
        addressTextByte = unpad(cipherDecode.decrypt_and_verify(addressCiphertext, addressTag), paddingSize)
        addressText = addressTextByte.decode()
        print(f'Password for {address} is: {addressText}')
    except(ValueError, KeyError):
        print(f'Failed to decrypt {address} data')
    return


if len(sys.argv) > 2:
    mp = sys.argv[2]
if sys.argv[1] == 'init':
    if len(sys.argv) < 3:
        print('Not enough arguments to init')
    else:
        saveInit(mp, {})
elif sys.argv[1] == 'put':
    if len(sys.argv) < 5:
        print('Not enough arguments to put password')
    else:
        location = readInit(mp)
        if not (location is None):
            saveInit(mp, savePassword(location, mp, sys.argv[4], sys.argv[3]))
elif sys.argv[1] == 'get':
    if len(sys.argv) < 4:
        print('Not enough arguments to get password')
    else:
        location = readInit(mp)
        if not (location is None):
            loadPassword(location, mp, sys.argv[3])
elif sys.argv[1] == 'test':
    if len(sys.argv) < 3:
        print('Not enough arguments to start test')
    else:
        mpk = 'UpsKrivi'
        saveInit(mp, {})
        saveInit(mp, savePassword(readInit(mp), mp, 'GooglePass', 'www.google.hr'))
        saveInit(mp, savePassword(readInit(mp), mp, 'FacebookPass', 'www.facebook.hr'))
        saveInit(mp, savePassword(readInit(mp), mp, 'FerPass', 'www.fer.hr'))
        saveInit(mp, savePassword(readInit(mp), mp, 'TvzPass', 'www.tvz.hr'))
        loadPassword(readInit(mp), mp, 'www.google.hr')
        loadPassword(readInit(mp), mp, 'www.facebook.hr')
        loadPassword(readInit(mp), mp, 'www.fer.hr')
        loadPassword(readInit(mp), mp, 'www.tvz.hr')
        saveInit(mp, savePassword(readInit(mp), mp, 'FerPass2', 'www.fer.hr'))
        saveInit(mp, savePassword(readInit(mp), mp, 'GooglePass2', 'www.google.hr'))
        loadPassword(readInit(mp), mp, 'www.fer.hr' )
        loadPassword(readInit(mp), mp, 'www.google.hr')
        print()
        print('A sada primjer s krivim master password:')
        readInit(mpk)
else:
    print(f'Invalid command {sys.argv[1]}')
