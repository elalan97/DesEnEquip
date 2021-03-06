#include <pgmspace.h>

#define SECRET
#define THINGNAME "MyESP32"

const char WIFI_SSID[] = "Flia_Gonzalez";
const char WIFI_PASSWORD[] = "770720970525";
const char AWS_IOT_ENDPOINT[] = "a1k1lhdwmaa0ia-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
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

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUafpTrG5kI1XOS0LICj8qAwThY5swDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMTAwOTA5MTEx
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJTbtTvSDhegjCI/SCo2
rOISEjhVWnc5SA9/MRUMSAmYaPMEw4w5SFJY0BJGmnXl/3xDut3dZrjwM4LolPox
WOdxQQE22gmdz2jxijQcnow0Y69skGFFlrDcGKDEZp10rRGocSlUc9b0Pd+rpbLV
yTNzYvA0QdREs9qmOvFGRAznp0AnugpZ7p1QeOQokAkfY/rQ3VMkuB/r3hJjJmwB
dvwxLjaYP50RHrmYtdmG2g9hNyUUpkK12/c8Aj/xAU2ZlBkxrXjpNS9GyHozbvQs
v3PnnJ+ZCrKGX5ktyELvchISWYw/Q+L5H44J0XJx1pnevysQWLUTUIuykRaUhKGo
3aUCAwEAAaNgMF4wHwYDVR0jBBgwFoAUhCzkUP5Sk3iIKPcrp6qQEyvIUbUwHQYD
VR0OBBYEFPQClt8aXVHVSXSO/riX+XDe48LbMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCIuwugXNyfMYvEB2vPLeCIu1zz
a+lNSYZBJT7b0eVruYjbeMnnJWYdi1WWexHDP0OCA1NPclQ55avFgbEMb14uLmHI
ZIjTZ9NqJhqJUUQjKSi4EJ9sjey9zAVMU9x/hcqffG0PjOPx7IGfLl9GEu0J5Kz6
q52S6XMPw2aAJ7C8iYIOfftG1EEBEXzzsZ7WFEM3fBEK4+iOTUi6R8HV7B3BbO31
dor7ERTwXSDvZ8ahJL8T5PHSs64udSqJKJfTcJ5VFgPUjQPtcwap0pSqx+1HPX0V
3QkKxzLVy1kP4pxvCInZ8ARxnVnMSzQz89Rv8VlKGMMlfwzSooH66LsrVxI/
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAlNu1O9IOF6CMIj9IKjas4hISOFVadzlID38xFQxICZho8wTD
jDlIUljQEkaadeX/fEO63d1muPAzguiU+jFY53FBATbaCZ3PaPGKNByejDRjr2yQ
YUWWsNwYoMRmnXStEahxKVRz1vQ936ulstXJM3Ni8DRB1ESz2qY68UZEDOenQCe6
ClnunVB45CiQCR9j+tDdUyS4H+veEmMmbAF2/DEuNpg/nREeuZi12YbaD2E3JRSm
QrXb9zwCP/EBTZmUGTGteOk1L0bIejNu9Cy/c+ecn5kKsoZfmS3IQu9yEhJZjD9D
4vkfjgnRcnHWmd6/KxBYtRNQi7KRFpSEoajdpQIDAQABAoIBADL11GGaU8C68b53
s5jgBueOEDbA4auXLJhBjugJwE+ooaUwqFFE+wFV7kWTbiWWi5RbC4oQ1a3SbZAP
V5Efe7QgDYUA5jwMjoj6x7l3Yr/U35uaqwLh8+iwMK45DngxDV7SL4taoh2gl94O
wTcsASlgAysAeNjWfEwKRHt89qcD0Y6n7kgC33pN4CruPkeNF031xYjPZnLBNB68
UwaPMvXNKb6BT+kTsytN0hTvPPuDYo0yzUZK5Y/HraYE0oFoom5IaX03V8R2hcL3
Eom0eV9FGiz8O0bWKoOeqgFz3cjyNvqMt1HOjRm41OIRXSzxmG+2kccts8r9bQ3X
2J+QJYECgYEAxZM/5UOMGIZMZ2tuiLrsRmwIfzMdggsQ/GY2belVExcERi/UJ1yw
qxqdtJKvJWrNO8xZm0gJ/0PATSux8LjPtpadypXZDC5iOqRfYv77BM16txdOO33E
DuKaD9yUAteCMYbOewh56elqV9tzYewHMgdGrHnC4fDi57+xr1/Zr6kCgYEAwOCC
LZgxBRYtzS79Mrwzlb28JETCKjxiT59Mgys+4VnJXmCNb1pOJZYdZwZKj97bekRz
W8BLbKrvKaBtVrSzjHbQxh1WTI9bj2ps+Oqpl7zaPFz/RUoxnjyca0+bS3uOSTGI
fx1W68r8JFhZVeQIJKcbrCqGNXRSbBj8l46o650CgYEAu0xMVlsihF1MMP53WsdZ
Fal0pKEgaBd1ktCS6L86F07Kjn7o8Ce+k3Y36ubjguUsinO+vqYcVBE2S/IQTdPl
lYJTM6m6iQGvvUf15TMzY+onW0qMr3kaU8IdqsvAxLDoi2rwc1IlwMm2NnOjfkDy
0Up0hS0owmhJssjW+Ro0k4ECgYEAuLFDdq2ZoylNyoEIbCDTtLvvATvmQdN4wI3m
EmTC3b/Al+MVDGAJHOzWUuUvWP0qZbZOULmef/xe8BlzGegHVqYf3NYS4VUVdAuR
NfpfU7G/uLXEq3EUelXH4upj5q/13BjWgAJ0TW4ebB89zIWDVrW+ReqigWVV17VF
i0tMbfECgYEAnKylQBAZCEhPPKYZj745VK/VZUBLFV+W4GSahB6eDIW8iFzAWk9O
zfrje+HPuR9aVZVKTp2u72VaTvlUXzkYVU3rqPcBOHvV1Az3DKrwFCWGPGbWY8Ug
PkM9ShTMEoayf2pOD0ixwkOXf7ddgFNBjb3sO+4sKsIsPjUP70VxScY=
-----END RSA PRIVATE KEY-----
)KEY";
