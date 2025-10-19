import secrets
import string
import bcrypt

def generate_secure_password(length=10):
    characters = string.ascii_letters + string.digits + ".!$@"
    while True:
        password = ''.join(secrets.choice(characters) for _ in range(length))
        if (any(c.islower() for c in password) and any(c.isupper() for c in password) and any(c.isdigit() for c in password) and any(c in ".!$@" for c in password)):
            return password

def generate_url_safe(length=32):
    return secrets.token_urlsafe(length)

def generate_hex_token(length=32):
    return secrets.token_hex(length)

def check_identical(seq1, seq2):
    return secrets.compare_digest(seq1, seq2)

def generate_encryption_key(message_length=100):
    return secrets.randbits(message_length * 8)

def hash_password(password):
    salt = bcrypt.gensalt()
    hashed_password = bcrypt.hashpw(password.encode('utf-8'), salt)
    return hashed_password

def verify_password(password, hashed_password):
    return bcrypt.checkpw(password.encode('utf-8'), hashed_password)
 
print(generate_secure_password())
print(generate_url_safe())
print(generate_hex_token())
print(check_identical("secventa", "secventa"))
print(generate_encryption_key())
