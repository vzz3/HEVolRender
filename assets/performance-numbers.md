
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



Linux 20.04, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled, force basic school multiplication
Key: P=CDBFA68FF7D237295407446F84137481, Q=ACEDA1FA2CFD937A2D451D9DBE704197, M=8AFBC08486DB9BAFA6EEDDCC08154A0C6FB219D12F96673C655FF7678E7E7917, M^2=4B746321F60C45616D758A70F9CD6DA8DD6522A6CAE645873A2E45FF2666F0B827AD7A203D25D31889D02BBF37DC5D168E07CCA02E11D10E0BD25F52EFEAC011
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 60924ms
Begin Task draw on GPU ... time required: 303ms
Begin Task decrypt ... time required: 691ms
Begin Task draw on GPU ... time required: 305ms
Begin Task decrypt ... time required: 689ms


Linux 20.04, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled
Key: P=CAC04FD763ED1BAD6CAE7ABA349C8AC7, Q=E228335BF2889F7378551A75C1CD1AC3, M=B31D9D35C23939E11B02D217056F13702FC34B203C290E4077DB2E1C21B0EB95, M^2=7D526D462C55036C18D0EB4A6FF01C2FF9E57E7FEE9E5E7E10C5158D8BD8D95F5DAB0D3982B3E9DC73EF1D769BA6CC57C4CF8E9F93B6556A8EBA2B992FAAE4B9
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 62754ms
Begin Task draw on GPU ... time required: 225ms
Begin Task decrypt ... time required: 713ms
Begin Task draw on GPU ... time required: 211ms
Begin Task decrypt ... time required: 718ms

Linux 20.04, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction enabled
Key: P=B961B898F2DAC45BEC388C6E122507E5, Q=B91F1F3A50C599F74204516C1ACC44CD, M=860E27D8F20179D506302D4454494271B287B7C2C9F1056BCCD6B2E1EA3C2661, M^2=4632D27F7F47D54A102A665E882551A13A33C03DD672052DA283157D0F828FEA7D73C6DAE56CFB6D3D0D441C121AE64331E18FB0586C49E9FB985ECD5738F0C1
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 62012ms
Begin Task draw on GPU ... time required: 199ms
Begin Task decrypt ... time required: 717ms
Begin Task draw on GPU ... time required: 199ms
Begin Task decrypt ... time required: 718ms

Linux 20.04, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction disabled
Thread 1 "HEVolRender" received signal SIGFPE, Arithmetic exception.
0x00007fffee8de464 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
```
    #0  0x00007fffee8de464 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #1  0x00007fffee90c3ae in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #2  0x00007fffee8ace8a in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #3  0x00007fffee834320 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #4  0x00007fffee834789 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #5  0x00007fffee82b13d in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #6  0x00007fffee82cf4a in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #7  0x00007fffee82f944 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #8  0x00007fffee82fa36 in ?? () from /usr/lib/x86_64-linux-gnu/libvulkan_radeon.so
    #9  0x00007fffeda10a5c in ?? () from /lib/x86_64-linux-gnu/libVkLayer_khronos_validation.so
    #10 0x00007fffed998ac8 in ?? () from /lib/x86_64-linux-gnu/libVkLayer_khronos_validation.so
    #11 0x00007ffff749bda8 in QVulkanDeviceFunctions::vkCreateGraphicsPipelines (this=0x5555560e3650, 
        device=0x5555561586d0, pipelineCache=0x0, createInfoCount=1, pCreateInfos=0x7fffffffb8d0, pAllocator=0x0, 
        pPipelines=0x55555641aef0) at vulkan/qvulkanfunctions_p.cpp:448
    #12 0x00005555555b798a in ppvr::rendering::EncryptedXRay::createPipeline (this=0x55555641ae50, ySwapChain=...)
        at /home/sebastian/Desktop/HEVolRender-Cpp/src/rendering/EncryptedXRay.cpp:429
    #13 0x00005555555b514c in ppvr::rendering::EncryptedXRay::initSwapChainResources (this=0x55555641ae50, 
        ySwapChain=..., yPK=0x7fffffffbe90, yVolumeSet=0x55555616ef70, yCubeFront=0x10dc00000010dc, 
        yCubeBack=0x10e100000010e1) at /home/sebastian/Desktop/HEVolRender-Cpp/src/rendering/EncryptedXRay.cpp:35
    #14 0x00005555555b0db4 in ppvr::rendering::EncryptedVulkanRenderer::initSwapChainResources (this=0x5555561289b0, 
        yTargetSize=..., ySwapChainImageCount=1)
        at /home/sebastian/Desktop/HEVolRender-Cpp/src/rendering/EncryptedVulkanRenderer.cpp:199
    #15 0x000055555568c344 in MainWindow::renderEcrypted (this=0x555555749340)
        at /home/sebastian/Desktop/HEVolRender-Cpp/app/hellovulkanwidget.cpp:256
    #16 0x0000555555563d93 in MainWindow::qt_static_metacall (_o=0x555555749340, _c=QMetaObject::InvokeMetaMethod, 
        _id=4, _a=0x7fffffffc9a0)
        at /home/sebastian/Desktop/HEVolRender-Cpp/build/HEVolRender_autogen/VJIZ3MDCXP/moc_hellovulkanwidget.cpp:95
```

