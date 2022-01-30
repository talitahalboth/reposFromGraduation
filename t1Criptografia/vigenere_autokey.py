import sys

range_t=16
alphabet_e=range_t*range_t

def encrypt_va(key_s, message_s):
	#Change it to array to use useful methods
	key=[]
	for e in key_s:
		key.append(e)

	message=[]
	for e in message_s:
		message.append(e)
	
	cipher=[]
	for i in range(len(message)):
		key.append(message[i])

		p = ord(message[i])
		k = ord(key[i])
		c = (p+k)%alphabet_e
		cipher.append(chr(c))

	return ''.join(cipher)


def decrypt_va(key_s, cipher_s):
	#Change it to array to use useful methods
	key_s=key_s
	key=[]
	for e in key_s:
		key.append(e)

	cipher=[]
	for e in cipher_s:
		cipher.append(e)
	
	message=[]
	i=0
	for i in range(len(cipher)):
		c = ord(cipher[i])
		k = ord(key[i])
		p = (c-k+alphabet_e)%alphabet_e
		message.append(chr(p))

		key.append(message[i])

	return ''.join(message)
