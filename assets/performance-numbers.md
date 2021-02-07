
# render on GPU
mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
Key: P=DA29B6CA7A109BB63282E6B69B5E288B, Q=C3759A579B5A68CD1CE2744183982EA5, M=A691FED4860BAA17056D769B3FEF7B09504B2328376DCAEC9DBE398F42811B97, M^2=6C61A9BE48416439F825B750101D29B4A50DD31A389A898C25451502365FCC381A8023526005DF4EFE4DD645405A30D29DB31A05F35559AD05F0E408AD273311
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 3641770ms
Begin Task draw on GPU ... time required: 3148ms
Begin Task decrypt ... time required: 16459ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, without obfuscated
Key: P=B1CD116975517149B28FA3CFD657733D12A284490015E1EFCC1A742B7D1B392D, Q=EF0211E6675F0B59F02641A34457074F28D500D5EDEADE725C1A044F91C5EEB3, M=A5FFE34A3B8B1DEDAB24E1FC2C21725CC284D1C3B6749A423B9E5BAE2EA698146CC3D4BE4268656E932628B5F2511320BB041AAC28AE774E58B0B2F045D1D077, M^2=6BA3DAC44870AED92F72B518AFD573BE8FC88AC1A37BB4C5024C06F03A6897D5E7CE24754D9BEB401534CE70E3DD9B459FE43D67A7428214724C3C465596C4D0821932B884C3219645BCFC2F4D2C4DE633E4C30EC6DE78F519C6F255236A4D7FC2D612B808F61435111B5E0611D1747593332693E4E0ECEF35F72176320F9751
Begin Task create volume ... time required: 173ms
Begin Task encrypt volume ... time required: 3428ms
Begin Task draw on GPU ... time required: 387ms
Begin Task decrypt ... time required: 415000ms



# modPow
modPow() Naiv 2048bit        ... time required:  7479ms, addTwoIntsCounter: 24776765
modPow() Montgomery 2048bit  ... time required: 10078ms, addTwoIntsCounter: 36830577


modPow() Naiv  8192bit       ... time required: 22917ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 30174ms, addTwoIntsCounter: 2408179141

## Alternative addTwoInts:
modPow() Naiv  8192bit       ... time required: 21348ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 28083ms, addTwoIntsCounter: 2408179141

## inlined addTwoWords:
modPow() Naiv  8192bit       ... time required: 22538ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 30274ms, addTwoIntsCounter: 2408179141


## ASM addTwoInts:
modPow() Naiv  8192bit       ... time required: 31035ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 44066ms, addTwoIntsCounter: 2406953916