Linux 20.04, Radeon RX 580 8 GB, 256 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction enabled
Key: P=EF089D040D465223CD0075789471CB03, Q=EEA13B7849E86A34495DFA0AC06A907F, M=DED08DEBD11FBA4B35B8F75F49EB5A71AB01CDD69F6D4FE1905AC5CFF5E3667D, M^2=C1EE600BEC94783FB9AFCAFB14A1D68DE1E9FCFD78063D566CCDD42E36A87168B4CF883F15920E5564136C61D1508964F2E1B7FAC31FBE4A3D8D2C502CB5D909
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 65940ms
Begin Task draw on GPU ... time required: 250ms
Begin Task decrypt ... time required: 767ms
Begin Task draw on GPU ... time required: 242ms
Begin Task decrypt ... time required: 792ms



Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled, force basic school multiplication
Key: P=E1AEC8F22FC77B060EBFE1057F70759FADA380042762BDF14C2A14C85643C761, Q=CC1E9E6A3C02A3AC2A38EC25E61E5DC698007A8A22F320841AF857744B8640D3, M=B3F2464411C087EE8AAE825402950219BFD46D05FD5D5D969C47B52A20C14B02ADE137E17ABE04D959385E9519029C7965BB92E3A566F50EFD748887D37B94F3, M^2=7E7CB38C1CCE19E74EC8099ADAD5184FB2AC24DB1AD36377EC714C07C40610C4454BADD3274B2373D4C9C23FE941FC62788AEAE16C95D1CD011D745F559F920EE1ECA197028216679404828B9BEFCD82F532CFF279BD2B093F07BE4925F5937D06A06086085B37715E67B0FEE31A60C0FFED9BFC182BEDBF53863B7B0A2BDEA9
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 307975ms
Begin Task draw on GPU ... time required: 4032ms
Begin Task decrypt ... time required: 2837ms
Begin Task draw on GPU ... time required: 4045ms
Begin Task decrypt ... time required: 2847ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction disabled
Key: P=E9E04E596CACC67685F8FAB293062B584AE31F13335FD38B3EEB6CADEF48B1E7, Q=BCF39F9AAE08B1837DDEEE63FFFDE5B681C48CF875F3240A0AA4CFF0FE26BB85, M=AC9F4B43AB481C798DB1F4B3AB6B27D0B0F1CFA92BBE6A1725DF932337B1537934F9E5B03752CD8B85A02C26FA6B4EA0789606A306E5A32B77EABB0505022A03, M^2=7466704182586216106CAEE040E48AD040AB90667821F598B51DBE6389CFC9BBC5D7CD2BF374C568814F52D44D8B1FE9A2F54978D66686AD8F0C3E94F2462667EB8FE635CFF7126FC9FB6983542431ADE813341FA104F31461F3E023FC3C25C647187DAEDBB8BFF373D0BB1980768F19C4A3FCD2D60D6F6FF30B1BC6CCF0FC09
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 309151ms
Begin Task draw on GPU ... time required: 3657ms
Begin Task decrypt ... time required: 2871ms
Begin Task draw on GPU ... time required: 3640ms
Begin Task decrypt ... time required: 2853ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery disabled, branch reduction enabled
Key: P=DB2FA944072208F9EC87F775924A69B894F7815E71770C2AF83DBDBAA18C4CB3, Q=F8FBCA523F60D5E07A85630ED10AA26AAA90096915FB3E9E4A53009996077AEF, M=D52DC0EEE3B380221FDF63667AC60563D3C2DB7F5CB96D6EEAE9D96C2623E25F512986A84725BFB4CB957C6020511A61C7D932C09158D0F3E1B488FBA96DE91D, M^2=B1852B3AEC4BF4CD4186324CC72C1A63F182147F7CA3918250B0B8D7F6990B2FDDA4FDB68D4DDBA5EBD34B8BF178BE1BBDD532022483B0AEC68C04F4A967A6AD3B407C10457A1B9BD1D312BF02F14AD104C6C853B5CB522952A4E85C0EF5DDECF09799E6558D4984A5FE4B3EA54356CE425DD654AA6D7ECD40203BD6A0F7CD49
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 321388ms
Begin Task draw on GPU ... time required: 3065ms
Begin Task decrypt ... time required: 2885ms
Begin Task draw on GPU ... time required: 3121ms
Begin Task decrypt ... time required: 2893ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction disabled
Key: P=D0FA4BFDCF5970FC2CE8546FB5D00CB71495AF1CC0D0235E219902B9B0906575, Q=B5809CD7105F9E6F861F201E161ED84AC78EF7EE3F8716A08A9AA9CE8B0B8967, M=9429F4E88864191603DDD59931090D3C8FD295E889520ADC24D80CB6C1D31762D9027BE9B900CB0F0CA0DF5E6A0FD2BD13B4F3756F6E6C91D96C56A4336B6F13, M^2=55C08A0D3A7B8447CB6FAD186CC75E3E070480FDF4D7319453BCE5C7C1B5E03560D8AB497176ED1859ABEBE9774DD0F84E36DEC8AE18D8F539157BBB906AB56FCAAB0AF7551EE5D389BF465C9289E98E556ED9924505CC80017066A50557715BC21F1077E2DB3A6D7905E46985128A1C41FA7E246ACA1C5808A30FAF9C137B69
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 309090ms
Begin Task draw on GPU ... time required: 1936ms
Begin Task decrypt ... time required: 2971ms
Begin Task draw on GPU ... time required: 1945ms
Begin Task decrypt ... time required: 2935ms
Begin Task draw on GPU ... time required: 1936ms
Begin Task decrypt ... time required: 2930ms
Begin Task draw on GPU ... time required: 1945ms
Begin Task decrypt ... time required: 2956ms
Begin Task draw on GPU ... time required: 1930ms
Begin Task decrypt ... time required: 2927ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction disabled but "if less" 64bit addTwoWords
Key: P=A336A5069F837CB106A697C1D637D256822F94EFD4B48C06E24C2D76CEE5E6E7, Q=E302D56A5BA399E250C5FEAC7A1670F323D3FFE4683A1A5B80B3C9BFB69AF561, M=90BB42D26FDA689EC5C1F3EA65A041EFA16F7BBD9592C8C2BFB60285E1DDB6C59555513A9323341C9AA7628FAEDDC977AF7CB74869024BBC4A477BD48C0D9087, M^2=51D334276EB64D6FC793BF4687662E424050AAD497B0D542E189BE2E1285DC195B3A2C646F402491A2E41C269D5EBE67BC915A5A2B88056341597D893AA83E946D14875073A7575917C331B37DCBC019B381C30F8DE6086260EB8F5D04AAEA7E2D8E3032B7238D9F30D0550AD18FC6BE1C59707F737AD66982D9F063A74E2731
Begin Task create volume ... time required: 5ms
Begin Task encrypt volume ... time required: 307686ms
Begin Task draw on GPU ... time required: 1939ms
Begin Task decrypt ... time required: 2862ms
Begin Task draw on GPU ... time required: 1945ms
Begin Task decrypt ... time required: 2875ms
Begin Task draw on GPU ... time required: 1913ms
Begin Task decrypt ... time required: 2878ms
Begin Task draw on GPU ... time required: 1945ms
Begin Task decrypt ... time required: 2869ms
Begin Task draw on GPU ... time required: 1953ms
Begin Task decrypt ... time required: 2882ms


