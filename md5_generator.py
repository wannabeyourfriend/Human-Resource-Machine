import hashlib

def generate_md5(file_path, chunk_size=1024):
    md5 = hashlib.md5()
    with open(file_path, 'rb') as f:
        while chunk := f.read(chunk_size):
            md5.update(chunk)
    return md5.hexdigest()

if __name__ == "__main__":
    file_path = input("Enter the file path: ")
    md5_hash = generate_md5(file_path)
    print(f"MD5: {md5_hash}")