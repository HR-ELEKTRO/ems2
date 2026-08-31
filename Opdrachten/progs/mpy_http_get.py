import requests

response = requests.get("http://example.com") # GET-request naar example.com
print("Status:", response.status_code)
inhoud = response.text
print("Inhoud:", inhoud)
response.close()
