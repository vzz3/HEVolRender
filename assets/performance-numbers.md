
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

mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated, 24 Threads
Key: P=BFD79D3E36524737644A8439A70EBB01, Q=CCFDCCE4F0A49516C789799CFCD81F2D, M=999E02EF5B705807170D59747E9277EDC95945B0B4EA8757961A1B7BEB13FE2D, M^2=5C2E4109BAC9C51EC01BF2E31A46B2F76DC6283757A79A93EA9FEB6101C7DA7A75553CA0DC791D91B1F4DD9F196C821ECFA798E39F88C61451D57374550B53E9
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 3130552ms
Begin Task draw on GPU ... time required: 4394ms
Begin Task decrypt ... time required: 21957ms

### Encryption test with first implementation of Montgomery reduction in SArbBigInt.
Arbitrary length BigInteger Class was used! not the the fixed length as usual for GPU rendering.
mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
Key: P=B2B13CEA6EC5CF72A96B292AE94B6B69, Q=C1A9104ED1E667BE7B1CC4EDE9086C01, M=872DA1500C98FEB7E5B3CB0FB34A2018438EC728741BB1DE220106E9A6E3B769, M^2=476128448913934FD18B968C5DC0EFB1C2096533FD044602C531FD5C246CD470892DA5744CD5EDE58EDAF53398236B0A3B2D7CEB4D0EDFAF36BAE58CF39D4911
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 1600172ms
Begin Task draw on GPU ... time required: 5780ms

### Encryption test with Left-To-Right K-ary and Montgomery reduction in SArbBigInt.
Arbitrary length BigInteger Class was used! not the the fixed length as usual for GPU rendering.
mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
Key: P=D74FCD6A985A45562419EF113692276D, Q=A7C2506BEEAD7B3418D345D32050ADC3, M=8D187D1DEB749C53B3B02BF83B13E1EF65F1143E2D744B31F870EE6E4808B107, M^2=4DC3FC2AA820D5809546360827AFC1492DB293CD3FF790121168127ACDCB203A5762C3AF9CCBD31989C24A0B01993949265C11B4B986FAB89B0609E37ADAAE31
Begin Task create volume ... time required: 6ms
Begin Task encrypt volume ... time required: 1491403ms
Begin Task draw on GPU ... time required: 3655ms

### Encryption test with Left-To-Right K-ary and Montgomery reduction in SFixBigInt (multithreaded encryption).
mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
Key: P=AD7C4715EFCFD455D6A4D46D6F934F41, Q=E861C489B844FED74347AF23AFA9B04B, M=9D7AE1B34B7321538986B52F0933CB67B9D959EA352F002A32321914B78DE80B, M^2=60DFF3D1D06BC8CF34206A7F66F57CB68C6432964BE75ABB0BFCF11B69F31DC854CD8B66A9A933AB442A8C97944BE809CF4DD8B1E2DA5335D96698212871F079
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 69675ms
Begin Task draw on GPU ... time required: 3189ms
Begin Task decrypt ... time required: 9296ms


### Rendering on GPU with standardized model-/view- and projection matrixes from Java
mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled, force basic school multiplication
Key: P=E0036F7B3446C9B94AE76CD984A1A42D, Q=C5465D187388377101D0962D388D0E3F, M=ACA03730EFD5B78C8F37951A932B342BF57ED5902321C5C237E551A2BF8ADD13, M^2=7467AE6ECB590A32F5D9AF3914CDB624328D8AE9ECC404E8444A67860601BF1FAF566BDC65824D9532A242EAE3A098DFCC8C39954D1D0CE688F453417165CF69
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 63034ms
Begin Task draw on GPU ... time required: 3505ms
Begin Task decrypt ... time required: 659ms
Begin Task draw on GPU ... time required: 3459ms
Begin Task decrypt ... time required: 675ms


mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled
Key: P=F194367DE565CFC1907CA7D53E3FF003, Q=BF255AF757CD7F7E0B441E583E408367, M=B460D4EB525D3E5A766F9D09AD338421BB8CCA19CE6F88FF4C538CCB7E4B1A35, M^2=7F18500B4D677E58BB5BF4B2009E2E1BB1CA22903423B9356F62E67CF592587931C8048EF5BFC0665B15B63D16A2CDE2CA83901AD7CC35BC24718BE289BCCEF9
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 63266ms
Begin Task draw on GPU ... time required: 2703ms
Begin Task decrypt ... time required: 642ms
Begin Task draw on GPU ... time required: 2697ms
Begin Task decrypt ... time required: 685ms


mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction enabled
Key: P=D3A19FE913168882D99D27CDD960BA1F, Q=A98BD85124E04D278B46034D4B3CC7CB, M=8C294E2624B3A5E58E7F79888FF3B5EFB61451C95B4D081B9A3E35BB44A5AF95, M^2=4CBD3423D837830A9B13397841B2CF4CA4A79E3FB816E483E01B2FCB604B0E696F07899669678F1C047C93C401987B812F710A07C42204584756A630F67F0CB9
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 61354ms
Begin Task draw on GPU ... time required: 2479ms
Begin Task decrypt ... time required: 648ms
Begin Task draw on GPU ... time required: 2464ms
Begin Task decrypt ... time required: 653ms


mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction disabled
Key: P=9233B18CA8EAC158459FEFB50749E111, Q=E6D336A4D5159529AF83821D73DB3B49, M=83D31154C0F4E317E36B7C85A0B623AEDC46493A9DFA244F3B59A088477B18D9, M^2=43E1B1C2505D11C8846F57670FF2EB0685EC66871B312FD2590ED1CE7B6CC3007A175C1F14826F91951BF1FF8EEC78B2BCB174D1432970DF32B1298940EF67F1
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 61622ms
Begin Task draw on GPU ... time required: 3058ms
Begin Task decrypt ... time required: 679ms
Begin Task draw on GPU ... time required: 3043ms
Begin Task decrypt ... time required: 679ms


mac OS 10.15, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction enabled
Key: P=CEFC7309B91D89BBB90CD74DC6D2DABB, Q=DE88E1D8D693A29543FB91267378FD83, M=B3ED987ABF4CF79DBD3437731C9D7E13018DF50C14064BA996A95825A8B8BCB1, M^2=7E761FBF559DD4CF5B029BE15242CBA7611E6A0F6FC0AF34D976F12D140A236536D3623024A7EDFEFEEF100CD784380E297E96A324900243C405382219847261
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 62310ms
Begin Task draw on GPU ... time required: 1617ms
Begin Task decrypt ... time required: 691ms
Begin Task draw on GPU ... time required: 1631ms
Begin Task decrypt ... time required: 666ms



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


## 32bit*32bit=64bit mulTwoWords
modPow() Naiv  8192bit       ... time required: 17663ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 21656ms, addTwoIntsCounter: 2406953916


## 32bit*32bit=64bit mulTwoWords, 32bit+32bit=64bit addTwoInts
modPow() Naiv  8192bit       ... time required: 17169ms, addTwoIntsCounter: 1608527035
modPow() Montgomery 8192bit  ... time required: 21611ms, addTwoIntsCounter: 2406953916

## javas multiplyToLen()
modPow() Naiv  8192bit       ... time required: 11410ms, addTwoIntsCounter:  806370374
modPow() Montgomery 8192bit  ... time required:  2945ms, addTwoIntsCounter:     213575

## javas multiplyToLen(), square()
modPow() Naiv  8192bit       ... time required: 11232ms, addTwoIntsCounter:  802177095
modPow() Montgomery 8192bit  ... time required:  2655ms, addTwoIntsCounter:     213063

## javas multiplyToLen(), square()
modPow() Mont(4)Ary 8192bit  ... time required:  2167ms, addTwoIntsCounter:     213063
modPow() Mont(6)Ary 8192bit  ... time required:  2026ms, addTwoIntsCounter:     213063
modPow() Mont(8)Ary 8192bit  ... time required:  2017ms, addTwoIntsCounter:     213063

modPow() Mont(4)Ary 2024bit  ... time required:    42ms, addTwoIntsCounter:      16332
modPow() Mont(6)Ary 2024bit  ... time required:    40ms, addTwoIntsCounter:      16332
modPow() Mont(8)Ary 2024bit  ... time required:    42ms, addTwoIntsCounter:      16332
