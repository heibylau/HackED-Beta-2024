
//Amazon trust services endpoint
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

//Device certificate
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUPUZdLo2aAmC/8L5tIMCfwc7euUkwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTExMDA0NTcz
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANbI52pDj6rJ65d96jiq
q2Kt3FKaqB10+LrbPokgP+4I78QSZhswhaxR+oG5KbTr6wqsOrH27A0yaoY+BSn1
PF2dTtnyS0yZuipsCyi3xHBXABAOIVz17Cw9bu5ayPp3ZBPGUB25X36lCjaAR0qi
0/VpB9yjtqSNle8rV4v0HRFzW0l7AA3GAR6RpXFUIMwwY6q+m4DsYJWdbyps7LCN
xA3QIPvP/KIqc6u/PyXpPWcXOM9v4y6Ik/RS4BOV7Ew0nn7BlGS7alUSrFtCafxq
jasmy+96jT1pf2ZP/R6qEtWHveTrlJA90KNiUlZ24E81jXjNa7oznzx9XfsfXT93
ZMkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUwRm5gk0J965VtJ9AI8KDkewq5QswHQYD
VR0OBBYEFOrzRloeH7bNYZqQUdb3Il4B/7XmMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCMyXMeFj+Yb8rxhJYOFXkZa4dW
i0eoxHgvJbtUILVPY1S1zFpXOtWVaR9ae6nfY8zWnptBlBicPgkLMmXqkX1XmZb3
hj/Fyua8cE/iJ4IPT7UfhRdxGrDf7Art85dsSu97soL3294csaYFxp7jf3ktUs4Q
l+vmuZCohmTdo1na/LsNV1QidgX+19KdCeu2kri9n53tGcfaDgo/xqeNwmwEB2A9
15s3CYLde9E7/g6u62i/GsxrpuGN+HqiouHH+UaollQepbjY+LLIE51XJg+WOgZo
GqrVyJxXnF1dlKlYq8GQe1x30djanqnga9eq0EYHTvj4flK9+S4wpBU7eoYm
-----END CERTIFICATE-----
)KEY";


//Private key file
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA1sjnakOPqsnrl33qOKqrYq3cUpqoHXT4uts+iSA/7gjvxBJm
GzCFrFH6gbkptOvrCqw6sfbsDTJqhj4FKfU8XZ1O2fJLTJm6KmwLKLfEcFcAEA4h
XPXsLD1u7lrI+ndkE8ZQHblffqUKNoBHSqLT9WkH3KO2pI2V7ytXi/QdEXNbSXsA
DcYBHpGlcVQgzDBjqr6bgOxglZ1vKmzssI3EDdAg+8/8oipzq78/Jek9Zxc4z2/j
LoiT9FLgE5XsTDSefsGUZLtqVRKsW0Jp/GqNqybL73qNPWl/Zk/9HqoS1Ye95OuU
kD3Qo2JSVnbgTzWNeM1rujOfPH1d+x9dP3dkyQIDAQABAoIBAHmMeGnKkiM04f55
Y3NuIk9V1LlqjHkfGSOlr14qwgMTS5zKTL5WV0+NlRaUkuWwHPONRCoycqOFRINz
1bhI8ECKJXVxiOtwk8ouGqKQXLq2gXKUjIzvHxhqK7z344Tay+fk8rHflgs1mvH8
5lt2ijz3k1tpypKVDaSsAn9RRqH4fNoPI15OOTZuGXoO2JDY66MsXTQEN7IGfxiB
rPAjbJAoUTNkKD8npENgshBZzCsHE/HxbvILLVis1TjYelsWvycMmyMGBteAmGi3
fTYbE5Aq0ACtNkEsmFclKc0RFpkP3xpFOAj7yL3m3ZbtEpcLFdcXQHcf/lVMm3yR
EX5t1gECgYEA75DjJFlNjfIgLOCOKK9KjCInWkFD/fpaj8wbqDFK6pesBc2BSb8n
MLCJzAnzOiAfVVn1ZyNdusHDGyAvzJ/ZPrtR08j+v5Jv4h7Vi8cCF3QY7/htuFJ/
PgR//jQfCdr6WaBUAQiVNnAf6pxZlowO3opHX+pHqk/GpeKyk6Yuz7UCgYEA5YTT
EmPy4EGY5hDTiQMnsD5uKyh0nk+7k2R/LExYhLqwzCKsmlih1HcWmWy4odX3O6Ni
Zwk4U4nZcoX3/i9xD2DXxZSpKVd1LcnmT6WrGc9AcIm71NF+grychjCY7NtdErF0
xZJYTO+P9xfqMvu2YyekJOSuZ2oZHaMNDKOrZUUCgYAl8JE4cXgp0b2svcdlxBUP
Sl1nGsz0zRBIk6+RnHTb4DdbF+ew0TgYquy3xp+hhfLQZpXJxr0SVZtbkWZghrQ2
Dh5wZvWJS1yyt+Vj5Jl9M2K7pmFh/pauMLJAhOqhee+KAC0tmLlgzLMRSb+aawXz
0nxpQUYmP8oa/WMApSHmvQKBgQCGTnltE4u2auxcBJCkZnI9EetJ2fyT/zhWgcJh
W7OYx95ZNhkmoKLiP2W8FgDcwuZPwcX9YUnSqKHUAE0kMwLH6vWYqutqQ8FQMAtT
pDBBhCPDNvXxDT4optI5PArg32TRYYJhcse1DaKDBz2G5ADQeQv2gtMDtPRJgXZL
ZSMQuQKBgQCF6eJncwpAMydaJgObUIwd7pm3jTJyz3WQTF+0MMg7gsgZJqAW7Xdk
eoBt7r6AuzwWdrZWDlpnblm7ns+E27xoPg3ZGmvOLpTr5xvbhe4bOu4Cpwbfby9g
Qdxr3LyRBec+NFCzOWcnJprsH4ipH9IbZwZi5KrkV/ufX7BkTIkWrg==
-----END RSA PRIVATE KEY-----
)KEY";