Linux 20.04, Radeon RX 580 8 GB, 512 bit modulus, 32 bit words, obfuscated
GPU: Montgomery enabled, branch reduction enabled
Key: P=C96DCCE7177E1930A4447C175F3BBD3500A04EE549E54B32916012DB52C54DAD, Q=E3D5AA14AEF883A6B26FB2CFC0F10EB5E4E694CDBA61610398ED28E5AE9D4B03, M=B3447ADF966CFF2294FF7DD2D8AD94D5F425634890A8FEB878D7BB9008D0AEE2BBD2BD0A5A7E0AA11210F482DE1D565796AC51D21EE986D9FC34DB5EFF2A9807, M^2=7D88D6262E1E35593431CF57961F0EBB5C6D532A9248D88E24B8A199B6E2FF0655775D7B5516125FA0D7D6B7514EA11D0C68BED02372820A5F04E74B4FEB04159A7ACD2B48E72B620583EC287A0317333A1657758F8F2C865A07018F5DFC995522C958A95AD25050E5FFF467CDD742C089F3C5A06F0A404CCC9181182E945031
Begin Task create volume ... time required: 4ms
Begin Task encrypt volume ... time required: 308083ms
Begin Task draw on GPU ... time required: 3596ms
Begin Task decrypt ... time required: 2950ms
Begin Task draw on GPU ... time required: 3663ms
Begin Task decrypt ... time required: 2920ms




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
