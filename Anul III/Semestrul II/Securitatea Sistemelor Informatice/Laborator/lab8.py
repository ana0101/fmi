import hashlib
import requests
import sys

def calc_sha256(filepath):
    with open(filepath, "rb") as f:
        file_bytes = f.read()
        sha256_hash = hashlib.sha256(file_bytes).hexdigest()
    return sha256_hash

def virus_total(hash_sha256):
    url = f"https://www.virustotal.com/api/v3/files/{hash_sha256}"
    headers = {
        "x-apikey": "889a8342d5e0338a4a47c7900bbcd1e48972d0d95bddc024682bc17e8d784252"
    }

    response = requests.get(url, headers=headers)
    
    if response.status_code == 200:
        json_data = response.json()
        stats = json_data.get("data", {}).get("attributes", {}).get("last_analysis_stats", {})
        malicious = stats.get("malicious", 0)
        total = sum(stats.values())
        print(f"{malicious} out of {total} vendors detected the file as malicious.")
    else:
        print(f"Error {response.status_code}")
        print(response.text)

sha256_hash = calc_sha256("malware.png")
virus_total(sha256_hash)
